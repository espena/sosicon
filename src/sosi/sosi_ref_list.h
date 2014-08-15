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
#ifndef __SOSI_REF_LIST_H__
#define __SOSI_REF_LIST_H__

#include "../interface/i_sosi_element.h"
#include "sosi_types.h"
#include <iostream>
#include <string>
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
            Implements SOSI reference list, as given via the REF element.
         */
        class SosiRefList {

            ISosiElement* mSosiElement;

            GeometryCollection mRefListCollection;

            GeometryCollection::size_type mRefListCollectionIndex;
            GeometryRef::size_type mRefListIndex;

            void ragelParseSosiRef( std::string data );

        public:

            //! Construct new SOSI REF element
            SosiRefList() : mSosiElement( 0 ), mRefListIndex( 0 ) { };

            //! Construct new SOSI REF element
            SosiRefList( ISosiElement* e );

            //! Destructor
            ~SosiRefList();

            //! Next list of references
            /*!
                A reference list represents a geometry, i.e. a polygon or its holes.
            */
            bool getNextGeometry( GeometryRef*& geometry );

            //SosiReferenceListCollection::size_type size() { return mRefListCollection.size(); };

        }; // class SosiRef
        /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif
