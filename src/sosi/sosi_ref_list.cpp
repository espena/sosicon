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
    mRefListIndex = 0;
}

sosicon::sosi::SosiRefList::
~SosiRefList() {
    for( std::vector<SosiReferenceList*>::iterator l = mRefListCollection.begin(); l != mRefListCollection.end(); l++ ) {
        std::vector<Reference*>* refList = *l;
        for( std::vector<Reference*>::iterator i = refList->begin(); i != refList->end(); i++ ) {
            delete *i;
        }
        refList->clear();
    }
    mRefListCollection.clear();
}

bool sosicon::sosi::SosiRefList::
getNextReference( Reference*& reference ) {

    if( 0 == reference ) {
        mRefListColletionIndex = 0;
        mRefListIndex = 0;
    }

    if( mRefListCollection.size() == 0 || mRefListColletionIndex >= mRefListCollection.size() ) {
        return false;
    }
    else {
        SosiReferenceList* refList = mRefListCollection[ mRefListColletionIndex ];
        if( mRefListIndex == refList->size() ) {
            if( ++mRefListColletionIndex == mRefListCollection.size() ) {
                return false;
            }
            SosiReferenceList* refList = mRefListCollection[ mRefListColletionIndex ];
        }
        if( mRefListIndex == refList->size() ) {
            return false;
        }
        reference = ( *refList ) [ mRefListIndex ];
        mRefListIndex++;
    }
    return true;
}