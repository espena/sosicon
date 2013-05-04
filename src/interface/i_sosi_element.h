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
#include "../sosi/address_unit.h"
#include "../sosi/cadastral_unit.h"
#include "../sosi/coord_list.h"

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

        //! Retrieve string data
        /*!
            Get string value by key. Every SOSI element has several data fields. These fields
            are loaded into current element by the parser.
            \param key The key for the string data to be retrieved.
            \return If the key exists, the corresponding data string will be returned. Otherwise,
                    a blank string is returned.
        */
        virtual std::string getData( const char* key ) = 0;

        //! Retrieve next cadastral unit
        /*!
            If there are a vector of CadastralUnit objects associated with current ISosiElement,
            this function will return the next such object in the list. A pointer to the object
            will be stored in the provided cunit pointer reference.
            
            If the initial value of the cunit pointer is 0, the first CadastralUnit in the list
            will be returned. Subsequent calls will retrieve the next item in list, until reaching
            the end. The pointer will then be set back to 0.
            
            \sa sosicon::sosi::CadastralUnit
            
            \param cunit Reference to a pointer to receive the address to the CadastralUnit object.
            \return A string representation of the CadastralUnit being returned, or an empty string
                    if the list was empty or the iterator moved past the last element in the list.
        */
        virtual std::string getData( ::sosicon::sosi::CadastralUnit* &cunit ) = 0;

        //! Retrieve next address
        /*!
            If there are a vector of AddressUnit objects associated with current ISosiElement,
            this function will return the next such object in the list. A pointer to the object
            will be stored in the provided cunit pointer reference.
            
            If the initial value of the aunit pointer is 0, the first AddressUnit in the list
            will be returned. Subsequent calls will retrieve the next item in list, until reaching
            the end. The pointer will then be set back to 0.
            
            \sa sosicon::sosi::CadastralUnit
            
            \param aunit Reference to a pointer to receive the address to the AddressUnit object.
            \return A string representation of the AddressUnit being returned, or an empty string
                    if the list was empty or the iterator moved past the last element in the list.
        */
        virtual std::string getData( ::sosicon::sosi::AddressUnit* &aunit ) = 0;

        //! Retrieve next coordinate list
        /*!
            If there are a vector of CoordList objects associated with current ISosiElement,
            this function will return the next such object in the list. A pointer to the object
            will be stored in the provided cunit pointer reference.
            
            If the initial value of the aunit pointer is 0, the first CoordList in the list
            will be returned. Subsequent calls will retrieve the next item in list, until reaching
            the end. The pointer will then be set back to 0.
            
            \sa sosicon::sosi::CoordList
            
            \param clist Reference to a pointer to receive the address to the CoordList object.
            \return A string representation of the CoordList being returned, or an empty string
                    if the list was empty or the iterator moved past the last element in the list.
        */
        virtual std::string getData( ::sosicon::sosi::CoordList* &clist ) = 0;

        //! Retrieve list of available SOSI fields
        /*!
            Lists all SOSI fields from current element. These are the fields available for export
            to other formats.

            \return Reference to a string vector containing the names of all SOSI fields
                    encountered by the parser in current element.
         */
        virtual std::vector<std::string>& getFields() = 0;

        //! Retrieve SOSI element OBJTYPE
        /*!
            Get the object type for current element.
         */
        virtual std::string getType() = 0;

        //! Set value
        /*!
            Insert or update a SOSI field value. Call this function to insert string values
            into current element, or to alter an existing value. If the field entry does not
            exist, it will be created.
            
            \param key Name of the SOSI field to update/insert.
            \param val New string value.
         */
        virtual void set( const std::string& key, const std::string& val ) = 0;

        //! Append character to value
        /*!
            Appends one character to a SOSI field. The parser works by consuming characters
            one-by-one. Upon encountering a SOSI field value, the character is injected into the
            element's corresponding field through this function, placing the character at the end
            of the current string. If the field entry does not exist, it will be created.
            
            \sa sosicon::Parser::parseSosiLine()

            \param key Name of the SOSI field to update.
            \param var The character to be appended at the end of current SOSI field value.
         */
        virtual void append( const std::string& key, char val ) = 0;
    };
   /*! @} end group interfaces */

}; // namespace sosicon

#endif