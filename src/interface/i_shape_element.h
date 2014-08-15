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
#ifndef __I_SHAPE_ELEMENT_H__
#define __I_SHAPE_ELEMENT_H__

#include "i_binary_streamable.h"
#include "i_sosi_element.h"
#include "i_rectangle.h"

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        This is a listing of generic interfaces used within sosicon.
        @{
    */
    //! Interface: Shape element
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class IShapeElement : public IBinaryStreamable {
    public:

        //! Destructor
        virtual ~IShapeElement() { };
        
        //! Create from SOSI element
        /*!
            Takes a SOSI element and creates a shape element from it.
            \param sosiElement Pointer to the SOSI element to be converted to a shape element.
            \return The result of the operation.
            \retval true on success.
            \retval false on failure.
         */
        virtual bool populate( ISosiElement* sosiElement ) = 0;
        
        //! Get original SOSI element
        /*!
            Delivers a pointer to the original SOSI element populating current IShapeElement.
            The pointer is usually stored with current object when IShapeElement::populate()
            is called.
            \sa IShapeElement::populate()
            \return Pointer to the source SOSI element.
         */
        virtual ISosiElement* getSosiElement() = 0;
        
        //! Get minimum bounding rectangle
        /*!
            Populates the referenced IRectangle implementation with the coordinates for the
            minimum bounding rectangle (MBR) of current element.
            \param Reference to the IRectangle implementation to receive the coordinates
                   of the minium bounding rectangle.
         */
        virtual void getMBR( IRectangle& rect ) = 0;
        
        //! Get element size in 16-bit words
        /*!
            Size of current element, in 16-bit words. Some parts of the SOSI standard requires
            size notation on 16-bit words. This is the byte size divided by two.
            \sa IShapeElement::getByteSize()
            \return The binary size of current element in 16-bit words. Equals its byte size
                    divided by two.
         */
        virtual int getWordSize() = 0;
        
        //! Get element size in bytes
        /*!
            Size of current element, in bytes.
            \sa IShapeElement::getWordSize()
            \return The vinary size of current element in bytes.
         */
        virtual int getByteSize() = 0;
    };
   /*! @} end group interfaces */
}; // namespace sosicon

#endif