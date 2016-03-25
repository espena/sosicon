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
#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include <memory>
#include <vector>
#include <iostream>

namespace sosicon {

   //! Event dispatcher template class
   /*!
        \author Espen Andersen
        \copyright GNU General Public License

        Impelements event dispatcher for specified event type.
    */
    template<typename Event>
    class EventDispatcher {

    public:

        class Listener {

        public:
            virtual ~Listener() { }
            virtual void onEvent( Event& e, EventDispatcher<Event>& d ) = 0;

        }; // class Listener

        typedef std::vector<Listener*> ListenerLst;

    private:

        ListenerLst mListeners;

    public:

        void addEventListener( Listener* listener ) {
            if( std::find( mListeners.begin(), mListeners.end(), listener ) == mListeners.end() ) {
                mListeners.push_back( listener );
            }
        }

        void removeEventListener( Listener* listener ) {
            typename ListenerLst::iterator i = std::find( mListeners.begin(), mListeners.end(), listener );
            if( i != mListeners.end() ) {
                mListeners.erase( i );
            }
        }

        void Dispatch( Event& e ) {
            for( typename ListenerLst::iterator i = mListeners.begin(); i != mListeners.end(); i++ ) {
                ( *i )->onEvent( e, *this );
            }
        }

    }; // class EventDispatcher

} // namespece sosicon

#endif
