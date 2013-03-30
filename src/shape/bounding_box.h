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
#ifndef __BOUNDING_BOX_H__
#define __BOUNDING_BOX_H__

#include <algorithm>
#include <limits>
#include "shapefile_types.h"
#include "../interface/i_rectangle.h"

namespace sosicon {

    namespace shape {
        
        //! Shapefile bounding box
        /*!
            The actual extent of the shapes in the file: Minimum bounding rectangle orthogonal to
            the X and Y (and possibly M and Z) axes that contains all the shapes.
         */
        class BoundingBox : public IRectangle {

        public:
            
            // Constructor
            BoundingBox();

            // Described in IRectangle
            virtual double left() { return mXmin.d; }

            // Described in IRectangle
            virtual void left( double val ) { mXmin.d = val; }

            // Described in IRectangle
            virtual double top() { return mYmax.d; }

            // Described in IRectangle
            virtual void top( double val ) { mYmax.d = val; }

            // Described in IRectangle
            virtual double right() { return mXmax.d; }

            // Described in IRectangle
            virtual void right( double val ) { mXmax.d = val; }

            // Described in IRectangle
            virtual double bottom() { return mYmin.d; }
            
            // Described in IRectangle
            virtual void bottom( double val ) { mYmin.d = val; }
            
            void merge( IRectangle& rect );

            //! Minimimum X coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mXmin;

            //! Minimimum Y coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mYmin;

            //! Maximum X coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mXmax;

            //! Maximum Y coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mYmax;

            //! Minimum Z coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mZmin;

            //! Maximum Z coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mZmax;

            //! Minimum M coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mMmin;

            //! Maximum M coordinate
            /*!
                If the shapefile is empty, this value is unspecified.
             */
            DoubleField mMmax;
        };
    }; // namespace shape
}; // namespace sosicon

#endif