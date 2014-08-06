/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2012  Espen Andersen
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

void sosicon::shape::Shapefile::
build( ISosiElement* sosiTree, sosi::ElementType selection ) {

    ShapeType shapeTypeEquivalent = getShapeEquivalent( selection );

    if( shape_type_none != shapeTypeEquivalent ) {

        ISosiElement* sosi = 0;
        sosi::SosiElementSearch src;

        while( sosiTree->getChild( src ) ) {
            sosi = src.element();
            if( selection == sosi->getType() ) {
                buildShpElement( sosi, shapeTypeEquivalent );
                insertDbfRecord( sosi );
            }
        }

        buildDbf();
        buildShpHeader( shapeTypeEquivalent );
        buildShx();
    }
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

int sosicon::shape::Shapefile::
expandShpBuffer( int byteLength ) {

    int offset = 0;

    if( 0 == mShpSize ) {
        mShpSize = byteLength;
        while( mShpBufferSize < mShpSize ) {
            mShpBufferSize += BUFFER_CHUNK_SIZE;
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
        mShpSize += byteLength;
        if( mShpBufferSize < mShpSize ) {
            while( mShpBufferSize < mShpSize ) {
                mShpBufferSize += BUFFER_CHUNK_SIZE;
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
buildShpElement( ISosiElement* sosi, ShapeType type ) {

    CoordinateCollection cc;
    cc.discoverCoords( sosi );
    if( type == shape_type_polygon ) {
        //cc.mkClosedPolygon();
    }

    Int32Field recordNumber;
    recordNumber.i = ++mRecordNumber;

    Int32Field shapeType;
    shapeType.i = type;

    Int32Field numParts;
    numParts.i = 1; //cc.getNumPartsGeom(); 

    Int32Field numPoints;
    numPoints.i = cc.getNumPointsGeom(); 

    //int byteLength = 44 + ( 4 * numParts.i ) + ( 16 * numPoints.i );
    int byteLength = 52 + ( 4 ) + ( 16 * numPoints.i );

    Int32Field contentLength;
    contentLength.i = ( byteLength / 2 ) - 4; // Record header not included in contentLength

    ShxIndex shxIndex;
    shxIndex.offset.i = 50 + ( mShpSize / 2 );
    shxIndex.length.i = contentLength.i;
    mShxOffsets.push_back( shxIndex );

    int o = expandShpBuffer( byteLength );

    double xMin = cc.getXmin();
    double yMin = cc.getYmin();
    double xMax = cc.getXmax();
    double yMax = cc.getYmax();

    adjustMasterMbr( xMin, yMin, xMax, yMax );

    // Record header
    byteOrder::toBigEndian( recordNumber.b,  &mShpBuffer[ o +  0 ], 4 ); // Record serial
    byteOrder::toBigEndian( contentLength.b, &mShpBuffer[ o +  4 ], 4 ); // Record content length

    // Record content
    byteOrder::toLittleEndian( shapeType.b,  &mShpBuffer[ o +  8 ], 4 ); // Shape type
    byteOrder::doubleToLittleEndian( xMin,   &mShpBuffer[ o + 12 ] );    // Box minX
    byteOrder::doubleToLittleEndian( yMin,   &mShpBuffer[ o + 20 ] );    // Box minY
    byteOrder::doubleToLittleEndian( xMax,   &mShpBuffer[ o + 28 ] );    // Box maxX
    byteOrder::doubleToLittleEndian( yMax,   &mShpBuffer[ o + 36 ] );    // Box maxY
    byteOrder::toLittleEndian( numParts.b,   &mShpBuffer[ o + 44 ], 4 ); // NumParts
    byteOrder::toLittleEndian( numPoints.b,  &mShpBuffer[ o + 48 ], 4 ); // NumPoints

    o += 52;

    int part = -1;

    std::vector<ICoordinate*> theGeom = getNormalized( cc );
    
    while( cc.getNextOffsetInGeom( part ) ) {
        Int32Field offset;
        offset.i = part;
        byteOrder::toLittleEndian( offset.b,  &mShpBuffer[ o ], 4 );
        o += 4;
        break;
    }

    static int cnt = 0;

    for( std::vector<ICoordinate*>::size_type i = 0; i < theGeom.size(); i++ ) {
        ICoordinate* c = theGeom[ i ];
        byteOrder::doubleToLittleEndian( c->getE(), &mShpBuffer[ o ] );
        byteOrder::doubleToLittleEndian( c->getN(), &mShpBuffer[ o + 8 ] );
        o += 16;
    }
}

std::vector<sosicon::ICoordinate*> sosicon::shape::Shapefile::
getNormalized( CoordinateCollection& cc ) {
    std::vector<sosicon::ICoordinate*> theGeom;
    ICoordinate* c = 0;
    while( cc.getNextInGeom( c ) ) {
        theGeom.push_back( c );
    }
    if( theGeom.size() > 1 ) {
        if( theGeom[ 0 ]->rightOf( theGeom[ 1 ] ) ) {
            std::reverse( theGeom.begin(), theGeom.end() );
        }
    }
    return theGeom;
}

void sosicon::shape::Shapefile::
insertDbfRecord( ISosiElement* sosi ) {

    DbfRecord rec;
    std::string field;
    std::string data;
    ISosiElement* child = 0;
    sosi::SosiElementSearch src;

    saveToDbf( rec, "SOSI_ID", sosi->getSerial() );
    saveToDbf( rec, "TYPE", sosi->getName() );
    
    std::vector<ISosiElement*>& children = sosi->children();

    while( sosi->getChild( src ) ) {
        child = src.element();
        field = child->getName();
        data = utils::trim( child->getData() );
        saveToDbf( rec, field, data );
    }

    mDbfRecordSet.push_back( rec );
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
buildDbf() {

    Int16Field recordLength;
    recordLength.i = 1; // Deleted flag == 1 byte

    for( DbfFieldLengths::iterator i = mDbfFieldLengths.begin(); i != mDbfFieldLengths.end(); i++ ) {
        recordLength.i += i->second;
    }

    Int16Field headerLength;
    headerLength.i =

        /* Fixed header size       */   sizeof( mDbfHeader ) +
        /* Field description array */ ( mDbfFieldLengths.size() * 32 ) +
        /* Terminator              */   1;

    mDbfBufferSize =                        

        /* Field description array */ ( mDbfFieldLengths.size() * 32 ) +
        /* Terminator              */   1 +
        /* Record structure        */ ( recordLength.i * mDbfRecordSet.size() ) +
        /* EOF                     */   1 ;

    try {
        mDbfBuffer = 0;
        mDbfBuffer = new char [ mDbfBufferSize ];
    }
    catch( ... ) {
        std::cout << "Memory allocation error\n";
        throw;
    }

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

    int o = 0;

    for( DbfFieldLengths::iterator i = mDbfFieldLengths.begin(); i != mDbfFieldLengths.end(); i++ ) {

        std::string fieldName = i->first;
        fieldName.resize( 10, ' ' );
        const char* sz = fieldName.c_str();
        std::copy( sz, sz + 11, &mDbfBuffer[ o ] );

        // Field data type (char)
        mDbfBuffer[ o + 11 ] = 'C';

        // Field data address (N/A)
        for( int j = 12; j < 16; j++ ) {
            mDbfBuffer[ o + j ] = 0x00;
        }
        mDbfBuffer[ o + 16 ] = char( i->second );

        // Reserved or N/A
        for( int i = 17; i < 32; i++ ) {
            mDbfBuffer[ o + i ] = 0x00;
        }
        o += 32;
    }

    // Terminator
    mDbfBuffer[ o++ ] = 0x0d;

    // Records
    for( DbfRecordSet::iterator i = mDbfRecordSet.begin(); i != mDbfRecordSet.end(); i++ ) {
        char* recordBuffer = 0;
        try {
            recordBuffer = new char[ recordLength.i ];
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
        std::copy( recordBuffer, recordBuffer + recordLength.i, &mDbfBuffer[ o ] );
        delete [ ] recordBuffer;
        o += recordLength.i;
    }

    // End of file
    mDbfBuffer[ o ] = 0x1a;
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
    int o = 0;
    for( ShxOffsets::iterator i = mShxOffsets.begin(); i != mShxOffsets.end(); i++ ) {
        byteOrder::toBigEndian( ( *i ).offset.b,  &mShxBuffer[ o +  0 ], 4 ); // Offset
        byteOrder::toBigEndian( ( *i ).length.b,  &mShxBuffer[ o +  4 ], 4 ); // Length
        o += 8;
    }
}

void sosicon::shape::Shapefile::
insert( ISosiElement* sosiElement ) {

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

}

sosicon::shape::ShapeType sosicon::shape::
getShapeEquivalent( sosi::ElementType sosiType ) {
    switch( sosiType ) {
        case sosi::sosi_element_curve:
        case sosi::sosi_element_surface:
            return shape_type_polyLine;
        case sosi::sosi_element_point:
        case sosi::sosi_element_text:
            return shape_type_point;
        default:
            return shape_type_none;
    }
}