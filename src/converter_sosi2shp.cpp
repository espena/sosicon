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
#include "converter_sosi2shp.h"

sosicon::ConverterSosi2shp::
ConverterSosi2shp() {

}

sosicon::ConverterSosi2shp::
~ConverterSosi2shp() {

}

void sosicon::ConverterSosi2shp::
init( sosicon::CommandLine cmd ) {
    mCmd = cmd;
}

void sosicon::ConverterSosi2shp::
makeShp( ISosiElement* sosiTree ) {

    shape::Shapefile shp;
    for( std::vector<std::string>::iterator g = mCmd.mGeomTypes.begin(); g != mCmd.mGeomTypes.end(); g++ ) {
        shp.build( sosiTree, sosi::sosiNameToType( *g ) );
    }

    std::string basePath = makeBasePath();

    std::ofstream shpfs;
    shpfs.open( ( basePath + ".shp" ).c_str(), std::ios::out | std::ios::trunc | std::ios::binary );
    shpfs << *( static_cast<IShapefileShpPart*>( &shp ) );
    shpfs.close();

    std::ofstream shxfs;
    shxfs.open( ( basePath + ".shx" ).c_str(), std::ios::out | std::ios::trunc | std::ios::binary );
    shxfs << *( static_cast<IShapefileShxPart*>( &shp ) );
    shxfs.close();

    std::ofstream dbffs;
    dbffs.open( ( basePath + ".dbf" ).c_str(), std::ios::out | std::ios::trunc | std::ios::binary );
    dbffs << *( static_cast<IShapefileDbfPart*>( &shp ) );
    dbffs.close();
}

std::string sosicon::ConverterSosi2shp::
makeBasePath() {

    std::string candidatePath = mCmd.mOutputFile.empty() ? mCmd.mSourceFiles[ 0 ] : mCmd.mOutputFile;
    std::string dir, tit, ext;
    utils::getPathInfo( candidatePath, dir, tit, ext );

    candidatePath = dir + tit;
    int sequence = 0;

    while( utils::fileExists( candidatePath + ".shp" ) ||
           utils::fileExists( candidatePath + ".shx" ) ||
           utils::fileExists( candidatePath + ".dbf" ) ||
           utils::fileExists( candidatePath + ".prj" ) )
    {
        std::stringstream ss;
        ss << dir << tit << "_" << std::setw( 2 ) << std::setfill( '0' ) << ++sequence;
        candidatePath = ss.str();
    }

    return candidatePath;
}

void sosicon::ConverterSosi2shp::
run() {
    if( mCmd.mIsTtyOut ) {
        std::cout << "\e[?25l"; // Cursor off
    }
    Parser* pp;
    for( std::vector<std::string>::iterator f = mCmd.mSourceFiles.begin(); f != mCmd.mSourceFiles.end(); f++ ) {
        std::cout << "Reading " << *f << "\n";
        Parser p;
        pp = &p;
        char ln[ 1024 ];
        std::ifstream ifs( ( *f ).c_str() );
        int n = 0;
        while( !ifs.eof() ) {
            if( mCmd.mIsTtyOut && ++n % 100 == 0 ) {
                std::cout << "\rParsing line " << n;
            }
            memset( ln, 0x00, sizeof ln );
            ifs.getline( ln, sizeof ln );
            p.ragelParseSosiLine( ln );
        }
        p.complete();
        ifs.close();
        std::cout << "\r" << n << " lines parsed        \n";
        std::cout << "Building shape file...\n";
        ISosiElement* root = p.getRootElement();
        makeShp( root );
    }
    if( mCmd.mIsTtyOut ) {
        std::cout << "\e[?25h"; // Cursor on
    }
}
