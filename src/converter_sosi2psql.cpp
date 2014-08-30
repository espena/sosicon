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
#include "converter_sosi2psql.h"

void sosicon::ConverterSosi2psql::
makePsql( ISosiElement* sosiTree ) {

    std::string candidatePath = mCmd->mOutputFile.empty() ? mCurrentSourcefile : mCmd->mOutputFile;
    std::string dir, tit, ext;
    utils::getPathInfo( candidatePath, dir, tit, ext );

    candidatePath = dir + tit + "." + ext;
    int sequence = 0;

    while( utils::fileExists( candidatePath ) )
    {
        std::stringstream ss;
        ss << dir << tit << "_" << std::setw( 2 ) << std::setfill( '0' ) << ++sequence << "." << ext;
        candidatePath = ss.str();
    }

    sosi::SosiTranslationTable ttbl;

    std::map<std::string,int> fields;
    std::vector<std::map<std::string,std::string>*> rows;

    sosi::SosiElementSearch src;

    while( sosiTree->getChild( src ) ) {
        ISosiElement* sosi = src.element();
        std::map<std::string,std::string>* row = new std::map<std::string,std::string>();
        ( *row )[ "type" ] = sosi->getName();
    }

    std::ofstream fs;
    std::string fileName = candidatePath;
    fs.open( fileName.c_str(), std::ios::out | std::ios::trunc );

    fs << "--\n";
    fs << "-- PostgreSQL/Sosicon database dump\n";
    fs << "--\n";
    fs << "\n";

    fs.close();
    std::cout << "    > " << fileName << " written\n";

}

void sosicon::ConverterSosi2psql::
run() {
    Parser* pp;
    for( std::vector<std::string>::iterator f = mCmd->mSourceFiles.begin(); f != mCmd->mSourceFiles.end(); f++ ) {
        mCurrentSourcefile = *f;
        if( !utils::fileExists( mCurrentSourcefile ) ) {
            std::cout << mCurrentSourcefile << " not found\n";
        }
        else {
            std::cout << "Reading " << mCurrentSourcefile << "\n";
            Parser p;
            pp = &p;
            char ln[ 1024 ];
            std::ifstream ifs( ( mCurrentSourcefile ).c_str() );
            int n = 0;
            while( !ifs.eof() ) {
                if( mCmd->mIsTtyOut && ++n % 100 == 0 ) {
                    std::cout << "\rParsing line " << n;
                }
                memset( ln, 0x00, sizeof ln );
                ifs.getline( ln, sizeof ln );
                p.ragelParseSosiLine( ln );
            }
            p.complete();
            ifs.close();
            std::cout << "\r" << n << " lines parsed        \n";
            std::cout << "Building postGIS export...\n";
            ISosiElement* root = p.getRootElement();
            makePsql( root );
        }
    }
}
