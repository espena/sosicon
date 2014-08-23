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
#include "command_line.h"

sosicon::CommandLine::
CommandLine() {
    mVerbose = 0;   
    mIsTtyIn = isatty( fileno( stdin ) ) != 0;
    mIsTtyOut = isatty( fileno( stdout ) ) != 0;
#if defined( __APPLE__ ) || defined( __linux__ )
    if( mIsTtyOut ) {
        std::cout << "\e[?25l"; // Cursor off
    }
#endif
    std::cout << "\n";

    std::cout << "Sosicon, Copyright (C) 2014 Espen Andersen.\n";
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details type `sosicon -w'\n";
    std::cout << "This is free software, and you are welcome to redistribute it under certain\nconditions; type `sosicon -c' for details.\n";
    std::cout << "\n";
}

sosicon::CommandLine::
~CommandLine() {
#if defined( __APPLE__ ) || defined( __linux__ )
    if( mIsTtyOut ) {
        std::cout << "\e[?25h"; // Cursor on
    }
#endif
}

void sosicon::CommandLine::
parse( int argc, char* argv[] ) {

    bool inputExpected = true;
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
                inputExpected = false;
                mCommand = param;
                outputHelpText();
                break;
            }
            else if( "-w" == param ) {
                inputExpected = false;
                mCommand = param;
                outputDisclaimer();
                break;
            }
            else if( "-c" == param ) {
                inputExpected = false;
                mCommand = param;
                outputLicense();
                break;
            }
        }
    }

    if( mCommand.empty() || ( inputExpected && mSourceFiles.size() == 0 ) ) {
        std::cout << "Missing input parameters.\n";
        std::cout << "Type sosicon -help for instructions.\n\n";
        return;
    }
}

void sosicon::CommandLine::
outputHelpText() {
    std::cout << "\n";
    std::cout << "Usage: sosicon [OPTIONS]... [FILES]...\n";
    std::cout << "\n";
    std::cout << "Converts SOSI files to other output formats.\n";
    std::cout << "\n";
    std::cout << "Example:\n";
    std::cout << "sosicon -2sho cities.sos poi.sos\n";
    std::cout << "\n";
    std::cout << "Conversion output formats:\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "  -2shp\n";
    std::cout << "      Convert SOSI source to ESRI Shape (shp).\n";
    std::cout << "\n";
    std::cout << "  -stat\n";
    std::cout << "      Print out statistics for a SOSI file.\n";
    std::cout << "\n";
    std::cout << "\n";
}

void sosicon::CommandLine::
outputDisclaimer() {
    std::cout << "\n";
    std::cout << "Disclaimer here\n";
    std::cout << "\n";
}

void sosicon::CommandLine::
outputLicense() {
    std::cout << "\n";
    std::cout << "License information here\n";
    std::cout << "\n";
}
