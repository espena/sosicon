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
#include <sstream>
#include "interface/i_coordinate.h"

namespace sosicon {

    //! Coordinate container
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Stores a geographical position with some additional information.
     */
    class Coordinate : public ICoordinate {

        int mEast;
        int mNorth;

    public:

        virtual ~Coordinate() { };
        virtual void setE( std::string coordEast ) { std::stringstream ss; ss << coordEast; ss >> mEast; };
        virtual void setN( std::string coordNorth ) { std::stringstream ss; ss << coordNorth; ss >> mNorth; };
        virtual void shift( int offsetN, int offsetE ) { mNorth += offsetN; mEast += offsetE; };
        virtual std::string toString() { std::stringstream ss; ss << "POINT( " << mNorth << " " << mEast << " )"; return ss.str(); };

    }; // class Coordinate
    
}; // namespece sosicon

#endif
