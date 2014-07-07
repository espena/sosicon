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
#ifndef __SOSI_REF_H__
#define __SOSI_REF_H__

#include "../interface/i_sosi_element.h"
#include "sosi_types.h"
#include <vector>

namespace sosicon {

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        //! SOSI REF list
        /*!
            Implements basic characteristics of a SOSI element.
         */
        class SosiRef {

            ISosiElement* mSosiElement;

            std::vector<Reference*> mRefList;

            void parseSosiRef( std::string data );

        public:

            //! Construct new SOSI REF element
            SosiRef( ISosiElement* e );

            //! Destructor
            ~SosiRef();

        }; // class SosiRef
       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif