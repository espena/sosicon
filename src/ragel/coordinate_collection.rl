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
#include "coordinate_collection.h"
#include "coordinate.h"
#include "interface/i_coordinate.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    %%{
        machine parseCoordinateCollection;
        write data;
    }%%
    //! \endcond

}

void sosicon::CoordinateCollection::
ragelParseCoordinates( sosi::Reference* ref, std::string data )
{

    //data = "-123456 789088 987654 321234\r\n";

 /* Variables used by Ragel */
    int cs = 0;
    int stack[ 1024 ];
    int top = 0;
    int act = 0;
    char* ts = 0;
    char* te = 0;
    const char* s = data.c_str();
    const char* p = s;
    const char* pe = p + data.size();
    const char* eof = pe;

    CoordinateList lst;
    std::string tmp;
    std::string coordN;
    std::string coordE;

    %%{

        action strbuild {
            tmp += fc;
        }

        action set_n {
            coordN = tmp;
            tmp = "";
        }

        action set_e {
            coordE = tmp;
            tmp = "";
        }

        action save_coord {
            ICoordinate* c = new Coordinate();
            c->setN( coordN );
            c->setE( coordE );
            lst.push_back( c );
        }

        action merge_list {
            CoordinateList& target = ref->subtract ? mIslands : mGeom;
            if( ref->reverse ) {
                std::reverse( lst.begin(), lst.end() );
            }
            for( CoordinateList::iterator i = lst.begin(); i != lst.end(); i++ ) {
                target.push_back( *i );
            }
            lst.clear();
        }

        coord = ( [\-]?[0-9]+ ) $strbuild;
        main := ( space* ( ( coord %set_n ' ' coord %set_e [ \t\r\n!]* ) %save_coord )** ) %merge_list;

        write init;
        write exec;

    }%%

};