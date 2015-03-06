
/* #line 1 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
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
    
/* #line 2 "D:\\Prosjekter\\sosicon\\src\\sosi_north_east_ragel.cpp" */
static const char _parseCoordinateHeightCollection_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 2, 2, 3, 2, 3, 0, 3, 
	2, 3, 0
};

static const char _parseCoordinateHeightCollection_key_offsets[] = {
	0, 0, 2, 5, 8, 10, 16, 24
};

static const char _parseCoordinateHeightCollection_trans_keys[] = {
	48, 57, 32, 48, 57, 45, 48, 57, 
	48, 57, 32, 45, 9, 13, 48, 57, 
	13, 45, 9, 10, 32, 33, 48, 57, 
	13, 45, 9, 10, 32, 33, 48, 57, 
	0
};

static const char _parseCoordinateHeightCollection_single_lengths[] = {
	0, 0, 1, 1, 0, 2, 2, 2
};

static const char _parseCoordinateHeightCollection_range_lengths[] = {
	0, 1, 1, 1, 1, 2, 3, 3
};

static const char _parseCoordinateHeightCollection_index_offsets[] = {
	0, 0, 2, 5, 8, 10, 15, 21
};

static const char _parseCoordinateHeightCollection_indicies[] = {
	0, 1, 2, 0, 1, 3, 4, 1, 
	4, 1, 5, 6, 5, 0, 1, 7, 
	8, 7, 7, 4, 1, 9, 10, 9, 
	9, 11, 1, 0
};

static const char _parseCoordinateHeightCollection_trans_targs[] = {
	2, 0, 3, 4, 6, 5, 1, 7, 
	1, 7, 1, 2
};

static const char _parseCoordinateHeightCollection_trans_actions[] = {
	1, 0, 3, 1, 1, 0, 1, 5, 
	15, 0, 12, 12
};

static const char _parseCoordinateHeightCollection_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 9, 7
};

static const int parseCoordinateHeightCollection_start = 5;
static const int parseCoordinateHeightCollection_first_final = 5;
static const int parseCoordinateHeightCollection_error = 0;

static const int parseCoordinateHeightCollection_en_main = 5;


/* #line 27 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */

    //! \endcond

}

void sosicon::sosi::SosiNorthEast::
ragelParseCoordinatesNe( std::string data )
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

    
/* #line 59 "D:\\Prosjekter\\sosicon\\src\\sosi_north_east_ragel.cpp" */
	{
	cs = parseCoordinateHeightCollection_start;
	}

/* #line 62 "D:\\Prosjekter\\sosicon\\src\\sosi_north_east_ragel.cpp" */
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
	_keys = _parseCoordinateHeightCollection_trans_keys + _parseCoordinateHeightCollection_key_offsets[cs];
	_trans = _parseCoordinateHeightCollection_index_offsets[cs];

	_klen = _parseCoordinateHeightCollection_single_lengths[cs];
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

	_klen = _parseCoordinateHeightCollection_range_lengths[cs];
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
	_trans = _parseCoordinateHeightCollection_indicies[_trans];
	cs = _parseCoordinateHeightCollection_trans_targs[_trans];

	if ( _parseCoordinateHeightCollection_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parseCoordinateHeightCollection_actions + _parseCoordinateHeightCollection_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 53 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
	{
            tmp += (*p);
        }
	break;
	case 1:
/* #line 57 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
	{
            coordN = tmp;
            tmp = "";
        }
	break;
	case 2:
/* #line 62 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
	{
            coordE = tmp;
            tmp = "";
        }
	break;
	case 3:
/* #line 67 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
	{
            append( coordN, coordE );
        }
	break;
/* #line 157 "D:\\Prosjekter\\sosicon\\src\\sosi_north_east_ragel.cpp" */
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
	const char *__acts = _parseCoordinateHeightCollection_actions + _parseCoordinateHeightCollection_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 2:
/* #line 62 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
	{
            coordE = tmp;
            tmp = "";
        }
	break;
	case 3:
/* #line 67 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */
	{
            append( coordN, coordE );
        }
	break;
/* #line 183 "D:\\Prosjekter\\sosicon\\src\\sosi_north_east_ragel.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 78 "D:\\Prosjekter\\sosicon\\src\\ragel\\sosi_north_east.rl" */


};