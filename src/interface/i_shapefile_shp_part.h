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
#ifndef __I_SHAPEFILE_SHP_PART_H__
#define __I_SHAPEFILE_SHP_PART_H__

#include <iostream>
#include "i_binary_streamable.h"

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        @{
    */
    //! Interface: ShapefileShpPart
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class IShapefileShpPart : public IBinaryStreamable {

    public:

        virtual void writeBinary( std::ostream &os ) { writeShp( os );  }

        virtual void writeShp( std::ostream &os ) = 0;        
        
    };
   /*! @} end group interfaces */
}; // namespace sosicon

#endif