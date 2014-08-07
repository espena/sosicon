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
#ifndef __I_SHAPEFILE_H__
#define __I_SHAPEFILE_H__

#include "i_shapefile_shp_part.h"
#include "i_shapefile_shx_part.h"
#include "i_shapefile_dbf_part.h"
#include "i_sosi_element.h"
#include "../sosi/sosi_types.h"

namespace sosicon {
    /*!
        \addtogroup interfaces Interfaces
        @{
    */

    //! Interface: Shapefile
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class IShapefile : public IShapefileShpPart,
                       public IShapefileShxPart,
                       public IShapefileDbfPart {

        public:
            
            virtual ~IShapefile() {}

            //! Build shapefile from SOSI data
            /*!
                \param sosiTree Root SOSI element. The first-level children of this element
                       will be examined and exported if they are compatible.
                \param selection SOSI element type scheduled for shapefile conversion.
                       Since a shapefile may contain only one geometry type at a time,
                       one must select what element type to extract from the SOSI file.
             */
            virtual void build( ISosiElement* sosiTree, sosi::ElementType selection ) = 0;

    };
   /*! @} end group interfaces */
}; // namespace sosicon

#endif
