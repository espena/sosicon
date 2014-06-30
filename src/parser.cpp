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
#include "parser.h"

sosicon::Parser::
Parser() {
    mSosiElementsIterator = mSosiElements.end();
    mHeadElement = 0;
    mCurrentElement = 0;
}

sosicon::Parser::
~Parser() {
    reset();
}

void sosicon::Parser::
appendElementFieldChar( const std::string& field, char val ) {
  if( mCurrentElement ) {
      mCurrentElementField = field;
      mCurrentElement->append( mCurrentElementField, val );
  }
}

void sosicon::Parser::
reset() {

    while( !mSosiElements.empty() ) {
        ISosiElement* e = mSosiElements.back();
        delete e;
        mSosiElements.pop_back();
    }
    mSosiElementsIterator = mSosiElements.end();
    mHeadElement = 0;
    mCurrentElement = 0;

}

void sosicon::Parser::
dump( bool all ) {
    
    ISosiElement* e = 0;

    if( all ) {
        for( std::vector<ISosiElement*>::iterator i = mSosiElements.begin(); i != mSosiElements.end(); i++ ) {

            e = *i;

            if( e->getType() == "hode" ) continue;

            std::cout << e->getType() << "\n";

            std::cout << "ID............: " << e->getData( "id"                         ) << "\n";
            std::cout << "KOMM..........: " << e->getData( "komm"                       ) << "\n";
            std::cout << "GATENAVN......: " << e->getData( "gatenavn"                   ) << "\n";
            std::cout << "AID-GATE......: " << e->getData( "aid_gate"                   ) << "\n";
            std::cout << "AID-HUSNR.....: " << e->getData( "aid_husnr"                  ) << "\n";
            std::cout << "AID-BOKSTAV...: " << e->getData( "aid_bokstav"                ) << "\n";
            std::cout << "AID-UNR.......: " << e->getData( "aid_unr"                    ) << "\n";
            std::cout << "POST-NR.......: " << e->getData( "post_nr"                    ) << "\n";
            std::cout << "POST-STED.....: " << e->getData( "post_sted"                  ) << "\n";
            std::cout << "OBJTYPE.......: " << e->getData( "objtype"                    ) << "\n";
            std::cout << "NORD..........: " << e->getData( "koord_n"                    ) << "\n";
            std::cout << "OST...........: " << e->getData( "koord_o"                    ) << "\n";
            std::cout << "\n";

            ::sosicon::sosi::AddressUnit* aunit = 0;
            while( !e->getData( aunit ).empty() ) {
                std::cout << "ADRESSEBRUK...: " << aunit->toString() << "\n";
                std::cout << "LOPENR........: " << aunit->mDoorNumber << "\n";
                std::cout << "ETASJENR......: " << aunit->mFloorNumber << "\n";
                std::cout << "ETASJEPLAN....: " << aunit->mFloorLevel << "\n";
                std::cout << "\n";
            }

            ::sosicon::sosi::CadastralUnit* cunit = 0;
            while( !e->getData( cunit ).empty() ) {
                std::cout << "KOMMNR........: " << cunit->mMunicipality << "\n";
                std::cout << "GNR...........: " << cunit->mCadastre     << "\n";
                std::cout << "BNR...........: " << cunit->mProperty     << "\n";
                std::cout << "SNR...........: " << cunit->mSection      << "\n";
                std::cout << "FNR...........: " << cunit->mLeasehold    << "\n";
                std::cout << "\n";
            }        
        }   
    }

    e = mHeadElement;
    
    std::cout << "ORIGO-N.......: " << e->getData( "origo_n"                    ) << "\n";
    std::cout << "ORIGO-O.......: " << e->getData( "origo_o"                    ) << "\n";
    std::cout << "ENHET.........: " << e->getData( "enhet"                      ) << "\n";
    std::cout << "MAX-N.........: " << e->getData( "max_n"                      ) << "\n";
    std::cout << "MIN-N.........: " << e->getData( "min_n"                      ) << "\n";
    std::cout << "SOSI-VERSJON..: " << e->getData( "sosi_versjon"               ) << "\n";
    std::cout << "PRODUKTSPEK...: " << e->getData( "produktspek"                ) << "\n";
    std::cout << "TEGNSETT......: " << e->getData( "tegnsett"                   ) << "\n";
    std::cout << "\n";
}

std::vector<std::string>& sosicon::Parser::
getSosiElementsFields() {
    if( mSosiElementsFields.size() == 0 ) {
        ISosiElement* e = 0;
        while( getNextSosiElement( e ) ) {
            std::vector<std::string>& elementFields = e->getFields();
            for( std::vector<std::string>::iterator f = elementFields.begin(); f != elementFields.end(); f++ ) {
                if( std::find( mSosiElementsFields.begin(), mSosiElementsFields.end(), *f ) == mSosiElementsFields.end() ) {
                    mSosiElementsFields.push_back( *f );
                }
            }
        }
    }
    return mSosiElementsFields;
}

void sosicon::Parser::
setObjTypeSelection( std::vector<std::string>& objTypes ) {
    mObjTypeFilter = objTypes;
}

std::vector<std::string>::size_type sosicon::Parser::
getCountSosiElements() {
    return mSosiElements.size();
}

std::vector<std::string>::size_type sosicon::Parser::
getCountSosiElementsSelection() {
    return mSosiElementsSelection.size();
}

bool sosicon::Parser::
getNextSosiElement( ISosiElement*& sosiElement ) {
    
    std::vector<ISosiElement*>& selection = mSosiElementsSelection.size() > 0
                                          ? mSosiElementsSelection
                                          : mSosiElements;
    if( 0 == sosiElement ) {
        mSosiElementsIterator = selection.begin();
    }
    
    if( selection.end() == mSosiElementsIterator ) {
        sosiElement = 0;
    }
    else {
        sosiElement = *mSosiElementsIterator++;
        
    }
    
    return 0 != sosiElement;
}

sosicon::ISosiElement* sosicon::Parser::
getHeadElement() {
    return mHeadElement;
}
