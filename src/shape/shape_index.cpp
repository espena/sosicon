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
#include "shape_index.h"

sosicon::shape::ShapeIndex::
ShapeIndex( IShapeHeader* header ) {
    mHeader = header;
    mOffset = ( mHeader->getWordSize() );
}

sosicon::shape::ShapeIndex::
~ShapeIndex() { }

void sosicon::shape::ShapeIndex::
append( IShapeElement* e ) {
    Record rec;
    rec.offset.i = mOffset;
    rec.length.i = e->getByteSize();
    mRecords.push_back( rec );
    mOffset += ( e->getWordSize() );
}

void sosicon::shape::ShapeIndex::
writeBinary( std::ostream& os ) {
    int fileWordLength = mHeader->getWordSize() + mRecords.size() * ( sizeof( Record ) / 2 );
    mHeader->setFileLength( fileWordLength );
    os << *mHeader;
    for( std::vector<Record>::iterator i = mRecords.begin(); i != mRecords.end(); i++ ) {
        char buffer[ 8 ];
        byteOrder::toBigEndian( ( *i ).offset.b, &buffer[ 0 ], 4 );
        byteOrder::toBigEndian( ( *i ).length.b, &buffer[ 4 ], 4 );
        os.write( buffer, sizeof( buffer ) );
    }
}