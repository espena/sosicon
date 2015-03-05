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

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "utils.h"
#include "interface/i_converter.h"
#include "interface/i_sosi_element.h"
#include "sosi/sosi_types.h"
#include "sosi/sosi_translation_table.h"
#include "sosi/sosi_north_east.h"
#include "command_line.h"
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

        //! Command line wrapper
        CommandLine* mCmd;

        //! Souce file currently in process
        std::string mCurrentSourcefile;

        //! Build SQL insert statements
        std::string buildInsertStatements( std::string dbSchema,
                                           std::string dbTable,
                                           std::map<std::string,std::string::size_type>& fields,
                                           std::vector<std::map<std::string,std::string>*>& rows );

        //! Build SQL create statements
        std::string buildCreateStatements( std::string sridDest,
                                           std::string dbSchema,
                                           std::string dbTable,
                                           std::map<std::string,std::string::size_type>& fields );

        //! Read current coordinate system from SOSI tree
        std::string getSrid( ISosiElement* sosiTree );

        //! Make SQL dump from SOSI tree
        void makePsql( ISosiElement* sosiTree,
                       std::string sridDest,
                       std::string dbSchema,
                       std::string dbTable,
                       std::map<std::string,std::string::size_type>& fields,
                       std::vector<std::map<std::string,std::string>*>& rows );

        //! Fetch element data fields recursively
        void extractData( ISosiElement* parent,
                          std::map<std::string,std::string::size_type>& fields,
                          std::map<std::string,std::string>*& row );

        void writePsql( std::string sridDest,
                        std::string dbSchema,
                        std::string dbTable,
                        std::map<std::string,std::string::size_type>& fields,
                        std::vector<std::map<std::string,std::string>*>& rows );

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
