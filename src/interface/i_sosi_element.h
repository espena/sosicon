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
#ifndef __I_SOSI_ELEMENT_H__
#define __I_SOSI_ELEMENT_H__

#include <string>
#include <vector>
#include <map>
#include "../sosi/sosi_types.h"
#include "../sosi/sosi_element_search.h"

namespace sosicon {

    /*!
        \addtogroup interfaces Interfaces
        This is a listing of generic interfaces used within sosicon.
        @{
    */

    //! Interface: SOSI element
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

       Represents the generic form of a SOSI element. All SOSI elements must implement this
       interface. It provides functionality for setting and retrieveing field values. The parser
       writes field values to current SOSI element through this interface.
       
       \sa sosicon::Parser::parseSosiLine()
       
       Data retrieval is provided by one of the getData() overloads. Single string data fields are
       associated with their unique keys, while collections of other data objects, such as
       address units and cadastral units, are retrieved one-by-one by sequential calls to 
       getData(). 
    */
    class ISosiElement {

    public:
        //! Destructor
        virtual ~ISosiElement(){ };

        virtual void addChild( ISosiElement* child ) = 0;

        virtual std::string getName() = 0;

        virtual bool getChild( sosi::SosiElementSearch& src ) = 0;

        virtual bool getChild( sosi::SosiElementSearch& src, sosi::ElementType type ) = 0;

        virtual std::string getData() = 0;

        virtual int getLevel() = 0;

        virtual sosi::ElementType getType() = 0;

        virtual ISosiElement* getRoot() = 0;

        virtual std::string getSerial() = 0;

        virtual void deleteChildren() = 0;

        virtual void dump( int indent = 0 ) = 0;

        virtual ISosiElement* find( std::string ref ) = 0;

    };
   /*! @} end group interfaces */

}; // namespace sosicon

#endif
