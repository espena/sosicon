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
        sosiTypeNameMap[ "EIER"             ] = sosi_element_owner;            // Dataset owner
        sosiTypeNameMap[ "ENHET"            ] = sosi_element_unit;             // Unit (fraction of a metre)
        sosiTypeNameMap[ "FLATE"            ] = sosi_element_surface;          // Surface
        sosiTypeNameMap[ "HODE"             ] = sosi_element_head;             // File header
        sosiTypeNameMap[ "H\xD8YDE"         ] = sosi_element_height;           // Height
        sosiTypeNameMap[ "IATAKODE"         ] = sosi_element_iata_code;        // IATA code (aviation)
        sosiTypeNameMap[ "ICAOKODE"         ] = sosi_element_icao_code;        // ICAO code (aviation)
        sosiTypeNameMap[ "KOMM"             ] = sosi_element_municipality;     // Municipality
        sosiTypeNameMap[ "KOORDSYS"         ] = sosi_element_coordsys;         // Coordinate system
        sosiTypeNameMap[ "KURVE"            ] = sosi_element_curve;            // Curve
        sosiTypeNameMap[ "KVALITET"         ] = sosi_element_quality;          // Quality of data
        sosiTypeNameMap[ "LUFTHAVNVEIER"    ] = sosi_element_airport_roads;    // Airport roads
        sosiTypeNameMap[ "LUFTHAVNTYPE"     ] = sosi_element_airport_type;     // Airport type
        sosiTypeNameMap[ "MAX-N\xD8"        ] = sosi_element_max_ne;           // Maximum north-east (bbox)
        sosiTypeNameMap[ "MIN-N\xD8"        ] = sosi_element_min_ne;           // Minimum north-east (bbox)
        sosiTypeNameMap[ "NAVN"             ] = sosi_element_name;             // Name
        sosiTypeNameMap[ "N\xD8"            ] = sosi_element_ne;               // North-east coordinate (NØ)
        sosiTypeNameMap[ "OBJTYPE"          ] = sosi_element_objtype;          // Object type
        sosiTypeNameMap[ "OMR\xC5""DE"      ] = sosi_element_area;             // Area
        sosiTypeNameMap[ "OPPDATERINGSDATO" ] = sosi_element_updatedate;       // Update date
        sosiTypeNameMap[ "ORIGO-N\xD8"      ] = sosi_element_origo_ne;         // Origo north-east
        sosiTypeNameMap[ "PRODUSENT"        ] = sosi_element_vendor;           // Data vendor
        sosiTypeNameMap[ "PUNKT"            ] = sosi_element_point;            // Point
        sosiTypeNameMap[ "REF"              ] = sosi_element_ref;              // Element reference
        sosiTypeNameMap[ "SOSI-NIV\xC5"     ] = sosi_element_level;            // SOSI level
        sosiTypeNameMap[ "SOSI-VERSJON"     ] = sosi_element_version;          // SOSI version
        sosiTypeNameMap[ "TEGNSETT"         ] = sosi_element_charset;          // Character set
        sosiTypeNameMap[ "TEKST"            ] = sosi_element_text;             // Text label
        sosiTypeNameMap[ "TRAFIKKTYPE"      ] = sosi_element_traffic_type;     // Traffic type
        sosiTypeNameMap[ "TRANSPAR"         ] = sosi_element_transpar;         // Datum/projection/coordsys
        sosiTypeNameMap[ "VANNBR"           ] = sosi_element_water_width;      // Water width
    }

    try{
        type = sosiTypeNameMap[ sosiElementName ];
    }
    catch( ... ) {
        type = sosi_element_unknown;
    }

    return type;
}

sosicon::sosi::ObjType sosicon::sosi::
sosiObjNameToType( std::string sosiObjTypeName ) {

    static std::map<std::string, ObjType> sosiObjTypeNameMap;

    ObjType type;

    if( sosiObjTypeNameMap.empty() ) {
        sosiObjTypeNameMap[ "Arealbrukgrense"      ] = sosi_objtype_land_use_boundary;      // Land use boundary
        sosiObjTypeNameMap[ "Dataavgrensning"      ] = sosi_objtype_data_delineation;       // Data delineation
        sosiObjTypeNameMap[ "ElvBekk"              ] = sosi_objtype_river_brook;            // River or stream
        sosiObjTypeNameMap[ "ElvBekkKant"          ] = sosi_objtype_river_brook_edge;       // River or stream bank
        sosiObjTypeNameMap[ "FiktivDelelinje"      ] = sosi_objtype_fictious_dividing_line; // Line splitting large surfeces
        sosiObjTypeNameMap[ "Fylkesgrense"         ] = sosi_objtype_county_boundary;        // Virtual border
        sosiObjTypeNameMap[ "Golfbane"             ] = sosi_objtype_golf_course;            // Golf course
        sosiObjTypeNameMap[ "Grunnlinje"           ] = sosi_objtype_baseline;               // Baseline
        sosiObjTypeNameMap[ "HavElvSperre"         ] = sosi_objtype_sea_river_delineation;  // Sea or river delineation
        sosiObjTypeNameMap[ "Havflate"             ] = sosi_objtype_sea_surface;            // Sea surface
        sosiObjTypeNameMap[ "Industriomr\xE5""de"  ] = sosi_objtype_industrial_area;        // Industrial area
        sosiObjTypeNameMap[ "Innsj\xF8"            ] = sosi_objtype_lake;                   // Lake
        sosiObjTypeNameMap[ "Innsj\xF8""ElvSperre" ] = sosi_objtype_lake_river_barrier;     // Lake-to-river delineation
        sosiObjTypeNameMap[ "Innsj\xF8kant"        ] = sosi_objtype_lake_edge;              // Lake edge
        sosiObjTypeNameMap[ "Kantutsnitt"          ] = sosi_objtype_edge_view;              // Edge view
        sosiObjTypeNameMap[ "Kommune"              ] = sosi_objtype_municipality;           // Municipality
        sosiObjTypeNameMap[ "Kommunegrense"        ] = sosi_objtype_municipality_boundary;  // Municipality boundary
        sosiObjTypeNameMap[ "Kystkontur"           ] = sosi_objtype_coastline;              // Shoreline
        sosiObjTypeNameMap[ "Lufthavn"             ] = sosi_objtype_airport;                // Airport
        sosiObjTypeNameMap[ "LufthavnType"         ] = sosi_objtype_airport_type;           // Airport type
        sosiObjTypeNameMap[ "Myr"                  ] = sosi_objtype_marsh;                  // Marsh
        sosiObjTypeNameMap[ "Riksgrense"           ] = sosi_objtype_national_border;        // National border
        sosiObjTypeNameMap[ "Skog"                 ] = sosi_objtype_forest;                 // Forest
        sosiObjTypeNameMap[ "Sn\xF8Isbre"          ] = sosi_objtype_snow_field;             // Snow/glacier
        sosiObjTypeNameMap[ "Steinbrudd"           ] = sosi_objtype_stone_quarry;           // Area for stone quarry
        sosiObjTypeNameMap[ "Territorialgrense"    ] = sosi_objtype_territorial_boundary;   // Territorial boundary (nautical)
        sosiObjTypeNameMap[ "TettBebyggelse"       ] = sosi_objtype_developed_area;         // Built-up area
        sosiObjTypeNameMap[ "\xC5pentOmr\xE5""de"  ] = sosi_objtype_open_land;              // Open land
    }

    try{
        type = sosiObjTypeNameMap[ sosiObjTypeName ];
    }
    catch( ... ) {
        type = sosi_objtype_unknown;
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
    mObjType = sosi::sosi_objtype_unknown;
    mRoot = root ? root : this;
    if( !mSerial.empty() ) {
        mIndex[ mSerial ] = this;
    }
}

void sosicon::sosi::SosiElement::
addChild( ISosiElement* child ) {
    if( child->getType() == sosi::sosi_element_objtype ) {
        mObjType = sosiObjNameToType( child->getData() );
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