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
#include "byte_order.h"

// Initialize endianness variable
enum sosicon::byteOrder::Endianness sosicon::byteOrder::endianness = not_set;

sosicon::byteOrder::Endianness sosicon::byteOrder::
determine() {
    if( not_set == endianness ) {
        union {
            uint32_t i;
            char b[ 4 ];
        } test = { 0x01000000 };
        endianness = test.b[ 0 ] == 1 ? big : little;
    }
    return endianness;
}

void sosicon::byteOrder::
toBigEndian( const char* from, char* to, size_t bufSize ) {
    std::copy( from,
               from + bufSize,
               to );
    if( determine() == little ) {
        std::reverse( to, to + bufSize );
    }
}

void sosicon::byteOrder::
toLittleEndian( const char* from, char* to, size_t bufSize ) {
    std::copy( from,
               from + bufSize,
               to );
    if( determine() == big ) {
        std::reverse( to, to + bufSize );
    }
}

