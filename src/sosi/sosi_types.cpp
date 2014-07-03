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
strToType( std::string sosiElementName ) {

    static std::map<std::string, ElementType> sosiTypeNameMap;

    ElementType type;

    if( sosiTypeNameMap.empty() ) {
        sosiTypeNameMap[ "ANNET"           ] = sosi_element_annet;            // Other
        sosiTypeNameMap[ "ENHET"           ] = sosi_element_enhet;            // Unit (mm)
        sosiTypeNameMap[ "FLATE"           ] = sosi_element_flate;            // Area
        sosiTypeNameMap[ "HODE"            ] = sosi_element_hode;             // File header
        sosiTypeNameMap[ "KOORDSYS"        ] = sosi_element_koordsys;         // Coordinate system
        sosiTypeNameMap[ "KURVE"           ] = sosi_element_kurve;            // Curve
        sosiTypeNameMap[ "NØ"              ] = sosi_element_no;               // North-east coordinate
        sosiTypeNameMap[ "OBJTYPE"         ] = sosi_element_objtype;          // Object type
        sosiTypeNameMap[ "PPDATERINGSDATO" ] = sosi_element_oppdateringsdato; // Update date
        sosiTypeNameMap[ "ORIGO-NØ"        ] = sosi_element_origo_no;         // Origo north-east
        sosiTypeNameMap[ "PUNKT"           ] = sosi_element_punkt;            // Point
        sosiTypeNameMap[ "REF"             ] = sosi_element_ref;              // Element reference
        sosiTypeNameMap[ "TEGNSETT"        ] = sosi_element_tegnsett;         // Character set
        sosiTypeNameMap[ "TEKST"           ] = sosi_element_tekst;            // Text
    }

    try{
        type = sosiTypeNameMap[ sosiElementName ];
    }
    catch( ... ) {
        type = sosi_element_annet;
    }

    return type;
}