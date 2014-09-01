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

            std::vector<std::string> mFilterSosiId;       //!< List of IDs of SOSI elements to be exported, if specified
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
            /*!
                The minimum bounding rectangle (MBR) for all geometries in current
                file is stored in members Shapefile::mXmin, Shapefile::mYmin,
                Shapefile::mXmax and Shapefile::mYmax.
                This method expands the MBR to fit provided coordinates.
                \param xMin Minimum X coordinate of geometry to be included i MBR.
                \param yMin Minimum Y coordinate of geometry to be included i MBR.
                \param xMAx Maximum X coordinate of geometry to be included i MBR.
                \param yMax Maximum Y coordinate of geometry to be included i MBR.
            */
            void adjustMasterMbr( double xMin, double yMin, double xMax, double yMax );

            //! Create SHP element
            /*!
                If a shapefile equivalent to current SOSI element exists, this method
                creates the low-level shape data structure and writes it to the output
                buffer Shapefile::mShpBuffer.
                \param sosi Pointer to SOSI element to be converted to shape.
                \param type Type of Shapefile geometry equivalent to the
                            SOSI element to be converted.
            */
            void buildShpElement( ISosiElement* sosi, ShapeType type );

            //! Populate shape header struct
            /*!
                Creates master file header for SHP and SHX file parts and writes it
                to the DBF header buffer Shapefile::mDbfHeader.
                \param type The shape type for current file.
            */
            void buildShpHeader( ShapeType type );

            //! Build shape element: Point
            /*!
                Inserts a single point into the shapefile buffer.
                \param cc CoordinateCollection containing one or more points. Only the
                          first point in the collection will be handled.
            */
            void buildShpPoint( CoordinateCollection& cc );

            //! Build shape element: Polygon
            /*!
                Inserts a polygon into the shapefile buffer.
                \param cc CoordinateCollection containing three or more points,
                          defining the polygon and holes.
            */
            void buildShpPolygon( CoordinateCollection& cc );

            //! Build shape element: PolyLine
            /*!
                Inserts a polyLine into the shapefile buffer.
                \param cc CoordinateCollection containing two or more points,
                          defining the polyLine.
            */
            void buildShpPolyLine( CoordinateCollection& cc );

            //! Write first coordinate pair in collection to shapefile buffer
            /*!
                Build shapefile coordinate from the first coordinate pair in the
                provided CoordinateCollection and update buffer position.
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param cc The coordinate collection from which the first coordinate
                          pair is to be extracted.
            */
            void buildShpRecCoordinate( int& pos, CoordinateCollection& cc );

            //! Write coordinate pair to shapefile buffer
            /*!
                Build shapefile coordinate from the provided coordinate pair and
                update buffer position.
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param c The coordinate to be written to the buffer.
            */
            void buildShpRecCoordinate( int& pos, ICoordinate* c );

            //! Write multiple coordinate pairs to shapefile buffer
            /*!
                Build shapefile coordinate from a collection of coordinate pairs and
                update buffer position.
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param cc The coordinate collection to be written to the buffer.
            */
            void buildShpRecCoordinates( int& pos, CoordinateCollection& cc );

            //! Create shapefile record header, common part
            /*!
                The first part of the shapefile record header are common for all
                geometry types. This method writes the common part to the buffer.
                \see Shapefile::buildShpRecHeaderExtended
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param contentLength Length of the record in 16-bit words, record
                                     header not included.
                \param type The shape type for current file.
            */
            void buildShpRecHeaderCommonPart( int& pos, int contentLength, ShapeType type );

            //! Create shapefile record header, extended part
            /*!
                For multipoint, polyLine and polygon. This is the second part of the
                shapefile record header.
                \see Shapefile::buildShpRecHeaderCommonPart
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param cc The coordinate collection containing the points for the
                          geometry in current record.
            */
            void buildShpRecHeaderExtended( int& pos, CoordinateCollection& cc );

            //! Create shapefile record header, offsets
            /*!
                The shapefile record header includes a list of offsets to the various
                parts of the geometry. Applicable to polygons where the main
                outline is the first part and subsequent parts denotes holes or islands.
                This method constructs the list of offset values for the multipart
                geometry and writes it to the shapefile buffer.
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param cc The coordinate collection containing the points for the
                          multi-part geometry in current record.
            */
            void buildShpRecHeaderOffsets( int& pos, CoordinateCollection& cc );

            //! Create DBF file content
            /*!
                Part of DBF creation.
                Creates the dBase file content for current shapefile. Populates
                \see Shapefile::buildDbfHeader
                \see Shapefile::buildDbfFieldDescriptor
                \see Shapefile::buildDbfRecordSection
                Shapefile::mDbfBuffer.
            */
            void buildDbf();

            //! Create DBF field descriptor
            /*!
                Part of DBF creation.
                Iterates through individual fields found in current dataset and
                creates a field descriptor header for the following dBase records.
                \see Shapefile::buildDbf
                \see Shapefile::buildDbfHeader
                \see Shapefile::buildDbfRecordSection
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
            */
            void buildDbfFieldDescriptor( int& pos );
            
            //! Create DBF header
            /*!
                Part of DBF creation.
                Creates dBase file header and writes it to Shapefile::mDbfHeader.
                \see Shapefile::buildDbf
                \see Shapefile::buildDbfFieldDescriptor
                \see Shapefile::buildDbfRecordSection
                \param recLen Length of a single record, in bytes.
            */
            void buildDbfHeader( int recLen );

            //! Create DBF records
            /*!
                Part of DBF creation.
                Iterates through all records and writes each one to the DBF buffer
                Shapefile::mDbfBuffer.
                \see Shapefile::buildDbf
                \see Shapefile::buildDbfFieldDescriptor
                \see Shapefile::buildDbfHeader
                \param pos Reference to an integer holding current position within
                           the shapefile buffer Shapefile::mShpBuffer. The position
                           is updated to reflect the first "free" position after
                           writing to the buffer.
                \param recLen Length of a single record, in bytes.
            */
            void buildDbfRecordSection( int& pos, int recLen );

            //! Create SHX file content
            /*!
                Part of SHX index creation.
                Builds the shapefile index from the Shapefile::mShxOffsets entries and
                writes it to the SHX buffer Shapefile::mShxBuffer and the SHX header
                Shapefile::mShxHeader.
                \see Shapefile::insertShxOffset
            */
            void buildShx();

            //! Append offset value to SHX (index)
            /*!
                For each shapefile record, it's offset within the main file is pushed
                to the Shapefile::mShxOffsets vector.
                \param contentLen Length of the shapefile record content, in 16-bit
                                  words, record header not included.
            */
            void insertShxOffset( int contentLen );

            //! Expand shp payload buffer
            /*!
                The shape buffer grows by larger chunks as it is gradually filled up with
                smaller blocks. For each expansion, the allocation size is doubled, until
                it reaches MAX_BUFFER_CHUNK_SIZE bytes. This is a tradeoff between execution
                time and memory consumption. For larger files, there will be relatively few
                buffer re-allocations and block transfers, in order to save time. For smaller
                files there will be more frequent re-allocations to save memory.
                \param byteLen The exact length in bytes of the amount of data about to be
                               written to the shapefile buffer. If the current buffer is too
                               small to hold the new block, it will be expanded.
            */
            int expandShpBuffer( int byteLen );

            //! Recursive func to extract SOSI field data
            /*!
                Traverses the SOSI element, mining the data fields and stores them in the
                provided record set container.
                \see Shapefile::insertDbfRecord
                \param sosi The SOSI element (sub tree) to extract data fields from.
                \param rec The recordset container to populate with data.
            */
            void extractDbfFields( ISosiElement* sosi, DbfRecord& rec );

            //! Create and insert DBF record
            /*!
                Prepares dBase record for current SOSI element. Creates the two mandatory
                fields "SOSI_ID" and "TYPE", before it calls Shapefil::extractDbfFields to
                retrieve the other data fields. The record is then inserted into the
                Shapefile::mDbfRecordSet member.
                \see Shapefil::extractDbfFields
                \param sosi The SOSI element (sub tree) to extract data fields from.
            */
            void insertDbfRecord( ISosiElement* sosi );

            //! Shapefile polys must have clockwise-ordered vertices
            /*!
                This is one of the core functions for handling polygons. Tests the direction
                for SOSI coordinates, and reverses them if they are in the wrong order with
                respect to the Shapefile format epscification.

                \note The direction of the vertices in a SOSI polygon is not significant, whist
                in a Shapefile polygon, it is crucial. The vertices in the outer polygon should
                always be ordered in a clockwise direction, while the holes or islands must be
                ordered in a counter-clockwise direction.

                \param neLst List of SOSI NorthEast elements describing current multipart
                             gemoetry (polygon with holes/islands).
            */
            std::vector<ICoordinate*> getNormalized( sosi::NorthEastList& neLst );
            
            //! Update or insert new DBF field
            /*!
                Appends or updates data for the DFB record, updating list of field names
                and lengths.
            */
            void saveToDbf( DbfRecord& rec, std::string field, std::string data );

        public:

            //! Constructor
            /*!
                Inlined, initializes native members.
            */
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
            virtual void filterSosiId( std::vector<std::string> sosiId ) { mFilterSosiId = sosiId; };

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
