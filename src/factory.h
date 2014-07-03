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
#ifndef __factory_h
#define __factory_h

#include "interface/i_converter.h"
#include "converter_sosi2shp.h"
#include "converter_sosi2tsv.h"

namespace sosicon {
    
    //! Factory class
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Responsible for creating an appropriate IConverter implementation instance. Uses the
        command-line arguments to decide what type of converter is required.
    */
    class Factory {
    public:

        //! Retrieve converter
        /*!
            Selects an IConverter implementation and creates an object of that class based on
            the user's command-line arguments.
            
            \note Any object delivered with Factory::get() must be freed by calling
                  Factory::release()

            \sa Factory::release()

            \param converter Reference to the pointer to receive the new IConverter.
            \param cmd CommandLine object with current command-line arguments.
         */
        static void get( IConverter* &converter, CommandLine cmd );

        //! Releases converter
        /*!
            Frees allocated resources and releases IConverter object. Any object retrieved from
            Factory::get() must be disposed of through this function.
            
            \param converter Reference to a pointer containing the IConverter instance to be
                   released. The pointer will be reset to 0 after object deletion.
         */
        static void release( IConverter* &converter );
    }; // class Factory
    
}; // namespace sosicon

#endif