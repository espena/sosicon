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

bool sosicon::utils::
isNumeric( const std::string& str ) {
    const std::string::size_type len = str.length();
    const std::string tmp = trim( str );
    const char* sz = tmp.c_str();
    if( sz[ 0 ] == '0' ) {
        return false;
    }
    for( std::string::size_type i = 0; i < len; i++ ) {
        std::locale loc;
        if( !std::isdigit( sz[ i ], loc ) ) {
            return false;
        }
    }
    return true;
}

void sosicon::utils::
asciify( char* str ) {
    static unsigned char const transcodingTable[ 256 ] = {
//      0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
/* 0 */ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
/* 1 */ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
/* 2 */ 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
/* 3 */ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
/* 4 */ 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
/* 5 */ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
/* 6 */ 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
/* 7 */ 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
/* 8 */ 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
/* 9 */ 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
/* A */ 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f,
/* B */ 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f,
/* C */ 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x45, 0x43, 0x45, 0x45, 0x45, 0x45, 0x49, 0x49, 0x49, 0x49,
/* D */ 0x44, 0x4e, 0x4f, 0x4f, 0x4f, 0x4f, 0x4f, 0x58, 0x4f, 0x55, 0x55, 0x55, 0x55, 0x59, 0x59, 0x42,
/* E */ 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x65, 0x63, 0x65, 0x65, 0x65, 0x65, 0x69, 0x69, 0x69, 0x69,
/* F */ 0x6f, 0x6e, 0x6f, 0x6f, 0x6f, 0x6f, 0x6f, 0x2f, 0x6f, 0x75, 0x75, 0x75, 0x75, 0x79, 0x79, 0x79 };
    std::string::size_type i = 0;
    while( *( str + i ) != '\0' ) {
        *( str + i ) = transcodingTable[ static_cast<const unsigned char&> ( *( str + i ) ) ];
        i++;
    }
}

std::string sosicon::utils::
nonExistingFilename( std::string defaultName ) {

    std::string candidatePath = defaultName;
    std::string dir, tit, ext;

    getPathInfo( candidatePath, dir, tit, ext );

    candidatePath = dir + tit + ext;
    int sequence = 0;

    while( fileExists( candidatePath ) )
    {
        std::stringstream ss;
        ss << dir << tit << "_" << std::setw( 2 ) << std::setfill( '0' ) << ++sequence << ".sql";
        candidatePath = ss.str();
    }

    return candidatePath;
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
purgeCrLf( string str ) {
    str.erase( std::remove( str.begin(), str.end(), '\r' ), str.end() );
    str.erase( std::remove( str.begin(), str.end(), '\n' ), str.end() );
    return str;
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
sqlNormalize( const std::string &str )
{
    std::string tmp = trim( str );
    std::string res;
    std::string::size_type len = tmp.length();
    if( len > 2 && tmp.at( 0 ) == '\"' && tmp.at( len - 1 ) == '\"' ) {
        tmp = tmp.substr( 1, len - 2 );
    }
    for( std::string::size_type n = 0; n < tmp.length(); n++ ) {
        char c = tmp.at( n );
        switch( c ) {
            case '\"':
            case '\'':
            case '\\':
                res += '\\' + c;
                break;
            default:
                res += c;
        }
    }
    return res;
}

string sosicon::utils::
toFieldname( const std::string &str )
{
    std::string res, tmp = toLower( str );
    for( std::string::size_type i = 0; i < tmp.length(); i++ ) {
        char c = tmp.at( i );
        /* If toLower() operates on a non-nordic default locale,
           it will fail to convert nordic uppercase characters to lowercase.
           Hence we include character codes for uppercase ÆØÅ as well */
        switch( c ) {
            case '\xC6':
            case '\xE6':
                res += "ae";
                break;
            case '\xD8':
            case '\xF8':
                res += "oe";
                break;
            case '\xC5':
            case '\xE5':
                res += "aa";
                break;
            case '-':
                res += "_";
                break;
            default:
                res += c;
        }
    }
    if( res.length() > 63 ) {
        // Default size limit for PostgreSQL labels is 63 bytes
        res = res.substr( 0, 63 );
    }
    return res;
}

string sosicon::utils::
toLower( const std::string &str )
{
    static std::locale loc = std::locale( "" );
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

string sosicon::utils::
stripTrailingSlash( const std::string &str )
{
    string res = trim( str );
    if( !res.empty() ) {
        const std::string::size_type len = res.length();
        if( len > 0 && ( res.at( len - 1 ) == '\"' || res.at( len - 1 ) == '\\' ) ) {
            res = res.substr( 0, len - 1 );
        }
    }
    return res;
}

string sosicon::utils::
unquote( const std::string &str )
{
    string res = trim( str );
    if( !res.empty() ) {
        if( res.at( 0 ) == '\"' ) {
            res = res.substr( 1 );
        }
        const std::string::size_type len = res.length();
        if( len > 0 && res.at( len - 1 ) == '\"' ) {
            res = res.substr( 0, len - 1 );
        }
    }
    return res;
}

void sosicon::utils::
getPathInfo( std::string path, std::string &dir, std::string &tit, std::string &ext ) {
    dir = tit = ext = "";
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


std::string sosicon::utils::
wktToStr( Wkt wktGeom ) {

    switch( wktGeom ) {
        case wkt_point:
            return "POINT";
        case wkt_linestring:
            return "LINESTRING";
        case wkt_polygon:
            return "POLYGON";
        default:
            return "";
    }
}
