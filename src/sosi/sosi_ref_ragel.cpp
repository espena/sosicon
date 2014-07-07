
/* #line 1 "ragel/sosi_ref.rl" */
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
#include "sosi_ref.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    
/* #line 28 "sosi/sosi_ref_ragel.cpp" */
static const char _parseSosiRef_key_offsets[] = {
	0
};

static const char _parseSosiRef_trans_keys[] = {
	0
};

static const char _parseSosiRef_single_lengths[] = {
	0
};

static const char _parseSosiRef_range_lengths[] = {
	0
};

static const char _parseSosiRef_index_offsets[] = {
	0
};

static const char _parseSosiRef_trans_targs[] = {
	0, 0
};

static const int parseSosiRef_start = 0;
static const int parseSosiRef_first_final = 0;
static const int parseSosiRef_error = -1;

static const int parseSosiRef_en_main = 0;


/* #line 27 "ragel/sosi_ref.rl" */

    //! \endcond

}

void sosicon::sosi::SosiRef::
parseSosiRef( std::string data )
{

 /* Variables used by Ragel */
    int cs = 0;
    int stack[ 1024 ];
    int top = 0;
    int act = 0;
    char* ts = 0;
    char* te = 0;
    const char* s = data.c_str();
    const char* p = s;
    const char* pe = p + data.size();
    const char* eof = pe;

    
/* #line 83 "sosi/sosi_ref_ragel.cpp" */
	{
	cs = parseSosiRef_start;
	}

/* #line 88 "sosi/sosi_ref_ragel.cpp" */
	{
	int _klen;
	unsigned int _trans;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_keys = _parseSosiRef_trans_keys + _parseSosiRef_key_offsets[cs];
	_trans = _parseSosiRef_index_offsets[cs];

	_klen = _parseSosiRef_single_lengths[cs];
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

	_klen = _parseSosiRef_range_lengths[cs];
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
	cs = _parseSosiRef_trans_targs[_trans];

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

/* #line 55 "ragel/sosi_ref.rl" */


};