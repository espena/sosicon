/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen, Norwegian Broadcast Corporation (NRK)
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
getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::iterator& i ) {
    if( 0 == coord ) {
        i = list.begin();
    }
    if( i == list.end() ) {
        return false;
    }
    if( false == ( *i )->getNext( coord ) ) {
        i++;
        coord = 0;
        if( i != list.end() ) {
            return false;
        }
        else {
            ( *i )->getNext( coord );
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

bool sosicon::
isCounterClockwise( std::vector<ICoordinate*>::iterator& begin, std::vector<ICoordinate*>::iterator& end ) {
    return end != ( begin + 2 ) ? false : !isClockwise( begin, end );
}

bool sosicon::
isClockwise( std::vector<ICoordinate*>::iterator& begin, std::vector<ICoordinate*>::iterator& end ) {
    double edgeSum = 0.0;
    for( std::vector<ICoordinate*>::iterator i = begin; i != end; i++ ) {
        ICoordinate* v1 = *i;
        ICoordinate* v2 = *( i + 1 != end ? i + 1 : begin );
        edgeSum += ( v2->getE() - v1->getE() ) * ( v2->getN() + v1->getN() );
        if( v1->equals( v2 ) ) {
            break;
        }
    }
    return edgeSum > 0;
}

void sosicon::
neListToCoordList( sosi::NorthEastList& neList, std::vector<ICoordinate*>& coordList ) {
    coordList.clear();
    for( sosi::NorthEastList::iterator i = neList.begin(); i != neList.end(); i++ ) {
        sosi::SosiNorthEast* ne = *i;
        ICoordinate* c = 0;
        while( ne->getNext( c ) ) {
            coordList.push_back( c );
        }
    }
}

sosicon::CoordinateCollection::
~CoordinateCollection() {
    free();
}

void sosicon::CoordinateCollection::
free() {
    sosi::deleteNorthEasts( mGeom );
    sosi::deleteNorthEasts( mHoles );
}

void sosicon::CoordinateCollection::
discoverCoords( ISosiElement* e ) {
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
                        int numPoints = 0;
                        sosi::NorthEastList tmpNEList;
                        for( sosi::GeometryRef::iterator i = geometry->begin(); i != geometry->end(); i++ ) {
                            sosi::ReferenceData* refData = *i;
                            ISosiElement* referencedElement = rawRefElement->find( refData->serial );
                            if( referencedElement ) {

                                extractPath( referencedElement,
                                             refData->reverse,
                                             numPoints,
                                             isHole? mHoles : mGeom ); // target&

                            }
                        }

                        if( isHole ) {
                            mHoleSizes.insert( mHoleSizes.begin(), numPoints );
                            mNumPointsHoles += numPoints;
                            mNumPartsHoles++;
                        }
                        else {
                            mGeomSizes.insert( mGeomSizes.begin(), numPoints );
                            mNumPointsGeom += numPoints;
                            mNumPartsGeom++;
                        }

                    }
                }
            }
            break;
        case sosi::sosi_element_text:
        case sosi::sosi_element_point:
        case sosi::sosi_element_curve:
            {
                mNumPartsGeom = 1;
                mNumPartsHoles = 0;
                int numPoints = 0;
                sosi::SosiElementSearch srcNe( sosi::sosi_element_ne );
                while( e->getChild( srcNe ) ) {
                    sosi::SosiNorthEast* ne = new sosi::SosiNorthEast( srcNe.element() );
                    mGeom.push_back( ne );
                    numPoints += ne->getNumPoints();
                    ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
                }
                mGeomSizes.push_back( numPoints );
                mNumPointsGeom = numPoints;
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
             sosi::NorthEastList& target ) {

    sosi::SosiElementSearch  src( sosi::sosi_element_ne );
    sosi::ElementType type = referencedElement->getType();
    std::string obj = referencedElement->getObjType();
    sosi::NorthEastList tmpLst;

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
        numPoints += ne->getNumPoints();
        ne->expandBoundingBox( mXmin, mYmin, mXmax, mYmax );
    }
    target.insert( target.begin(), tmpLst.begin(), tmpLst.end() );
}

std::vector<sosicon::ICoordinate*>& sosicon::CoordinateCollection::
getGeom() {

    neListToCoordList( mGeom, mGeomNormalized );
    if( mGeomNormalized.size() > 1 ) {
        std::vector<ICoordinate*>::iterator i0 = mGeomNormalized.begin();
        std::vector<ICoordinate*>::iterator i1 = mGeomNormalized.end();
        if( isCounterClockwise( i0, i1 ) ) {
            std::reverse( mGeomNormalized.begin(), mGeomNormalized.end() );
        }
    }
    return mGeomNormalized;
}

std::vector<sosicon::ICoordinate*>& sosicon::CoordinateCollection::
getHoles() {

    neListToCoordList( mHoles, mHolesNormalized );
    if( mHolesNormalized.size() > 1 ) {
        std::vector<ICoordinate*>::size_type p0 = 0;
        std::vector<ICoordinate*>::size_type p1 = 0;
        for( std::vector<int>::iterator i = mHoleSizes.begin(); i != mHoleSizes.end(); i++ ) {
            int size = *i;
            p1 += size;
            if( size > 1 ) {
                std::vector<ICoordinate*>::iterator i0 = mHolesNormalized.begin() + p0;
                std::vector<ICoordinate*>::iterator i1 = p1 < mHolesNormalized.size() ? mHolesNormalized.begin() + p1 : mHolesNormalized.end();
                if( isClockwise( i0, i1 ) ) {
                    std::reverse( i0, i1 );
                }
            }
            p0 += size;
        }
    }
    return mHolesNormalized;
}

bool sosicon::CoordinateCollection::
getNextInGeom( ICoordinate*& coord ) {
    return getNext( coord, mGeom, mGeomIndex );
}
