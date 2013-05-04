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
#ifndef __SOSI_ELEMENT_POINT_H__
#define __SOSI_ELEMENT_POINT_H__

#include "sosi_element.h"
#include "address_unit.h"
#include "cadastral_unit.h"
#include <vector>

namespace sosicon {

    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            @{
        */
        //! Sosi point element (PUNKT)
        /*!
            Represents the SOSI point object, describing a geographical location within current
            grid reference system.
         */
    	class SosiElementPoint : public ISosiElement {

            //! Base element
            /*!
                Basic SOSI element functionality is delegated to this object.
             */
            SosiElement mElement;

            //! List of cadastral units
            /*!
                If current SOSI element contains one or more related cadastral units, they will be
                sequentially inserted into this vector.
             */
    		std::vector<CadastralUnit*> mCadastralUnits;

            //! Cadastral units iterator
            /*!
                Points at current location within SosiElementPoint::mCadastralUnits. Used internally
                by SosiElementPoint::getData( CadastralUnit*& ).
             */
    		std::vector<CadastralUnit*>::iterator mCadastralUnitIterator;

            //! Pointer to current CadastralUnit
            /*!
                Points to the CadastralUnit currently in process by the parser. Used internally
                within SosiElementPoint::append() when the parser adds data to the last encountered
                CadastralUnit element (i.e. the "MATRIKKELNUMMER" sub element within the SOSI file).
             */
    		CadastralUnit* mCurrentCadastralUnit;

            //! List of address units
            /*!
                If current SOSI element contains one or more related address units, they will be
                sequentially inserted into this vector.
             */
    		std::vector<AddressUnit*> mAddressUnits;

            //! Address units iterator
            /*!
                Points at current location within SosiElementPoint::mAddressUnits. Used internally
                by SosiElementPoint::getData( AddressUnit*& ).
             */
    		std::vector<AddressUnit*>::iterator mAddressUnitIterator;

            //! Pointer to current AddressUnit
            /*!
                Points to the AddressUnit currently in process by the parser. Used internally
                within SosiElementPoint::append() when the parser adds data to the last encountered
                AddressUnit element (i.e. the "ADRESSEBRUKSENHET" sub element within the SOSI file).
             */
    		AddressUnit* mCurrentAddressUnit;

    	public:

            //! Constructor
            SosiElementPoint();

            //! Destructor
            virtual ~SosiElementPoint();

            // Described in ISosiElement::getData( AddressUnit*& )
            virtual std::string getData( AddressUnit* &aunit );

            // Described in ISosiElement::getData( CadastralUnit*& )
            virtual std::string getData( CadastralUnit* &cunit );

            // Described in ISosiElement::getData( CoordList* )
            virtual std::string getData( CoordList* &clist ) { clist = 0; return ""; };

            // Described in ISosiElement::getData( const char* )
            virtual std::string getData( const char* key ) { return mElement.getData( key ); }

            // Described in ISosiElement::getFields()
            virtual std::vector<std::string>& getFields() { return mElement.getFields(); }

            // Described in ISosiElement::getType()
            virtual std::string getType() { return "PUNKT"; }

            // Described in ISosiElement::set()
            virtual void set( const std::string& key, const std::string& val ) { mElement.set( key, val ); }

            // Described in ISosiElement::append()
            virtual void append( const std::string& key, char val );
    	};
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif