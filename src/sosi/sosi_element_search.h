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
#ifndef __SOSI_ELEMENT_SEARCH_H__
#define __SOSI_ELEMENT_SEARCH_H__

#include <map>
#include <vector>
#include "sosi_types.h"

namespace sosicon {

    //! Forward declaration
    class ISosiElement;

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        //! Element index type
        typedef std::map<std::string,ISosiElement*> SosiElementMap;

        typedef std::vector<ISosiElement*> SosiChildrenList;

        typedef SosiChildrenList::iterator SosiChildrenIterator;

        class SosiElementSearch {
            SosiChildrenList::size_type mIndex;
            ISosiElement* mSosiElement;
            sosi::ElementType mElementType;
        public:
            SosiElementSearch() : mIndex( 0 ), mSosiElement( 0 ), mElementType( sosi_element_unknown ) { };
            SosiElementSearch( sosi::ElementType filter ) : mIndex( 0 ), mSosiElement( 0 ), mElementType( filter ) { };
            SosiChildrenList::size_type index() { return mIndex; };
            SosiChildrenList::size_type index( SosiChildrenList::size_type i ) { mIndex = i; return mIndex; };
            ISosiElement* element() { return mSosiElement; };
            ISosiElement* element( ISosiElement* e ) { mSosiElement = e; return mSosiElement; };
            sosi::ElementType type() { return mElementType; };
            sosi::ElementType type( sosi::ElementType t ) { mElementType = t; return mElementType; };
            void next() { mIndex++; };
        };

       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif
