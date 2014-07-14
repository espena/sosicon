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
#include "sosi_north_east.h"

void sosicon::sosi::
deleteNorthEasts( NorthEastList& lst ) {
    for( NorthEastList::iterator i = lst.begin(); i != lst.end(); i++ ) {
        delete *i;
    }
    lst.clear();
}

sosicon::sosi::SosiNorthEast::
SosiNorthEast( ISosiElement* e ) {
    mSosiElement = e;
    ragelParseCoordinates( mSosiElement->getData() );
}

sosicon::sosi::SosiNorthEast::
~SosiNorthEast() {
    for( CoordinateList::iterator i = mCoordinates.begin(); i != mCoordinates.end(); i++ ) {
        delete *i;
    }
    mCoordinates.clear();
}

void sosicon::sosi::SosiNorthEast::
dump() {
    for( CoordinateList::iterator i = mCoordinates.begin(); i != mCoordinates.end(); i++ ) {
        std::cout << ( *i )->toString() << "\n";
    }
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