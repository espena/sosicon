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
#ifndef __I_CONVERTER_H__
#define __I_CONVERTER_H__

#include "../command_line.h"

namespace sosicon {

    /*!
        \addtogroup interfaces
        @{
    */
    //! Interface: Converter
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Represents the generic form of a converter. The factory class is responsible for creating
        a converter based upon input parameters. The returned object is then interacted on
        through this interface.
    */
    class IConverter {

    public:

        //! Destructor
        virtual ~IConverter(){}

        //! Initialize converter
        /*!
            Conversion setup. Uses the CommandLine to determine what operations to perform.
            \param cmd Arguments from the command-line parsed and ready within a
            sosicon::CommandLine object.
         */
        virtual void init( CommandLine* cmd ) = 0;

        //! Start conversion
        /*!
            Run the conversion routine. Outputs the destination file accrding to the preferences
            given from the command-line.
         */
        virtual void run() = 0;
    };
    /*! @} end group interfaces */
};

#endif
