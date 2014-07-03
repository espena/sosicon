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
#include "sosi_element_point.h"

sosicon::sosi::SosiElementPoint::
SosiElementPoint() {
	mCurrentCadastralUnit = 0;
	mCadastralUnitIterator = mCadastralUnits.begin();
}

sosicon::sosi::SosiElementPoint::
~SosiElementPoint() {
	while( mAddressUnits.size() > 0 ) {
		AddressUnit* a = mAddressUnits.back();
		delete a;
		mAddressUnits.pop_back();
	}	
	while( mCadastralUnits.size() > 0 ) {
		CadastralUnit* c = mCadastralUnits.back();
		delete c;
		mCadastralUnits.pop_back();
	}	
}

void sosicon::sosi::SosiElementPoint::
append( std::string key, char val ) {
	mElement.append( key, val );
}

std::string sosicon::sosi::SosiElementPoint::
getData( sosicon::sosi::CadastralUnit* &cunit ) {
	std::string res = "";
	if( 0 == cunit ) {
        mCadastralUnitIterator = mCadastralUnits.begin();
	}
	if( mCadastralUnitIterator != mCadastralUnits.end() ) {
		cunit = *mCadastralUnitIterator;
		res = cunit->toString();
		mCadastralUnitIterator++;
	}
	else {
		cunit = 0;
	}
	return res;
}

std::string sosicon::sosi::SosiElementPoint::
getData( sosicon::sosi::AddressUnit* &aunit ) {
	std::string res = "";
	if( 0 == aunit ) {
        mAddressUnitIterator = mAddressUnits.begin();
	}
	if( mAddressUnitIterator != mAddressUnits.end() ) {
		aunit = *mAddressUnitIterator;
		res = aunit->toString();
		mAddressUnitIterator++;
	}
	else {
		aunit = 0;
	}
	return res;
}