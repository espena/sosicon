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
            Implements basic characteristics of a SOSI element. Mostly a key/value container with
            ISosiElement stubs. Other SOSI elements delegates basic functionality to this class,
            whilst taking care of more specialized tasks themselves.
         */
        class SosiElement : public ISosiElement {

            std::string mName;
            std::string mSerial;
            std::string mAttributes;
            std::vector<ISosiElement*> mChildren;
            int mLevel;

        public:

            SosiElement( std::string name, std::string serial, std::string attributes, int level );

            virtual void addChild( ISosiElement* child ) { mChildren.push_back( child ); };
            virtual int getLevel() { return mLevel; };
            virtual std::string getName() { return mName; };
            virtual void deleteChildren();
            virtual void dump( int indent = 0 );


        };
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif