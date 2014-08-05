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
#include "sosi/sosi_ref_list.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    %%{
        machine parseSosiRef;
        write data;
    }%%
    //! \endcond

}

void sosicon::sosi::SosiRefList::
ragelParseSosiRef( std::string data )
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
    std::string tmpstr;
    Reference* ref = 0;
    bool reverse = false;
    bool subtract = false;

    %%{

        action init {
            ref = new Reference();
            ref->reverse = reverse;
            ref->subtract = subtract;
            mRefList.insert( mRefList.begin(), ref );
        }

        action build_serial {
            ref->serial += fc;
        }

        open_parenthesis = ( [\(]? ${ subtract = ( fc == '(' ); } );
        close_parenthesis = ( [\)]? ${ subtract = ( fc == ')' ); } );
        sign = ( [\-]? >{ reverse = false; } ${ reverse = true; } );
        serial = ( [0-9]+ >init @build_serial );

        main := space* ( open_parenthesis . space* ':' . sign . serial . space* . close_parenthesis . space* )+;

        write init;
        write exec;

    }%%

};