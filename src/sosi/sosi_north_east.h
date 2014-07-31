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
#ifndef __SOSI_NORTH_EAST_H__
#define __SOSI_NORTH_EAST_H__

#include "../interface/i_sosi_element.h"
#include "../interface/i_coordinate.h"
#include "../common_types.h"
#include "../coordinate.h"
#include "sosi_types.h"
#include "sosi_origo_ne.h"
#include "sosi_unit.h"
#include <algorithm>
#include <limits>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace sosicon {

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        //! SOSI North-east element
        /*!
            Implements SOSI north east element, as given via the NØ element.
         */
        class SosiNorthEast {

            ISosiElement* mSosiElement;

            CoordinateList mCoordinates;

            CoordinateList::iterator mCoordinatesIterator;

            static SosiOrigoNE mOrigo;

			static SosiUnit mUnit;

            double mMinX;
            double mMinY;
            double mMaxX;
            double mMaxY;

            //! Populate mCoordinates
            void ragelParseCoordinates( std::string data );

            void initHeadMember( ISosiHeadMember& headMember, ElementType type );

        public:

            void append( double n, double e );
            void append( std::string n, std::string e );

			//!< Frees allocated memory
			void free();
			
			//! Construct new SOSI north-east element
            SosiNorthEast( ISosiElement* e );

            //! Destructor
            virtual ~SosiNorthEast();

            //! Debug
            void dump();

            void expandBoundingBox( double& minX, double& minY, double& maxX, double& maxY );

            ICoordinate* front() { return mCoordinates.size() > 0 ? mCoordinates.front() : 0; }

            ICoordinate* back() { return mCoordinates.size() > 0 ? mCoordinates.back() : 0; }

            //* Get next coordinate in list
            bool getNext( ICoordinate*& coord );

            //* Get number of points in current segment
            int getNumPoints() { return mCoordinates.size(); };

            //! Reverse polygon (point order)
            void reverse() { std::reverse( mCoordinates.begin(), mCoordinates.end() ); };

            SosiNorthEast& operator+= ( SosiOrigoNE& origo );

            SosiNorthEast& operator/= ( SosiUnit& unit );

        }; // class SosiNorthEast
       /*! @} end group sosi_elements */

        //! List of SosiSNorthEast elements
        typedef std::vector<SosiNorthEast*> NorthEastList;

        //! Deletes SosiNorthEast elements of NorthEastList
        void deleteNorthEasts( NorthEastList& lst );


    }; // namespace sosi

}; // namespace sosicon

#endif
