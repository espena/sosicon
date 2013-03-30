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
#include "shape_element_header.h"

// Static member initialization
int sosicon::shape::ShapeElementHeader::mRecordCounter = 0;

sosicon::shape::ShapeElementHeader::
ShapeElementHeader() {
    mRecordNumber.i = ++mRecordCounter;
}

void sosicon::shape::ShapeElementHeader::
setContentLength( uint32_t contentLength ) {
    mContentLength.i = contentLength;
}

void sosicon::shape::ShapeElementHeader::
writeBinary( std::ostream &os ) {
    char header[ 8 ] = { 0x00 };
    byteOrder::toBigEndian( mRecordNumber.b,  header,     4 );
    byteOrder::toBigEndian( mContentLength.b, header + 4, 4 );
    os.write( header, sizeof( header ) );
}