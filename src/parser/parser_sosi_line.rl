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
parseSosiLine( std::string sosiLine )
{
 /* Variables used by Ragel */
    int cs = 0;
    int stack[ 1024 ];
    int top = 0;
    int act = 0;
    char* ts = 0;
    char* te = 0;
    const char* s = sosiLine.c_str();
    const char* p = s;
    const char* pe = p + sosiLine.size();
    const char* eof = pe;

    %%{

        action flag_ref_subtraction {

            switch( fc ) {

                case '(':
                    if( mCurrentElement ) mCurrentElement->set( "ref_subtract", "1" );
                    break;

                case ')':
                    if( mCurrentElement ) mCurrentElement->set( "ref_subtract", "0" );
                    break;
            }
        }

        action see_sosi_element {
            mPendingSosiElementName += fc;
        }

        action see_sosi_level {
            mPendingSosiElementLevel++;
        }        

        action digest_sosi_element {

            sosi::ElementType type = sosi::strToType( mPendingSosiElementName );

            if( 1 == mPendingSosiElementLevel ) { // root level?
                createLevel1SosiElement();
            }

            switch( type ) {

                case sosi::sosi_element_kurve:
                case sosi::sosi_element_flate:
                    fgoto id;
                    break;

                case sosi::sosi_element_ref:
                    fgoto reflist;
                    break;

                case sosi::sosi_element_origo_no:
                    fgoto coordpair;
                    break;

                case sosi::sosi_element_enhet:
                case sosi::sosi_element_koordsys:
                case sosi::sosi_element_objtype:
                case sosi::sosi_element_oppdateringsdato:
                case sosi::sosi_element_tegnsett:
                    fgoto attribute;
                    break;

                default:
                    ;
            }
        }

        action digest_pending_value {
            if( mCurrentElement ) {
                mCurrentElement->set( mPendingSosiElementName, mPendingSosiValue );
            }
            mPendingSosiValue = "";
        }

        coord = ( [\-\+]?[0-9]+[\.]?[0-9]* );

        sosi_element_attribute = ( space* ( [^ \r\n]+ ${ appendFieldChar( mPendingSosiElementName, fc ); } ) );

        sosi_element_coordpair = ( space* ( coord . [ ]+ . coord ) ${ mPendingSosiValue += fc; }  %digest_pending_value . [ \r\n] );

        sosi_element_id = ( [ ]* [0-9]+ ${ appendFieldChar( "id", fc ); } );

        sosi_element = ( ( [\.]+  >{ clearPending(); } $see_sosi_level ) . [^ \.\r\n]+ $see_sosi_element %digest_sosi_element . [ \r\n] );

        sosi_non_comment = ( [^!]+ );

        sosi_reflist = ( ( ( ( [\(]? $flag_ref_subtraction ) . space* ) . ':' . ( [+\-]?[0-9]+ ) ${ mPendingSosiValue += fc; } %digest_pending_value ) . ( ( [\)]? $flag_ref_subtraction ) . space* ) . [ \r\n]* )+;



        attribute := sosi_element_attribute;

        coordpair := sosi_element_coordpair;

        id := sosi_element_id;

        dataln := sosi_element | sosi_reflist | sosi_element_coordpair;

        main := sosi_non_comment ${ fhold; fgoto dataln; };

        reflist := sosi_reflist;



        write init;
        write exec;

    }%%

};