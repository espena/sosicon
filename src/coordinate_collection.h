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
#ifndef __COORDINATE_COLLECTION_H__
#define __COORDINATE_COLLECTION_H__

#include <vector>
#include <iostream>
#include "sosi/sosi_ref.h"
#include "interface/i_coordinate.h"
#include "interface/i_sosi_element.h"

namespace sosicon {

    //! Coordinate container
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Stores a collection of geographical positions.
     */
    class CoordinateCollection {

        //! Stores collection of pointers to coordinates
        std::vector<ICoordinate*> mCoordinates;

    public:
        void discoverCoords( ISosiElement* sosi );

    }; // class Coordinate
    
}; // namespece sosicon

#endif
