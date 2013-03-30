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
#include <algorithm>
#include <limits>
#include "../interface/i_rectangle.h"

namespace sosicon {

    namespace shape {
        
        
        //! Shapefile geometries
        namespace geom {
            //! Geometry types
            /*!
                The numeric values are in accordance with the shapefile specification.
             */
            enum ShapeType {
                none        = - 1,
                nullShape   =   0,
                point       =   1,
                polyLine    =   3,
                polygon     =   5,
                multipoint  =   8,
                pointZ      =  11,
                polyLineZ   =  13,
                polygonZ    =  15,
                multipointZ =  18,
                pointM      =  21,
                polyLineM   =  23,
                polygonM    =  25,
                multiPointM =  28,
                multiPatch  =  31
            };                    
        }; // namespace geom

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
            geom::ShapeType t;
        };

        //! 32 bit double / byte field
        union DoubleField {
            double d;
            char b[ sizeof( double ) ];
        };
    }; // namespace shape
}; // namespace sosicon

#endif
