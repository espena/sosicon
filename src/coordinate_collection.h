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

#include <algorithm>
#include <vector>
#include <iostream>
#include "common_types.h"
#include "sosi/sosi_types.h"
#include "sosi/sosi_element_search.h"
#include "sosi/sosi_ref_list.h"
#include "sosi/sosi_north_east.h"
#include "interface/i_coordinate.h"
#include "interface/i_sosi_element.h"

namespace sosicon {

    typedef std::vector<ICoordinate*> CoordinateList;

    //! Get next coordinate in list
    bool getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::iterator& iterator );
    
    //! Coordinate container
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Stores a collection of geographical positions.
     */
    class CoordinateCollection {

        //! Stores feature's center point, if applicable
        sosi::SosiNorthEast* mCenterPoint;

        //! Stores collection of pointers to coordinates for geometries
        sosi::NorthEastList mGeom;
        sosi::NorthEastList::iterator mGeomIterator;

        //! Stores collection of pointers to coordinates for holes
        sosi::NorthEastList mIslands;
        sosi::NorthEastList::iterator mIslandsIterator;

        //! Get ccordinate values from SOSI element
        void extractPath( sosi::Reference* ref, ISosiElement* referencedElement );

    public:

        //! Destructor
        ~CoordinateCollection();

        void discoverCoords( ISosiElement* sosi );

        bool getNextInGeom( ICoordinate*& coord );

        bool getNextInIslands( ICoordinate*& coord );

    }; // class Coordinate
    
}; // namespece sosicon

#endif
