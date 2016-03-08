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
#include "sosi_charset_singleton.h"

sosicon::sosi::SosiCharsetSingleton* sosicon::sosi::SosiCharsetSingleton::mInstance = 0;

sosicon::sosi::SosiCharsetSingleton::
SosiCharsetSingleton() {
    mCharset = sosi_charset_undetermined;
    mSosiElement = 0;
    mInitialized = false;
}

void sosicon::sosi::SosiCharsetSingleton::
init( ISosiElement* sosiElement ) {
    mSosiElement = sosiElement;
    mCharsetName = sosiElement->getData();
    mInitialized = true;
         if( "ANSI"       == mCharsetName ) mCharset = sosi_charset_ansi;
    else if( "DECN7"      == mCharsetName ) mCharset = sosi_charset_decn7;
    else if( "DOSN8"      == mCharsetName ) mCharset = sosi_charset_dosn8;
    else if( "ISO8859-1"  == mCharsetName ) mCharset = sosi_charset_iso8859_1;
    else if( "ISO8859-10" == mCharsetName ) mCharset = sosi_charset_iso8859_10;
    else if( "ND7"        == mCharsetName ) mCharset = sosi_charset_nd7;
    else                                    mCharset = sosi_charset_iso8859_1;
}

std::string sosicon::sosi::SosiCharsetSingleton::
toIso8859_1( const std::string& str ) {
    unsigned char const* contable;
    switch( mCharset ) {
        case sosi_charset_ansi:
        case sosi_charset_iso8859_1:
        case sosi_charset_iso8859_10:
            return str; // No conversion
        case sosi_charset_decn7:
            contable = chartables::DECN7_TO_ISO8859_1;
            break;
        case sosi_charset_dosn8:
            contable = chartables::DOSN8_TO_ISO8859_1;
            break;
        case sosi_charset_nd7:
            contable = chartables::ND7_TO_ISO8859_1;
            break;
        default:
            return str; // Unknown charset, no conversion
    }
    std::string res = "";
    std::string::size_type len = str.length();
    for( std::string::size_type i = 0; i < len; i++ ) {
        res += static_cast<char>( contable[ static_cast<unsigned char>( str.at( i ) ) ] );
    }
    return res;
}