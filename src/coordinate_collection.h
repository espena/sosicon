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
#include "logger.h"
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
    bool getNext( ICoordinate*& coord, sosi::NorthEastList& list, sosi::NorthEastList::iterator& i );
    
    //! Get next offset in part offsets list
    bool getNextOffset( int& offset, std::vector<int>& offsets, std::vector<int>::iterator& iterator );

    //! Analyzes polygon direction
    /*!
        Checks a series of coordinates to see if they are ordered in a clockwise manner.
        \param begin Iterator to the first item to be analyzed.
        \param end Iterator to the end item, one item past the last one to be analyzed.
        \return true if the coordinates are ordered clockwise.
    */
    bool isClockwise( std::vector<ICoordinate*>::iterator& begin, std::vector<ICoordinate*>::iterator& end );

    //! Analyzes polygon direction
    /*!
        Checks a series of coordinates to see if they are ordered in a counter-clockwise manner.
        \param begin Iterator to the first item to be analyzed.
        \param end Iterator to the end item, one item past the last one to be analyzed.
        \return true if the coordinates are ordered counter-clockwise.
    */
    bool isCounterClockwise( std::vector<ICoordinate*>::iterator& begin, std::vector<ICoordinate*>::iterator& end );

    //! Extracts single coordinates from list of North-East elements
    /*!
        Converts a vector of NE elements to a vector of coordinates.

        \param neList The source vector.
        \param coordList The destination vector.
    */
    void neListToCoordList( sosi::NorthEastList& neList, std::vector<ICoordinate*>& coordList );

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

        sosi::NorthEastList::iterator mGeomIndex;

        double mXmin;
        double mYmin;
        double mXmax;
        double mYmax;

        //! Get coordinate values from SOSI element
        void extractPath( ISosiElement* referencedElement,
                          bool reverse,
                          int& numPoints,
                          sosi::NorthEastList& target );

    public:

        //! Destructor
        virtual ~CoordinateCollection();

        //! Constructor
        CoordinateCollection() :
            mNumPartsGeom( 0 ),
            mNumPartsHoles( 0 ),
            mNumPointsGeom( 0 ),
            mNumPointsHoles( 0 ),
            mXmin( +9999999999 ),
            mYmin( +9999999999 ),
            mXmax( -9999999999 ),
            mYmax( -9999999999 ) { };

        //!< Free allocated memory
        void free();

        //! Extracts coordinates from SOSI element
        /*!
            This method retrieves the physical coordinates for a SOSI geometry,
            if applicable, and populates the coordinate collection.

            This algorithm resolves referenced objects for polygons and presents
            the coordinates in correct order.
            \param sosi SOSI element from which to extract coordinates.
        */
        void discoverCoords( ISosiElement* sosi );

        //! Retrieve next coordinate in collection
        /*!
            Iterates through the coordinate list until it reaches the end,
            passing a pointer to the next element to the coord reference. 
            Tne value of coord must be zero on the first pass in order to
            start the iteration on the first ISosiElement.
            \return The function returns true if there are more coordinates in
                    the collection, or false if the last coordinate is
                    encoutered.
        */
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
