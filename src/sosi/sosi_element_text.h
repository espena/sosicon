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
#ifndef __SOSI_ELEMENT_TEXT_H__
#define __SOSI_ELEMENT_TEXT_H__

#include "sosi_element.h"

namespace sosicon {

    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            @{
        */
        //! Sosi text element (TEKST)
        /*!
            Represents the placement of a text string in the SOSI file specification.
         */
    	class SosiElementText : public ISosiElement {

            //! Base element
            /*!
                Basic SOSI element functionality is delegated to this object.
             */
            SosiElement mElement;

    	public:
            //! Constructor
            SosiElementText() { }

            //! Destructor
            virtual ~SosiElementText() { }

            //! Get next AddressUnit
            /*!
                Not implemented in this class.
                \sa ISosiElement::getData( AddressUnit*& )
            
                \param aunit Reference to pointer to AddressUnit will be set to 0.
                \return Empty string.
             */
            virtual std::string getData( AddressUnit* &aunit ) { aunit = 0; return ""; }

            //! Get next CadastralUnit
            /*!
                Not implemented in this class.
                \sa ISosiElement::getData( CadastralUnit*& )
            
                \param cunit Reference to pointer to CadastralUnit will be set to 0.
                \return Empty string.
             */
            virtual std::string getData( CadastralUnit* &cunit ) { cunit = 0; return ""; }

            // Described in ISosiElement::getData( CoordList* )
            virtual std::string getData( CoordList* &clist ) { clist = 0; return ""; };

            // Described in ISosiElement::getData( ReferenceList* )
            virtual std::string getData( std::vector<std::string>* &rlist ) { rlist = 0; return ""; };

            //  Described in ISosiElement::getData( const char* )
            virtual std::string getData( const char* key ) { return mElement.getData( key ); }

            //  Described in ISosiElement::getFields()
            virtual std::vector<std::string>& getFields() { return mElement.getFields(); }

            //  Described in ISosiElement::getType()
            virtual std::string getType() { return "TEKST"; }

            //  Described in ISosiElement::set()
            virtual void set( const std::string& key, const std::string& val ) { mElement.set( key, val ); }

            //  Described in ISosiElement::append()
            virtual void append( const std::string& key, char val ) { mElement.append( key, val ); }
    	};
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif