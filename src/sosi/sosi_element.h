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
#include "../interface/i_sosi_element.h"

namespace sosicon {

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */
        //! Basic SOSI element
        /*!
            Implements basic characteristics of a SOSI element.
         */
        class SosiElement : public ISosiElement {

            //! Current element's data content
            std::string mAttributes;

            //! List of children elements
            std::vector<ISosiElement*> mChildren;

            //! Iterator for mChildren
            std::vector<ISosiElement*>::iterator mChildrenIterator;

            //! Current element's nesting level
            int mLevel;

            //! Current element's name
            std::string mName;

            //! Current element's serial number if provided
            std::string mSerial;

        public:

            //! Construct new SOSI element
            SosiElement( std::string name, std::string serial, std::string attributes, int level );

            //! Insert children element
            virtual void addChild( ISosiElement* child ) { mChildren.push_back( child ); };

            //! Recursively deletes all children
            virtual void deleteChildren();

            //! Debug function
            virtual void dump( int indent = 0 );

            //! Get next child in list
            /*!
                Always pass a null pointer to start iterating through the children list.
                The referenced pointer will point to the next child in list when the function returns.
                If the end of the list is reached, the function returns false.
             */
            virtual bool getChild( ISosiElement*& e );

            //! Get nesting level of current element
            virtual int getLevel() { return mLevel; };

            //! Get name of current element
            virtual std::string getName() { return mName; };

        };
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif