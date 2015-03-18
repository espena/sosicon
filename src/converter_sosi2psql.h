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

#pragma warning(disable:4503)

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
    //! SOSI to PostGreSQL converter
    /*!
        If command-line parameter -2psql is specified, this converter will handle the output
        generation. Produces a PostGreSQL dump file from the SOSI source(s).
     */
    class ConverterSosi2psql : public IConverter {

        typedef std::map< std::string,std::string::size_type > FieldsList;
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
        std::string buildInsertStatements( std::string dbSchema,
                                           std::string dbTable );

        //! Build SQL insert statement for one geometry
        std::string buildInsertStatement( Wkt wktGeom,
                                          std::string dbSchema,
                                          std::string dbTable );

        //! Build SQL create statements for all geometries
        std::string buildCreateStatements( std::string sridDest,
                                           std::string dbSchema,
                                           std::string dbTable );

        //! Build SQL create statement for one geometry
        std::string buildCreateStatement( Wkt wktGeom,
                                          std::string sridDest,
                                          std::string dbSchema,
                                          std::string dbTable );

        // Free all heap allocations
        void cleanup();

        // Free heap allocations for single geometry
        void cleanup( Wkt wktGeom );

        //! Fetch element data fields recursively
        void extractData( ISosiElement* parent,
                          FieldsList& hdr,
                          std::map<std::string,std::string>*& row );

        //! Read current coordinate system from SOSI tree
        std::string getSrid( ISosiElement* sosiTree );

        //! Convert curve geomery (sosi KURVE) to SQL export data
        void insertLineString( ISosiElement* lineString,
                               std::string sridSource,
                               std::string sridDest,
                               std::string geomField );

        //! Convert single point geomery (sosi PUNKT) to SQL export data
        void insertPoint( ISosiElement* point,
                          std::string sridSource,
                          std::string sridDest,
                          std::string geomField );

        //! Convert polygons (sosi FLATE) to SQL export data
        void insertPolygon( ISosiElement* polygon,
                            std::string sridSource,
                            std::string sridDest,
                            std::string geomField );

        //! Make SQL dump from SOSI tree
        void makePsql( ISosiElement* sosiTree,
                       std::string sridDest,
                       std::string dbSchema,
                       std::string dbTable );

        //! Test if current element is filtered out by -t parameter
        bool objTypeExcluded( sosi::SosiElementSearch& src );

        //! Write SQL content
        void writePsql( std::string sridDest,
                        std::string dbSchema,
                        std::string dbTable );

        //! Destructor
        virtual ~ConverterSosi2psql() { };

    public:

        //! Constructor
        ConverterSosi2psql() : mCmd( 0 ) { };
        
        //! Initialize converter
        /*!
            Implementation details in sosicon::IConverter::init()
            \param cmd Pointer to (the one and only) CommandLine instance.
            \sa sosicon::IConverter::init()
         */
        virtual void init( CommandLine* cmd ) { mCmd = cmd; };

        //! Start conversion
        /*!
            Implementation details in sosicon::IConverter::run()
            \sa sosicon::IConverter::run()
         */
        virtual void run();

    }; // class ConverterSosi2tsv
   /*! @} end group converters */
    
}; // namespace sosi2tsv

#endif
