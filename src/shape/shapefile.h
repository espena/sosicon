/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen, Norwegian Broadcast Corporation (NRK)
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
#ifndef __SHAPEFILE_H__
#define __SHAPEFILE_H__

#pragma warning ( disable: 4996 )

#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "shapefile_types.h"
#include "../byte_order.h"
#include "../utils.h"
#include "../coordinate_collection.h"
#include "../sosi/sosi_types.h"
#include "../sosi/sosi_element.h"
#include "../sosi/sosi_element_search.h"
#include "../interface/i_shapefile.h"
#include "../interface/i_coordinate.h"

namespace sosicon {

    //! ESRI Shape
    namespace shape {
        

        //! Resolve geometry type
        /*!
            Translate SOSI geomtry type to corresponding shape geometry, if applicable
         */
        ShapeType getShapeEquivalent( sosi::ElementType sosiType );

        //! Shapefile implementation
        /*!
            Wraps all ESRI Shape output files (shp, shx, dbf, prj...) in one class.
            \author Espen Andersen
            \copyright GNU General Public License
        */
        class Shapefile : public IShapefile {

            //! Buffer allocation size
            /*!
                To speed things up, heap allocations are done in increasingly large
                chunks. This parameters defines how many bytes to request for the largest
                buffer expansion.
            */
            static const int  MAX_BUFFER_CHUNK_SIZE = 262144;

            ISosiElement* mSosiTree;   //!< SOSI source

            std::string mFilterSosiId;                    //!< ID of single SOSI element to be exported, if specified
            std::vector<std::string> mFilterSosiObjTypes; //!< Objtypes of selected elements to be exported, if specified

            char mShpHeader[ 100 ];    //!< Main SHP file header
            char* mShpBuffer;          //!< SHP file payload
            int mShpSize;              //!< Data length of SHP file buffer
            int mShpBufferSize;        //!< Allocated buffer length

            char mShxHeader[ 100 ];    //!< Index file header
            char* mShxBuffer;          //!< Index file payload
            int mShxBufferSize;        //!< Length of SHX file buffer

            char mDbfHeader[ 32 ];     //!< dBase file header
            char* mDbfBuffer;          //!< dBase file payload
            int mDbfBufferSize;        //!< Length of dBase file buffer

            int mRecordNumber;         //!< Number of current record in process

            double mXmin;              //!< Minimum bounding rectangle, min X
            double mYmin;              //!< Minimum bounding rectangle, min Y
            double mXmax;              //!< Minimum bounding rectangle, max X
            double mYmax;              //!< Minimum bounding rectangle, max Y

            DbfFieldLengths mDbfFieldLengths; //!< Accumulation of DBF fields and their lenghts
            DbfRecordSet mDbfRecordSet;       //!< All DBF records
            ShxOffsets mShxOffsets;           //!< Index file offsets

            //! Expand MBR to contain Coordinate collection
            void adjustMasterMbr( double xMin, double yMin, double xMax, double yMax );

            //! Create SHP element
            void buildShpElement( ISosiElement* sosi, ShapeType type );

            //! Populate shape header struct
            void buildShpHeader( ShapeType type );

            //! Build shape element: Point
            void buildShpPoint( CoordinateCollection& cc );

            //! Build shape element: Polygon
            void buildShpPolygon( CoordinateCollection& cc );

            //! Build shape element: PolyLine
            void buildShpPolyLine( CoordinateCollection& cc );

            //! Write first coordinate pair in collection to shapefile buffer
            void buildShpRecCoordinate( int& o, CoordinateCollection& cc );

            //! Write coordinate pair to shapefile buffer
            void buildShpRecCoordinate( int& o, ICoordinate* c );

            //! Write multiple coordinate pairs to shapefile buffer
            void buildShpRecCoordinates( int& o, CoordinateCollection& cc );

            //! Create shapefile record header, common part
            void buildShpRecHeaderCommonPart( int& o, int contentLength, ShapeType type );

            //! Create shapefile record header, multipoint/polyLine/polygon part
            void buildShpRecHeaderExtended( int& o, CoordinateCollection& cc );

            //! Create shapefile record header, offsets
            void buildShpRecHeaderOffsets( int& o, CoordinateCollection& cc );

            //! Create DBF file content
            void buildDbf();

            //! Create DBF field descriptor
            void buildDbfFieldDescriptor( int& pos );
            
            //! Create DBF header
            void buildDbfHeader( Int16Field recordLength );

            //! Create DBF records
            void buildDbfRecordSection( int& pos, int recordLength );

            //! Create SHX file content
            void buildShx();

            //! Expand shp payload buffer
            int expandShpBuffer( int byteLength );

            //! Recursive func to extract SOSI field data
            void extractDbfFields( ISosiElement* sosi, DbfRecord& rec );

            //! Create and insert DBF record
            void insertDbfRecord( ISosiElement* sosi );

            //! Append offset value to SHX (index)
            void insertShxOffset( int contentLength );

            //! Shapefile polys must have clockwise-ordered vertices
            std::vector<ICoordinate*> getNormalized( sosi::NorthEastList& neLst );
            
            //! Update or insert new DBF field
            void saveToDbf( DbfRecord& rec, std::string field, std::string data );

        public:

            //! Constructor
            Shapefile() :
                mSosiTree( 0 ),
                mShpBuffer( 0 ),
                mShxBuffer( 0 ),
                mDbfBuffer( 0 ),
                mShpSize( 0 ),
                mShpBufferSize( 0 ),
                mShxBufferSize( 0 ),
                mDbfBufferSize( 0 ),
                mRecordNumber( 0 ),
                mXmin( +99999999 ),
                mYmin( +99999999 ),
                mXmax( -99999999 ),
                mYmax( -99999999 ) { };

            //! Destructor
            virtual ~Shapefile();

            //! Described in IShapefile
            virtual int build( ISosiElement* sosiTree, std::string objType, sosi::ElementType geomType );

            //! Described in IShapefile
            virtual void filterSosiId( std::string sosiId ) { mFilterSosiId = sosiId; };

            //! Described in IShapefileDbfPart
            virtual void writeDbf( std::ostream &os );

            //! Described in IShapefileShpPart
            virtual void writeShp( std::ostream &os );

            //! Described in IShapefileShxPart
            virtual void writeShx( std::ostream &os );

            //! Described in IShapefilePrjPart
            virtual void writePrj( std::ostream &os );
        };

    }; // namespace shape

}; // namespace sosicon

#endif
