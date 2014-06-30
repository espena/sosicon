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
#ifndef __SHAPEFILE_H__
#define __SHAPEFILE_H__

#include <string>
#include <vector>
#include <iostream>
#include "shape_header.h"
#include "shape_index.h"
#include "shape_database.h"
#include "shape_element_point.h"
#include "shape_element_polygon.h"
#include "../sosi/reference_list.h"
#include "../interface/i_sosi_element.h"
#include "../interface/i_shape_element.h"
#include "../interface/i_shapefile.h"

namespace sosicon {

    //! ESRI Shape
    namespace shape {
        
        //! Shapefile implementation
        /*!
            Wraps all ESRI Shape output files (shp, shx, dbf, prj...) in one class.
            \author Espen Andersen
            \copyright GNU General Public License
        */
        class Shapefile : public IShapefile {

        private:

            //! Shape file header
            /*!
                Implementation of the file header with global characteristics for current shapefile.
             */
            ShapeHeader mHeader;

            //! Shape elements list
            /*!
                Elements to be included in current file is added to this list.
             */
            std::vector<IShapeElement*> mShapeElements;

            //! SOSI refs dictionary
            /*!
              Lookup table for SOSI file. ISosiElement* keyed by SOSI ID.
             */
            sosi::ReferenceList mSosiReferenceList;

            void prepareHeader();

            void prepareHeader( int recordSize );

        public:

            //! Constructor
            Shapefile();

            //! Destructor
            virtual ~Shapefile();
        
            //! Insert SOSI element
            /*!
                Converts and inserts a SOSI element into current shapefile, if the SOSI element is
                compatible with current shapefile's geometry type.
             */
            void insert( ISosiElement* sosiElement );

            // Described in IShapefileShpPart
            virtual void writeShp( std::ostream &os );
            
            // Described in IShapefileShxPart
            virtual void writeShx( std::ostream &os );
            
            // Described in IShapefileDbfPart
            virtual void writeDbf( std::ostream &os );
            
            // Described in IShapefilePrjPart
            virtual void writePrj( std::ostream &os );
        };

    }; // namespace shape

}; // namespace sosicon

#endif