
/* #line 1 "ragel/parser.rl" */
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
    
/* #line 28 "parser_ragel.cpp" */
static const char _parseSosiLine_actions[] = {
	0, 1, 0, 1, 2, 1, 4, 1, 
	5, 1, 6, 2, 1, 0, 2, 1, 
	5, 2, 1, 6, 2, 2, 0, 2, 
	4, 0, 2, 4, 5, 2, 8, 5, 
	3, 7, 1, 0, 3, 9, 3, 2, 
	4, 4, 9, 3, 2, 4, 6, 9, 
	3, 2, 5, 1, 0, 9, 3, 2, 
	5, 1, 6, 9, 3, 2, 5, 4, 
	0, 9, 3, 2
};

static const char _parseSosiLine_key_offsets[] = {
	0, 0, 16, 19, 38, 46, 52, 55, 
	57, 59, 80, 88, 94
};

static const char _parseSosiLine_trans_keys[] = {
	-104, -72, -61, 45, 46, 95, -123, -122, 
	-91, -90, 48, 57, 65, 90, 97, 122, 
	10, 13, 33, -104, -72, -61, 10, 13, 
	33, 45, 46, 95, -123, -122, -91, -90, 
	48, 57, 65, 90, 97, 122, 9, 10, 
	13, 32, 33, 58, 48, 57, 9, 10, 
	13, 32, 33, 58, 10, 13, 33, 33, 
	46, 33, 46, -104, -72, -61, 9, 10, 
	13, 32, 33, 45, 46, 95, -123, -122, 
	-91, -90, 48, 57, 65, 90, 97, 122, 
	9, 10, 13, 32, 33, 46, 48, 57, 
	13, 46, 9, 10, 32, 33, -104, -72, 
	-61, 9, 10, 13, 32, 33, 45, 46, 
	95, -123, -122, -91, -90, 48, 57, 65, 
	90, 97, 122, 0
};

static const char _parseSosiLine_single_lengths[] = {
	0, 6, 3, 9, 6, 6, 3, 2, 
	2, 11, 6, 2, 11
};

static const char _parseSosiLine_range_lengths[] = {
	0, 5, 0, 5, 1, 0, 0, 0, 
	0, 5, 1, 2, 5
};

static const char _parseSosiLine_index_offsets[] = {
	0, 0, 12, 16, 31, 39, 46, 50, 
	53, 56, 73, 81, 86
};

static const char _parseSosiLine_indicies[] = {
	0, 0, 0, 0, 2, 0, 0, 0, 
	0, 0, 0, 1, 4, 4, 1, 3, 
	5, 5, 5, 4, 4, 1, 5, 6, 
	5, 5, 5, 5, 5, 5, 3, 7, 
	4, 4, 7, 1, 9, 8, 3, 7, 
	4, 4, 7, 1, 9, 3, 10, 10, 
	1, 3, 1, 12, 11, 1, 14, 13, 
	15, 15, 15, 16, 17, 17, 16, 17, 
	15, 18, 15, 15, 15, 15, 15, 15, 
	1, 20, 21, 21, 20, 22, 23, 24, 
	19, 22, 25, 22, 22, 1, 26, 26, 
	26, 27, 28, 28, 27, 17, 26, 29, 
	26, 26, 26, 26, 26, 26, 3, 0
};

static const char _parseSosiLine_trans_targs[] = {
	9, 0, 1, 2, 11, 12, 3, 5, 
	4, 6, 11, 8, 1, 8, 1, 9, 
	10, 11, 1, 2, 10, 11, 11, 3, 
	4, 1, 12, 10, 11, 3
};

static const char _parseSosiLine_trans_actions[] = {
	32, 0, 3, 1, 7, 32, 20, 1, 
	1, 1, 29, 11, 56, 1, 45, 1, 
	5, 5, 40, 11, 11, 14, 0, 50, 
	11, 36, 1, 23, 26, 62
};

static const char _parseSosiLine_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 17, 
	9, 5, 0, 0, 5
};

static const int parseSosiLine_start = 7;
static const int parseSosiLine_first_final = 7;
static const int parseSosiLine_error = 0;

static const int parseSosiLine_en_main = 7;


/* #line 27 "ragel/parser.rl" */

    //! \endcond

}

void sosicon::Parser::
parseSosiLine( std::string sosiLine )
{

    sosiLine += "\r\n";

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

    
/* #line 149 "parser_ragel.cpp" */
	{
	cs = parseSosiLine_start;
	}

/* #line 154 "parser_ragel.cpp" */
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
/* #line 55 "ragel/parser.rl" */
	{
            if( '\r' != (*p) ) {
                tmpstr += (*p);
            }
        }
	break;
	case 1:
/* #line 61 "ragel/parser.rl" */
	{
            tmpstr.clear();
        }
	break;
	case 2:
/* #line 65 "ragel/parser.rl" */
	{
            tmpint++;
        }
	break;
	case 3:
/* #line 69 "ragel/parser.rl" */
	{
            tmpint = 0;
        }
	break;
	case 4:
/* #line 73 "ragel/parser.rl" */
	{
            mPendingElementName = tmpstr;
        }
	break;
	case 5:
/* #line 77 "ragel/parser.rl" */
	{
            mPendingElementAttributes = tmpstr;
            tmpstr.clear();
        }
	break;
	case 6:
/* #line 82 "ragel/parser.rl" */
	{
            mPendingElementAttributes += ( " " + sosicon::stringUtils::trim( tmpstr ) );
            tmpstr.clear();
        }
	break;
	case 7:
/* #line 87 "ragel/parser.rl" */
	{
            mPendingElementLevel = tmpint;
            tmpstr.clear();
        }
	break;
	case 8:
/* #line 92 "ragel/parser.rl" */
	{
            mPendingElementSerial = tmpstr.substr( 0, tmpstr.length() - 1 );
            tmpstr.clear();
        }
	break;
	case 9:
/* #line 97 "ragel/parser.rl" */
	{
            digestPendingElement();
        }
	break;
/* #line 294 "parser_ragel.cpp" */
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
/* #line 61 "ragel/parser.rl" */
	{
            tmpstr.clear();
        }
	break;
	case 4:
/* #line 73 "ragel/parser.rl" */
	{
            mPendingElementName = tmpstr;
        }
	break;
	case 6:
/* #line 82 "ragel/parser.rl" */
	{
            mPendingElementAttributes += ( " " + sosicon::stringUtils::trim( tmpstr ) );
            tmpstr.clear();
        }
	break;
/* #line 329 "parser_ragel.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 122 "ragel/parser.rl" */


};