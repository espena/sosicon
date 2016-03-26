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
#include "converter_sosi_stat.h"

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
printElementData( ISosiElement* e, sosi::SosiElementSearch src, int padding ) {
    while( e->getChild( src ) ) {
        ISosiElement* child = src.element();
        if( !child->getData().empty() ) {
            std::string label = child->getName();
            label.resize( padding, '.' );
            sosicon::logstream << " " << label << ": " << child->getData() << "\n";
        }
    }
}

void sosicon::ConverterSosiStat::
printListContent( std::map<std::string, int> list, int padding ) {
    for( std::map<std::string, int>::iterator i = list.begin(); i != list.end(); i++ ) {
        std::string label = i->first;
        std::stringstream ss;
        ss << i->second;
        std::string value = std::string( 8 - ss.str().size(), ' ' ) + ss.str();
        label.resize( padding, '.' );
        sosicon::logstream << " " << label << ": " << value << "\n";
    }
}

void sosicon::ConverterSosiStat::
printTableHeader( std::string col1, std::string col2, int padding ) {
    col1.resize( padding, ' ' );
    sosicon::logstream << " " << col1 << ": " << col2 << "\n";
    sosicon::logstream << "------------------------------------------\n";
}

void sosicon::ConverterSosiStat::
run( bool* cancel ) {
    for( std::vector<std::string>::iterator f = mCmd->mSourceFiles.begin(); f != mCmd->mSourceFiles.end(); f++ ) {
        sosicon::logstream << "\nGenerating statistics for " << *f << "\n";
        Parser p;
        char ln[ 1024 ];
        std::ifstream ifs( ( *f ).c_str() );
        int c = 0;
        while( !ifs.eof() ) {
            c++;
            if( mCmd->mIsTtyOut && ( c % 100 ) == 0 ) {
                sosicon::logstream << "\rParsing " << c << " lines...";
            }
            memset( ln, 0x00, sizeof ln );
            ifs.getline( ln, sizeof ln );
            p.ragelParseSosiLine( ln );
        }
        sosicon::logstream << "\n" << c << " lines in file   \n\n";
        p.complete();
        ifs.close();

        ISosiElement* root = p.getRootElement();
        makeStat( root );

        sosi::SosiElementSearch srcHead( sosi::sosi_element_head );
        if( root->getChild( srcHead ) ) {
            sosi::SosiElementSearch srcHeadItem;
            
            printTableHeader( "SOSI HEADER", "VALUE", 22 );
            printElementData( srcHead.element(), sosi::SosiElementSearch(), 22 );
            sosicon::logstream << "\n\n";
            
            sosi::SosiElementSearch srcTranspar( sosi::sosi_element_transpar );
            if( srcHead.element()->getChild( srcTranspar ) ) {
                sosi::SosiElementSearch srcTransparItem;
                printTableHeader( "SOSI HEADER/TRANSPAR", "VALUE", 22 );
                printElementData( srcTranspar.element(), sosi::SosiElementSearch(), 22 );
                sosicon::logstream << "\n\n";
            }
        }

        printTableHeader( "SOSI ELEMENT", "COUNT", 30 );
        printListContent( mGeoTypes, 30 );
        sosicon::logstream << "\n\n";

        printTableHeader( "OBJTYPE", "COUNT", 30 );
        printListContent( mObjTypes, 30 );
        sosicon::logstream << "\n\n";

    }
}

