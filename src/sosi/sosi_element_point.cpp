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
append( const std::string& key, char val ) {

	if( "adressebruksenhet" == key ) {
		mCurrentAddressUnit = new AddressUnit();
		mAddressUnits.push_back( mCurrentAddressUnit );
		mAddressUnitIterator = mAddressUnits.begin();
	}
	else if( "matrikkelnummer_kommunenr" == key ) {
		if( 0 == mCurrentCadastralUnit || !mCurrentCadastralUnit->mCadastre.empty() ) {
			mCurrentCadastralUnit = new CadastralUnit();
			mCadastralUnits.push_back( mCurrentCadastralUnit );
			mCadastralUnitIterator = mCadastralUnits.begin();
		}
		mCurrentCadastralUnit->mMunicipality += val;
	}
	
	else if( "adressebruksenhet_lopenummer" == key && mCurrentAddressUnit != 0 )
		mCurrentAddressUnit->mDoorNumber += val;
	
	else if( "adressebruksenhet_etasjenummer" == key && mCurrentAddressUnit != 0 )
		mCurrentAddressUnit->mFloorNumber += val;
	
	else if( "adressebruksenhet_etasjeplan" == key && mCurrentAddressUnit != 0 )
		mCurrentAddressUnit->mFloorLevel += val;
	
	else if( "matrikkelnummer_bruksnr" == key && mCurrentCadastralUnit != 0 )
		mCurrentCadastralUnit->mCadastre += val;
	
	else if( "matrikkelnummer_gardsnr" == key && mCurrentCadastralUnit != 0 )
		mCurrentCadastralUnit->mProperty += val;
	
	else if( "matrikkelnummer_seksjonsnr" == key && mCurrentCadastralUnit != 0 )
		mCurrentCadastralUnit->mSection += val;
	
	else if( "matrikkelnummer_festenr" == key && mCurrentCadastralUnit != 0 )
		mCurrentCadastralUnit->mLeasehold += val;
	
	else
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