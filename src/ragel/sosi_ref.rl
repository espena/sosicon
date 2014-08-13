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
    ReferenceData* refData = 0;
    bool reverse = false;
    bool subtract = false;
    SosiReferenceList* refList = 0;

    %%{

        action init_ref {
            refData = new ReferenceData();
            refData->reverse = reverse;
            refData->subtract = subtract;
            if( 0 == refList ) {
                refList = new SosiReferenceList();
                mRefListCollection.push_back( refList );
            }
            refList->insert( refList->begin(), refData );
        }

        action build_serial {
            refData->serial += fc;
        }

        action see_opening_parenthesis {
            subtract = ( fc == '(' );
            refList = new SosiReferenceList();
            mRefListCollection.push_back( refList );
        }

        action see_closing_parenthesis {
            subtract = ( fc == ')' );
            refList = 0;
        }

        open_parenthesis = ( [\(]? $see_opening_parenthesis );
        close_parenthesis = ( [\)]? $see_closing_parenthesis );
        sign = ( [\-]? >{ reverse = false; } ${ reverse = true; } );
        serial = ( [0-9]+ >init_ref @build_serial );

        main := space* ( open_parenthesis . space* ':' . sign . serial . space* . close_parenthesis . space* )+;

        write init;
        write exec;

    }%%

};