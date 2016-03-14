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
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>

namespace sosicon {

    //! SOSI logger
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        User output logger. Redirects to stdin, or a dedicated ILogReceiver implementation.
    */
    class Logger {
    public:
        Logger& operator << ( std::string v );
        Logger& operator << ( unsigned int v );
        Logger& operator << ( unsigned long v );
        Logger& operator << ( int v );
        Logger& operator << ( long v );
        Logger& operator << ( Logger& ( *func ) ( Logger& ) );
    };
    Logger& flush( Logger& l );
    extern Logger logstream;
};

#endif
