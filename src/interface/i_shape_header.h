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
#ifndef __I_SHAPE_HEADER_H__
#define __I_SHAPE_HEADER_H__

#include "i_binary_streamable.h"
#include "../shape/shapefile_types.h"
#include "../shape/bounding_box.h"

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        This is a listing of generic interfaces used within sosicon.
        @{
    */
    //! Interface: Shape element
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class IShapeHeader : public IBinaryStreamable {
    public:

        //! Destructor
        virtual ~IShapeHeader() { };

        //! Return mShapeType
        /*!
            \sa ShapeHeader::mShapeType
            \return The shape type in current file.
         */
        virtual shape::geom::ShapeType getShapeType() = 0;

        //! Set mShapeType
        /*!
            \sa ShapeHeader::mShapeType
         */
        virtual void setShapeType( shape::geom::ShapeType shapeType ) = 0;
    
        virtual void setFileLength( int fileLength ) = 0;

        virtual int getFileLength() = 0;

        virtual void setBoundingBox( shape::BoundingBox boundingBox ) = 0;

        virtual shape::BoundingBox getBoundingBox() = 0;
        
        //! Size of header in bytes
        virtual int getByteSize() = 0;
        
        //! Size of header in 16-bit words
        virtual int getWordSize() = 0;

    };
   /*! @} end group interfaces */
}; // namespace sosicon

#endif