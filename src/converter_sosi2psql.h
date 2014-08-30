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
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "interface/i_converter.h"
#include "command_line.h"
#include "parser.h"

namespace sosicon {

    /*!
        \addtogroup converters
        @{
    */
    //! SOSI to TSV converter
    /*!
        If command-line parameter -2tsv is specified, this converter will handle the output
        generation. Produces a TSV file (tab separated values) SOSI source.
     */
    class ConverterSosi2psql : public IConverter {

        //! Command line wrapper
        CommandLine* mCmd;

        //! Souce file currently in process
        std::string mCurrentSourcefile;

        void makePsql( ISosiElement* sosiTree );

        //! Destructor
        virtual ~ConverterSosi2psql() { };

    public:
        //! Constructor
        ConverterSosi2psql() : mCmd( 0 ) { };
        
        //! Initialize converter
        /*!
            Implementation details in sosicon::IConverter::init()
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
