
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
	0, 1, 0, 1, 2, 1, 4, 1, 
	6, 1, 8, 2, 0, 5, 2, 1, 
	0, 2, 1, 6, 2, 2, 0, 2, 
	4, 0, 2, 8, 0, 3, 1, 0, 
	5, 3, 4, 0, 5, 3, 7, 1, 
	0, 3, 8, 0, 5, 3, 9, 3, 
	2, 4, 0, 9, 3, 2, 4, 4, 
	9, 3, 2, 4, 6, 9, 3, 2, 
	5, 1, 0, 9, 3, 2, 5, 1, 
	6, 9, 3, 2, 5, 4, 0, 9, 
	3, 2
};

static const char _parseSosiLine_key_offsets[] = {
	0, 0, 15, 18, 36, 44, 50, 55, 
	57, 59, 79, 87, 93, 99
};

static const char _parseSosiLine_trans_keys[] = {
	-40, -8, 45, 46, 95, -59, -58, -27, 
	-26, 48, 57, 65, 90, 97, 122, 10, 
	13, 33, -40, -8, 10, 13, 33, 45, 
	46, 95, -59, -58, -27, -26, 48, 57, 
	65, 90, 97, 122, 9, 10, 13, 32, 
	33, 58, 48, 57, 9, 10, 13, 32, 
	33, 58, 9, 10, 13, 32, 33, 33, 
	46, 33, 46, -40, -8, 9, 10, 13, 
	32, 33, 45, 46, 95, -59, -58, -27, 
	-26, 48, 57, 65, 90, 97, 122, 9, 
	10, 13, 32, 33, 46, 48, 57, 9, 
	10, 13, 32, 33, 46, 13, 46, 9, 
	10, 32, 33, -40, -8, 9, 10, 13, 
	32, 33, 45, 46, 95, -59, -58, -27, 
	-26, 48, 57, 65, 90, 97, 122, 0
};

static const char _parseSosiLine_single_lengths[] = {
	0, 5, 3, 8, 6, 6, 5, 2, 
	2, 10, 6, 6, 2, 10
};

static const char _parseSosiLine_range_lengths[] = {
	0, 5, 0, 5, 1, 0, 0, 0, 
	0, 5, 1, 0, 2, 5
};

static const char _parseSosiLine_index_offsets[] = {
	0, 0, 11, 15, 29, 37, 44, 50, 
	53, 56, 72, 80, 87, 92
};

static const char _parseSosiLine_indicies[] = {
	0, 0, 0, 2, 0, 0, 0, 0, 
	0, 0, 1, 4, 4, 1, 3, 5, 
	5, 4, 4, 1, 5, 6, 5, 5, 
	5, 5, 5, 5, 3, 7, 4, 4, 
	7, 1, 9, 8, 3, 7, 4, 4, 
	7, 1, 9, 3, 10, 11, 11, 10, 
	12, 3, 1, 14, 13, 1, 16, 15, 
	17, 17, 18, 19, 19, 18, 19, 17, 
	20, 17, 17, 17, 17, 17, 17, 1, 
	22, 23, 23, 22, 24, 25, 26, 21, 
	27, 4, 4, 27, 24, 28, 3, 24, 
	29, 24, 24, 1, 30, 30, 31, 32, 
	32, 31, 19, 30, 33, 30, 30, 30, 
	30, 30, 30, 3, 0
};

static const char _parseSosiLine_trans_targs[] = {
	9, 0, 1, 2, 11, 13, 3, 5, 
	4, 6, 11, 11, 12, 8, 1, 8, 
	1, 9, 10, 12, 1, 2, 10, 11, 
	12, 3, 4, 11, 3, 1, 13, 10, 
	11, 3
};

static const char _parseSosiLine_trans_actions[] = {
	37, 0, 3, 1, 11, 37, 20, 1, 
	1, 1, 26, 41, 9, 14, 70, 1, 
	59, 1, 5, 5, 54, 14, 14, 29, 
	0, 64, 14, 1, 49, 45, 1, 23, 
	33, 76
};

static const char _parseSosiLine_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 17, 
	7, 5, 0, 0, 0, 5
};

static const int parseSosiLine_start = 7;
static const int parseSosiLine_first_final = 7;
static const int parseSosiLine_error = 0;

static const int parseSosiLine_en_main = 7;


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

    std::string tmpstr;
    int tmpint;

    
/* #line 151 "parser_sosi_line.cpp" */
	{
	cs = parseSosiLine_start;
	}

/* #line 156 "parser_sosi_line.cpp" */
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
/* #line 52 "parser/parser_sosi_line.rl" */
	{
            if( '\r' != (*p) )
                tmpstr += (*p);
        }
	break;
	case 1:
/* #line 57 "parser/parser_sosi_line.rl" */
	{
            tmpstr.clear();
        }
	break;
	case 2:
/* #line 61 "parser/parser_sosi_line.rl" */
	{
            tmpint++;
        }
	break;
	case 3:
/* #line 65 "parser/parser_sosi_line.rl" */
	{
            tmpint = 0;
        }
	break;
	case 4:
/* #line 69 "parser/parser_sosi_line.rl" */
	{
            mPendingElementName = tmpstr;
        }
	break;
	case 5:
/* #line 73 "parser/parser_sosi_line.rl" */
	{
            mPendingElementAttributes = tmpstr;
            tmpstr.clear();
        }
	break;
	case 6:
/* #line 78 "parser/parser_sosi_line.rl" */
	{
            mPendingElementAttributes += ( " " + sosicon::stringUtils::trim( tmpstr ) );
            tmpstr.clear();
        }
	break;
	case 7:
/* #line 83 "parser/parser_sosi_line.rl" */
	{
            mPendingElementLevel = tmpint;
            tmpstr.clear();
        }
	break;
	case 8:
/* #line 88 "parser/parser_sosi_line.rl" */
	{
            mPendingElementSerial = tmpstr.substr( 0, tmpstr.length() - 1 );
            tmpstr.clear();
        }
	break;
	case 9:
/* #line 93 "parser/parser_sosi_line.rl" */
	{
            digestPendingElement();
        }
	break;
/* #line 295 "parser_sosi_line.cpp" */
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
	case 1:
/* #line 57 "parser/parser_sosi_line.rl" */
	{
            tmpstr.clear();
        }
	break;
	case 4:
/* #line 69 "parser/parser_sosi_line.rl" */
	{
            mPendingElementName = tmpstr;
        }
	break;
	case 6:
/* #line 78 "parser/parser_sosi_line.rl" */
	{
            mPendingElementAttributes += ( " " + sosicon::stringUtils::trim( tmpstr ) );
            tmpstr.clear();
        }
	break;
/* #line 330 "parser_sosi_line.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 118 "parser/parser_sosi_line.rl" */


};