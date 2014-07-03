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
Shapefile() { }

sosicon::shape::Shapefile::
~Shapefile() {
    while( mShapeElements.size() > 0 ) {
        IShapeElement* e = mShapeElements.back();
        mShapeElements.pop_back();
        delete e;
    }
}

void sosicon::shape::Shapefile::
insert( ISosiElement* sosiElement ) {

}

void sosicon::shape::Shapefile::
prepareHeader() {
    prepareHeader( -1 );
}

void sosicon::shape::Shapefile::
prepareHeader( int recordSize ) {
    std::vector<IShapeElement*>::iterator i;
    int fileLength = mHeader.getByteSize();
    shape::BoundingBox mbr;    
    for( i = mShapeElements.begin(); i != mShapeElements.end(); i++ ) {
        IShapeElement* e = *i;
        fileLength += ( recordSize > -1 ? recordSize : e->getByteSize() );
        shape::BoundingBox bbox;
        e->getMBR( bbox );
        mbr.merge( bbox );
    }
    mHeader.setFileLength( 1932 );
    mHeader.setBoundingBox( mbr );
}

void sosicon::shape::Shapefile::
writeShp( std::ostream &os ) {
    prepareHeader();
    os << mHeader;
    std::vector<IShapeElement*>::iterator i;
    for( i = mShapeElements.begin(); i != mShapeElements.end(); i++ ) {
        IShapeElement* e = *i;
        os << *e;
    }
}

void sosicon::shape::Shapefile::
writeShx( std::ostream &os ) {
    ShapeIndex index( &mHeader );
    std::vector<IShapeElement*>::iterator i;
    for( i = mShapeElements.begin(); i != mShapeElements.end(); i++ ) {
        index.append( *i );
    }
    os << index;
}

void sosicon::shape::Shapefile::
writeDbf( std::ostream &os ) {
    ShapeDatabase database( &mHeader );
    std::vector<IShapeElement*>::iterator i;
    for( i = mShapeElements.begin(); i != mShapeElements.end(); i++ ) {
        database.append( *i );
    }
    os << database;
}

void sosicon::shape::Shapefile::
writePrj( std::ostream &os ) {
    os << "This is the projection data...\n";
}