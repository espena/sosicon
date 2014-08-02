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
#ifndef __CONVERTER_SOSI_STAT_H__
#define __CONVERTER_SOSI_STAT_H__

#include <iostream>
#include <fstream>
#include <map>
#include "interface/i_converter.h"
#include "interface/i_sosi_element.h"
#include "sosi/sosi_types.h"
#include "sosi/sosi_element_search.h"
#include "command_line.h"
#include "utils.h"
#include "parser.h"

namespace sosicon {

    /*!
        \addtogroup converters
        Collection of sosicon::IConverter implementations for handling and generating file output.
        Different command-line arguments will employ different converters. The factory class
        sosicon::Factory is responsible for creating correct IConverter instance. The following
        arguments are currently interpreted:
        - -2shp: sosicon::ConverterSosi2shp Shapefile conversion
        - -2tsv: sosicon::ConverterSosi2tsv TSV file conversion
        - -stat: sosicon::ConverterSosi2Xml XML conversion
        - -stat: sosicon::ConverterSosiStat SOSI statistics (printout)
        @{
    */
    //! SOSI to ESRI Shape converter
    /*!
        If command-line parameter -stat is specified, this converter will handle the output
        generation. Produces an ESRI Shape-file from SOSI source.
     */
    class ConverterSosiStat : public IConverter {

        //! Command line wrapper
        CommandLine mCmd;

        //! Map keeping count of objtypes
        std::map<std::string, int> mObjTypes;
        
        //! Map keeping count of geometry
        std::map<std::string, int> mGeoTypes;

        //! Output simple element attributes
        void printElementData( ISosiElement* e, sosi::SosiElementSearch src, int padding );

        //! Output simple element attributes
        void printTableHeader( std::string col1, std::string col2, int padding );

        //! Output table header with column titles
        void makeStat( ISosiElement* parent );

    public:

        //! Constructor
        ConverterSosiStat();

        //! Destructor
        virtual ~ConverterSosiStat();

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

    }; // class ConverterSosistat
   /*! @} end group converters */
    
}; // namespace sosicon

#endif
