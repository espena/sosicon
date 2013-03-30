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
#include "shape_element_point.h"

sosicon::shape::ShapeElementPoint::
~ShapeElementPoint() {
    
}

sosicon::shape::ShapeElementPoint::
ShapeElementPoint() {
    mSosiElement = 0;
    mContents.fields.type.t = geom::none;
    mContents.fields.x.d = 0.0;
    mContents.fields.y.d = 0.0;
}

bool sosicon::shape::ShapeElementPoint::
populate( ISosiElement* sosiElement ) {

    mSosiElement = sosiElement;
    mHeader.setContentLength( sizeof( mContents ) / 2 );
    mContents.fields.type.t = geom::point;
    std::stringstream ssX, ssY;
    try {
        ssX << sosiElement->getData( "koord_o" );
        ssY << sosiElement->getData( "koord_n" );
        ssX >> mContents.fields.x.d;
        ssY >> mContents.fields.y.d;
    }
    catch( std::exception ) { }

    return false;
}

void sosicon::shape::ShapeElementPoint::
writeBinary( std::ostream &os ) {
    char contents[ 20 ];
    byteOrder::toLittleEndian( mContents.fields.type.b, contents,      4 );
    byteOrder::toLittleEndian( mContents.fields.x.b,    contents +  4, 8 );
    byteOrder::toLittleEndian( mContents.fields.y.b,    contents + 12, 8 );
    os.write( contents, sizeof( contents ) );
}

void sosicon::shape::ShapeElementPoint::
getMBR( IRectangle& rect ) {
    rect.left( mContents.fields.x.d );
    rect.right( mContents.fields.x.d );
    rect.top( mContents.fields.y.d );
    rect.bottom( mContents.fields.y.d );
}