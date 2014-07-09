/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen
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
#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include <string>
#include "interface/i_coordinate.h"

namespace sosicon {

    //! Coordinate container
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Stores a geographical position with some additional information.
     */
    class Coordinate : public ICoordinate {

        std::string mEast;
        std::string mNorth;

    public:

        virtual ~Coordinate() { };
        virtual void setE( std::string coordEast ) { mEast = coordEast; };
        virtual void setN( std::string coordNorth ) { mNorth = coordNorth; };
        virtual std::string toString() const { return "POINT( " + mNorth + " " + mEast + " )"; };

    }; // class Coordinate
    
}; // namespece sosicon

#endif
