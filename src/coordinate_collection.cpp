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
getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::size_type& index ) {
    if( 0 == coord ) {
        index = 0;
    }
    if( index >= list.size() ) {
        return false;
    }
    if( false == ( list[ index ] )->getNext( coord ) ) {
        index++;
        coord = 0;
        if( index >= list.size() ) {
            return false;
        }
        else {
            ( list[ index ] )->getNext( coord );
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
        case sosi::sosi_element_surface:
            {
                sosi::SosiElementSearch srcRef( sosi::sosi_element_ref );
                ISosiElement* rawRefElement = 0;
                while( e->getChild( srcRef ) ) {
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
        case sosi::sosi_element_curve:
            {
                sosi::SosiElementSearch srcNe( sosi::sosi_element_ne );
                while( e->getChild( srcNe ) ) {
		            sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( srcNe.element() );
                    mGeom.push_back( ne );
                    mPartOffsetsGeom.push_back( mNumPointsGeom );
                    mNumPointsGeom += ne->getNumPoints();
                    ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
                }
            }
            break;
        default:
            ;
    }
}

void sosicon::CoordinateCollection::
extractPath( sosi::Reference* ref, ISosiElement* referencedElement ) {
    sosi::SosiElementSearch src( sosi::sosi_element_ne );
    sosi::ElementType type = referencedElement->getType();
    sosi::ObjType obj = referencedElement->getObjType();
    /*
    if( type == sosi::sosi_element_curve ) {
        // First segment describes the center point
        referencedElement->getChild( src );
        mCenterPoint = new sosi::SosiNorthEast( src.element() );
    }
    */
    sosi::NorthEastList& lst = ref->subtract ? mIslands : mGeom;
    std::vector<int>& offsets = ref->subtract ? mPartOffsetsIslands : mPartOffsetsGeom;
    sosi::NorthEastList tmpLst;
    while( referencedElement->getChild( src ) ) {
		sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( src.element() );
        int& pointCount = ref->subtract ? mNumPointsIslands : mNumPointsGeom;
        if( ref->reverse ) {
            ne->reverse();
            if( tmpLst.size() == 0 ) {
                tmpLst.push_back( ne );
            }
            else {
                tmpLst.insert( tmpLst.begin(), ne );
            }
            offsets.insert( offsets.begin(), pointCount );
        }
        else {
            tmpLst.push_back( ne );
            offsets.push_back( pointCount );
        }
        pointCount += ne->getNumPoints();
        ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
    }
    lst.insert( lst.begin(), tmpLst.begin(), tmpLst.end() );
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
    return getNext( coord, mGeom, mGeomIndex );
}

bool sosicon::CoordinateCollection::
getNextInIslands( ICoordinate*& coord ) {
    return getNext( coord, mIslands, mIslandsIndex );
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
            neBack->append( coordFront->getN(), coordFront->getE() );
			mNumPointsGeom++;
        }
    }
}