
/* #line 1 "ragel/sosi_origo_ne.rl" */
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
    
/* #line 28 "sosi_origo_ne_ragel.cpp" */
static const char _parseSosiOrigoNE_actions[] = {
	0, 1, 0, 1, 1, 1, 2
};

static const char _parseSosiOrigoNE_key_offsets[] = {
	0, 0, 7, 14, 21, 25, 25
};

static const char _parseSosiOrigoNE_trans_keys[] = {
	32, 43, 45, 9, 13, 48, 57, 32, 
	43, 45, 9, 13, 48, 57, 32, 43, 
	45, 9, 13, 48, 57, 43, 45, 48, 
	57, 43, 45, 48, 57, 0
};

static const char _parseSosiOrigoNE_single_lengths[] = {
	0, 3, 3, 3, 2, 0, 2
};

static const char _parseSosiOrigoNE_range_lengths[] = {
	0, 2, 2, 2, 1, 0, 1
};

static const char _parseSosiOrigoNE_index_offsets[] = {
	0, 0, 6, 12, 18, 22, 23
};

static const char _parseSosiOrigoNE_indicies[] = {
	0, 2, 2, 0, 2, 1, 3, 2, 
	2, 3, 2, 1, 3, 4, 4, 3, 
	4, 1, 6, 6, 4, 5, 1, 6, 
	6, 4, 5, 0
};

static const char _parseSosiOrigoNE_trans_targs[] = {
	1, 0, 2, 3, 4, 5, 6
};

static const char _parseSosiOrigoNE_trans_actions[] = {
	0, 0, 1, 0, 3, 0, 3
};

static const char _parseSosiOrigoNE_eof_actions[] = {
	0, 0, 0, 0, 0, 5, 5
};

static const int parseSosiOrigoNE_start = 1;
static const int parseSosiOrigoNE_first_final = 5;
static const int parseSosiOrigoNE_error = 0;

static const int parseSosiOrigoNE_en_main = 1;


/* #line 27 "ragel/sosi_origo_ne.rl" */

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

    
/* #line 108 "sosi_origo_ne_ragel.cpp" */
	{
	cs = parseSosiOrigoNE_start;
	}

/* #line 113 "sosi_origo_ne_ragel.cpp" */
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
	_keys = _parseSosiOrigoNE_trans_keys + _parseSosiOrigoNE_key_offsets[cs];
	_trans = _parseSosiOrigoNE_index_offsets[cs];

	_klen = _parseSosiOrigoNE_single_lengths[cs];
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

	_klen = _parseSosiOrigoNE_range_lengths[cs];
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
	_trans = _parseSosiOrigoNE_indicies[_trans];
	cs = _parseSosiOrigoNE_trans_targs[_trans];

	if ( _parseSosiOrigoNE_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parseSosiOrigoNE_actions + _parseSosiOrigoNE_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 53 "ragel/sosi_origo_ne.rl" */
	{
            n += (*p);
        }
	break;
	case 1:
/* #line 57 "ragel/sosi_origo_ne.rl" */
	{
            e += (*p);
        }
	break;
/* #line 199 "sosi_origo_ne_ragel.cpp" */
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
	const char *__acts = _parseSosiOrigoNE_actions + _parseSosiOrigoNE_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 2:
/* #line 61 "ragel/sosi_origo_ne.rl" */
	{
          std::stringstream ssN, ssE;
            ssN << n;
            ssN >> mOrigoN;
            ssE << e;
            ssE >> mOrigoE;
        }
	break;
/* #line 225 "sosi_origo_ne_ragel.cpp" */
		}
	}
	}

	_out: {}
	}

/* #line 74 "ragel/sosi_origo_ne.rl" */


};