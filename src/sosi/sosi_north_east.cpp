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
#include "sosi_north_east.h"

void sosicon::sosi::
deleteNorthEasts( NorthEastList& lst ) {
    static int n = 0;
    for( NorthEastList::iterator i = lst.begin(); i != lst.end(); i++ ) {
        ( *i )->free();
        delete *i;
    }
    lst.clear();
}

sosicon::sosi::SosiOrigoNE sosicon::sosi::SosiNorthEast::mOrigo = sosicon::sosi::SosiOrigoNE();
sosicon::sosi::SosiUnit sosicon::sosi::SosiNorthEast::mUnit = sosicon::sosi::SosiUnit();

sosicon::sosi::SosiNorthEast::
SosiNorthEast( ISosiElement* e ) {
    mSosiElement = e;
    mMinX = +9999999999;
    mMinY = +9999999999;
    mMaxX = -9999999999;
    mMaxY = -9999999999;
    if( e->getName() == "N\xD8H" ) {
        ragelParseCoordinatesNeh( mSosiElement->getData() );
    }
    else {
        ragelParseCoordinatesNe( mSosiElement->getData() );
    }
    initHeadMember( mOrigo, sosi_element_origo_ne );
    initHeadMember( mUnit, sosi_element_unit );
    *this /= mUnit;
    *this += mOrigo;
}

sosicon::sosi::SosiNorthEast::
~SosiNorthEast() { }

void sosicon::sosi::SosiNorthEast::
append( std::string n, std::string e ) {
    double coordN, coordE;
    std::stringstream ssN, ssE;
    ssN << n;
    ssE << e;
    ssN >> coordN;
    ssE >> coordE;
    append( coordN, coordE );
}

void sosicon::sosi::SosiNorthEast::
append( std::string n, std::string e, std::string h ) {
    double coordN, coordE, height;
    std::stringstream ssN, ssE, ssH;
    ssN << n;
    ssE << e;
    ssH << h;
    ssN >> coordN;
    ssE >> coordE;
    ssH >> height;
    append( coordN, coordE, height );
}

void sosicon::sosi::SosiNorthEast::
free() {
	for( CoordinateList::iterator i = mCoordinates.begin(); i != mCoordinates.end(); i++ ) {
		delete *i;
	}
	mCoordinates.clear();
}

void sosicon::sosi::SosiNorthEast::
append( double n, double e ) {
    append( n, e, 0 );
}

void sosicon::sosi::SosiNorthEast::
append( double n, double e, double h ) {

    ICoordinate* c = 0;
    try {
        c = new Coordinate();
    }
    catch( ... ) {
        sosicon::logstream << "Memory allocation failed";
    }

    c->setN( n );
    c->setE( e );
    c->setH( h );

    mMinX = std::min( mMinX, c->getE() );
    mMinY = std::min( mMinY, c->getN() );
    mMaxX = std::max( mMaxX, c->getE() );
    mMaxY = std::max( mMaxY, c->getN() );
    mCoordinates.push_back( c );
}

void sosicon::sosi::SosiNorthEast::
initHeadMember( ISosiHeadMember& headMember, ElementType type ) {
    if( !headMember.initialized() ) {
        SosiElementSearch head( sosi_element_head );
        SosiElementSearch transpar( sosi_element_transpar );
        SosiElementSearch target( type );
        ISosiElement* root = mSosiElement->getRoot();
        if( root->getChild( head ) &&
            head.element()->getChild( transpar ) &&
            transpar.element()->getChild( target ) )
        {
            headMember.init( target.element() );
        }
    }
}

void sosicon::sosi::SosiNorthEast::
dump() {
    for( CoordinateList::iterator i = mCoordinates.begin(); i != mCoordinates.end(); i++ ) {
        sosicon::logstream << ( *i )->toString() << "\n";
    }
}

void sosicon::sosi::SosiNorthEast::
expandBoundingBox( double& minX, double& minY, double& maxX, double& maxY ) {
    minX = std::min( minX, mMinX );
    minY = std::min( minY, mMinY );
    maxX = std::max( maxX, mMaxX );
    maxY = std::max( maxY, mMaxY );
}

bool sosicon::sosi::SosiNorthEast::
getNext( ICoordinate*& coord ) {
    bool moreToGo = mCoordinates.size() > 0;
    if( moreToGo ) {
        if( 0 == coord ) {
            mCoordinatesIterator = mCoordinates.begin();
        }
        moreToGo = mCoordinatesIterator != mCoordinates.end();
        if( moreToGo ) {
            coord = *mCoordinatesIterator;
            mCoordinatesIterator++;
        }
    }
    return moreToGo;
}

sosicon::sosi::SosiNorthEast& sosicon::sosi::SosiNorthEast::
operator+= ( SosiOrigoNE& origo ) {
    int offsetN = origo.getN();
    int offsetE = origo.getE();
    ICoordinate* c = 0;
    while( getNext( c ) ) {
        c->shift( offsetN, offsetE );

    }
    mMinX += offsetE;
    mMinY += offsetN;
    mMaxX += offsetE;
    mMaxY += offsetN;
    return *this;
}

sosicon::sosi::SosiNorthEast& sosicon::sosi::SosiNorthEast::
operator/= ( SosiUnit& unit ) {
    ICoordinate* c = 0;
    int divisor = unit.getDivisor();
    while( getNext( c ) ) {
        c->divide( divisor );
    }
    mMinX /= divisor;
    mMinY /= divisor;
    mMaxX /= divisor;
    mMaxY /= divisor;
    return *this;
}