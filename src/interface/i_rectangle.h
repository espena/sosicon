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
#ifndef __I_RECTANGLE_H__
#define __I_RECTANGLE_H__

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        This is a listing of generic interfaces used within sosicon.
        @{
    */
    //! Interface: Rectangle
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class IRectangle {
    public:

        //! Destructor
        virtual ~IRectangle() { };
        
        //! Get left position
        /*!
            Returns the left (x0) coordinate of current rectangle.
            \return Left/x0 position.
         */
        virtual double left() = 0;
        
        //! Set left position
        /*!
            Sets the left (x0) coordinate of current rectangle.
            \param val The new left/x0 position.
         */
        virtual void left( double val ) = 0;

        //! Get top position
        /*!
            Returns the top (y0) coordinate of current rectangle.
            \return Top/y0 position.
         */
        virtual double top() = 0;

        //! Set top position
        /*!
            Sets the top (y0) coordinate of current rectangle.
            \param val The new top/y0 position.
         */
        virtual void top( double val ) = 0;

        //! Get right position
        /*!
            Returns the right (x1) coordinate of current rectangle.
            \return Right/x1 position.
         */
        virtual double right() = 0;

        //! Set right position
        /*!
            Sets the right (x1) coordinate of current rectangle.
            \param val The new right/x1 position.
         */
        virtual void right( double val ) = 0;

        //! Get bottom position
        /*!
            Returns the bottom (y1) coordinate of current rectangle.
            \return Bottom/y1 position.
         */
        virtual double bottom() = 0;

        //! Set bottom position
        /*!
            Sets the bottom (y1) coordinate of current rectangle.
            \param val The new bottom/y1 position.
         */
        virtual void bottom( double val ) = 0;
    };
   /*! @} end group interfaces */
}; // namespace sosicon

#endif