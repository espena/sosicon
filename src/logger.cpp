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
#include "logger.h"

sosicon::Logger sosicon::logstream;

sosicon::Logger&
sosicon::Logger::operator << ( std::string v )
{
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( unsigned int v )
{
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( unsigned long v )
{
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( int v )
{
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( long v )
{
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( sosicon::Logger& ( *func ) ( sosicon::Logger& ) )
{
    return func( *this );
}

sosicon::Logger&
sosicon::flush( sosicon::Logger& l )
{
    std::cout << std::flush; return l;
}