
/* #line 1 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
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
#include "parser.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    
/* #line 2 "D:\\Prosjekter\\sosicon\\src\\parser_ragel.cpp" */
static const char _parseSosiLine_actions[] = {
	0, 1, 0, 1, 2, 1, 4, 1, 
	5, 1, 6, 2, 0, 1, 2, 0, 
	4, 2, 1, 0, 2, 1, 5, 2, 
	1, 6, 2, 2, 0, 2, 4, 0, 
	2, 4, 5, 2, 8, 5, 3, 0, 
	4, 1, 3, 4, 1, 0, 3, 4, 
	1, 5, 3, 4, 8, 5, 3, 7, 
	1, 0, 3, 9, 3, 2, 4, 4, 
	9, 3, 2, 4, 6, 9, 3, 2, 
	5, 1, 0, 9, 3, 2, 5, 1, 
	6, 9, 3, 2, 5, 4, 0, 9, 
	3, 2, 6, 4, 1, 0, 9, 3, 
	2
};

static const char _parseSosiLine_key_offsets[] = {
	0, 0, 4, 7, 12, 20, 26, 29, 
	31, 33, 39, 47, 53, 59, 67, 76, 
	85, 94
};

static const char _parseSosiLine_trans_keys[] = {
	10, 13, 32, 46, 10, 13, 33, 10, 
	13, 32, 33, 46, 9, 10, 13, 32, 
	33, 58, 48, 57, 9, 10, 13, 32, 
	33, 58, 10, 13, 33, 33, 46, 33, 
	46, 9, 10, 13, 32, 33, 46, 9, 
	10, 13, 32, 33, 46, 48, 57, 9, 
	10, 13, 32, 33, 46, 13, 46, 9, 
	10, 32, 33, 9, 10, 13, 32, 33, 
	46, 48, 57, 9, 10, 13, 32, 33, 
	46, 58, 48, 57, 9, 10, 13, 32, 
	33, 46, 58, 48, 57, 9, 10, 13, 
	32, 33, 46, 58, 48, 57, 9, 10, 
	13, 32, 33, 46, 0
};

static const char _parseSosiLine_single_lengths[] = {
	0, 4, 3, 5, 6, 6, 3, 2, 
	2, 6, 6, 6, 2, 6, 7, 7, 
	7, 6
};

static const char _parseSosiLine_range_lengths[] = {
	0, 0, 0, 0, 1, 0, 0, 0, 
	0, 0, 1, 0, 2, 1, 1, 1, 
	1, 0
};

static const char _parseSosiLine_index_offsets[] = {
	0, 0, 5, 9, 15, 23, 30, 34, 
	37, 40, 47, 55, 62, 67, 75, 84, 
	93, 102
};

static const char _parseSosiLine_indicies[] = {
	1, 1, 1, 2, 0, 4, 4, 1, 
	3, 4, 4, 3, 0, 6, 5, 7, 
	4, 4, 7, 1, 9, 8, 3, 7, 
	4, 4, 7, 1, 9, 3, 10, 10, 
	1, 3, 1, 12, 11, 1, 14, 13, 
	16, 17, 17, 18, 19, 20, 15, 22, 
	23, 23, 24, 19, 25, 26, 21, 16, 
	28, 28, 29, 19, 30, 27, 31, 32, 
	31, 31, 1, 34, 35, 35, 34, 31, 
	36, 37, 33, 38, 28, 28, 39, 19, 
	30, 41, 40, 27, 42, 23, 23, 43, 
	19, 25, 44, 26, 21, 45, 35, 35, 
	45, 31, 36, 46, 37, 33, 16, 47, 
	47, 29, 19, 30, 27, 0
};

static const char _parseSosiLine_trans_targs[] = {
	9, 0, 1, 2, 12, 11, 3, 5, 
	4, 6, 12, 8, 1, 8, 1, 9, 
	10, 12, 13, 9, 1, 11, 10, 12, 
	13, 3, 14, 11, 12, 13, 3, 12, 
	1, 2, 13, 12, 3, 4, 15, 16, 
	14, 17, 15, 16, 17, 16, 6, 12
};

static const char _parseSosiLine_trans_actions[] = {
	54, 0, 3, 1, 7, 54, 26, 1, 
	1, 1, 35, 17, 78, 1, 67, 1, 
	14, 5, 5, 14, 62, 11, 38, 46, 
	42, 90, 11, 1, 32, 29, 84, 0, 
	58, 17, 17, 20, 72, 17, 14, 29, 
	1, 1, 38, 42, 11, 17, 11, 50
};

static const char _parseSosiLine_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 23, 
	9, 5, 5, 5, 0, 0, 5, 5, 
	0, 5
};

static const int parseSosiLine_start = 7;
static const int parseSosiLine_first_final = 7;
static const int parseSosiLine_error = 0;

static const int parseSosiLine_en_main = 7;


/* #line 27 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */

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

    
/* #line 105 "D:\\Prosjekter\\sosicon\\src\\parser_ragel.cpp" */
	{
	cs = parseSosiLine_start;
	}

/* #line 108 "D:\\Prosjekter\\sosicon\\src\\parser_ragel.cpp" */
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
/* #line 55 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            if( '\r' != (*p) ) {
                tmpstr += (*p);
            }
        }
	break;
	case 1:
/* #line 61 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            tmpstr.clear();
        }
	break;
	case 2:
/* #line 65 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            tmpint++;
        }
	break;
	case 3:
/* #line 69 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            tmpint = 0;
        }
	break;
	case 4:
/* #line 73 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementName = sosicon::utils::trim( tmpstr );
        }
	break;
	case 5:
/* #line 77 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementAttributes = sosicon::utils::trim( tmpstr );
            tmpstr.clear();
        }
	break;
	case 6:
/* #line 82 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementAttributes += ( " " + sosicon::utils::trim( tmpstr ) );
            tmpstr.clear();
        }
	break;
	case 7:
/* #line 87 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementLevel = tmpint;
            tmpstr.clear();
        }
	break;
	case 8:
/* #line 92 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementSerial = tmpstr.substr( 0, tmpstr.length() - 1 );
            tmpstr.clear();
        }
	break;
	case 9:
/* #line 97 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            digestPendingElement();
        }
	break;
/* #line 237 "D:\\Prosjekter\\sosicon\\src\\parser_ragel.cpp" */
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
/* #line 61 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            tmpstr.clear();
        }
	break;
	case 4:
/* #line 73 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementName = sosicon::utils::trim( tmpstr );
        }
	break;
	case 6:
/* #line 82 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */
	{
            mPendingElementAttributes += ( " " + sosicon::utils::trim( tmpstr ) );
            tmpstr.clear();
        }
	break;
/* #line 268 "D:\\Prosjekter\\sosicon\\src\\parser_ragel.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 122 "D:\\Prosjekter\\sosicon\\src\\ragel\\parser.rl" */


};