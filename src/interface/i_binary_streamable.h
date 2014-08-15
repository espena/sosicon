/*
 *  This file is part of the command-line tool sosicon.
 *  geomRefCopyright (C) 2014  Espen Andersen, Norwegian Broadcast Corporation (NRK)
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
#ifndef __I_BINARY_STREAMABLE_H__
#define __I_BINARY_STREAMABLE_H__

#include <iostream>

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        @{
    */
    //! Interface: Binary streamable object
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class IBinaryStreamable {
    public:

        //! Destructor
        virtual ~IBinaryStreamable() { };
        
        //! Writes binary data to output stream
        /*!
            Invoked when the operator<< is used to strem to an std::ostream object. Binary write
            operation is performed for current impementation here.
            \param os Target stream object.
         */
        virtual void writeBinary( std::ostream &os ) = 0;
        
    };

    //! Stream output operator
    /*!
        Placed outside any class definitions. Invokes WriteBinary() on the source IBinaryStreamable
        object.
        \param os target stream.
        \param binaryStreamable target object.
        \return The stream object is returned to allow for chaining.
     */
    inline std::ostream& operator<<( std::ostream &os, IBinaryStreamable &binaryStreamable ) {
        binaryStreamable.writeBinary( os );
        return os;
    }

   /*! @} end group interfaces */
}; // namespace sosicon

#endif
