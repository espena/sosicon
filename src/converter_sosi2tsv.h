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
#ifndef __CONVERTER_SOSI2TSV_H__
#define __CONVERTER_SOSI2TSV_H__

#include <iostream>
#include <fstream>
#include <vector>
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
    class ConverterSosi2tsv : public IConverter {

        //! Command line wrapper
        CommandLine mCmd;

        //! Destructor
        virtual ~ConverterSosi2tsv();

    public:
        //! Constructor
        ConverterSosi2tsv();
        
        //! Initialize converter
        /*!
            Implementation details in sosicon::IConverter::init()
            \sa sosicon::IConverter::init()
         */
        virtual void init( CommandLine cmd );

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
