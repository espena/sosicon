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
#include "reference_lookup.h"
#include <iostream>
#include <sstream>

void sosicon::sosi::ReferenceLookup::
build( Parser& p ) {
    mElements.clear();
    ISosiElement* e = 0;
    while( p.getNextSosiElement( e ) ) {
        try {
          append( e->getData( "id" ), e );
        }
        catch( ... ) { }
    } // while
}

sosicon::ISosiElement* sosicon::sosi::ReferenceLookup::
get( std::string key ) {
    ISosiElement* ref = 0;
    try {
        ref = mElements[ key ];
    }
    catch( ... ) { }
    return ref;
}

std::string sosicon::sosi::ReferenceLookup::
toString() {
    std::stringstream ss;
    ss << size();
    return ss.str();
}