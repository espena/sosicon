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
#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "logger.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX    // Ugly Windows-shait!
#endif
#include <windows.h>
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif
#include "utils.h"

namespace sosicon {

    //! Command-line parser
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Takes the arguments from the command-line and parses them into the class member variables.
        On Linux systems, this class also reads piped content (file list to be processed) from
        stdin, using it as input parameters.
     */
    class CommandLine {
    public:

        //! Conversion command
        /*!
            Specifies what type of conversion to perform. If this string is -2tsv, the SOSI file
            will be exported as tab separated values. The factory class uses this parameter to
            determine which IConverter implementation to employ upon initialization.
         */
        std::string mCommand;

        //! Build create statements only
        /*!
            For PostgreSQL export: If this flag is set (by specifying the -create parameter),
            database table creation script will be output.

            \note If neither -create nor -insert is specified, both create and insert statements
            are included in the export.
        */
        bool mCreateStatements;

        //! Build insert statements only
        /*!
            For PostgreSQL export: If this flag is set (by specifying the -insert parameter),
            database table insertion script will be output.

            \note If neither -create nor -insert is specified, both create and insert statements
            are included in the export.
        */
        bool mInsertStatements;

        //! List of input files
        /*!
            String vector containing the list of SOSI input files to be converted. This list is
            populated either by the file names specified directly on the command-line, or by the
            content of stdin as piped in from other commands (such as ls *.sos | ...) on Linux
            based systems.
         */
        std::vector<std::string> mSourceFiles;

        //! Create output file log
        /*!
            Name of output file log. If specified, a list of generated files from current run
            is written to this location.
         */
        std::string mOutputFileLog;

        //! List of object types to output
        /*!
            String vector containing the SOSI OBJTYPE identifiers for the elements to be included
            in the export. Specified as a comma-separated list of strings
            following the -t argument.
         */
        std::vector<std::string> mObjTypes;

        //! Export specific SOSI elements
        /*!
            List of SOSI IDs of individual element/features to be exported.
            Specified as a comma-separated list of strings following the -id argument.
         */
        std::vector<std::string> mFilterSosiId;

        //! List of geometry types to output
        /*!
            String vector containing the geometry types for the elements to be included in the
            export. Relevant for shapefile exports, since shapefiles can only contain one geometry
            type at a time. Specified as a comma-separated list of strings following the
            -g argument. The converter will output one shapefile for each selected geometry.
         */
        std::vector<std::string> mGeomTypes;

        //! List of selected fields
        /*!
            String vector containing the identifiers for the SOSI fields to be included in the
            export. Specified as a comma-separated list of strings following the -f argument.
         */
        std::vector<std::string> mFieldSelection;

        //! Destination directory
        /*!
            Path to the target directory where the output files will be written. Specified by
            the -d argument.
         */
        std::string mDestinationDirectory;

        //! Destination file
        /*!
            Specified by the -o argument. The target file name.
         */
        std::string mOutputFile;

        //! Expand command-line output
        /*!
            Set this flag to 1 if command-line output from Sosicon should be output as single lines
            for processing by other applications (i.e. web assembly).
         */
        bool mTtyLineExpand;

        //! TTY in flag
        /*!
            This flag is false if input is redirected (not a terminal window).
         */
        bool mIsTtyIn;

        //! TTY out flag
        /*!
            This flag is false if output is redirected (not a terminal window).
         */
        bool mIsTtyOut;

        //! Append flag
        /*!
            If the destination file (-o ...) is specified together with the -a argument, this
            flag will be true to signal that data from several source files should be merged into
            one destination file.
         */
        bool mAppend;

        //! PostGreSQL database schema
        /*!
            Name of database schema to export SOSI data to, when using -2psql converter.
         */
        std::string mDbSchema;

        //! PostGreSQL database table
        /*!
            Name of database table to export SOSI data to, when using -2psql converter.
         */
        std::string mDbTable;

        //! Include column headers
        /*!
            For some output formats, such as tsv, this flag governs whether a line with the column
            header names should be included in the target file.
         */
        bool mIncludeHeader;

        //! Create a sub directory for the output files
        /*!
            If the /s switch is specified, this flag is set to true. Instead of emitting the output
            files directly to current directory, a sub directory will be created, to which the
            ouput files are written.
         */
        bool mMakeSubDir;

        //! Specifies SRID for exports
        /*!
            Used for grid conversion exports to postGIS or other conversions that supports this.
         */
        std::string mSrid;

        //! Verbose output
        /*!
            Verbose level. If this value is 0, no informative output will be emitted during file
            parsing. If the value is 1 (-v), limited output will be written to stdout - mostly file
            header information from each SOSI file to be converted. If the value i 2 (-V), a
            more comprehensive summary of every SOSI element in all source files will be output.
         */
        int  mVerbose;

        //! Display help text
        /*!
            Outputs simple help text to the command-line.
         */
        void outputHelpText();

        //! Display disclaimer
        /*!
            Outputs disclaimer text.
         */
        void outputDisclaimer();

        //! Display license
        /*!
            Outputs lisence text.
         */
        void outputLicense();

        //! Read command-line arguments
        /*!
            Parses the command-line arguments and loads the settings into the member variables.
            This function will also read piped content (file name list) from stdin on linux systems,
            adding it to the CommandLine::mSourceFiles list of files to be processed.

            \param argc Number of arguments present. Passed on from main() function.
            \param argv Array of string pointers to each argument. Passed on from main() function.
         */
        void parse( int argc, char* argv[] );

        //! Read command-line string
        /*!
            Parses the command-line string and loads the settings into the member variables.

            \param cmdStr Complete command-line string to be parsed.
         */
        void parse( std::string cmdStr );

        //! Constructor
        CommandLine();

        //! Destructor
        virtual ~CommandLine();

    };

}; // namespece sosicon

#endif
