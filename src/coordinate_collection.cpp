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
                    sosi::GeometryRef* geometry = 0;
                    while( refList.getNextGeometry( geometry ) ) {
                        bool isHole = ( *geometry )[ 0 ]->subtract;
                        for( sosi::GeometryRef::iterator i = geometry->begin(); i != geometry->end(); i++ ) {
                            sosi::ReferenceData* refData = *i;
                            ISosiElement* referencedElement = rawRefElement->find( refData->serial );
                            if( referencedElement ) {

                                extractPath( referencedElement,
                                             refData->reverse,
                                             isHole? mNumPointsHoles : mNumPointsGeom,  // numPoints&
                                             isHole? mHoleSizes : mGeomSizes,           // sizes&
                                             isHole? mHoles : mGeom );                  // target&

                                /*
                                extractPath( referencedElement,
                                             refData->reverse,
                                             isHole ? mNumPointsHoles : mNumPointsGeom, // numPoints&
                                             isHole ? mOffsetsHoles   : mOffsetsGeom,   // offsets&
                                             isHole ? mHoles          : mGeom );        // target&
                                */
                            }
                        }
                    }
                }
            }
            break;
        case sosi::sosi_element_text:
        case sosi::sosi_element_curve:
            {
                sosi::SosiElementSearch srcNe( sosi::sosi_element_ne );
                while( e->getChild( srcNe ) ) {
                    sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( srcNe.element() );
                    mGeom.push_back( ne );
                    mNumPointsGeom += ne->getNumPoints();
                    mGeomSizes.push_back( ne->getNumPoints() );
                    ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
                }
            }
            break;
        default:
            ;
    }
}

void sosicon::CoordinateCollection::
extractPath( ISosiElement* referencedElement,
             bool reverse,
             int& numPoints,
             std::vector<int>& sizes,
             sosi::NorthEastList& target ) {

    sosi::SosiElementSearch  src( sosi::sosi_element_ne );
    sosi::ElementType type = referencedElement->getType();
    sosi::ObjType obj = referencedElement->getObjType();
    sosi::NorthEastList tmpLst;
    int tmpNumPoints = 0;

    while( referencedElement->getChild( src ) ) {
        sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( src.element() );
        if( reverse ) {
            ne->reverse();
            if( tmpLst.size() == 0 ) {
                tmpLst.push_back( ne );
            }
            else {
                tmpLst.insert( tmpLst.begin(), ne );
            }
        }
        else {
            tmpLst.push_back( ne );
        }
        tmpNumPoints += ne->getNumPoints();
        ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
    }
    target.insert( target.begin(), tmpLst.begin(), tmpLst.end() );
    sizes.insert( sizes.begin(), tmpNumPoints );
    numPoints += tmpNumPoints;
}

bool sosicon::CoordinateCollection::
getNextInGeom( ICoordinate*& coord ) {
    return getNext( coord, mGeom, mGeomIndex );
}
