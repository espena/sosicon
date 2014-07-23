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
#include "parser.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    %%{
        machine parseSosiLine;
        write data;
    }%%
    //! \endcond

}

void sosicon::Parser::
ragelParseSosiLine( std::string sosiLine )
{

    sosiLine += "\r\n";

 /* Variables used by Ragel */
    int cs = 0;
    int top = 0;
    int act = 0;
    char* ts = 0;
    char* te = 0;
    const char* s = sosiLine.c_str();
    const char* p = s;
    const char* pe = p + sosiLine.size();
    const char* eof = pe;

    std::string tmpstr;
    int tmpint;

    %%{

        action strbuild {
            if( '\r' != fc ) {
                tmpstr += fc;
            }
        }

        action strinit {
            tmpstr.clear();
        }

        action intincr {
            tmpint++;
        }

        action intinit {
            tmpint = 0;
        }

        action set_name {
            mPendingElementName = sosicon::stringUtils::trim( tmpstr );
        }

        action set_attributes {
            mPendingElementAttributes = sosicon::stringUtils::trim( tmpstr );
            tmpstr.clear();
        }

        action append_attributes {
            mPendingElementAttributes += ( " " + sosicon::stringUtils::trim( tmpstr ) );
            tmpstr.clear();
        }

        action set_level {
            mPendingElementLevel = tmpint;
            tmpstr.clear();
        }

        action set_serial {
            mPendingElementSerial = tmpstr.substr( 0, tmpstr.length() - 1 );
            tmpstr.clear();
        }

        action digest_element {
            digestPendingElement();
        }

        delimiter = ( [\!\t\r\n ] );

        ndelimiter = ( [^\!\t\r\n ] );

        element_level = ( [\.]+ >intinit $intincr %set_level );

        element_name = ( ( any - [ \.\r\n] )+ >strinit @strbuild %set_name );

        element_serial = ( [\t ]+ ( ( [0-9]+[ \t]*[\:] ) >strinit @strbuild %set_serial ) [\r\n]+ );

        element_attributes =  ( [\t ]+ ( ( [^!\r\n]* ) >strinit @strbuild %set_attributes ) [\r\n]+ );

        prev_element_data = ( ( any - [\.!] )* >strinit @strbuild %append_attributes );

        next_element = ( element_level element_name ( element_serial | element_attributes )? delimiter* ) >digest_element;

        main := prev_element_data . next_element*;

        write init;
        write exec;

    }%%

};