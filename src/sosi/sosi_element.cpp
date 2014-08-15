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
#include "sosi_element.h"

sosicon::sosi::SosiElement::
SosiElement( std::string name, std::string serial, std::string data, int level, ISosiElement* root, SosiElementMap& index ) : mIndex( index ) {
    mName = name;
    mSerial = serial;
    mData = data;
    mLevel = level;
    mType = mTranslation.sosiNameToType( mName );
    mObjType = sosi::sosi_objtype_unknown;
    mRoot = root ? root : this;
    if( !mSerial.empty() ) {
        mIndex[ mSerial ] = this;
    }
}

void sosicon::sosi::SosiElement::
addChild( ISosiElement* child ) {
    if( child->getType() == sosi::sosi_element_objtype ) {
        mObjTypeStr = child->getData();
        mObjType = mTranslation.sosiObjNameToType( mObjTypeStr );
    }
    mChildren.push_back( child );
};

void sosicon::sosi::SosiElement::
deleteChildren() {
    for( std::vector<ISosiElement*>::iterator i = mChildren.begin(); i != mChildren.end(); i++ ) {
        ( *i )->deleteChildren();
        delete *i;
    }
}

void sosicon::sosi::SosiElement::
dump( int indent ) {
    std::string space = std::string( indent, ' ' );
    std::cout << space << mName <<  "[ " << mSerial << " ]" << "\n";
    std::cout << space << "    -> " << mData << "\n";
    for( std::vector<ISosiElement*>::iterator i = mChildren.begin(); i != mChildren.end(); i++ ) {
        ( *i )->dump( indent + 2 );
    }
}

sosicon::ISosiElement* sosicon::sosi::SosiElement::
find( std::string ref ) {
    ISosiElement* e;
    try {
        e = mIndex[ ref ];
    }
    catch ( ... ) {
        e = 0;
    }
    return e;
}

bool sosicon::sosi::SosiElement::
nextChild( SosiElementSearch& src ) {
    SosiChildrenList::size_type n = mChildren.size();
    bool moreToGo = n > 0;
    if( moreToGo ) {
        if( src.element() == 0 ) {
            src.index( 0 );
        }
        if( src.index() < n ) {
            src.element( mChildren[ src.index() ] );
            moreToGo = true;
            src.next();
        }
        else {
            moreToGo = false;
        }
    }
    return moreToGo;
}

bool sosicon::sosi::SosiElement::
getChild( SosiElementSearch& src ) {
    bool res = nextChild( src );
    sosi::ElementType t = src.type();
    while( res == true  && t != sosi::sosi_element_unknown && src.element()->getType() != t ) {
        res = getChild( src );
    }
    return res;
}