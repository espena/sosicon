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
#ifndef __SOSI_TYPES_H__
#define __SOSI_TYPES_H__

#include <map>

namespace sosicon {
    namespace sosi {
        //! List of SOSI types
        enum ElementType {
            sosi_element_annet,            //!< Other
            sosi_element_enhet,            //!< Unit (mm)
            sosi_element_flate,            //!< Area
            sosi_element_hode,             //!< Header
            sosi_element_koordsys,         //!< Grid type
            sosi_element_kurve,            //!< Curve
            sosi_element_no,               //!< North-east coordinate
            sosi_element_objtype,          //!< Object type
            sosi_element_oppdateringsdato, //!< Update date
            sosi_element_origo_no,         //!< Origo north-east
            sosi_element_punkt,            //!< Point
            sosi_element_ref,              //!< Element reference
            sosi_element_tegnsett,         //!< Character set
            sosi_element_tekst             //!< Text
        };

        //! Convert SOSI Level 1 element names to ElementType enum value
        ElementType strToType( std::string sosiElementName );

    }; // namespace sosi
}; // namespace sosicon

#endif
