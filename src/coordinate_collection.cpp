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

bool sosicon::
getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::iterator& iterator ) {
    if( 0 == coord ) {
        iterator = list.begin();
    }
    if( iterator == list.end() ) {
        return false;
    }
    while( false == ( *iterator )->getNext( coord ) ) {
        iterator++;
        coord = 0;
        if( iterator == list.end() ) {
            return false;
        }
    }
    return true;
}

sosicon::CoordinateCollection::
~CoordinateCollection() {
    delete mCenterPoint;
    sosi::deleteNorthEasts( mGeom );
    sosi::deleteNorthEasts( mIslands );
}

void sosicon::CoordinateCollection::
discoverCoords( ISosiElement* e ) {
    mCenterPoint = 0;
    switch( e->getType() ) {
        case sosi::sosi_element_area:
            {
                ISosiElement* rawRefElement = 0;
                while( e->getChild( rawRefElement, sosi::sosi_element_ref ) ) {
                    sosi::SosiRefList refList( rawRefElement );
                    sosi::Reference* ref = 0;
                    int i = 0;
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
        case sosi::sosi_element_kp:
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
    ISosiElement* childElement = 0;
    if( referencedElement->getType() == sosi::sosi_element_curve ) {
        // First segment describes the center point
        referencedElement->getChild( childElement, sosi::sosi_element_ne );
        mCenterPoint = new sosi::SosiNorthEast( childElement );
    }
    while( referencedElement->getChild( childElement, sosi::sosi_element_ne ) ) {
        sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( childElement );
        sosi::NorthEastList& lst = ref->subtract ? mIslands : mGeom;
        if( ref->reverse ) {
            ne->reverse();
        }
        lst.push_back( ne );
    }
}

bool sosicon::CoordinateCollection::
getNextInGeom( ICoordinate*& coord ) {
    return getNext( coord, mGeom, mGeomIterator );
}

bool sosicon::CoordinateCollection::
getNextInIslands( ICoordinate*& coord ) {
    return getNext( coord, mIslands, mIslandsIterator );
}
