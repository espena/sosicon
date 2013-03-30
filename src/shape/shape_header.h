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
#ifndef __SHAPE_HEADER_H__
#define __SHAPE_HEADER_H__

#include <limits>
#include <string>
#include <iostream>
#include "../interface/i_shape_header.h"
#include "../byte_order.h"
#include "shapefile_types.h"
#include "bounding_box.h"

namespace sosicon {

    namespace shape {
        
        //! Shapefile header
        /*!

         */
    	class ShapeHeader : public IShapeHeader {

            //! Magic number
            /*!
                Always 9994.
             */
            Int32Field mFileCode;

            //! Total length of shape file
            /*!
                The size, in bytes, of the shape file.
             */
            Int32Field mFileLength;

            //! File version
            /*!
                Always 1000.
             */
            Int32Field mVersion;

            //! Shape type in current file
            /*!
                Possible values, according to the shapefile specification:
            
                -  0 Null Shape
                -  1 Point
                -  3 PolyLine
                -  5 Polygon
                -  8 MultiPoint
                - 11 PointZ
                - 13 PolyLineZ
                - 15 PolygonZ
                - 18 MultiPointZ
                - 21 PointM
                - 23 PolyLineM
                - 25 PolygonM
                - 28 MultiPointM
                - 31 MultiPatch

                \sa ShapeType

             */
            Int32TField mShapeType;

            //! Minimum bounding box
            /*!
                The actual extent of the shapes in the file.
                \sa sosicon::ShapeHeader::BoundingBox
             */
            BoundingBox mBoundingBox;

    	public:

    	    //! Constructor
            ShapeHeader();

            //! Destructor
            virtual ~ShapeHeader() { }
        
            //! Return mShapeType
            /*!
                \sa ShapeHeader::mShapeType
                \return The shape type in current file.
             */
            virtual geom::ShapeType getShapeType() { return mShapeType.t; }
        
            static geom::ShapeType shapeTypeFromSosiType( std::string sosiType );
        
            //! Set mShapeType
            /*!
                \sa ShapeHeader::mShapeType
             */
            virtual geom::ShapeType setShapeType( geom::ShapeType shapeType ) { mShapeType.t = shapeType; }
        
            virtual void setFileLength( int fileLength ) { mFileLength.i = fileLength; }

            virtual int getFileLength() { return mFileLength.i; }

            virtual void setBoundingBox( BoundingBox boundingBox ) { mBoundingBox = boundingBox; }

            virtual BoundingBox getBoundingBox() { return mBoundingBox; }
        
            virtual void writeBinary( std::ostream &os );
            
            virtual int getByteSize() { return 100; }
            
            virtual int getWordSize() { return getByteSize() / 2; }
        
    	};
    }; // namespace shape

}; // namespace sosicon

#endif