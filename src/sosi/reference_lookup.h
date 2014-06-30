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
#ifndef __REFERENCE_LOOKUP_H__
#define __REFERENCE_LOOKUP_H__

#include "../interface/i_sosi_element.h"
#include "../parser.h"
#include <string>
#include <map>

namespace sosicon {

    namespace sosi {

        class ReferenceLookup {

            //! List of North-East coordinate pairs
            std::map<std::string, ISosiElement*> mElements;

        public:

            //! Virtual destructor
            virtual ~ReferenceLookup() { };

            //! Append coordinate string
            void append( std::string key, ISosiElement* val ) { mElements.insert( std::pair<std::string, ISosiElement*>( key, val ) ); }

            //! Populate map with parsed SOSI elements
            void build( Parser& parser );

            //! Render as string representation
            std::string toString();
            
        };

    }; // namespace sosi

}; // namespace sosicon

#endif