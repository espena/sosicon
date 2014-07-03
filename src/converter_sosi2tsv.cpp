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
#include "converter_sosi2tsv.h"

sosicon::ConverterSosi2tsv::
ConverterSosi2tsv() {

}

sosicon::ConverterSosi2tsv::
~ConverterSosi2tsv() {

}

void sosicon::ConverterSosi2tsv::
init( sosicon::CommandLine cmd ) {
    mCmd = cmd;
}

void sosicon::ConverterSosi2tsv::
run() {
    if( mCmd.mSourceFiles.size() == 0 ) return;
    
    for( std::vector<std::string>::iterator i = mCmd.mSourceFiles.begin(); i != mCmd.mSourceFiles.end(); i++ ) {
        Parser p;
        p.setObjTypeSelection( mCmd.mObjTypes );
        char ln[ 1024 ];
        std::ifstream ifs( ( *i ).c_str() );
        while( !ifs.eof() ) {
            memset( ln, 0x00, sizeof ln );
            ifs.getline( ln, sizeof ln );
            p.parseSosiLine( ln );
        }
        ifs.close();
        std::string destFile;
        std::string dir, tit, ext;
        if( mCmd.mOutputFile.empty() ) {
            stringUtils::getPathInfo( *i, dir, tit, ext );
            if( !mCmd.mDestinationDirectory.empty() ) {
                dir = mCmd.mDestinationDirectory;
                char psep = dir.at( dir.length() - 1 );
                if( psep != '\\' || psep != '/' ) {
                    dir += '/';
                }
            }
            destFile = dir + tit + ".tsv";
        }
        else {
            destFile = mCmd.mOutputFile;
        }
        std::ofstream of( destFile.c_str(), mCmd.mAppend ? std::fstream::app : std::fstream::trunc );
        ISosiElement* h = p.getHeadElement();
        std::vector<std::string>& fields = mCmd.mFieldSelection.size() > 0 ? mCmd.mFieldSelection : p.getSosiElementsFields();
        if( mCmd.mIncludeHeader ) {
            for( std::vector<std::string>::iterator f = fields.begin(); f != fields.end(); f++ ) {
                of << ( f == fields.begin() ? "" : "\t" ) << *f;
            }
            of << "\n";
        }
        ISosiElement* e = 0;
        while( p.getNextSosiElement( e ) ) {
            for( std::vector<std::string>::iterator f = fields.begin(); f != fields.end(); f++ ) {

                /*
                std::string val = h && ( *f ).substr( 0, 5 ) == "hode:"
                                ? h->getData( ( *f ).substr( 5, 9999 ).c_str() )
                                : e->getData( ( *f ).c_str() );

                of << ( f == fields.begin() ? "" : "\t" ) << val;

                */
            }
            of << "\n";
        } // while

        of.close();

        if( mCmd.mVerbose > 0 ) {
            std::cout << "\n";
            std::cout << "SOSI-FIL......: " << *i << "\n";
            std::cout << "SOSIELEMENTER.: " << p.getCountSosiElements() << "\n";
            std::cout << "TSV-FIL.......: " << destFile << "\n";
            std::cout << "TSVRADER......: " << p.getCountSosiElementsSelection() << "\n";
            p.dump( mCmd.mVerbose == 2 );
        }

    }
}

