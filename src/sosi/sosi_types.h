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
#ifndef __SOSI_TYPES_H__
#define __SOSI_TYPES_H__

#include "../interface/i_coordinate.h"
#include <string>
#include <vector>
#include <map>

namespace sosicon {

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        //! List of SOSI types
        enum ElementType {
            sosi_element_area,             //!< Area
            sosi_element_charset,          //!< Character set
            sosi_element_coordsys,         //!< Grid type
            sosi_element_curve,            //!< Curve
            sosi_element_head,             //!< Header
            sosi_element_kp,               //!< Junction point
            sosi_element_ne,               //!< North-east coordinate
            sosi_element_objtype,          //!< Object type
            sosi_element_origo_ne,         //!< Origo north-east
            sosi_element_other,            //!< Other
            sosi_element_point,            //!< Point
            sosi_element_ref,              //!< Element reference
            sosi_element_text,             //!< Text
            sosi_element_transpar,         //!< Datum/projection/coordinate system
            sosi_element_unit,             //!< Unit (mm)
            sosi_element_updatedate        //!< Update date
        };

        //! Default SOSI junction point layer types
        enum JunctionPoint {
            sosi_junction_node = 1,         //!< Node point (KP 1)
            sosi_junction_connection = 900, //!< Connection point (KP 900)
            sosi_junction_open_end = 999    //!< Valid open-ended point (KP 999)
        };

        //! SOSI reference number
        struct Reference {
            std::string serial;  //!< The element ID.
            bool reverse;        //!< Minus sign = reverse coordinate sequence.
            bool subtract;       //!< Parenthesis = subtract shape.
        };

        //! List of SOSI references
        typedef std::vector<Reference*> SosiReferenceList;

       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif