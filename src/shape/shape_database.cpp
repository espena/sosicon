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
#include "shape_database.h"

sosicon::shape::ShapeDatabase::
ShapeDatabase( IShapeHeader* header ) {
    mShpHeader = header;
}

sosicon::shape::ShapeDatabase::
~ShapeDatabase() { }

void sosicon::shape::ShapeDatabase::
append( IShapeElement* e ) {
    mShapeElements.push_back( e );
}

void sosicon::shape::ShapeDatabase::
writeBinary( std::ostream& os ) {

    //time_t t = time( NULL );
    //tm* tp localtime( &t );

    mDbfHeader.fileType.i = 0x43;
    
    std::vector<IShapeElement*>::iterator i;
    for( i = mShapeElements.begin(); i != mShapeElements.end(); i++ ) {
        ISosiElement& sosi = *( *i )->getSosiElement();
        
    }
}