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
    bool getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::iterator& iterator );
    
    //! Get next offset in part offsets list
    bool getNextOffset( int& offset, std::vector<int>& offsets, std::vector<int>::iterator& iterator );

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
        std::vector<int> mPartOffsetsGeom;
        std::vector<int>::iterator mPartOffsetsGeomIterator;
        int mNumPointsGeom;

        //! Stores collection of pointers to coordinates for holes
        sosi::NorthEastList mIslands;
        sosi::NorthEastList::iterator mIslandsIterator;
        std::vector<int> mPartOffsetsIslands;
        std::vector<int>::iterator mPartOffsetsIslandsIterator;
        int mNumPointsIslands;

        double mXmin;
        double mYmin;
        double mXmax;
        double mYmax;

        //! Get ccordinate values from SOSI element
        void extractPath( sosi::Reference* ref, ISosiElement* referencedElement );

    public:

        //! Destructor
        virtual ~CoordinateCollection();

        //! Constructor
        CoordinateCollection() :
            mXmin( +9999999999 ),
            mYmin( +9999999999 ),
            mXmax( -9999999999 ),
            mYmax( -9999999999 ),
            mNumPointsGeom( 0 ),
            mNumPointsIslands( 0 ) { };

        void discoverCoords( ISosiElement* sosi );

        bool getNextOffsetInGeom( int& offset );
            
        bool getNextOffsetInIslands( int& offset );
            
        bool getNextInGeom( ICoordinate*& coord );

        bool getNextInIslands( ICoordinate*& coord );

        CoordinateList::size_type getNumPartsGeom() { return mGeom.size(); };

        CoordinateList::size_type getNumPartsIslands() { return mIslands.size(); };

        int getNumPointsGeom() { return mNumPointsGeom; };

        int getNumPointsIslands() { return mNumPointsIslands; };

        double getXmin() { return mXmin == +9999999999 ? 0 : mXmin; };

        double getYmin() { return mYmin == +9999999999 ? 0 : mYmin; };

        double getXmax() { return mXmax == -9999999999 ? 0 : mXmax; };

        double getYmax() { return mYmax == -9999999999 ? 0 : mYmax; };

    }; // class Coordinate
    
}; // namespece sosicon

#endif
