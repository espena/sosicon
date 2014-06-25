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
#include "sosi_element_area.h"

sosicon::sosi::SosiElementArea::
SosiElementArea() {
    mCurrentCoords = new CoordList();
    mCoordinates.push_back( mCurrentCoords );
    mElement.append( "koord", '\0' );
}

sosicon::sosi::SosiElementArea::
~SosiElementArea() {
	while( mCoordinates.size() > 0 ) {
		CoordList* l = mCoordinates.back();
		delete l;
		mCoordinates.pop_back();
	}
    mCurrentCoords = 0;
}

void sosicon::sosi::SosiElementArea::
append( const std::string& key, char val ) {

    if( ( key == "n_oe" || key == "koord_n" ) && mCoordPair.east != "" ) {
        mCurrentCoords->append( mCoordPair.north );
        mCurrentCoords->append( mCoordPair.east );
        mCoordPair.north = "";
        mCoordPair.east = "";
        if( key == "n_oe" ) {
            mCurrentCoords = new CoordList();
            mCoordinates.push_back( mCurrentCoords );
        }
    }

    if( key == "koord_n" ) {
        mCoordPair.north += val;
    }
	else if( key == "koord_o" ) {
        mCoordPair.east += val;
	}
	else {
        mElement.append( key, val );
	}
}

std::string sosicon::sosi::SosiElementArea::
getData( const char* key ) {
    std::string res;
    if( std::string( key ) == "koord" ) {
        CoordList* clist = 0;
        while( getData( clist ) != "" ) {
            res += clist->toString();
        }
    }
    else {
        res = mElement.getData( key );
    }
    return res;
}

std::string sosicon::sosi::SosiElementArea::
getData( sosicon::sosi::CoordList* &clist ) {
	std::string res = "";
	if( 0 == clist ) {
        mCoordinatesIterator = mCoordinates.begin();
	}
	if( mCoordinatesIterator != mCoordinates.end() ) {
		clist = *mCoordinatesIterator;
		res = clist->toString();
		mCoordinatesIterator++;
	}
	else {
		clist = 0;
	}
	return res;
}



