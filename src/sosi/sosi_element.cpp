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
#include "sosi_element.h"

sosicon::sosi::ElementType sosicon::sosi::
sosiNameToType( std::string sosiElementName ) {

    static std::map<std::string, ElementType> sosiTypeNameMap;

    ElementType type;

    if( sosiTypeNameMap.empty() ) {
        sosiTypeNameMap[ "ENHET"            ] = sosi_element_unit;             // Unit (fraction of a metre)
        sosiTypeNameMap[ "FLATE"            ] = sosi_element_area;             // Area
        sosiTypeNameMap[ "HODE"             ] = sosi_element_head;             // File header
        sosiTypeNameMap[ "KOORDSYS"         ] = sosi_element_coordsys;         // Coordinate system
        sosiTypeNameMap[ "KURVE"            ] = sosi_element_curve;            // Curve
        sosiTypeNameMap[ "N\xD8"            ] = sosi_element_ne;               // North-east coordinate (NØ)
        sosiTypeNameMap[ "OBJTYPE"          ] = sosi_element_objtype;          // Object type
        sosiTypeNameMap[ "OPPDATERINGSDATO" ] = sosi_element_updatedate;       // Update date
        sosiTypeNameMap[ "ORIGO-N\xD8"      ] = sosi_element_origo_ne;         // Origo north-east
        sosiTypeNameMap[ "PUNKT"            ] = sosi_element_point;            // Point
        sosiTypeNameMap[ "REF"              ] = sosi_element_ref;              // Element reference
        sosiTypeNameMap[ "TEGNSETT"         ] = sosi_element_charset;          // Character set
        sosiTypeNameMap[ "TEKST"            ] = sosi_element_text;             // Text label
        sosiTypeNameMap[ "TRANSPAR"         ] = sosi_element_transpar;         // Datum/projection/coordsys
    }

    try{
        type = sosiTypeNameMap[ sosiElementName ];
    }
    catch( ... ) {
        type = sosi_element_unknown;
    }

    return type;
}

sosicon::sosi::SosiElement::
SosiElement( std::string name, std::string serial, std::string data, int level, ISosiElement* root, SosiElementMap& index ) : mIndex( index ) {
    mName = name;
    mSerial = serial;
    mData = data;
    mLevel = level;
    mType = sosiNameToType( mName );
    mRoot = root ? root : this;
    if( !mSerial.empty() ) {
        mIndex[ mSerial ] = this;
    }
}

void sosicon::sosi::SosiElement::
addChild( ISosiElement* child ) {
	mChildren.push_back( child );
	std::string test = child->getData();
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
getChild( SosiElementSearch& src ) {
    bool moreToGo = mChildren.size() > 0;
    if( moreToGo ) {
        if( src.element() == 0 ) {
            src.iterator( mChildren.begin() );
        }
		if( src.iterator() != mChildren.end() ) {
			src.element( *( src.iterator() ) );
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
getChild( SosiElementSearch& src, ElementType type ) {
    bool res = getChild( src );
    while( res == true && src.element()->getType() != type ) {
        res = getChild( src );
    }
    return res;
}