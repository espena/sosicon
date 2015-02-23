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
#include "sosi/sosi_origo_ne.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    %%{
        machine parseSosiOrigoNE;
        write data;
    }%%
    //! \endcond

}

void sosicon::sosi::SosiOrigoNE::
ragelParseSosiOrigoNE( std::string data )
{

 data += "\n";

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
    std::string n;
    std::string e;

    %%{

        action see_n {
            n += fc;
        }

        action see_e {
            e += fc;
        }

        action save_ne {
          std::stringstream ssN, ssE;
            ssN << n;
            ssN >> mOrigoN;
            ssE << e;
            ssE >> mOrigoE;
        }

        main := space* ( [\+\-0-9]+ $see_n ) space+ ( [\+\-0-9]+ $see_e ) ( ( any - [0-9] ) %save_ne );

        write init;
        write exec;

    }%%

};