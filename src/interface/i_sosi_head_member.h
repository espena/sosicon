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
#ifndef __I_SOSI_HEAD_MEMBER_H__
#define __I_SOSI_HEAD_MEMBER_H__

#include "i_sosi_element.h"

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        This is a listing of generic interfaces used within sosicon.
        @{
    */

    //! Interface: SOSI header element
    /*!
        \author Espen Andersen
        \copyright GNU General Public License
    */
    class ISosiHeadMember {

    public:
        //! Destructor
        virtual ~ISosiHeadMember(){ };

        virtual void init( ISosiElement* e ) = 0;

        virtual bool initialized() = 0;
    };
   /*! @} end group interfaces */

}; // namespace sosicon

#endif
