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
#ifndef __SHAPE_DATABASE_H__
#define __SHAPE_DATABSE_H__

#include <vector>
#include <ctime>
#include "../interface/i_binary_streamable.h"
#include "../interface/i_shape_element.h"
#include "../interface/i_shape_header.h"
#include "../byte_order.h"
#include "shapefile_types.h"

namespace sosicon {

    namespace shape {
        
        //! Shapefile database (dbf) implementation
        /*!
            Represents the dpf part of the shapefile format.
         */
        class ShapeDatabase : public IBinaryStreamable {

            //! Shapefile database (dbf) file header
            struct DbfHeader {
                Int8Field fileType;
                Int8Field lastUpdateY;
                Int8Field lastUpdateM;
                Int8Field lastUpdateD;
                Int32Field recordCount;
                Int16Field recordOffset;
                Int16Field recordLength;
                Int8Field tableFlags;
                Int8Field codePageMark;
            } mDbfHeader;

            //! Shape header element
            /*!
                Pointer to the main shapefile header, provided by the constructor.
             */
            IShapeHeader* mShpHeader;
            
            //! List of appended shape elements
            /*!
                Vector with pointer to the shape elements whose features to be included in
                the database file.
             */
            std::vector<IShapeElement*> mShapeElements;

        public:

            ShapeDatabase( IShapeHeader* header );

            virtual ~ShapeDatabase();
            
            void append( IShapeElement* e );

            virtual void writeBinary( std::ostream& os );

        };
    }; // namespace shape
}; // namespace sosicon

#endif