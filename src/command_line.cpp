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
#include "command_line.h"

sosicon::CommandLine::
CommandLine() {
    mCommand = "-2tsv";
    mVerbose = 0;   

    int test = isatty( fileno( stdin ) );

    mIsTtyIn = isatty( fileno( stdin ) ) != 0;
    mIsTtyOut = isatty( fileno( stdout ) ) != 0;
#if defined( __linux__ ) || defined( __MACH__ )
    if( mIsTtyOut )
        std::cout << "\e[?25l"; // Cursor off
#endif
}

sosicon::CommandLine::
~CommandLine() {
#if defined( __linux__ ) || defined( __MACH__ )
    if( mIsTtyOut )
        std::cout << "\e[?25h"; // Cursor on
#endif
}

void sosicon::CommandLine::
parse( int argc, char* argv[] ) {

    std::string inputLine = "";
    if( !mIsTtyIn ) {
        while( std::cin ) {
            std::cin >> inputLine;
            mSourceFiles.push_back( inputLine );
        }       
    }
    
    for( int i = 1; i < argc; i++ ) {
        std::string param( argv[ i ] );
        if( param.at( 0 ) != '-' ) {
            while( i < argc ) {
                mSourceFiles.push_back( argv[ i ] );
                i++;
            }
        }
        else {

            if( "-a" == param ) {
                mAppend = true;
            }
            else if( "-d" == param && argc > ( ++i ) ) {
                mDestinationDirectory = argv[ i ];
            }
            else if( "-h" == param ) {
                mIncludeHeader = true;
            }
            else if( "-o" == param && argc > ( ++i ) ) {
                mOutputFile = argv[ i ];
            }
            else if( "-t" == param && argc > ( ++i ) ) {
                std::string objType;
                std::string objtypes = argv[ i ];
                if( objtypes.length() > 0 ) {
                    std::string::size_type j = 0, k = 0;
                    for( k = 0; k < objtypes.length(); k++ ) {
                        if( objtypes.at( k ) == ',' ) {
                            if( !( objType = utils::trim( objtypes.substr( j, k - j ) ) ).empty() ) {
                                mObjTypes.push_back( objType );                     
                            }
                            j = k + 1;
                        }
                    }
                    if( !( objType = utils::trim( objtypes.substr( j, k - j ) ) ).empty() ) {
                        mObjTypes.push_back( objType );                     
                    }
                }
            }
            else if( "-g" == param && argc > ( ++i ) ) {
                std::string geomType;
                std::string geomtypes = argv[ i ];
                if( geomtypes.length() > 0 ) {
                    std::string::size_type j = 0, k = 0;
                    for( k = 0; k < geomtypes.length(); k++ ) {
                        if( geomtypes.at( k ) == ',' ) {
                            if( !( geomType = utils::trim( geomtypes.substr( j, k - j ) ) ).empty() ) {
                                mGeomTypes.push_back( geomType );                     
                            }
                            j = k + 1;
                        }
                    }
                    if( !( geomType = utils::trim( geomtypes.substr( j, k - j ) ) ).empty() ) {
                        mGeomTypes.push_back( geomType );
                    }
                }
            }
            else if( "-f" == param && argc > ( ++i ) ) {
                std::string field;
                std::string fields = argv[ i ];
                if( fields.length() > 0 ) {
                    std::string::size_type j = 0, k = 0;
                    for( k = 0; k < fields.length(); k++ ) {
                        if( fields.at( k ) == ',' ) {
                            if( !( field = utils::trim( fields.substr( j, k - j ) ) ).empty() ) {
                                mFieldSelection.push_back( field );
                            }
                            j = k + 1;
                        }
                    }
                    if( !( field = utils::trim( fields.substr( j, k - j ) ) ).empty() ) {
                        mFieldSelection.push_back( field );
                    }
                }
            }
            else if( "-v" == param ) {
                mVerbose = 1;
            }
            else if( "-V" == param ) {
                mVerbose = 2;
            }
            else if( "-2shp" == param ) {
                mCommand = param;
            }
            else if( "-2tsv" == param ) {
                mCommand = param;
            }
            else if( "-stat" == param ) {
                mCommand = param;
            }
            else if( "-help" == param ) {
                outputHelpText();
                break;
            }
        }
    }
}

void sosicon::CommandLine::
outputHelpText() {
    std::cout << "Usage: sosicon [OPTIONS]... [FILES]...\n";
    std::cout << "Convert SOSI files to other output formats.\n";
    std::cout << "Example: sosicon -2tsv cities.sos poi.sos\n";
    std::cout << "\n";
    std::cout << "Conversion output formats:\n";
    std::cout << "\n";
    std::cout << "  -2tsv\n";
    std::cout << "      Convert SOSI source to tab delimited values (tsv).\n";
    std::cout << "\n";
    std::cout << "  -2shp\n";
    std::cout << "      Convert SOSI source to ESRI Shape (shp).\n";
    std::cout << "\n";
    std::cout << "  -stat\n";
    std::cout << "      Print out statistics for a SOSI file.\n";
    std::cout << "\n";
    std::cout << "Export options:\n";
    std::cout << "\n";
    std::cout << "  -t \"TYPES\"\n";
    std::cout << "      SOSI OBJTYPES to export. TYPES is a comma-delimited\n";
    std::cout << "      list of OBJTYPE identifiers. Use quotes around the string.\n";
    std::cout << "\n";
    std::cout << "  -g \"GEOMETRIES\"\n";
    std::cout << "      For shapefile export. Geometries to convert. GEOMETRIES is a\n";
    std::cout << "      comma-delimited list of SOSI geometry types, such as PUNKT.\n";
    std::cout << "      The -t switch still applies as output filter, but it will take effect\n";
    std::cout << "      for relevant geometry types only. Use quotes around the string.\n";
    std::cout << "\n";
    std::cout << "  -f \"FIELDS\"\n";
    std::cout << "      SOSI fields to be included in the exported tsv file.\n";
    std::cout << "      FIELDS is a comma-delimited list of field identifiers. Use\n";
    std::cout << "      quotes around the string.\n";
    std::cout << "\n";
    std::cout << "  -o \"FILE\"\n";
    std::cout << "      Output file. Specify the name of the target file here.\n";
    std::cout << "\n";
    std::cout << "  -a\n";
    std::cout << "      Append to file. If output file (-o ...) is specified together with\n";
    std::cout << "      this parameter, the content of all source files will be merged into\n";
    std::cout << "      the target file.\n";
    std::cout << "\n";
    std::cout << "  -d \"DIRECTORY\"\n";
    std::cout << "      Output directory. Specify location for the target file(s).\n";
    std::cout << "\n";
    std::cout << "  -h\n";
    std::cout << "      For some output formats, like tsv, a data header with column names\n";
    std::cout << "      will be added to the beginning of the file if this parameter.\n";
    std::cout << "      is specified.\n";
    std::cout << "\n";
    std::cout << "Miscellaneous options:\n";
    std::cout << "\n";
    std::cout << "  -v\n";
    std::cout << "      Limited verbose, print file header information only.\n";
    std::cout << "\n";
    std::cout << "  -V\n";
    std::cout << "      Full verbose, print information about all elements.\n";
    std::cout << "\n";
}



