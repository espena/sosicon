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
#ifndef __ADDRESS_UNIT_H__
#define __ADDRESS_UNIT_H__

#include <string>

namespace sosicon {

    namespace sosi {

        /*!
            \addtogroup gis_entities GIS entities
            Collection of objects representing different aspects of geographical features embedded in
            the SOSI file format.
            @{
        */
        //!  Address usage unit
        /*!
            \author Espen Andersen
            \copyright GNU General Public License

            Represents address usage number. Since an address may consist of several housing units,
            this entitiy identify individual units (apartments or sections) on a given address. The
            address unit number consists of the following fields:
            - Floor level
            - Floor number
            - Door number
        */
        class AddressUnit {

        public:

            //! SOSI Address Unit field
            /*!
                Indicating at what floor level current address unit has its main entry. May be one of
                the following values:
                - "K" = Basement
                - "U" = Below ground level
                - "H" = Over ground level
                - "L" = Attic
            */
            std::string mFloorLevel;

            //! SOSI Address Unit field
            /*!
                Indicating the floor number for current address unit. The number sequence starts
                at 01 for each floor level.
            
                For floor levels over ground level, the lowermost floor is assigned to 01 and higher
                floors get higher numbers.
            
                For floor levels below ground level, the uppermost floor is assigned to 01 and lower
                floors get higher numbers.
            */
            std::string mFloorNumber;

            //! SOSI Address Unit field
            /*!
                Indicating the door number for current address unit. The number sequence starts
                at 01 and increments by one for each door, counting left-to-right.
            */
            std::string mDoorNumber;

            //! Constructor
            AddressUnit();

            //! Destructor
            virtual ~AddressUnit();
        
            std::string toString();

        };
        /*! @} end gis_entities */
    }; // namespace sosi
}; // namespace sosicon

#endif