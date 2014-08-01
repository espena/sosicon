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
#include "converter_sosi_stat.h"

sosicon::ConverterSosiStat::
ConverterSosiStat() {
}

sosicon::ConverterSosiStat::
~ConverterSosiStat() {

}

void sosicon::ConverterSosiStat::
init( sosicon::CommandLine cmd ) {
    mCmd = cmd;
}

void sosicon::ConverterSosiStat::
makeStat( ISosiElement* parent ) {

    sosi::SosiElementSearch src;
    while( parent->getChild( src ) ) {
        makeStat( src.element() );
    }
    std::string elementName = parent->getName();
    if( mGeoTypes.find( elementName ) == mGeoTypes.end() ) {
        mGeoTypes[ elementName ] = 1;
    }
    else {
        mGeoTypes[ elementName ]++;
    }
    if( parent->getType() == sosi::sosi_element_objtype ) {
        std::string objtype = parent->getData();
        if( mObjTypes.find( objtype ) == mObjTypes.end() ) {
            mObjTypes[ objtype ] = 1;
        }
        else {
            mObjTypes[ objtype ]++;
        }
    }
}

void sosicon::ConverterSosiStat::
run() {
    for( std::vector<std::string>::iterator f = mCmd.mSourceFiles.begin(); f != mCmd.mSourceFiles.end(); f++ ) {
        std::cout << "Generating statistics for " << *f << "\n";
        Parser p;
        char ln[ 1024 ];
        std::ifstream ifs( ( *f ).c_str() );
        while( !ifs.eof() ) {
            memset( ln, 0x00, sizeof ln );
            ifs.getline( ln, sizeof ln );
            p.ragelParseSosiLine( ln );
        }
        p.complete();
        ifs.close();
        ISosiElement* root = p.getRootElement();
        makeStat( root );
        for( std::map<std::string, int>::iterator i = mObjTypes.begin(); i != mObjTypes.end(); i++ ) {
            std::cout << i->first << ": " << i->second << "\n";
        }
    }
}
