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
#ifndef __CONVERTER_SOSI2PSQL_H__
#define __CONVERTER_SOSI2PSQL_H__

//#pragma warning(disable:4503)

#include "logger.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include <cmath>
#include <map>
#include "utils.h"
#include "interface/i_converter.h"
#include "interface/i_sosi_element.h"
#include "sosi/sosi_types.h"
#include "sosi/sosi_translation_table.h"
#include "coordinate_collection.h"
#include "sosi/sosi_north_east.h"
#include "command_line.h"
#include "common_types.h"
#include "parser.h"

namespace sosicon {

    /*!
        \addtogroup converters
        @{
    */
    //! SOSI to PostgreSQL/PostGIS converter
    /*!
        If command-line parameter -2psql is specified, this converter will handle the output
        generation. Produces a PostgreSQL/PostGIS dump file from the SOSI source(s).
     */
    class ConverterSosi2psql : public IConverter {

        class Field {
            std::string::size_type mMaxLength;
            std::string::size_type mMinLength;
            bool mIsNumeric;
        public:
            bool isNumeric() {
                if( mMaxLength == mMinLength ) {
                    // Treat fixed-length numerical data as character field, since they
                    // are in fact non-arithmetic types types like dates, phone numbers
                    // or serial numbers.
                    mIsNumeric = false;
                }
                return mIsNumeric;
            }
            std::string::size_type length() {
                return mMaxLength;
            }
            Field() {
                mIsNumeric = true;
                mMaxLength = 0;
            }
            Field( std::string& str ) {
                mIsNumeric = true;
                mMaxLength = 0;
                mMinLength = std::numeric_limits<std::string::size_type>::max();
                expand( str );
            }
            std::string::size_type expand( std::string& str ) {
                std::string::size_type len = str.length();
                mMinLength = std::min( mMinLength, len );
                mMaxLength = std::max( mMaxLength, len );
                if( mIsNumeric ) {
                    mIsNumeric = utils::isNumeric( str );
                }
                return mMaxLength;
            }
        };

        typedef std::map< std::string,Field > FieldsList;
        typedef std::map< Wkt, FieldsList* > FieldsListCollection;
        typedef std::vector< std::map< std::string,std::string >* > RowsList;
        typedef std::map< Wkt, RowsList* > RowsListCollection;

        //! Command line wrapper
        CommandLine* mCmd;

        //! Souce file currently in process
        std::string mCurrentSourcefile;

        //! Collection of fields, one item for each geometry type
        FieldsListCollection mFieldsListCollection;

        //! Collection of rows, one item for each geometry type
        RowsListCollection mRowsListCollection;

        //! Build SQL insert statements for all geometries
        /*!
            This function calls sosicon::ConverterSosi2psql::buildInsertStatement
            for each of the WKT geometries types to export.
            \param dbSchema String representing the name of the database schema.
            \param dbTable String representing the base name of the database table.
                           The name of the geometry for that table will be prepended
                           to the base name.
            \see sosicon::ConverterSosi2psql::buildInsertStatement()
            \return The SQL insertion script content.
        */
        std::string buildInsertStatements( std::string dbSchema,
                                           std::string dbTable );

        //! Build SQL insert statement for one geometry
        /*!
            Creates the SQL statements required to insert the data for one WKT
            geometry.
            \param wktGeom WKT geometry type for current insertion script.
            \param dbSchema String representing the name of the database schema.
            \param dbTable String representing the base name of the database table.
                           The name of the geometry for that table will be prepended
                           to the base name.
            \see sosicon::ConverterSosi2psql::buildInsertStatements()
            \return The SQL insertion script content.
        */
        std::string buildInsertStatement( Wkt wktGeom,
                                          std::string dbSchema,
                                          std::string dbTable );

        //! Build SQL create statements for all geometries
        /*!
            This function calls sosicon::ConverterSosi2psql::buildCreateStatement
            for each of the WKT geometries types to export.
            \param dbSchema String representing the name of the database schema.
            \param dbTable String representing the base name of the database table.
                           The name of the geometry for that table will be prepended
                           to the base name.
            \see sosicon::ConverterSosi2psql::buildCreateStatement()
            \return The SQL/DDL creation script content.
        */
        std::string buildCreateStatements( std::string sridDest,
                                           std::string dbSchema,
                                           std::string dbTable );

         //! Build SQL create statements for one geometry
         /*!
             This function calls sosicon::ConverterSosi2psql::buildCreateStatements
             for each of the WKT geometries types to export.
             \param dbSchema String representing the name of the database schema.
             \param dbTable String representing the base name of the database table.
                            The name of the geometry for that table will be prepended
                            to the base name.
             \see sosicon::ConverterSosi2psql::buildCreateStatements()
             \return The SQL/DDL creation script content.
         */
        std::string buildCreateStatement( Wkt wktGeom,
                                          std::string sridDest,
                                          std::string dbSchema,
                                          std::string dbTable );

        // Free all heap allocations
        /*!
            Release memory reserved for this converter. Called before destroying object.
            It may not be necesary to invoke cleanup() if the program is about to
            terminate anyway, as this can be quite time consuming after converting
            large files.
             \see sosicon::ConverterSosi2psql::cleanup( Wkt )
        */
        void cleanup();

        // Free heap allocations for single geometry
        /*!
            Release memory reserved for one geometry. Called
            from sosicon::ConverterSosi2psql::cleanup( Wkt )
            \param wktGeom The WKT geometry type for which to delete allocated memory.
            \see sosicon::ConverterSosi2psql::cleanup()
        */
        void cleanup( Wkt wktGeom );

        //! Fetch element data fields recursively
        /*!
            Traverses the SOSI element tree recursively, extracting plain data fields.
            The field names are stored in the hdr list, and the data values are stored
            in the row list. The data size value associated wit each entry in hdr is
            updated to reflect the longest encountered field length.
            \param parent The SOSI (sub)tree to be traversed.
            \param hdr The fields list (table header).
            \param row The record set (table row).
        */
        void extractData( ISosiElement* parent,
                          FieldsList& hdr,
                          std::map<std::string,std::string>*& row );

        //! Read current coordinate system from SOSI tree
        /*!
            Scans the SOSI header, searching for the KOORDSYS element with information
            about the current coordinate system.
            \param sosiTree Pointer to the root SOSI element.
            \return The SRID code for the grid used in current file.
        */
        std::string getSrid( ISosiElement* sosiTree );

        //! Convert curve geomery (sosi KURVE) to SQL export data
        /*!
            Extracts the coordinates from the given SOSI element and builds
            a linestring WKT geometry from it.
            \see sosicon::ConverterSosi2psql::insertPoint()
            \see sosicon::ConverterSosi2psql::insertPolygon()
            \param lineString SOSI geometry element (typically "KURVE").
            \param sridSource Spatial reference grid ID for the source file.
            \param sridDest Spatial reference grid ID for the target file.
            \param geomField The name of the field within the recordset
                             representing the geometry data.
        */
        void insertLineString( ISosiElement* lineString,
                               std::string sridSource,
                               std::string sridDest,
                               std::string geomField );

        //! Convert single point geomery (sosi PUNKT) to SQL export data
        /*!
            Extracts the coordinate from the given SOSI element and builds
            a point WKT geometry from it.
            \see sosicon::ConverterSosi2psql::insertLineString()
            \see sosicon::ConverterSosi2psql::insertPolygon()
            \param point SOSI geometry element (typically "PUNKT" or "TEKST").
            \param sridSource Spatial reference grid ID for the source file.
            \param sridDest Spatial reference grid ID for the target file.
            \param geomField The name of the field within the recordset
                             representing the geometry data.
        */
        void insertPoint( ISosiElement* point,
                          std::string sridSource,
                          std::string sridDest,
                          std::string geomField );

        //! Convert polygons (sosi FLATE) to SQL export data
        /*!
            Extracts the coordinates from the given SOSI element and builds
            a polygon WKT geometry from it.
            \see sosicon::ConverterSosi2psql::insertLineString()
            \see sosicon::ConverterSosi2psql::insertPoint()
            \param point SOSI geometry element (typically "FLATE").
            \param sridSource Spatial reference grid ID for the source file.
            \param sridDest Spatial reference grid ID for the target file.
            \param geomField The name of the field within the recordset
                             representing the geometry data.
        */
        void insertPolygon( ISosiElement* polygon,
                            std::string sridSource,
                            std::string sridDest,
                            std::string geomField );

        //! Make SQL dump from SOSI tree
        /*!
            Iterates the SOSI tree once for each geometry to be exported, extracting
            relevant elements and passing them on to one of the insertion routines.
            \param sosiTree Pointer to the root SOSI element.
            \param sridDest Spatial reference grid ID for the target file.
            \param dbSchema String representing the name of the database schema.
            \param dbTable String representing the base name of the database table.
                           The name of the geometry for that table will be prepended
                           to the base name.
            \see sosicon::ConverterSosi2psql::insertPoint()
            \see sosicon::ConverterSosi2psql::insertLineString()
            \see sosicon::ConverterSosi2psql::insertPolygon()
        */
        void makePsql( ISosiElement* sosiTree,
                       std::string sridDest,
                       std::string dbSchema,
                       std::string dbTable );

        //! Test if current element is filtered out by -t parameter
        /*!
            If the user uses the -t parameter to specify which OBJTYPE elements to
            include in the export, this function tests if current element is opted
            out of the export.
            \param src SOSI element serch result to test.
            \return True if current element should be excluded from the export file.
        */
        bool objTypeExcluded( sosi::SosiElementSearch& src );

        //! Write SQL content
        /*!
            Assebles and prepares the SQL statements before writing them to the
            destination file.
            \param sridDest Spatial reference grid ID for the target file.
            \param dbSchema String representing the name of the database schema.
            \param dbTable String representing the base name of the database table.
                           The name of the geometry for that table will be prepended
                           to the base name.
        */
        void writePsql( std::string sridDest,
                        std::string dbSchema,
                        std::string dbTable );

        //! Destructor
        virtual ~ConverterSosi2psql() { }

    public:

        //! Constructor
        ConverterSosi2psql() : mCmd( 0 ) { }
        
        //! Initialize converter
        /*!
            Implementation details in sosicon::IConverter::init()
            \param cmd Pointer to (the one and only) CommandLine instance.
            \sa sosicon::IConverter::init()
         */
        virtual void init( CommandLine* cmd ) { mCmd = cmd; }

        //! Start conversion
        /*!
            Implementation details in sosicon::IConverter::run()
            \sa sosicon::IConverter::run()
         */
        virtual void run( bool* cancel = 0x00 );

    }; // class ConverterSosi2tsv
   /*! @} end group converters */
    
}; // namespace sosi2tsv

#endif
