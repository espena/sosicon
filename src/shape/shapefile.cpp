/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen, Norwegian Broadcast Corporation (NRK)
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "shapefile.h"

sosicon::shape::ShapeType sosicon::shape::
getShapeEquivalent( sosi::ElementType sosiType ) {
    switch( sosiType ) {

        case sosi::sosi_element_curve:
            return shape_type_polyLine;

        case sosi::sosi_element_surface:
            return shape_type_polygon;

        case sosi::sosi_element_point:
        case sosi::sosi_element_text:
            return shape_type_point;

        default:
            return shape_type_none;
    }
}

sosicon::shape::Shapefile::
~Shapefile() {
    delete [ ] mShpBuffer;
    delete [ ] mShxBuffer;
    delete [ ] mDbfBuffer;
}

void sosicon::shape::Shapefile::
adjustMasterMbr( double xMin, double yMin, double xMax, double yMax ) {
    mXmin = std::min( mXmin, xMin );
    mYmin = std::min( mYmin, yMin );
    mXmax = std::max( mXmax, xMax );
    mYmax = std::max( mYmax, yMax );
}

int sosicon::shape::Shapefile::
build( ISosiElement* sosiTree, std::string objType, sosi::ElementType geomType ) {

    int count = 0;

    mSosiTree = sosiTree;

    ISosiElement* sosi = 0;
    sosi::SosiElementSearch src;
    ShapeType shapeTypeEquivalent = shape_type_none;

    while( sosiTree->getChild( src ) ) {

        sosi = src.element();

        if( 
            ( objType.empty() || objType == sosi->getObjType() ) &&
            ( mFilterSosiId.empty() || mFilterSosiId == sosi->getSerial() )
          )
        {
            
            if( sosi->getType() == geomType ) {
                shapeTypeEquivalent = getShapeEquivalent( sosi->getType() );
                buildShpElement( sosi, shapeTypeEquivalent );
                insertDbfRecord( sosi );
                ++count;
            }
        }
    }
    if( count > 0 ) {

        buildShpHeader( shapeTypeEquivalent );

        buildDbf(); // database (attributes table)
        buildShx(); // index

    }

    return count;
}

void sosicon::shape::Shapefile::
buildShpHeader( ShapeType type ) {

    Int32Field fileCode;
    Int32Field unused;
    Int32Field fileLength;
    Int32Field version;
    Int32Field shapeType;

    fileCode.i = 9994;
    unused.i = 0;
    fileLength.i = ( mShpSize / 2 ) + 50;
    version.i = 1000;
    shapeType.i = type;

    byteOrder::toBigEndian( fileCode.b,     &mShpHeader[  0 ], 4 );
    byteOrder::toBigEndian( unused.b,       &mShpHeader[  4 ], 4 );
    byteOrder::toBigEndian( unused.b,       &mShpHeader[  8 ], 4 );
    byteOrder::toBigEndian( unused.b,       &mShpHeader[ 12 ], 4 );
    byteOrder::toBigEndian( unused.b,       &mShpHeader[ 16 ], 4 );
    byteOrder::toBigEndian( unused.b,       &mShpHeader[ 20 ], 4 );
    byteOrder::toBigEndian( fileLength.b,   &mShpHeader[ 24 ], 4 );
    byteOrder::toLittleEndian( version.b,   &mShpHeader[ 28 ], 4 );
    byteOrder::toLittleEndian( shapeType.b, &mShpHeader[ 32 ], 4 );
    byteOrder::doubleToLittleEndian( mXmin, &mShpHeader[ 36 ] );
    byteOrder::doubleToLittleEndian( mYmin, &mShpHeader[ 44 ] );
    byteOrder::doubleToLittleEndian( mXmax, &mShpHeader[ 52 ] );
    byteOrder::doubleToLittleEndian( mYmax, &mShpHeader[ 60 ] );
    byteOrder::doubleToLittleEndian( 0.0,   &mShpHeader[ 68 ] );
    byteOrder::doubleToLittleEndian( 0.0,   &mShpHeader[ 76 ] );
    byteOrder::doubleToLittleEndian( 0.0,   &mShpHeader[ 84 ] );
    byteOrder::doubleToLittleEndian( 0.0,   &mShpHeader[ 92 ] );

}

void sosicon::shape::Shapefile::
buildShpElement( ISosiElement* sosi, ShapeType type ) {

    CoordinateCollection cc;
    cc.discoverCoords( sosi );

    switch( type ) {
    
    case shape_type_point:
        buildShpPoint( cc );
        break;

    case shape_type_polygon:
        buildShpPolygon( cc );
        break;

    case shape_type_polyLine:
        buildShpPolyLine( cc );
        break;

    default:
        ;
    }
}

void sosicon::shape::Shapefile::
buildShpPoint( CoordinateCollection& cc ) {
    int byteLength = 28;
    int contentLength = 10; // In 16-bit words, record header not included
    insertShxOffset( contentLength );
    int pos = expandShpBuffer( byteLength );
    buildShpRecHeaderCommonPart( pos, contentLength, shape_type_point );
    buildShpRecCoordinate( pos, cc );
}

void sosicon::shape::Shapefile::
buildShpPolyLine( CoordinateCollection& cc ) {
    int byteLength = 52 + ( 4 ) + ( 16 * cc.getNumPointsGeom() ) + ( 16 * cc.getNumPointsHoles() );
    int contentLength = ( byteLength / 2 ) - 4; // In 16-bit words, record header not included
    insertShxOffset( contentLength );
    int pos = expandShpBuffer( byteLength );
    buildShpRecHeaderCommonPart( pos, contentLength, shape_type_polyLine );
    buildShpRecHeaderExtended( pos, cc );
    buildShpRecHeaderOffsets( pos, cc );
    buildShpRecCoordinates( pos, cc );
}

void sosicon::shape::Shapefile::
buildShpPolygon( CoordinateCollection& cc ) {
    int byteLength = 52 + ( 4 * cc.getNumPartsGeom() ) + ( 4 * cc.getNumPartsHoles() ) + ( 16 * cc.getNumPointsGeom() ) + ( 16 * cc.getNumPointsHoles() );
    int contentLength = ( byteLength / 2 ) - 4; // In 16-bit words, record header not included
    insertShxOffset( contentLength );
    int pos = expandShpBuffer( byteLength );
    buildShpRecHeaderCommonPart( pos, contentLength, shape_type_polygon );
    buildShpRecHeaderExtended( pos, cc );
    buildShpRecHeaderOffsets( pos, cc );
    buildShpRecCoordinates( pos, cc );
}

void sosicon::shape::Shapefile::
buildShpRecCoordinate( int& pos, CoordinateCollection& cc ) {
    ICoordinate* c = 0;
    cc.getNextInGeom( c );
    if( c ) {
        buildShpRecCoordinate( pos, c );
    }
}

void sosicon::shape::Shapefile::
buildShpRecCoordinate( int& pos, ICoordinate* c ) {
    byteOrder::doubleToLittleEndian( c->getE(), &mShpBuffer[ pos ] );
    byteOrder::doubleToLittleEndian( c->getN(), &mShpBuffer[ pos + 8 ] );
    adjustMasterMbr( c->getE(), c->getN(), c->getE(), c->getN() );
    pos += 16;
}

void sosicon::shape::Shapefile::
buildShpRecCoordinates( int& pos, CoordinateCollection& cc ) {
    std::vector<ICoordinate*> theGeom = cc.getGeom();
    for( std::vector<ICoordinate*>::size_type i = 0; i < theGeom.size(); i++ ) {
        buildShpRecCoordinate( pos, theGeom[ i ] );
    }
    std::vector<ICoordinate*> theHoles = cc.getHoles();
    for( std::vector<ICoordinate*>::size_type i = 0; i < theHoles.size(); i++ ) {
        buildShpRecCoordinate( pos, theHoles[ i ] );
    }
}

void sosicon::shape::Shapefile::
buildShpRecHeaderExtended( int& pos, CoordinateCollection& cc ) {

    Int32Field numParts;
    numParts.i = cc.getNumPartsGeom() + cc.getNumPartsHoles(); 

    Int32Field numPoints;
    numPoints.i = cc.getNumPointsGeom() + cc.getNumPointsHoles();

    double xMin = cc.getXmin();
    double yMin = cc.getYmin();
    double xMax = cc.getXmax();
    double yMax = cc.getYmax();

    byteOrder::doubleToLittleEndian( xMin,   &mShpBuffer[ pos ] );         // Box minX
    byteOrder::doubleToLittleEndian( yMin,   &mShpBuffer[ pos + 8 ] );     // Box minY
    byteOrder::doubleToLittleEndian( xMax,   &mShpBuffer[ pos + 16 ] );    // Box maxX
    byteOrder::doubleToLittleEndian( yMax,   &mShpBuffer[ pos + 24 ] );    // Box maxY
    byteOrder::toLittleEndian( numParts.b,   &mShpBuffer[ pos + 32 ], 4 ); // NumParts
    byteOrder::toLittleEndian( numPoints.b,  &mShpBuffer[ pos + 36 ], 4 ); // NumPoints

    adjustMasterMbr( xMin, yMin, xMax, yMax );

    pos += 40;
}

void sosicon::shape::Shapefile::
buildShpRecHeaderOffsets( int& pos, CoordinateCollection& cc ) {

    std::vector<int> geomSizes = cc.getGeomSizes();
    std::vector<int> holeSizes = cc.getHoleSizes();

    Int32Field offset = { 0 };

    for( std::vector<int>::size_type i = 0; i < geomSizes.size(); i++ ) {
        byteOrder::toLittleEndian( offset.b,  &mShpBuffer[ pos ], 4 );
        pos += 4;
        offset.i += geomSizes[ i ];
    }

    for( std::vector<int>::size_type i = 0; i < holeSizes.size(); i++ ) {
        byteOrder::toLittleEndian( offset.b,  &mShpBuffer[ pos ], 4 );
        pos += 4;
        offset.i += holeSizes[ i ];
    }
}

void sosicon::shape::Shapefile::
buildShpRecHeaderCommonPart( int& pos, int contentLength, ShapeType type ) {

    Int32Field len;
    len.i = contentLength;

    Int32Field shapeType;
    shapeType.i = type;

    Int32Field recordNumber;
    recordNumber.i = ++mRecordNumber;

    byteOrder::toBigEndian( recordNumber.b,  &mShpBuffer[ pos ], 4 ); // Record serial
    byteOrder::toBigEndian( len.b, &mShpBuffer[ pos +  4 ], 4 ); // Record content length
    byteOrder::toLittleEndian( shapeType.b,  &mShpBuffer[ pos +  8 ], 4 ); // Shape type

    pos += 12;
}

void sosicon::shape::Shapefile::
buildDbf() {

    int recLen;
    recLen = 1; // Deleted flag == 1 byte
    for( DbfFieldLengths::iterator i = mDbfFieldLengths.begin(); i != mDbfFieldLengths.end(); i++ ) {
        recLen += i->second;
    }

    mDbfBufferSize =

        /* Field description array */ ( mDbfFieldLengths.size() * 32 ) +
        /* Terminator              */   1 +
        /* Record structure        */ ( recLen * mDbfRecordSet.size() ) +
        /* EOF                     */   1 ;

    try {
        mDbfBuffer = 0;
        mDbfBuffer = new char [ mDbfBufferSize ];
    }
    catch( ... ) {
        std::cout << "Memory allocation error\n";
        throw;
    }

    // Header
    buildDbfHeader( recLen );

    // Payload buffer
    int pos = 0;
    buildDbfFieldDescriptor( pos );
    buildDbfRecordSection( pos, recLen );
}

void sosicon::shape::Shapefile::
buildDbfFieldDescriptor( int& pos ) {
    
    for( DbfFieldLengths::iterator i = mDbfFieldLengths.begin(); i != mDbfFieldLengths.end(); i++ ) {

        std::string fieldName = i->first;
        fieldName.resize( 10, ' ' );
        const char* sz = fieldName.c_str();
        std::copy( sz, sz + 11, &mDbfBuffer[ pos ] );

        // Field data type (char)
        mDbfBuffer[ pos + 11 ] = 'C';

        // Field data address (N/A)
        for( int j = 12; j < 16; j++ ) {
            mDbfBuffer[ pos + j ] = 0x00;
        }
        mDbfBuffer[ pos + 16 ] = char( i->second );

        // Reserved or N/A
        for( int i = 17; i < 32; i++ ) {
            mDbfBuffer[ pos + i ] = 0x00;
        }

        pos += 32;
    }

    // Terminator
    mDbfBuffer[ pos++ ] = 0x0d;
}

void sosicon::shape::Shapefile::
buildDbfHeader( int recLen ) {

    Int16Field headerLength;
    Int16Field recordLength = { recLen };
    headerLength.i =
        /* Fixed header size       */   sizeof( mDbfHeader ) +
        /* Field description array */ ( mDbfFieldLengths.size() * 32 ) +
        /* Terminator              */   1;

    time_t rawTime;
    struct tm* timeInfo;
    time( &rawTime );
    timeInfo = localtime( &rawTime );
    Int32Field numRecords;
    numRecords.i = mDbfRecordSet.size();

    mDbfHeader[  0 ] = 0x03;                         // Version number
    mDbfHeader[  1 ] = char( timeInfo->tm_year );    // Year of last update
    mDbfHeader[  2 ] = char( timeInfo->tm_mon + 1 ); // Month of last update
    mDbfHeader[  3 ] = char( timeInfo->tm_mday );    // Day of last update

    byteOrder::toLittleEndian( numRecords.b,    &mDbfHeader[  4 ], 4 ); // Number of records
    byteOrder::toLittleEndian( headerLength.b,  &mDbfHeader[  8 ], 2 ); // Length of header structure
    byteOrder::toLittleEndian( recordLength.b,  &mDbfHeader[ 10 ], 2 ); // Length of record

    // Reserved or N/A
    for( int i = 12; i < 32; i++ ) {
        mDbfHeader[ i ] = 0x00;
    }
}

void sosicon::shape::Shapefile::
buildDbfRecordSection( int& pos, int recLen ) {

    for( DbfRecordSet::iterator i = mDbfRecordSet.begin(); i != mDbfRecordSet.end(); i++ ) {
        char* recordBuffer = 0;
        try {
            recordBuffer = new char[ recLen ];
        }
        catch( ... ) {
            std::cout << "Memory allocation error\n";
        }
        int recNumber = 0;
        int fldOffset = 0;
        recordBuffer[ fldOffset++ ] = 0x20; // Record deleted flag
        DbfRecord& rec = *i;
        for( DbfFieldLengths::iterator j = mDbfFieldLengths.begin(); j != mDbfFieldLengths.end(); j++ ) {
            std::string fieldName = j->first;
            std::string fieldValue;
            if( rec.find( fieldName ) != rec.end() ) {
                fieldValue = rec[ fieldName ];
            }
            int fieldLength = mDbfFieldLengths[ fieldName ];
            fieldValue.resize( fieldLength, ' ' );
            const char* sz = fieldValue.c_str();
            std::copy( sz, sz + fieldLength, &recordBuffer[ fldOffset ] );
            fldOffset += fieldLength;
        }
        std::copy( recordBuffer, recordBuffer + recLen, &mDbfBuffer[ pos ] );
        delete [ ] recordBuffer;
        pos += recLen;
    }
    // End of file
    mDbfBuffer[ pos ] = 0x1a;
}

void sosicon::shape::Shapefile::
buildShx() {

    mShxBufferSize = 8 * mDbfRecordSet.size();
    try {
        mShxBuffer = 0;
        mShxBuffer = new char [ mShxBufferSize ];
    }
    catch( ... ) {
        std::cout << "Memory allocation error\n";
    }

    Int32Field fileLength;
    fileLength.i = ( sizeof( mShxHeader ) + mShxBufferSize ) / 2;
    std::copy( &mShpHeader[ 0 ], &mShpHeader[ 99 ], mShxHeader );
    byteOrder::toBigEndian( fileLength.b,   &mShxHeader[ 24 ], 4 );
    int pos = 0;

    for( ShxOffsets::iterator i = mShxOffsets.begin(); i != mShxOffsets.end(); i++ ) {
        byteOrder::toBigEndian( ( *i ).offset.b,  &mShxBuffer[ pos +  0 ], 4 ); // Offset
        byteOrder::toBigEndian( ( *i ).length.b,  &mShxBuffer[ pos +  4 ], 4 ); // Length
        pos += 8;
    }
}

int sosicon::shape::Shapefile::
expandShpBuffer( int byteLen ) {

    int offset = 0;
    int chunkSize = 0;

    if( 0 == mShpBufferSize ) {
        chunkSize = 1024;
    }
    else if( mShpBufferSize < ( MAX_BUFFER_CHUNK_SIZE / 2 ) ) {
        chunkSize = mShpBufferSize * 2;
    }
    else {
        chunkSize = MAX_BUFFER_CHUNK_SIZE;
    }

    if( 0 == mShpSize ) {
        mShpSize = byteLen;
        while( mShpBufferSize < mShpSize ) {
            mShpBufferSize += chunkSize;
        }
        try {
            mShpBuffer = new char [ mShpBufferSize ];
        }
        catch( ... ) {
            std::cout << "Memory allocation error\n";
            throw;
        }
    }
    else {
        offset = mShpSize;
        mShpSize += byteLen;
        if( mShpBufferSize < mShpSize ) {
            while( mShpBufferSize < mShpSize ) {
                mShpBufferSize += chunkSize;
            }
            char* oldBuffer = mShpBuffer;
            try {
                mShpBuffer = new char [ mShpBufferSize ];
            }
            catch( ... ) {
                std::cout << "Memory allocation error\n";
                throw;
            }
            std::copy( oldBuffer, oldBuffer + offset, mShpBuffer );
            delete [ ] oldBuffer;
        }
    }
    return offset;
}

void sosicon::shape::Shapefile::
extractDbfFields( ISosiElement* sosi, DbfRecord& rec ) {

    std::string field;
    std::string data;
    ISosiElement* child = 0;
    sosi::SosiElementSearch src;
    std::vector<ISosiElement*>& children = sosi->children();

    while( sosi->getChild( src ) ) {
        child = src.element();
        if( child->getType() != sosi::sosi_element_ne ) {
            data = utils::trim( child->getData() );
            saveToDbf( rec, child->getName(), data );
            extractDbfFields( child, rec );
        }
    }
}

void sosicon::shape::Shapefile::
insertDbfRecord( ISosiElement* sosi ) {
    DbfRecord rec;
    saveToDbf( rec, "SOSI_ID", sosi->getSerial() );
    saveToDbf( rec, "TYPE", sosi->getName() );
    extractDbfFields( sosi, rec );
    mDbfRecordSet.push_back( rec );
}

void sosicon::shape::Shapefile::
insertShxOffset( int contentLen ) {
    ShxIndex shxIndex;
    shxIndex.offset.i = 50 + ( mShpSize / 2 );
    shxIndex.length.i = contentLen;
    mShxOffsets.push_back( shxIndex );
}

void sosicon::shape::Shapefile::
saveToDbf( DbfRecord& rec, std::string field, std::string data ) {
    int length = data.size();
    if( !data.empty() && length < 254 ) {
        if( mDbfFieldLengths.find( field ) != mDbfFieldLengths.end() ) {
            mDbfFieldLengths[ field ] = std::max( mDbfFieldLengths[ field ], length );
        }
        else {
            mDbfFieldLengths[ field ] = length;
        }
        rec[ field ] = data;
    }
}

void sosicon::shape::Shapefile::
writeShp( std::ostream &os ) {
    os.write( mShpHeader, sizeof( mShpHeader ) );
    os.write( mShpBuffer, mShpSize );
}

void sosicon::shape::Shapefile::
writeShx( std::ostream &os ) {
    os.write( mShxHeader, sizeof( mShxHeader ) );
    os.write( mShxBuffer, mShxBufferSize );
}

void sosicon::shape::Shapefile::
writeDbf( std::ostream &os ) {
    os.write( mDbfHeader, sizeof( mDbfHeader ) );
    os.write( mDbfBuffer, mDbfBufferSize );
}

void sosicon::shape::Shapefile::
writePrj( std::ostream &os ) {
    sosi::SosiTranslationTable ttbl;
    sosi::SosiElementSearch srcHeader( sosi::sosi_element_head );
    sosi::SosiElementSearch srcTranspar( sosi::sosi_element_transpar );
    sosi::SosiElementSearch srcKoordsys( sosi::sosi_element_coordsys );
    ISosiElement* coordSys = 0;
    if( mSosiTree && 
        mSosiTree->getChild( srcHeader ) &&
        srcHeader.element()->getChild( srcTranspar ) &&
        srcTranspar.element()->getChild( srcKoordsys ) )
    {
        std::stringstream ss;
        int coordSys;
        ss << srcKoordsys.element()->getData();
        ss >> coordSys;
        if( coordSys > 0 && coordSys <= sosi::MAX_COORDSYS_TABLE ) {
            os << ttbl.sysCodeToCoordSys( coordSys ).prjString();
        }
    }
}