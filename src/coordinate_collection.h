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
#ifndef __COORDINATE_COLLECTION_H__
#define __COORDINATE_COLLECTION_H__

#include <algorithm>
#include <limits>
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
    bool getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::size_type& index );
    
    //! Get next offset in part offsets list
    bool getNextOffset( int& offset, std::vector<int>& offsets, std::vector<int>::iterator& iterator );

    //! Coordinate container
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Stores a collection of geographical positions.
     */
    class CoordinateCollection {

        //! Stores collection of pointers to coordinates for geometries
        sosi::NorthEastList mGeom;
        std::vector<ICoordinate*> mGeomNormalized;

        sosi::NorthEastList mHoles;
        std::vector<ICoordinate*> mHolesNormalized;

        int mNumPartsGeom;
        int mNumPartsHoles;

        int mNumPointsGeom;
        int mNumPointsHoles;

        std::vector<int> mGeomSizes;
        std::vector<int> mHoleSizes;

        sosi::NorthEastList::size_type mGeomIndex;

        double mXmin;
        double mYmin;
        double mXmax;
        double mYmax;

        //! Get ccordinate values from SOSI element
        void extractPath( ISosiElement* referencedElement,
                          bool reverse,
                          int& numPoints,
                          sosi::NorthEastList& target );

        bool isClockwise( std::vector<ICoordinate*>::iterator begin, std::vector<ICoordinate*>::iterator end );
        bool isCounterClockwise( std::vector<ICoordinate*>::iterator begin, std::vector<ICoordinate*>::iterator end ) { return end != ( begin + 2 ) ? false : !isClockwise( begin, end ); };

    public:

        //! Destructor
        virtual ~CoordinateCollection();

        //! Constructor
        CoordinateCollection() :
            mXmin( +9999999999 ),
            mYmin( +9999999999 ),
            mXmax( -9999999999 ),
            mYmax( -9999999999 ),
            mNumPartsGeom( 0 ),
            mNumPartsHoles( 0 ),
            mNumPointsGeom( 0 ),
            mNumPointsHoles( 0 ) { };

        //!< Free allocated memory
        void free();

        void discoverCoords( ISosiElement* sosi );
        bool getNextInGeom( ICoordinate*& coord );

        std::vector<ICoordinate*>& getGeom();
        std::vector<int>& getGeomSizes() { return mGeomSizes; };
        int getNumPointsGeom() { return mNumPointsGeom; };
        int getNumPartsGeom() { return mNumPartsGeom; };

        std::vector<ICoordinate*>& getHoles();
        std::vector<int>& getHoleSizes() { return mHoleSizes; };
        int getNumPointsHoles() { return mNumPointsHoles; };
        int getNumPartsHoles() { return mNumPartsHoles; };

        double getXmin() { return mXmin == +9999999999 ? 0 : mXmin; };

        double getYmin() { return mYmin == +9999999999 ? 0 : mYmin; };

        double getXmax() { return mXmax == -9999999999 ? 0 : mXmax; };

        double getYmax() { return mYmax == -9999999999 ? 0 : mYmax; };

    }; // class Coordinate
    
}; // namespece sosicon

#endif
