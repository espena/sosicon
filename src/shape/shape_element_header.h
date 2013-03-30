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
#ifndef __SHAPE_ELEMENT_HEADER_H__
#define __SHAPE_ELEMENT_HEADER_H__

#include <iostream>
#include "shapefile_types.h"
#include "../byte_order.h"
#include "../interface/i_shape_element_header.h"

namespace sosicon {
    
    namespace shape {

        //! Shapefile record header
        /*!
            The header for each shapefile record stores the record number and content length for the
            record. The header have a fixed length of 8 bytes when serialized.
         */
    	class ShapeElementHeader : public IShapeElementHeader {
        
            //! Record counter
            /*!
                Static record counter, keeps track of current record number and initilizes the
                mRecordNumber member on class instatiation.
                Call ResetRecordCounter() to restart at 1.
                \sa ResetRecordCounter()
             */
            static int mRecordCounter;
        
            //! Serial number
            /*!
                Number in sequence for for current record. Starts at 1 and counts upward.
             */
            Int32Field mRecordNumber;
        
            //! Length of record contents
            /*!
                The content length for a record is the length of the record contents section measured
                in 16-bit words. Each record, therefore, contributes ( 4 + content length ) 16-bit
                words toward the total length of the file, as stored at Byte 24 in the file header.
             */
            Int32Field mContentLength;
        
        public:

            //! Constructor
            /*!
                Sets mRecordNumber to current sequence number.
             */
            ShapeElementHeader();

            //! Set length of record contents
            /*!
                Updates the record content length.
                \param contentLength Length of record content.
             */
            void setContentLength( uint32_t contentLength );

            //! Reset record counter
            /*!
                Resets internal record counter to 0, restarting the record number sequence.
             */
            static void resetRecordCounter() { mRecordCounter = 0; }
        
            // Described in IBinaryStreamable
            virtual void writeBinary( std::ostream &os );

    	};
        
    }; // namespace shape

}; // namespace sosicon

#endif