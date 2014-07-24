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
#include "sosi/sosi_north_east.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    %%{
        machine parseCoordinateCollection;
        write data;
    }%%
    //! \endcond

}

void sosicon::sosi::SosiNorthEast::
ragelParseCoordinates( std::string data )
{

 /* Variables used by Ragel */
    int cs = 0;
    int top = 0;
    int act = 0;
    char* ts = 0;
    char* te = 0;
    const char* s = data.c_str();
    const char* p = s;
    const char* pe = p + data.size();
    const char* eof = pe;

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
            append( coordN, coordE );
        }

        coord = ( [\-]?[0-9]+ ) $strbuild;
        main := ( space* ( ( coord %set_n ' ' coord %set_e [ \t\r\n!]* ) %save_coord )** );

        write init;
        write exec;

    }%%

};