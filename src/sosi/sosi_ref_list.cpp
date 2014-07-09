/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen
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
#include "sosi_ref_list.h"

sosicon::sosi::SosiRefList::
SosiRefList( ISosiElement* e ) {
    mSosiElement = e;
    ragelParseSosiRef( e->getData() );
}

sosicon::sosi::SosiRefList::
~SosiRefList() {
    for( std::vector<Reference*>::iterator i = mRefList.begin(); i != mRefList.end(); i++ ) {
        delete *i;
    }
}

bool sosicon::sosi::SosiRefList::
getNextReference( Reference*& reference ) {
    if( 0 == reference ) {
        mRefListIterator = mRefList.begin();
    }
    reference = *mRefListIterator++;
    return mRefListIterator != mRefList.end();
}