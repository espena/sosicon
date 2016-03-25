
/* #line 1 "ragel/sosi_north_east_height.rl" */
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
#include "sosi/sosi_north_east.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    
/* #line 28 "sosi_north_east_height_ragel.cpp" */
static const char _parseCoordinateCollection_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 2, 3, 4, 2, 4, 
	0, 3, 3, 4, 0
};

static const char _parseCoordinateCollection_key_offsets[] = {
	0, 0, 2, 5, 8, 10, 13, 16, 
	18, 24, 32
};

static const char _parseCoordinateCollection_trans_keys[] = {
	48, 57, 32, 48, 57, 45, 48, 57, 
	48, 57, 32, 48, 57, 45, 48, 57, 
	48, 57, 32, 45, 9, 13, 48, 57, 
	13, 45, 9, 10, 32, 33, 48, 57, 
	13, 45, 9, 10, 32, 33, 48, 57, 
	0
};

static const char _parseCoordinateCollection_single_lengths[] = {
	0, 0, 1, 1, 0, 1, 1, 0, 
	2, 2, 2
};

static const char _parseCoordinateCollection_range_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	2, 3, 3
};

static const char _parseCoordinateCollection_index_offsets[] = {
	0, 0, 2, 5, 8, 10, 13, 16, 
	18, 23, 29
};

static const char _parseCoordinateCollection_indicies[] = {
	0, 1, 2, 0, 1, 3, 4, 1, 
	4, 1, 5, 4, 1, 6, 7, 1, 
	7, 1, 8, 9, 8, 0, 1, 10, 
	11, 10, 10, 7, 1, 12, 13, 12, 
	12, 14, 1, 0
};

static const char _parseCoordinateCollection_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 9, 
	8, 1, 10, 1, 10, 1, 2
};

static const char _parseCoordinateCollection_trans_actions[] = {
	1, 0, 3, 1, 1, 5, 1, 1, 
	0, 1, 7, 17, 0, 14, 14
};

static const char _parseCoordinateCollection_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 11, 9
};

static const int parseCoordinateCollection_start = 8;
static const int parseCoordinateCollection_first_final = 8;
static const int parseCoordinateCollection_error = 0;

static const int parseCoordinateCollection_en_main = 8;


/* #line 27 "ragel/sosi_north_east_height.rl" */

    //! \endcond

}

void sosicon::sosi::SosiNorthEast::
ragelParseCoordinatesNeh( std::string data )
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
    std::string coordH;

    
/* #line 121 "sosi_north_east_height_ragel.cpp" */
	{
	cs = parseCoordinateCollection_start;
	}

/* #line 126 "sosi_north_east_height_ragel.cpp" */
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
	_keys = _parseCoordinateCollection_trans_keys + _parseCoordinateCollection_key_offsets[cs];
	_trans = _parseCoordinateCollection_index_offsets[cs];

	_klen = _parseCoordinateCollection_single_lengths[cs];
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
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _parseCoordinateCollection_range_lengths[cs];
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
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _parseCoordinateCollection_indicies[_trans];
	cs = _parseCoordinateCollection_trans_targs[_trans];

	if ( _parseCoordinateCollection_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parseCoordinateCollection_actions + _parseCoordinateCollection_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 54 "ragel/sosi_north_east_height.rl" */
	{
            tmp += (*p);
        }
	break;
	case 1:
/* #line 58 "ragel/sosi_north_east_height.rl" */
	{
            coordN = tmp;
            tmp = "";
        }
	break;
	case 2:
/* #line 63 "ragel/sosi_north_east_height.rl" */
	{
            coordE = tmp;
            tmp = "";
        }
	break;
	case 3:
/* #line 68 "ragel/sosi_north_east_height.rl" */
	{
            coordH = tmp;
            tmp = "";
        }
	break;
	case 4:
/* #line 73 "ragel/sosi_north_east_height.rl" */
	{
            append( coordN, coordE );
        }
	break;
/* #line 233 "sosi_north_east_height_ragel.cpp" */
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
	const char *__acts = _parseCoordinateCollection_actions + _parseCoordinateCollection_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 3:
/* #line 68 "ragel/sosi_north_east_height.rl" */
	{
            coordH = tmp;
            tmp = "";
        }
	break;
	case 4:
/* #line 73 "ragel/sosi_north_east_height.rl" */
	{
            append( coordN, coordE );
        }
	break;
/* #line 262 "sosi_north_east_height_ragel.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 84 "ragel/sosi_north_east_height.rl" */


};