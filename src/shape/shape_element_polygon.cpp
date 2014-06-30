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
#include "shape_element_polygon.h"

sosicon::shape::ShapeElementPolygon::
~ShapeElementPolygon() {
    
}

sosicon::shape::ShapeElementPolygon::
ShapeElementPolygon() {
    mSosiElement = 0;
    mContents.fields.type.t = geom::polygon;
    mContents.fields.mbrXMin.d = 0.0;
    mContents.fields.mbrXMax.d = 0.0;
    mContents.fields.mbrYMin.d = 0.0;
    mContents.fields.mbrYMax.d = 0.0;
}

bool sosicon::shape::ShapeElementPolygon::
populate( ISosiElement* sosiElement ) {

    mSosiElement = sosiElement;
    std::stringstream ssX, ssY;
    try {
      /*
        ssX << sosiElement->getData( "koord_o" );
        ssY << sosiElement->getData( "koord_n" );
        ssX >> mContents.fields.x.d;
        ssY >> mContents.fields.y.d;
      */
    }
    catch( std::exception ) { }

    return false;
}

void sosicon::shape::ShapeElementPolygon::
writeBinary( std::ostream &os ) {
    char* contents = 0;
    size_t pos = 0;
    byteOrder::toLittleEndian( mContents.fields.type.b,      contents,                4 );
    byteOrder::toLittleEndian( mContents.fields.mbrXMin.b,   contents + ( pos += 4 ), 8 );
    byteOrder::toLittleEndian( mContents.fields.mbrXMax.b,   contents + ( pos += 8 ), 8 );
    byteOrder::toLittleEndian( mContents.fields.mbrXMin.b,   contents + ( pos += 8 ), 8 );
    byteOrder::toLittleEndian( mContents.fields.mbrXMax.b,   contents + ( pos += 8 ), 8 );
    byteOrder::toLittleEndian( mContents.fields.numParts.b,  contents + ( pos += 8 ), 4 );
    byteOrder::toLittleEndian( mContents.fields.numPoints.b, contents + ( pos += 4 ), 4 );
    os.write( contents, pos + 8 );
}

void sosicon::shape::ShapeElementPolygon::
getMBR( IRectangle& rect ) {
    rect.left( mContents.fields.mbrXMin.d );
    rect.right( mContents.fields.mbrXMax.d );
    rect.top( mContents.fields.mbrYMin.d );
    rect.bottom( mContents.fields.mbrYMax.d );
}