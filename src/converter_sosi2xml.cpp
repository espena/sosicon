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
#include "converter_sosi2xml.h"

void sosicon::ConverterSosi2xml::
makeXML( ISosiElement* ) {

}

void sosicon::ConverterSosi2xml::
run( bool* ) {
    for( std::vector<std::string>::iterator f = mCmd->mSourceFiles.begin(); f != mCmd->mSourceFiles.end(); f++ ) {
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
        makeXML( root );
    }
}

