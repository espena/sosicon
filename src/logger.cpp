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
#include "sosi/sosi_charset_singleton.h"

sosicon::Logger sosicon::logstream;

sosicon::Logger&
sosicon::Logger::operator << ( std::string v )
{
    static bool updateable = false;
    std::cout << v.c_str();
    if( v.find( "\r", 0 ) != std::string::npos ) {
        std::string msgStr = sosicon::utils::purgeCrLf( sosicon::utils::trim( sosi::SosiCharsetSingleton::getInstance()->toIso8859_1( mMsgStream.str() ) ) );
        if( !msgStr.empty() ) {
            LogEvent e( sosicon::utils::purgeCrLf( mMsgStream.str() ), updateable );
            updateable = true;
            mMsgStream.str( std::string() );
            mMsgStream << sosicon::utils::purgeCrLf( v );
            mLogEventDispatcher.EventDispatcher<LogEvent>::Dispatch( e );
        }
    }
    else if( v.find( "\n", 0 ) != std::string::npos ) {
        mMsgStream << v;
        updateable = false;
        std::string msgStr = sosicon::utils::purgeCrLf( sosicon::utils::trim( sosi::SosiCharsetSingleton::getInstance()->toIso8859_1( mMsgStream.str() ) ) );
        if( !msgStr.empty() ) {
            LogEvent e( msgStr, updateable );
            mLogEventDispatcher.EventDispatcher<LogEvent>::Dispatch( e );
        }
        mMsgStream.str( std::string() );
    }
    else {
        mMsgStream << v;
    }
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( std::string::size_type v )
{
    mMsgStream << v;
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( unsigned int v )
{
    mMsgStream << v;
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( int v )
{
    mMsgStream << v;
    std::cout << v;
    return *this;
}

sosicon::Logger&
sosicon::Logger::operator << ( long v )
{
    mMsgStream << v;
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
    std::cout << std::flush;
    return l;
}
