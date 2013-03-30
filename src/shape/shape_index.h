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
#ifndef __SHAPE_INDEX_H__
#define __SHAPE_INDEX_H__

#include <vector>
#include "../interface/i_binary_streamable.h"
#include "../interface/i_shape_element.h"
#include "../interface/i_shape_header.h"
#include "../byte_order.h"
#include "shapefile_types.h"

namespace sosicon {

    namespace shape {
        
        //! Shapefile index
        /*!
            Represents the shx part of the shapefile format.
         */
        class ShapeIndex : public IBinaryStreamable {

            IShapeHeader* mHeader;

            int32_t mOffset;
            
            //! Shapefile index record
            struct Record {
                Int32Field offset;
                Int32Field length;
            };
            
            std::vector<Record> mRecords;

        public:

            ShapeIndex( IShapeHeader* header );

            virtual ~ShapeIndex();
            
            void append( IShapeElement* e );

            virtual void writeBinary( std::ostream& os );

        };
    }; // namespace shape
}; // namespace sosicon

#endif