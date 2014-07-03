
/* #line 1 "parser/parser_sosi_line.rl" */
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
    
/* #line 28 "parser_sosi_line.cpp" */
static const char _parseSosiLine_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 9, 1, 10, 2, 4, 0, 
	2, 8, 2
};

static const unsigned char _parseSosiLine_key_offsets[] = {
	0, 0, 1, 6, 13, 15, 19, 24, 
	26, 32, 37, 40, 43, 53, 61, 63, 
	67, 72, 74, 80, 85, 88, 92, 94, 
	98, 102, 106, 111, 115, 119, 121, 122, 
	125, 130, 130, 132, 132, 140, 145, 153
};

static const char _parseSosiLine_trans_keys[] = {
	33, 10, 13, 32, 9, 12, 32, 43, 
	45, 9, 13, 48, 57, 48, 57, 32, 
	46, 48, 57, 32, 43, 45, 48, 57, 
	48, 57, 10, 13, 32, 46, 48, 57, 
	10, 13, 32, 48, 57, 32, 48, 57, 
	32, 48, 57, 32, 40, 43, 45, 46, 
	58, 9, 13, 48, 57, 32, 43, 45, 
	58, 9, 13, 48, 57, 48, 57, 32, 
	46, 48, 57, 32, 43, 45, 48, 57, 
	48, 57, 10, 13, 32, 46, 48, 57, 
	10, 13, 32, 48, 57, 32, 48, 57, 
	43, 45, 48, 57, 48, 57, 32, 58, 
	9, 13, 10, 13, 32, 46, 10, 13, 
	32, 46, 32, 40, 58, 9, 13, 32, 
	58, 9, 13, 43, 45, 48, 57, 48, 
	57, 33, 10, 13, 32, 10, 13, 32, 
	9, 12, 48, 57, 32, 40, 41, 58, 
	9, 13, 48, 57, 32, 40, 58, 9, 
	13, 32, 40, 41, 58, 9, 13, 48, 
	57, 32, 40, 58, 9, 13, 0
};

static const char _parseSosiLine_single_lengths[] = {
	0, 1, 3, 3, 0, 2, 3, 0, 
	4, 3, 1, 1, 6, 4, 0, 2, 
	3, 0, 4, 3, 1, 2, 0, 2, 
	4, 4, 3, 2, 2, 0, 1, 3, 
	3, 0, 0, 0, 4, 3, 4, 3
};

static const char _parseSosiLine_range_lengths[] = {
	0, 0, 1, 2, 1, 1, 1, 1, 
	1, 1, 1, 1, 2, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	0, 0, 1, 1, 1, 1, 0, 0, 
	1, 0, 1, 0, 2, 1, 2, 1
};

static const unsigned char _parseSosiLine_index_offsets[] = {
	0, 0, 2, 7, 13, 15, 19, 24, 
	26, 32, 37, 40, 43, 52, 59, 61, 
	65, 70, 72, 78, 83, 86, 90, 92, 
	96, 101, 106, 111, 115, 119, 121, 123, 
	127, 132, 133, 135, 136, 143, 148, 155
};

static const char _parseSosiLine_indicies[] = {
	1, 0, 4, 4, 4, 3, 2, 5, 
	6, 6, 5, 7, 1, 7, 1, 8, 
	9, 7, 1, 8, 10, 10, 11, 1, 
	11, 1, 12, 12, 12, 13, 11, 1, 
	12, 12, 12, 13, 1, 8, 9, 1, 
	14, 15, 1, 16, 17, 18, 18, 19, 
	21, 16, 20, 1, 16, 18, 18, 21, 
	16, 20, 1, 20, 1, 22, 23, 20, 
	1, 22, 24, 24, 25, 1, 25, 1, 
	26, 26, 26, 27, 25, 1, 26, 26, 
	26, 27, 1, 22, 23, 1, 28, 28, 
	29, 1, 29, 1, 30, 21, 30, 1, 
	1, 1, 1, 32, 31, 33, 33, 33, 
	1, 31, 34, 35, 36, 34, 1, 34, 
	36, 34, 1, 37, 37, 38, 1, 38, 
	1, 1, 0, 1, 1, 1, 2, 4, 
	4, 4, 3, 2, 1, 15, 1, 1, 
	39, 40, 41, 42, 39, 29, 1, 43, 
	17, 21, 43, 1, 44, 45, 46, 47, 
	44, 38, 1, 48, 35, 36, 48, 1, 
	0
};

static const char _parseSosiLine_trans_targs[] = {
	30, 0, 31, 32, 2, 3, 4, 5, 
	6, 10, 7, 8, 33, 9, 11, 34, 
	13, 23, 14, 24, 15, 21, 16, 20, 
	17, 18, 35, 19, 22, 36, 23, 25, 
	24, 35, 27, 27, 28, 29, 38, 37, 
	23, 37, 21, 37, 39, 27, 39, 28, 
	39
};

static const char _parseSosiLine_trans_actions[] = {
	19, 0, 11, 11, 0, 0, 13, 13, 
	13, 13, 13, 13, 9, 13, 0, 15, 
	0, 1, 13, 24, 13, 0, 13, 13, 
	13, 13, 9, 13, 17, 17, 0, 3, 
	5, 7, 0, 1, 0, 17, 17, 9, 
	21, 21, 9, 0, 9, 21, 21, 9, 
	0
};

static const char _parseSosiLine_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 9, 0, 9, 0
};

static const int parseSosiLine_start = 1;
static const int parseSosiLine_first_final = 30;
static const int parseSosiLine_error = 0;

static const int parseSosiLine_en_attribute = 2;
static const int parseSosiLine_en_coordpair = 3;
static const int parseSosiLine_en_id = 11;
static const int parseSosiLine_en_dataln = 12;
static const int parseSosiLine_en_main = 1;
static const int parseSosiLine_en_reflist = 26;


/* #line 27 "parser/parser_sosi_line.rl" */

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

    
/* #line 177 "parser_sosi_line.cpp" */
	{
	cs = parseSosiLine_start;
	}

/* #line 182 "parser_sosi_line.cpp" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _parseSosiLine_trans_keys + _parseSosiLine_key_offsets[cs];
	_trans = _parseSosiLine_index_offsets[cs];

	_klen = _parseSosiLine_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _parseSosiLine_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _parseSosiLine_indicies[_trans];
	cs = _parseSosiLine_trans_targs[_trans];

	if ( _parseSosiLine_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parseSosiLine_actions + _parseSosiLine_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 49 "parser/parser_sosi_line.rl" */
	{

            switch( (*p) ) {

                case '(':
                    if( mCurrentElement ) mCurrentElement->set( "ref_subtract", "1" );
                    break;

                case ')':
                    if( mCurrentElement ) mCurrentElement->set( "ref_subtract", "0" );
                    break;
            }
        }
	break;
	case 1:
/* #line 63 "parser/parser_sosi_line.rl" */
	{
            mPendingSosiElementName += (*p);
        }
	break;
	case 2:
/* #line 67 "parser/parser_sosi_line.rl" */
	{
            mPendingSosiElementLevel++;
        }
	break;
	case 3:
/* #line 71 "parser/parser_sosi_line.rl" */
	{

            sosi::ElementType type = sosi::strToType( mPendingSosiElementName );

            if( 1 == mPendingSosiElementLevel ) { // root level?
                createLevel1SosiElement();
            }

            switch( type ) {

                case sosi::sosi_element_kurve:
                case sosi::sosi_element_flate:
                    {cs = 11; goto _again;}
                    break;

                case sosi::sosi_element_ref:
                    {cs = 26; goto _again;}
                    break;

                case sosi::sosi_element_origo_no:
                    {cs = 3; goto _again;}
                    break;

                case sosi::sosi_element_enhet:
                case sosi::sosi_element_koordsys:
                case sosi::sosi_element_objtype:
                case sosi::sosi_element_oppdateringsdato:
                case sosi::sosi_element_tegnsett:
                    {cs = 2; goto _again;}
                    break;

                default:
                    ;
            }
        }
	break;
	case 4:
/* #line 107 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->set( mPendingSosiElementName, mPendingSosiValue );
            }
            mPendingSosiValue = "";
        }
	break;
	case 5:
/* #line 116 "parser/parser_sosi_line.rl" */
	{ appendFieldChar( mPendingSosiElementName, (*p) ); }
	break;
	case 6:
/* #line 118 "parser/parser_sosi_line.rl" */
	{ mPendingSosiValue += (*p); }
	break;
	case 7:
/* #line 120 "parser/parser_sosi_line.rl" */
	{ appendFieldChar( "id", (*p) ); }
	break;
	case 8:
/* #line 122 "parser/parser_sosi_line.rl" */
	{ clearPending(); }
	break;
	case 9:
/* #line 126 "parser/parser_sosi_line.rl" */
	{ mPendingSosiValue += (*p); }
	break;
	case 10:
/* #line 138 "parser/parser_sosi_line.rl" */
	{ p--; {cs = 12; goto _again;} }
	break;
/* #line 355 "parser_sosi_line.cpp" */
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _parseSosiLine_actions + _parseSosiLine_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 4:
/* #line 107 "parser/parser_sosi_line.rl" */
	{
            if( mCurrentElement ) {
                mCurrentElement->set( mPendingSosiElementName, mPendingSosiValue );
            }
            mPendingSosiValue = "";
        }
	break;
/* #line 380 "parser_sosi_line.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 147 "parser/parser_sosi_line.rl" */


};