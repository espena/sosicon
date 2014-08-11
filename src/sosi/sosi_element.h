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
#ifndef __SOSI_ELEMENT_H__
#define __SOSI_ELEMENT_H__

#include <iostream>
#include <vector>
#include <string>
#include "sosi_element_search.h"
#include "sosi_types.h"
#include "../interface/i_sosi_element.h"

namespace sosicon {

    //! SOSI
    namespace sosi {

        //! Number of entries in coordsys lookup table
        static const int MAX_COORDSYS_TABLE = 184;

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        //! Convert SOSI SYSKODE value to coordinate system data
        /*!
            \param int The SOSI SYSKODE value.
            \return CoordSys structure with information about the requested
                    coordinate system.
         */
        CoordSys sysCodeToCoordSys( int sysCode );

        //! Convert SOSI element names to ElementType enum value
        /*!
            The enum member names are translations of the Norwegian element names.
            \param std::string sosiElementName The standard SOSI element name in Norwegian.
            \return ElementType enumeration value representing current element type.
         */
        ElementType sosiNameToType( std::string sosiElementName );

        //! Convert SOSI objtype names to ObjType enum value
        /*!
            The enum member names are translations of the Norwegian geograpic features.
            \param std::string sosiObjtypeName The standard SOSI objtype name in Norwegian.
            \return ObjType enumeration value representing current element objtype.
         */
        ObjType sosiObjNameToType( std::string sosiObjTypeName );

        //! Basic SOSI element
        /*!
            Implements basic characteristics of a SOSI element.
         */
        class SosiElement : public ISosiElement {

            //! Current element's data content
            std::string mData;

            //! List of children elements
            SosiChildrenList mChildren;

            //! Current element's nesting level
            int mLevel;

            //! Current element's name
            std::string mName;

            //! Current element's geometric type
            ElementType mType;

            //! Current element's objtype
            ObjType mObjType;

            //! Current element's serial number if provided
            std::string mSerial;

            //! Pointer to root element
            ISosiElement* mRoot;

            //! Reference to parser's lookup table
            SosiElementMap& mIndex;

            //! Increment to next child in list
            virtual bool nextChild( SosiElementSearch& src );

        public:

            //! Construct new SOSI element
            SosiElement( std::string name, std::string serial, std::string data, int level, ISosiElement* root, SosiElementMap& index );

            //! Insert children element
            virtual void addChild( ISosiElement* child );

            //! Recursively deletes all children
            virtual void deleteChildren();

            //! Debug function
            virtual void dump( int indent = 0 );

            //! Find element by reference
            virtual ISosiElement* find( std::string ref );

            std::vector<ISosiElement*>& children() { return mChildren; };
			
			//! Get next child in list
            /*!
                Always pass a null pointer to start iterating through the children list.
                The referenced pointer will point to the next child in list when the function returns.
                If the end of the list is reached, the function returns false.
             */
            virtual bool getChild( SosiElementSearch& src );

            //! Get unparsed element data
            virtual std::string getData() { return mData; };

            //! Get nesting level of current element
            virtual int getLevel() { return mLevel; };

            //! Get ObjType of current element
            virtual ObjType getObjType() { return mObjType; };

            //! Get name of current element
            virtual std::string getName() { return mName; };

            //! Get root element
            virtual ISosiElement* getRoot() { return mRoot; };

            //! Get serial number (ID) of current element
            virtual std::string getSerial() { return mSerial; };

            //! Get ElementType of current element
            virtual ElementType getType() { return mType; };

        };
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif
