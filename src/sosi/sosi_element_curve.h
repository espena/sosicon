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
#ifndef __SOSI_ELEMENT_CURVE_H__
#define __SOSI_ELEMENT_CURVE_H__

#include "../interface/i_lookup_table.h"
#include "../interface/i_sosi_element.h"
#include "sosi_element.h"
#include "coord_list.h"
#include <vector>

namespace sosicon {

    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            @{
        */
        //! Sosi curve element (KURVE)
        /*!
            Represents the SOSI curve object, describing a geographical curve/path within current
            grid reference system.
         */
    	class SosiElementCurve : public ISosiElement {

            //! Base element
            /*!
                Basic SOSI element functionality is delegated to this object.
             */
            SosiElement mElement;
            
            //! Curve shapes
            /*!
                One or more point lists describing current curve.
             */
            std::vector<CoordList*> mCoordinates;
            
            //! Iterator to next coordinate string in list
            std::vector<CoordList*>::iterator mCoordinatesIterator;
            
            //! Current list of coordinates
            CoordList* mCurrentCoords;
            
            //! Structure with north/east coordinates
            struct CoordPair {
                std::string north;
                std::string east;
            } mCoordPair;

    	public:

            //! Constructor
            SosiElementCurve();

            //! Destructor
            virtual ~SosiElementCurve();

            //! Get next AddressUnit
            /*!
                Not implemented in this class.
                \sa ISosiElement::getData( AddressUnit*& )
            
                \param aunit Reference to pointer to AddressUnit will be set to 0.
                \return Empty string.
             */
            virtual std::string getData( AddressUnit* &aunit ) { aunit = 0; return ""; };

            //! Get next CadastralUnit
            /*!
                Not implemented in this class.
                \sa ISosiElement::getData( CadastralUnit*& )
        
                \param cunit Reference to pointer to CadastralUnit will be set to 0.
                \return Empty string.
             */
            virtual std::string getData( CadastralUnit* &cunit ) { cunit = 0; return ""; };

            // Described in ISosiElement::getData( const char* )
            virtual std::string getData( const char* key );

            // Described in ISosiElement::getData( CoordList* )
            virtual std::string getData( CoordList* &clist );

            // Described in ISosiElement::getData( ReferenceList* )
            virtual std::string getData( ReferenceList* &rlist, bool inv = false ) { return mElement.getData( rlist ); };

            // Described in ISosiElement::getData( ILookupTable* )
            virtual std::string getData( ILookupTable* &lookup ) { return mElement.getData( lookup ); };

            // Described in ISosiElement::getFields()
            virtual std::vector<std::string>& getFields() { return mElement.getFields(); }

            // Described in ISosiElement::getType()
            virtual ElementType getType() { return sosi_element_kurve; }

            // Described in ISosiElement::set( std::string, const std::string& )
            virtual void set( std::string key, const std::string& val ) { mElement.set( key, val ); }

            // Described in ISosiElement::set( ILookupTable* )
            virtual void set( ILookupTable* lookup ) { mElement.set( lookup ); };

            // Described in ISosiElement::append()
            virtual void append( std::string key, char val );
    	};
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif