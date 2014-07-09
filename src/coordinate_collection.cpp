/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen
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
#include "coordinate_collection.h"

void sosicon::
deleteCoords( CoordinateList& coords ) {
    for( CoordinateList::iterator i = coords.begin(); i != coords.end(); i++ ) {
        delete *i;
    }
    coords.clear();
}

sosicon::CoordinateCollection::
~CoordinateCollection() {
    deleteAll();
}

void sosicon::CoordinateCollection::
deleteAll() {
    deleteCoords( mGeom );
    deleteCoords( mIslands );
}

void sosicon::CoordinateCollection::
discoverCoords( ISosiElement* e ) {
    switch( e->getType() ) {
        case sosi::sosi_element_area:
            {
                ISosiElement* rawRefElement = 0;
                while( e->getChild( rawRefElement, sosi::sosi_element_ref ) ) {
                    sosi::SosiRefList refList( rawRefElement );
                    sosi::Reference* ref = 0;
                    while( refList.getNextReference( ref ) ) {
                        ISosiElement* referencedElement = rawRefElement->find( ref->serial );
                        if( referencedElement ) {
                            extractPath( ref, referencedElement );
                        }
                    }
                }
            }
            break;
        case sosi::sosi_element_charset:
        case sosi::sosi_element_coordsys:
        case sosi::sosi_element_curve:
        case sosi::sosi_element_head:
        case sosi::sosi_element_ne:
        case sosi::sosi_element_objtype:
        case sosi::sosi_element_origo_ne:
        case sosi::sosi_element_other:
        case sosi::sosi_element_point:
        case sosi::sosi_element_ref:
        case sosi::sosi_element_text:
        case sosi::sosi_element_unit:
        case sosi::sosi_element_updatedate:
            {
                
            }
            break;
    }
}

void sosicon::CoordinateCollection::
extractPath( sosi::Reference* ref, ISosiElement* referencedElement ) {
    ISosiElement* ne = 0;
    while( referencedElement->getChild( ne, sosi::sosi_element_ne ) ) {
        ragelParseCoordinates( ref, ne->getData() );
    }
}

bool sosicon::CoordinateCollection::
getNextInGeom( ICoordinate*& coord ) {
    if( 0 == coord ) {
        mGeomIterator = mGeom.begin();
    }
    ICoordinate* test = *( mGeomIterator++ );
    /*
    return mGeomIterator != mGeom.end();
    */
    return false;
}

bool sosicon::CoordinateCollection::
getNextInIslands( ICoordinate*& coord ) {
    if( 0 == coord ) {
        mIslandsIterator = mIslands.begin();
    }
    coord = *( mIslandsIterator++ );
    return mIslandsIterator != mIslands.end();
}
