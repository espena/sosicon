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
#ifndef __CADASTRAL_UNIT_H__
#define __CADASTRAL_UNIT_H__

#include <string>

namespace sosicon {

    namespace sosi {

        /*!
            \addtogroup gis_entities GIS entities
            @{
        */
        //!  Cadastral unit
        /*!
            \author Espen Andersen
            \copyright GNU General Public License

            Represents a property as registered in the national cadastre. Some properties do not have
            street addresses. Instead, they are identified by their cadastral unit code consisting of
            the following parts:
            - Municipality number
            - Cadastral unit number
            - Property number
            - Section number
            - Leashold number
        */
    	class CadastralUnit {

    	public:

            //! Municipality number
    		std::string mMunicipality;

            //! Cadastral unit number
    		std::string mCadastre;

            //! Property number
    		std::string mProperty;

            //! Leasehold number
    		std::string mLeasehold;

            //! Section number
    		std::string mSection;

            //! Constructor
    		CadastralUnit();

            //! Destructor
    		virtual ~CadastralUnit();
		
    	    //! Return string representation
    	    /*!
    	        Creates a human-readable string representation for this cadastral unit number.
	        
    	        \return string representation of current object.
    	     */
    		std::string toString();

    	};
    	/*! @} end gis_entities */

    }; // namespace sosi

}; // namespace sosicon

#endif