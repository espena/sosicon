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
Shapefile() :
    mShpBuffer( 0 ),
    mDbfBuffer( 0 ),
    mShpBufferSize( 0 ),
    mRecordNumber( 0 ),
    mXmin( +99999999 ),
    mYmin( +99999999 ),
    mXmax( -99999999 ),
    mYmax( -99999999 ) { }

sosicon::shape::Shapefile::
~Shapefile() {
    delete [ ] mShpBuffer;
    delete [ ] mDbfBuffer;
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
                buildShpElement( sosi );
                buildDbfRecord( sosi );
            }
        }

        Int32Field fileCode;
        Int32Field unused;
        Int32Field fileLength;
        Int32Field version;
        Int32Field shapeType;

        fileCode.i = 9994;
        unused.i = 0;
        fileLength.i = ( mShpBufferSize / 2 ) + 50;
        version.i = 1000;
        shapeType.i = shapeTypeEquivalent;

        byteOrder::toBigEndian( fileCode.b,     &mFileHeader[  0 ], 4 );
        byteOrder::toBigEndian( unused.b,       &mFileHeader[  4 ], 4 );
        byteOrder::toBigEndian( unused.b,       &mFileHeader[  8 ], 4 );
        byteOrder::toBigEndian( unused.b,       &mFileHeader[ 12 ], 4 );
        byteOrder::toBigEndian( unused.b,       &mFileHeader[ 16 ], 4 );
        byteOrder::toBigEndian( unused.b,       &mFileHeader[ 20 ], 4 );
        byteOrder::toBigEndian( fileLength.b,   &mFileHeader[ 24 ], 4 );
        byteOrder::toLittleEndian( version.b,   &mFileHeader[ 28 ], 4 );
        byteOrder::toLittleEndian( shapeType.b, &mFileHeader[ 32 ], 4 );
        byteOrder::doubleToLittleEndian( mXmin, &mFileHeader[ 36 ] );
        byteOrder::doubleToLittleEndian( mYmin, &mFileHeader[ 44 ] );
        byteOrder::doubleToLittleEndian( mXmax, &mFileHeader[ 52 ] );
        byteOrder::doubleToLittleEndian( mYmax, &mFileHeader[ 60 ] );
        byteOrder::doubleToLittleEndian( 0.0,   &mFileHeader[ 68 ] );
        byteOrder::doubleToLittleEndian( 0.0,   &mFileHeader[ 76 ] );
        byteOrder::doubleToLittleEndian( 0.0,   &mFileHeader[ 84 ] );
        byteOrder::doubleToLittleEndian( 0.0,   &mFileHeader[ 92 ] );

    }
}

void sosicon::shape::Shapefile::
buildShpElement( ISosiElement* sosi ) {

    CoordinateCollection cc;
    cc.discoverCoords( sosi );
    ICoordinate* c = 0;

    Int32Field recordNumber;
    recordNumber.i = ++mRecordNumber;

    Int32Field shapeType;
    shapeType.i = 3;

    Int32Field numParts;
    numParts.i = cc.getNumPartsGeom(); 

    Int32Field numPoints;
    numPoints.i = cc.getNumPointsGeom(); 

    int byteLength = 44 + ( 4 * numParts.i ) + ( 16 * numPoints.i );

    Int32Field contentLength;
    contentLength.i = byteLength / 2;

    double xMin = cc.getXmin();
    double yMin = cc.getYmin();
    double xMax = cc.getXmax();
    double yMax = cc.getYmax();

    mXmin = std::min( mXmin, xMin );
    mYmin = std::min( mYmin, yMin );
    mXmax = std::max( mXmax, xMax );
    mYmax = std::max( mYmax, yMax );

    int o = 0;

    if( 0 == mShpBufferSize ) {
        mShpBufferSize = byteLength + 8;
        mShpBuffer = new char [ mShpBufferSize ];
    }
    else {
        char* oldBuffer = mShpBuffer;
        o = mShpBufferSize;
        mShpBufferSize += ( byteLength + 8 );
        mShpBuffer = new char [ mShpBufferSize ];
        std::copy( oldBuffer, oldBuffer + o, mShpBuffer );
        delete [ ] oldBuffer;
    }

    // Record header
    byteOrder::toBigEndian( recordNumber.b,  &mShpBuffer[ o +  0 ], sizeof recordNumber );  // Record serial
    byteOrder::toBigEndian( contentLength.b, &mShpBuffer[ o +  4 ], sizeof contentLength ); // Record content length

    // Record content
    byteOrder::toLittleEndian( shapeType.b,  &mShpBuffer[ o +  8 ], sizeof shapeType );     // Shape type
    byteOrder::doubleToLittleEndian( xMin,   &mShpBuffer[ o + 12 ] );                       // Box minX
    byteOrder::doubleToLittleEndian( yMin,   &mShpBuffer[ o + 20 ] );                       // Box minY
    byteOrder::doubleToLittleEndian( xMax,   &mShpBuffer[ o + 28 ] );                       // Box maxX
    byteOrder::doubleToLittleEndian( yMax,   &mShpBuffer[ o + 36 ] );                       // Box maxY
    byteOrder::toLittleEndian( numParts.b,   &mShpBuffer[ o + 44 ], sizeof numParts );      // NumParts
    byteOrder::toLittleEndian( numPoints.b,  &mShpBuffer[ o + 52 ], sizeof numPoints );     // NumPoints

    o += 52;

    int part = -1;

    while( cc.getNextOffsetInGeom( part ) ) {
        Int32Field offset;
        offset.i = part;
        byteOrder::toLittleEndian( offset.b,  &mShpBuffer[ o ], sizeof( offset.b ) );       // Shape type
        o += 4;
    }

    while( cc.getNextInGeom( c ) ) {
        byteOrder::doubleToLittleEndian( c->getE(), &mShpBuffer[ o ] );
        byteOrder::doubleToLittleEndian( c->getN(), &mShpBuffer[ o + 8 ] );
        o += 16;
    }
}

void sosicon::shape::Shapefile::
buildDbfRecord( ISosiElement* sosi ) {
    DbfRecord rec;
    std::string field;
    std::string data;
    ISosiElement* child = 0;
    sosi::SosiElementSearch src;
    while( sosi->getChild( src ) ) {
        child = src.element();
        data = stringUtils::trim( child->getData() );
        int length = data.size();
        if( !data.empty() && length < 254 ) {
            field = child->getName();
            if( mDbfRecordLengths.find( field ) != mDbfRecordLengths.end() ) {
                mDbfRecordLengths[ field ] = std::max( mDbfRecordLengths[ field ], length );
            }
            else {
                mDbfRecordLengths[ field ] = length;
            }
            rec[ field ] = data;
        }
    }
    mDbfRecordSet.push_back( rec );
}

void sosicon::shape::Shapefile::
insert( ISosiElement* sosiElement ) {

}

void sosicon::shape::Shapefile::
writeShp( std::ostream &os ) {
    os.write( mFileHeader, sizeof( mFileHeader ) );
    os.write( mShpBuffer, mShpBufferSize );
}

void sosicon::shape::Shapefile::
writeShx( std::ostream &os ) {

}

void sosicon::shape::Shapefile::
writeDbf( std::ostream &os ) {

}

void sosicon::shape::Shapefile::
writePrj( std::ostream &os ) {

}

sosicon::shape::ShapeType sosicon::shape::
getShapeEquivalent( sosi::ElementType sosiType ) {
    switch( sosiType ) {
        case sosi::sosi_element_area:
            return shape_type_polygon;
        case sosi::sosi_element_curve:
            return shape_type_polyLine;
        case sosi::sosi_element_point:
        case sosi::sosi_element_text:
            return shape_type_point;
        default:
            return shape_type_none;
    }
}