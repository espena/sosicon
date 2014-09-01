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
#include "utils.h"

using std::string;

string sosicon::utils::
className2FileName( const std::string &className )
{
    string clsL = toLower( className );
    string res = "";
    string::size_type len = className.length();
    for( string::size_type i = 0; i < len; i++ )
    {
        if( i > 0 &&                                        // 1) Not first character?
            className.at( i ) != clsL.at( i ) &&            // 2) Uppercase letter?
            ( i + 1 ) < len &&                              // 3) Not last character in class name?
            ( className.at( i + 1 ) == clsL.at( i + 1 ) ||  // 4) Following character is lower case
              className.at( i - 1 ) == clsL.at( i - 1 ) ) ) //    _OR_ previous character is lower case? 
        {
            res += "_";                                     // Then: Separate words with underscore
        }
        res += clsL.at( i );
    }
    return res;
}

std::vector<std::string> sosicon::utils::
explode( char delimiter, std::string str ) {
    const std::string::size_type len = str.length();
    std::string val;
    std::vector<std::string> lst;
    if( len > 0 ) {
        std::string::size_type j = 0, k = 0;
        for( k = 0; k < len; k++ ) {
            if( str.at( k ) == delimiter ) {
                if( !( val = utils::trim( str.substr( j, k - j ) ) ).empty() ) {
                    lst.push_back( val );
                }
                j = k + 1;
            }
        }
        if( !( val = utils::trim( str.substr( j, k - j ) ) ).empty() ) {
            lst.push_back( val );
        }
    }
    return lst;
}

string sosicon::utils::
normalizeAppClassName( const std::string &className )
{
    string clsL = toLower( className );
    string res = "";
    string::size_type len = className.length();
    for( string::size_type i = clsL.find( "app" ) == 0 ? 3 : 0; i < len; i++  )
    {
        if( res == "" )
        {
            res = toupper( className.at( i ) );
        }
        else
        {
            res += className.at( i );
        }
    }
    return res;
}

string sosicon::utils::
repeat( const std::string &seq, unsigned int count )
{
    std::string s;
    for( unsigned int i = 0; i < count; i ++ )
    {
        s.append( seq );
    }
    return s;
}

string sosicon::utils::
replaceAll( const std::string &from, const std::string &to, const std::string &subject )
{
    string res = subject;
    string::size_type lh = 0;
    string::size_type fh;
    while( ( fh = res.find( from, lh ) ) != string::npos )
    {
      res.replace( fh, from.size(), to );
      lh = fh + to.size();
    }
    return res;
}

string sosicon::utils::
toLower( const std::string &str )
{
    static std::locale loc = std::locale( "no_NO" );
    string::size_type n = str.length();
    const char* from = str.c_str();
    char* to = new char[ n + 1 ];
    for( string::size_type i = 0; i < n; i++ )
    {
        to[ i ] = tolower( from[ i ], loc );
    }
    to[ n ] = '\0';
    string res = to;
    delete[] to;
    return res;
}

string sosicon::utils::
trim( const std::string &str )
{
    return trimLeft( trimRight( str ) );
}

string sosicon::utils::
trimLeft( const std::string &str )
{
    string trm = str;
    return trm.erase( 0, trm.find_first_not_of( " \t\r\n" ) );
}

string sosicon::utils::
trimRight( const std::string &str )
{
    string trm = str;
    string::size_type i = trm.find_last_not_of( " \t\r\n" );
    return i == string::npos ? "" : trm.erase( i + 1 );
}

string sosicon::utils::
ucFirst( const std::string &str )
{
    const string::size_type len = str.length();
    string res;
    if( len > 0 )
    {
        char *buf = new char[ len + 1 ];
        if( buf )
        {
            memcpy( buf, str.c_str(), len );
            buf[ len ] = '\0';
            buf[ 0 ] = toupper( buf[ 0 ] );
            res = buf;
            delete[] buf;
        }
    }
    return res;
}

void sosicon::utils::
getPathInfo( std::string path, std::string &dir, std::string &tit, std::string &ext ) {
	std::string::size_type len = path.length();
	std::string tmp;
	while( len > 0 ) {
		const char c = path.at( --len );
		switch( c ) {
			case '.':
				tmp = ( c + tmp );
				if( ext.empty() ) {
					ext = tmp;
					tmp = "";
				}
				break;
			case '\\':
			case '/':
				if( tit.empty() ) {
					tit = tmp;
					tmp = c;
				}
				else {
					tmp = ( c + tmp );
				}
				break;
			default:
				tmp = ( c + tmp );
				break;
		}
	}
	if( tit.empty() ) {
		tit = tmp;
	}
	else {
		dir = tmp;
	}
}