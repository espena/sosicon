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

bool sosicon::
getNextOffset( int& offset, std::vector<int>& offsets, std::vector<int>::iterator& iterator ) {
    if( -1 == offset ) {
        iterator = offsets.begin();
    }
    if( iterator == offsets.end() ) {
        return false;
    }
    offset = *iterator;
    iterator++;
    return true;
}

sosicon::CoordinateCollection::
~CoordinateCollection() {
	free();
}

void sosicon::CoordinateCollection::
free() {
	if( mCenterPoint ) {
		mCenterPoint->free();
		delete mCenterPoint;
		mCenterPoint = 0;
	}
    sosi::deleteNorthEasts( mGeom );
    sosi::deleteNorthEasts( mIslands );
}

void sosicon::CoordinateCollection::
discoverCoords( ISosiElement* e ) {
    mCenterPoint = 0;
    switch( e->getType() ) {
        case sosi::sosi_element_area:
            {
                sosi::SosiElementSearch srcRef;
                ISosiElement* rawRefElement = 0;
                while( e->getChild( srcRef, sosi::sosi_element_ref ) ) {
                    rawRefElement = srcRef.element();
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
        case sosi::sosi_element_point:
        case sosi::sosi_element_ref:
        case sosi::sosi_element_text:
        case sosi::sosi_element_transpar:
        case sosi::sosi_element_unit:
        case sosi::sosi_element_updatedate:
            {
                
            }
            break;
        case sosi::sosi_element_unknown:
            {
                
            }
            break;
    }
}

void sosicon::CoordinateCollection::
extractPath( sosi::Reference* ref, ISosiElement* referencedElement ) {
	sosi::SosiElementSearch src;
    if( referencedElement->getType() == sosi::sosi_element_curve ) {
        // First segment describes the center point
        referencedElement->getChild( src, sosi::sosi_element_ne );
        mCenterPoint = new sosi::SosiNorthEast( src.element() );
    }
    while( referencedElement->getChild( src, sosi::sosi_element_ne ) ) {
		sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( src.element() );
        sosi::NorthEastList& lst = ref->subtract ? mIslands : mGeom;
        std::vector<int>& offsets = ref->subtract ? mPartOffsetsIslands : mPartOffsetsGeom;
        int& pointCount = ref->subtract ? mNumPointsIslands : mNumPointsGeom;
        if( ref->reverse ) {
            ne->reverse();
        }
        lst.push_back( ne );
        offsets.push_back( pointCount );
        pointCount += ne->getNumPoints();
        ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
    }
}

bool sosicon::CoordinateCollection::
getNextOffsetInGeom( int& offset ) {
    return getNextOffset( offset, mPartOffsetsGeom, mPartOffsetsGeomIterator );
}

bool sosicon::CoordinateCollection::
getNextOffsetInIslands( int& offset ) {
    return getNextOffset( offset, mPartOffsetsIslands, mPartOffsetsIslandsIterator );
}

bool sosicon::CoordinateCollection::
getNextInGeom( ICoordinate*& coord ) {
    return getNext( coord, mGeom, mGeomIterator );
}

bool sosicon::CoordinateCollection::
getNextInIslands( ICoordinate*& coord ) {
    return getNext( coord, mIslands, mIslandsIterator );
}

void sosicon::CoordinateCollection::
mkClosedPolygon() {
    if( mGeom.size() > 0 ) {
        sosi::SosiNorthEast* neFront = mGeom.front();
        sosi::SosiNorthEast* neBack = mGeom.back();
        ICoordinate* coordFront = neFront->front();
        ICoordinate* coordBack = neBack->back();
        if( coordFront && coordBack &&
            ( coordFront->getE() != coordBack->getE() ||
              coordFront->getN() != coordBack->getN() ) )
        {
            //neBack->append( coordFront->getN(), coordFront->getE() );
			//mNumPointsGeom++;
        }
    }
}