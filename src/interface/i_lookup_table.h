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
#ifndef __I_LOOKUP_TABLE_H__
#define __I_LOOKUP_TABLE_H__

#include <string>

namespace sosicon {
    /*!
        \addtogroup interfaces Interfaces
        This is a listing of generic interfaces used within sosicon.
        @{
    */

    //! Forward declaration
    class ISosiElement;

    //! Interface: Lookup table
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Interface to a lookup table, implemented by ReferenceLookup class.
    */
    class ILookupTable {
    public:

        //! Destructor
        virtual ~ILookupTable(){ };

        //! Print string representation of current table
        virtual std::string toString() = 0;

        //! Get SOSI element by ref ID
        virtual ISosiElement* get( std::string key ) = 0;

    };
   /*! @} end group interfaces */

}; // namespace sosicon

#endif