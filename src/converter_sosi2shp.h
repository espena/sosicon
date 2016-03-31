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
#ifndef __CONVERTER_SOSI2SHP_H__
#define __CONVERTER_SOSI2SHP_H__

#include "logger.h"
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
#if defined( _WIN32 ) || defined( _WIN64 )
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

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

        //! Save specific shapefile part
        /*!
            The shapefile format consists of several files. Use corresponding interface to cast
            a instance of IShapefile to the correct file part for writing. The shapefile parts
            interfaces are:

            - IShapefileShpPart
            - IShapefileShxPart
            - IShapefileDbfPart
            - IShapefilePrjPart

            \param shp Reference to the source ShapeFile instance.
            \param basePath Path and file title for the file to be written, without extension.
            \param extension additional file extensions to be appended before the main extension,
                   which is one of the following:
                   - shp (shapefile part)
                   - shx (index part)
                   - dbf (attributes part)
                   - prj (projection part)
        */
        template<typename T>
        void writeFile( shape::Shapefile& shp, std::string basePath, std::string extension ) {
            std::ofstream fs;
            std::string fileName = basePath + "." + extension;
            fs.open( fileName.c_str(), std::ios::out | std::ios::trunc | std::ios::binary );
            fs << *( static_cast<T*>( &shp ) );
            fs.close();
            std::cout << "    > " << fileName << " written\n";
        }

        //! Command line wrapper
        CommandLine* mCmd;

        //! Souce file currently in process
        std::string mCurrentSourcefile;

        void makeShp( ISosiElement* sosiTree, bool* cancel );

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
        std::string makeBasePath( std::string objTypeName );

    public:

        //! Constructor
        ConverterSosi2shp() : mCmd( 0 ) { }

        //! Destructor
        virtual ~ConverterSosi2shp() { }

        //! Initialize converter
        /*!
            Implementation details in sosicon::IConverter::init()
            \sa sosicon::IConverter::init()
         */
        virtual void init( CommandLine* cmd ) { mCmd = cmd; }

        //! Start conversion
        /*!
            Implementation details in sosicon::IConverter::run()
            \sa sosicon::IConverter::run()
         */
        virtual void run( bool* cancel = 0x00 );

    }; // class ConverterSosi2shp
   /*! @} end group converters */
    
} // namespace sosicon

#endif
