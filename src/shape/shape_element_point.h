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
#ifndef __SHAPE_ELEMENT_POINT_H__
#define __SHAPE_ELEMENT_POINT_H__

#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include "../interface/i_shape_element.h"
#include "shape_header.h"
#include "shape_element_header.h"

namespace sosicon {

    namespace shape {
        
        /*!
            \addtogroup shape_elements Shape Elements
            Implemented representation of shapefile elements.
            @{
        */
        //! Shapefile point
        /*!

         */
        class ShapeElementPoint : public IShapeElement {
        
        public:
        
            //! Shapefile point raw data
            union Data {
                struct {
                    Int32TField type;
                    DoubleField x;
                    DoubleField y;
                } fields;
                unsigned char array[ sizeof( uint16_t ) + ( sizeof( double ) * 2 ) ];
            };
        
        private:

            //! Shape record header
            ShapeElementHeader mHeader;
        
            //! Shape record contents
            Data mContents;
            
            //! Original SOSI element
            ISosiElement* mSosiElement;

        public:

            //! Constructor
            ShapeElementPoint();

            //! Destructor
            virtual ~ShapeElementPoint();
        
            //  Described in IShapeElement
            virtual void getMBR( IRectangle& rect );

            //  Described in IShapeElement
            virtual int getByteSize() { return 28; }

            //  Described in IShapeElement
            virtual int getWordSize() { return getByteSize() / 2; }

            //  Described in IShapeElement::populate( ISosiElement* )
            virtual bool populate( ISosiElement* sosiElement );

            //  Described in IShapeElement::getSosiElement
            virtual ISosiElement* getSosiElement() { return mSosiElement; }
        
            // Described in IBinaryStreamable
            virtual void writeBinary( std::ostream &os );
 
        };

    }; // namespace shape

   /*! @} end group shape_elements */

}; // namespace sosicon

#endif
