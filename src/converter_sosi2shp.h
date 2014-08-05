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
#ifndef __CONVERTER_SOSI2SHP_H__
#define __CONVERTER_SOSI2SHP_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "interface/i_converter.h"
#include "interface/i_sosi_element.h"
#include "command_line.h"
#include "parser.h"
#include "utils.h"
#include "shape/shapefile.h"

namespace sosicon {

    /*!
        \addtogroup converters
        Collection of sosicon::IConverter implementations for handling and generating file output.
        Different command-line arguments will employ different converters. The factory class
        sosicon::Factory is responsible for creating correct IConverter instance. The following
        arguments are currently interpreted:
        - -2shp: sosicon::ConverterSosi2shp Shapefile conversion
        - -2tsv: sosicon::ConverterSosi2tsv TSV file conversion
        - -2xml: sosicon::ConverterSosi2xml Shape file conversion
        - -stat: sosicon::ConverterSosiStat SOSI statistics (printout)
        @{
    */
    //! SOSI to ESRI Shape converter
    /*!
        If command-line parameter -2shp is specified, this converter will handle the output
        generation. Produces an ESRI Shape-file from SOSI source.
     */
    class ConverterSosi2shp : public IConverter {

        //! Command line wrapper
        CommandLine* mCmd;

        void makeShp( ISosiElement* sosiTree );

        //! Make base file path for destination files
        /*!
            If the user specified an output file name, it will be used as a candidate for a
            base name to create shp, shx and dbf files for the shape export. Otherwise, the
            name of the first source file will be used by default.

            This function checks if there are any name collisions, incrementing a postfixed number
            to the base name until a unique name is found.

            \return Modified, unique destination base name with directory (if provided), without
                    file name extension.
        */
        std::string makeBasePath();

    public:

        //! Constructor
        ConverterSosi2shp() : mCmd( 0 ) { };

        //! Destructor
        virtual ~ConverterSosi2shp() { };

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

    }; // class ConverterSosi2shp
   /*! @} end group converters */
    
}; // namespace sosicon

#endif
