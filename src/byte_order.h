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
#ifndef __BYTE_ORDER_H__
#define __BYTE_ORDER_H__

#pragma warning ( disable: 4996 )
#pragma warning ( disable: 4244 )

#include "inttypes.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace sosicon {

    //! Big/low-endian conversions
    namespace byteOrder {

		//! Big/little flag
        extern enum Endianness {
            not_set,
            big,
            little
        } 
        //! Stores system endianness
        endianness;

        //! Determines system endianness
        /*!
            Tests byte-order to see if the program runs on a big endian or a little endian
            architecture. Flags the byteOrder::endian variable.
            \return System endianness.
            \retval Endianness::big Big endian system.
            \retval Endianness::little Little endian system.
         */
        Endianness determine();

        //! Writes little endian representation of double
        /*!
            Serializes double-precision floating point value to IEEE little endian representation
            for binary embedding in files.
            \param from The double value to parse.
            \param to pointer to destination buffer. The buffer must be at least 8 bytes wide, as this
                   is the size of the IEEE 754 format.
         */
        void doubleToLittleEndian( double from, char* to );

        //! Reverses buffer to big endian if required
        /*!
            Copies source buffer to destination buffer. If the program runs on a little-endian
            system, the byte order will be reversed.
            \param from pointer to source buffer.
            \param to pointer to destination buffer. The buffer must be at least as big
                   as the source buffer.
            \param bufSize The number of bytes to copy.
         */
        void toBigEndian( const char* from, char* to, size_t bufSize );

        //! Reverses buffer to little endian if required
        /*!
            Copies source buffer to destination buffer. If the program runs on a big-endian
            system, the byte order will be reversed.
            \param from pointer to source buffer.
            \param to pointer to destination buffer. The buffer must be at least as big
                   as the source buffer.
            \param bufSize The number of bytes to copy.
         */
        void toLittleEndian( const char* from, char* to, size_t bufSize );
    };
};

#endif
