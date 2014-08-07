
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
#include "sosi/sosi_ref_list.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    
/* #line 28 "sosi_ref_ragel.cpp" */
static const char _parseSosiRef_actions[] = {
	0, 1, 1, 1, 2, 1, 3, 2, 
	0, 1, 2, 4, 5, 3, 4, 0, 
	1
};

static const char _parseSosiRef_key_offsets[] = {
	0, 0, 5, 9, 12, 14, 22, 28
};

static const char _parseSosiRef_trans_keys[] = {
	32, 40, 58, 9, 13, 32, 58, 9, 
	13, 45, 48, 57, 48, 57, 32, 40, 
	41, 58, 9, 13, 48, 57, 32, 40, 
	41, 58, 9, 13, 32, 40, 58, 9, 
	13, 0
};

static const char _parseSosiRef_single_lengths[] = {
	0, 3, 2, 1, 0, 4, 4, 3
};

static const char _parseSosiRef_range_lengths[] = {
	0, 1, 1, 1, 1, 2, 1, 1
};

static const char _parseSosiRef_index_offsets[] = {
	0, 0, 5, 9, 12, 14, 21, 27
};

static const char _parseSosiRef_indicies[] = {
	0, 2, 3, 0, 1, 4, 3, 4, 
	1, 5, 6, 1, 7, 1, 8, 2, 
	9, 3, 8, 10, 1, 8, 2, 9, 
	3, 8, 1, 11, 2, 3, 11, 1, 
	0
};

static const char _parseSosiRef_trans_targs[] = {
	1, 0, 2, 3, 2, 4, 5, 5, 
	6, 7, 5, 7
};

static const char _parseSosiRef_trans_actions[] = {
	0, 0, 3, 0, 0, 10, 13, 7, 
	0, 5, 1, 0
};

static const int parseSosiRef_start = 1;
static const int parseSosiRef_first_final = 5;
static const int parseSosiRef_error = 0;

static const int parseSosiRef_en_main = 1;


/* #line 27 "ragel/sosi_ref.rl" */

    //! \endcond

}

void sosicon::sosi::SosiRefList::
ragelParseSosiRef( std::string data )
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
    std::string tmpstr;
    Reference* ref = 0;
    bool reverse = false;
    bool subtract = false;
	SosiReferenceList* refList = 0;

    
/* #line 111 "sosi_ref_ragel.cpp" */
	{
	cs = parseSosiRef_start;
	}

/* #line 116 "sosi_ref_ragel.cpp" */
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
				_trans += (unsigned int)(_mid - _keys);
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
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _parseSosiRef_indicies[_trans];
	cs = _parseSosiRef_trans_targs[_trans];

	if ( _parseSosiRef_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _parseSosiRef_actions + _parseSosiRef_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 54 "ragel/sosi_ref.rl" */
	{
            ref = new Reference();
            ref->reverse = reverse;
            ref->subtract = subtract;
			if( 0 == refList ) {
				refList = new SosiReferenceList();
				mRefListCollection.push_back( refList );
			}
            refList->insert( refList->begin(), ref );
        }
	break;
	case 1:
/* #line 65 "ragel/sosi_ref.rl" */
	{
            ref->serial += (*p);
        }
	break;
	case 2:
/* #line 69 "ragel/sosi_ref.rl" */
	{
			subtract = ( (*p) == '(' );
			refList = new SosiReferenceList();
			mRefListCollection.push_back( refList );
		}
	break;
	case 3:
/* #line 75 "ragel/sosi_ref.rl" */
	{
			subtract = ( (*p) == ')' );
			refList = 0;
		}
	break;
	case 4:
/* #line 82 "ragel/sosi_ref.rl" */
	{ reverse = false; }
	break;
	case 5:
/* #line 82 "ragel/sosi_ref.rl" */
	{ reverse = true; }
	break;
/* #line 232 "sosi_ref_ragel.cpp" */
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

/* #line 90 "ragel/sosi_ref.rl" */


};