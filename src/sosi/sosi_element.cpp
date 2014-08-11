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

sosicon::sosi::CoordSys sosicon::sosi::
sysCodeToCoordSys( int sysCode ) {

    static CoordSys coordSysTable[ MAX_COORDSYS_TABLE + 1 ];

    if( !coordSysTable[ 1 ].valid() ) {

        coordSysTable[   1 ] = CoordSys(   1, "NGO 1948 (Oslo) / NGO zone I", "PROJCS[\"NGO 1948 (Oslo) / NGO zone I\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",-4.666666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   2 ] = CoordSys(   2, "NGO 1948 (Oslo) / NGO zone II", "PROJCS[\"NGO 1948 (Oslo) / NGO zone II\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",-2.333333333333333],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   3 ] = CoordSys(   3, "NGO 1948 (Oslo) / NGO zone III", "PROJCS[\"NGO 1948 (Oslo) / NGO zone III\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",0],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   4 ] = CoordSys(   4, "NGO 1948 (Oslo) / NGO zone IV", "PROJCS[\"NGO 1948 (Oslo) / NGO zone IV\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",2.5],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   5 ] = CoordSys(   5, "NGO 1948 (Oslo) / NGO zone V", "PROJCS[\"NGO 1948 (Oslo) / NGO zone V\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",6.166666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   6 ] = CoordSys(   6, "NGO 1948 (Oslo) / NGO zone VI", "PROJCS[\"NGO 1948 (Oslo) / NGO zone VI\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",10.16666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   7 ] = CoordSys(   7, "NGO 1948 (Oslo) / NGO zone VII", "PROJCS[\"NGO 1948 (Oslo) / NGO zone VII\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",14.16666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   8 ] = CoordSys(   8, "NGO 1948 (Oslo) / NGO zone VIII", "PROJCS[\"NGO 1948 (Oslo) / NGO zone VIII\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",18.33333333333333],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[   9 ] = CoordSys(   9, "NGO 1948 (Oslo)", "GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]]" );
        coordSysTable[  19 ] = CoordSys(  19, "ETRS89 / UTM zone 29N", "PROJCS[\"ETRS89 / UTM zone 29N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  20 ] = CoordSys(  20, "ETRS89 / UTM zone 30N", "PROJCS[\"ETRS89 / UTM zone 30N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  21 ] = CoordSys(  21, "ETRS89 / UTM zone 31N", "PROJCS[\"ETRS89 / UTM zone 31N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  22 ] = CoordSys(  22, "ETRS89 / UTM zone 32N", "PROJCS[\"ETRS89 / UTM zone 32N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  23 ] = CoordSys(  23, "ETRS89 / UTM zone 33N", "PROJCS[\"ETRS89 / UTM zone 33N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",15],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  24 ] = CoordSys(  24, "ETRS89 / UTM zone 34N", "PROJCS[\"ETRS89 / UTM zone 34N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",21],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  25 ] = CoordSys(  25, "ETRS89 / UTM zone 35N", "PROJCS[\"ETRS89 / UTM zone 35N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",27],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  26 ] = CoordSys(  26, "ETRS89 / UTM zone 36N", "PROJCS[\"ETRS89 / UTM zone 36N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",33],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  31 ] = CoordSys(  31, "ED50 / UTM zone 31N", "PROJCS[\"ED50 / UTM zone 31N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  32 ] = CoordSys(  32, "ED50 / UTM zone 32N", "PROJCS[\"ED50 / UTM zone 32N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  33 ] = CoordSys(  33, "ED50 / UTM zone 33N", "PROJCS[\"ED50 / UTM zone 33N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",15],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  34 ] = CoordSys(  34, "ED50 / UTM zone 34N", "PROJCS[\"ED50 / UTM zone 34N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",21],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  35 ] = CoordSys(  35, "ED50 / UTM zone 35N", "PROJCS[\"ED50 / UTM zone 35N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",27],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  36 ] = CoordSys(  36, "ED50 / UTM zone 36N", "PROJCS[\"ED50 / UTM zone 36N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",33],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  59 ] = CoordSys(  59, "WGS_1984_UTM_Zone_29N", "PROJCS[\"WGS_1984_UTM_Zone_29N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  60 ] = CoordSys(  60, "WGS_1984_UTM_Zone_30N", "PROJCS[\"WGS_1984_UTM_Zone_30N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  61 ] = CoordSys(  61, "WGS_1984_UTM_Zone_31N", "PROJCS[\"WGS_1984_UTM_Zone_31N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  62 ] = CoordSys(  62, "WGS_1984_UTM_Zone_32N", "PROJCS[\"WGS_1984_UTM_Zone_32N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  63 ] = CoordSys(  63, "WGS_1984_UTM_Zone_33N", "PROJCS[\"WGS_1984_UTM_Zone_33N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",15],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  64 ] = CoordSys(  64, "WGS_1984_UTM_Zone_34N", "PROJCS[\"WGS_1984_UTM_Zone_34N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",21],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  65 ] = CoordSys(  65, "WGS_1984_UTM_Zone_35N", "PROJCS[\"WGS_1984_UTM_Zone_35N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",27],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  66 ] = CoordSys(  66, "WGS_1984_UTM_Zone_36N", "PROJCS[\"WGS_1984_UTM_Zone_36N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",33],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        coordSysTable[  73 ] = CoordSys(  73, "ETRS89 / ETRS-LAEA", "PROJCS[\"ETRS89 / ETRS-LAEA\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Azimuthal_Equal_Area\"],PARAMETER[\"latitude_of_origin\",52],PARAMETER[\"central_meridian\",10],PARAMETER[\"false_easting\",4321000],PARAMETER[\"false_northing\",3210000],UNIT[\"Meter\",1]]" );
        coordSysTable[  74 ] = CoordSys(  74, "ETRS89 / ETRS-LCC", "PROJCS[\"ETRS89 / ETRS-LCC\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Conformal_Conic\"],PARAMETER[\"standard_parallel_1\",35],PARAMETER[\"standard_parallel_2\",65],PARAMETER[\"latitude_of_origin\",52],PARAMETER[\"central_meridian\",10],PARAMETER[\"false_easting\",4000000],PARAMETER[\"false_northing\",2800000],UNIT[\"Meter\",1]]" );
        coordSysTable[  84 ] = CoordSys(  84, "ETRS89", "GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]]" );
        coordSysTable[ 184 ] = CoordSys( 184, "GCS_WGS_1984", "GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]]" );
    }

    return coordSysTable[ sysCode ];
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