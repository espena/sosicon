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
#ifndef __SHAPEFILE_TYPES_H__
#define __SHAPEFILE_TYPES_H__

#include <stdint.h>
#include <map>
#include <algorithm>
#include <limits>

namespace sosicon {

    namespace shape {

        //! Geometry types
        /*!
            The numeric values are in accordance with the shapefile specification.
         */
        enum ShapeType {
            shape_type_none        = - 1,
            shape_type_nullShape   =   0,
            shape_type_point       =   1,
            shape_type_polyLine    =   3,
            shape_type_polygon     =   5,
            shape_type_multipoint  =   8,
            shape_type_pointZ      =  11,
            shape_type_polyLineZ   =  13,
            shape_type_polygonZ    =  15,
            shape_type_multipointZ =  18,
            shape_type_pointM      =  21,
            shape_type_polyLineM   =  23,
            shape_type_polygonM    =  25,
            shape_type_multiPointM =  28,
            shape_type_multiPatch  =  31
        };                    

        //! 8 bit integer / byte field
        union Int8Field {
            uint8_t i;
            char b[ sizeof( uint8_t ) ];
        };

        //! 16 bit integer / byte field
        union Int16Field {
            uint16_t i;
            char b[ sizeof( uint16_t ) ];
        };

        //! 32 bit integer / byte field
        union Int32Field {
            uint32_t i;
            char b[ sizeof( uint32_t ) ];
        };

        //! 32 bit integer / byte / geom::ShapeType field
        union Int32TField {
            uint32_t i;
            char b[ sizeof( uint32_t ) ];
            ShapeType t;
        };

        //! 32 bit double / byte field
        union DoubleField {
            double d;
            char b[ sizeof( double ) ];
        };

        struct ShxIndex {
            Int32Field offset;
            Int32Field length;
        };

        typedef std::map<std::string, std::string> DbfRecord;
        typedef std::vector<DbfRecord> DbfRecordSet;
        typedef std::map<std::string, int> DbfFieldLengths;
        typedef std::vector<ShxIndex> ShxOffsets;

    }; // namespace shape
}; // namespace sosicon

#endif
