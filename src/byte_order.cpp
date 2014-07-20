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

void sosicon::byteOrder::
doubleToLittleEndian( double from, char* to ) {
    // Using Dieter Lückings solution posted on StackOverflow Dec 8 '13:
    // http://stackoverflow.com/a/20453208
    uint8_t sign = 0;
    uint16_t exponent = 0;
    uint64_t fraction = 0;
    const uint16_t exp_base = 0x03ff;
    double dbl = from;
    if( std::signbit( dbl ) ) {
        sign = 1;
        dbl = -dbl;
    }
    if( std::isinf( dbl ) ) {
        exponent = 0x7ff;
    }
    else if( std::isnan( dbl ) ) {
        exponent = 0x7ff;
        fraction = 0x8000000000000;
    }
    else {
        int e;
        double f = frexp( dbl, &e );
        // Adjust exponent to account for the implicit, leading 1
        exponent = int16_t( e + exp_base - 1 );
        unsigned bits = 0;
        while( f ) {
            f *= 2;
            fraction <<= 1;
            if( 1 <= f ) {
                fraction |= 1;
                f -= 1;
            }
            bits++;
        }
        fraction = ( fraction << ( 53 - bits ) ) & ( ( uint64_t( 1 ) << 52 ) - 1 );
    }
    uint8_t data[ sizeof( double ) ];
    for( unsigned i = 0; i < 6; ++i ) {
        data[ i ] = fraction & 0xff;
        fraction >>= 8;
    }
    data[ 6 ] = ( exponent << 4 ) | fraction;
    data[ 7 ] = ( sign << 7 ) | ( exponent >> 4 );
    double result = * ( double* ) &data;
    if( result != from && ( std::isnan( from ) != std::isnan( result ) ) ) {
        std::reverse( data, data + sizeof( double ) );
    }
    std::copy( data, data + sizeof( double ), to );
}

