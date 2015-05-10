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
#include "sosi_translation_table.h"

// Static members
std::map<std::string, sosicon::sosi::ElementType> sosicon::sosi::SosiTranslationTable::mTypeNameMap;
std::map<std::string, sosicon::sosi::ObjType> sosicon::sosi::SosiTranslationTable::mObjTypeNameMap;
sosicon::sosi::CoordSys sosicon::sosi::SosiTranslationTable::mCoordSysTable[ MAX_COORDSYS_TABLE + 1 ];

sosicon::sosi::SosiTranslationTable::
SosiTranslationTable() {

    mSosiCharset = SosiCharsetSingleton::getInstance();

    if( mTypeNameMap.empty() ) {
        mTypeNameMap[ "DATAFANGSTDATO"   ] = sosi_element_data_collection_date; // Data collection date
        mTypeNameMap[ "EIER"             ] = sosi_element_owner;                // Dataset owner
        mTypeNameMap[ "ENHET"            ] = sosi_element_unit;                 // Unit (fraction of a metre)
        mTypeNameMap[ "FLATE"            ] = sosi_element_surface;              // Surface
        mTypeNameMap[ "HODE"             ] = sosi_element_head;                 // File header
        mTypeNameMap[ "H\xD8YDE"         ] = sosi_element_height;               // Height
        mTypeNameMap[ "IATAKODE"         ] = sosi_element_iata_code;            // IATA code (aviation)
        mTypeNameMap[ "ICAOKODE"         ] = sosi_element_icao_code;            // ICAO code (aviation)
        mTypeNameMap[ "KOMM"             ] = sosi_element_municipality;         // Municipality
        mTypeNameMap[ "KOORDSYS"         ] = sosi_element_coordsys;             // Coordinate system
        mTypeNameMap[ "KURVE"            ] = sosi_element_curve;                // Curve
        mTypeNameMap[ "KVALITET"         ] = sosi_element_quality;              // Quality of data
        mTypeNameMap[ "LUFTHAVNVEIER"    ] = sosi_element_airport_roads;        // Airport roads
        mTypeNameMap[ "LUFTHAVNTYPE"     ] = sosi_element_airport_type;         // Airport type
        mTypeNameMap[ "MAX-N\xD8"        ] = sosi_element_max_ne;               // Maximum north-east (bbox)
        mTypeNameMap[ "MIN-N\xD8"        ] = sosi_element_min_ne;               // Minimum north-east (bbox)
        mTypeNameMap[ "NAVN"             ] = sosi_element_name;                 // Name
        mTypeNameMap[ "N\xD8"            ] = sosi_element_ne;                   // North-east coordinate (NØ)
        mTypeNameMap[ "N\xD8H"           ] = sosi_element_ne;                   // North-east/height coordinate (NØH)
        mTypeNameMap[ "OBJTYPE"          ] = sosi_element_objtype;              // Object type
        mTypeNameMap[ "OMR\xC5""DE"      ] = sosi_element_area;                 // Area
        mTypeNameMap[ "OPPDATERINGSDATO" ] = sosi_element_updatedate;           // Update date
        mTypeNameMap[ "ORIGO-N\xD8"      ] = sosi_element_origo_ne;             // Origo north-east
        mTypeNameMap[ "PRODUSENT"        ] = sosi_element_vendor;               // Data vendor
        mTypeNameMap[ "PUNKT"            ] = sosi_element_point;                // Point
        mTypeNameMap[ "REF"              ] = sosi_element_ref;                  // Element reference
        mTypeNameMap[ "SOSI-NIV\xC5"     ] = sosi_element_level;                // SOSI level
        mTypeNameMap[ "SOSI-VERSJON"     ] = sosi_element_version;              // SOSI version
        mTypeNameMap[ "TEGNSETT"         ] = sosi_element_charset;              // Character set
        mTypeNameMap[ "TEKST"            ] = sosi_element_text;                 // Text label
        mTypeNameMap[ "TRAFIKKTYPE"      ] = sosi_element_traffic_type;         // Traffic type
        mTypeNameMap[ "TRANSPAR"         ] = sosi_element_transpar;             // Datum/projection/coordsys
        mTypeNameMap[ "VANNBR"           ] = sosi_element_water_width;          // Water width
        mTypeNameMap[ "VEGADRESSEIDENT"  ] = sosi_element_address_identifier;   // Street address identifier
    }

    if( mObjTypeNameMap.empty() ) {
        mObjTypeNameMap[ "Arealbrukgrense"          ] = sosi_objtype_land_use_boundary;                   // Land use boundary
        mObjTypeNameMap[ "Dataavgrensning"          ] = sosi_objtype_data_delineation;                    // Data delineation
        mObjTypeNameMap[ "ElvBekk"                  ] = sosi_objtype_river_brook;                         // River or stream
        mObjTypeNameMap[ "ElvBekkKant"              ] = sosi_objtype_river_brook_edge;                    // River or stream bank
        mObjTypeNameMap[ "FiktivDelelinje"          ] = sosi_objtype_fictious_dividing_line;              // Line splitting large surfeces
        mObjTypeNameMap[ "Fortau"                   ] = sosi_objtype_sidewalk;                            // Sidewalk
        mObjTypeNameMap[ "Fylkesgrense"             ] = sosi_objtype_county_boundary;                     // Virtual border
        mObjTypeNameMap[ "Gateadresse"              ] = sosi_objtype_street_address;                      // street address
        mObjTypeNameMap[ "GangSykkelVegSenterlinje" ] = sosi_objtype_pedestrian_bicycle_road_centre_line; // mid-way line
        mObjTypeNameMap[ "Golfbane"                 ] = sosi_objtype_golf_course;                         // Golf course
        mObjTypeNameMap[ "Grunnlinje"               ] = sosi_objtype_baseline;                            // Baseline
        mObjTypeNameMap[ "HavElvSperre"             ] = sosi_objtype_sea_river_delineation;               // Sea or river delineation
        mObjTypeNameMap[ "Havflate"                 ] = sosi_objtype_sea_surface;                         // Sea surface
        mObjTypeNameMap[ "Industriomr\xE5""de"      ] = sosi_objtype_industrial_area;                     // Industrial area
        mObjTypeNameMap[ "Innsj\xF8"                ] = sosi_objtype_lake;                                // Lake
        mObjTypeNameMap[ "Innsj\xF8""ElvSperre"     ] = sosi_objtype_lake_river_barrier;                  // Lake-to-river delineation
        mObjTypeNameMap[ "Innsj\xF8kant"            ] = sosi_objtype_lake_edge;                           // Lake edge
        mObjTypeNameMap[ "KantUtsnitt"              ] = sosi_objtype_edge_view;                           // Edge view
        mObjTypeNameMap[ "Kj\xF8rebane"             ] = sosi_objtype_carriageway;                         // Carriageway
        mObjTypeNameMap[ "Kj\xF8refelt"             ] = sosi_objtype_lane;                                // Lane
        mObjTypeNameMap[ "Kommune"                  ] = sosi_objtype_municipality;                        // Municipality
        mObjTypeNameMap[ "Kommunedele"              ] = sosi_objtype_municipal_divide;                    // Municipal boundary crossing
        mObjTypeNameMap[ "Kommunegrense"            ] = sosi_objtype_municipality_boundary;               // Municipality boundary
        mObjTypeNameMap[ "Kystkontur"               ] = sosi_objtype_coastline;                           // Shoreline
        mObjTypeNameMap[ "Lufthavn"                 ] = sosi_objtype_airport;                             // Airport
        mObjTypeNameMap[ "LufthavnType"             ] = sosi_objtype_airport_type;                        // Airport type
        mObjTypeNameMap[ "Matrikkeladresse"         ] = sosi_objtype_cadastral_address;                   // Cadastral address
        mObjTypeNameMap[ "Myr"                      ] = sosi_objtype_marsh;                               // Marsh
        mObjTypeNameMap[ "Planovergang"             ] = sosi_objtype_level_crossing;                      // Track level crossing
        mObjTypeNameMap[ "Riksgrense"               ] = sosi_objtype_national_border;                     // National border
        mObjTypeNameMap[ "Skog"                     ] = sosi_objtype_forest;                              // Forest
        mObjTypeNameMap[ "Skrivem\xE5te"            ] = sosi_objtype_spelling;                            // Spelling of place names
        mObjTypeNameMap[ "Sn\xF8Isbre"              ] = sosi_objtype_snow_field;                          // Snow/glacier
        mObjTypeNameMap[ "Steinbrudd"               ] = sosi_objtype_stone_quarry;                        // Area for stone quarry
        mObjTypeNameMap[ "Svingekonnekteringslenke" ] = sosi_objtype_turn_connecting_segment;             // artificial object, turn lane conn.
        mObjTypeNameMap[ "Territorialgrense"        ] = sosi_objtype_territorial_boundary;                // Territorial boundary (nautical)
        mObjTypeNameMap[ "TettBebyggelse"           ] = sosi_objtype_developed_area;                      // Built-up area
        mObjTypeNameMap[ "Valgkretsgrense"          ] = sosi_objtype_constituency_boundary;               // Constituency boundary
        mObjTypeNameMap[ "VegSenterlinje"           ] = sosi_objtype_road_centre_line;                    // Road centre line
        mObjTypeNameMap[ "Vegsperring"              ] = sosi_objtype_road_block;                          // Road block
        mObjTypeNameMap[ "VegUnderBane"             ] = sosi_objtype_road_under_railway;                  // Road under railway
        mObjTypeNameMap[ "\xC5pentOmr\xE5""de"      ] = sosi_objtype_open_land;                           // Open land
    }

    if( !mCoordSysTable[ 1 ].valid() ) {
        mCoordSysTable[   1 ] = CoordSys(   1, "27391", "NGO 1948 (Oslo) / NGO zone I", "PROJCS[\"NGO 1948 (Oslo) / NGO zone I\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",-4.666666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   2 ] = CoordSys(   2, "27392", "NGO 1948 (Oslo) / NGO zone II", "PROJCS[\"NGO 1948 (Oslo) / NGO zone II\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",-2.333333333333333],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   3 ] = CoordSys(   3, "27393", "NGO 1948 (Oslo) / NGO zone III", "PROJCS[\"NGO 1948 (Oslo) / NGO zone III\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",0],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   4 ] = CoordSys(   4, "27394", "NGO 1948 (Oslo) / NGO zone IV", "PROJCS[\"NGO 1948 (Oslo) / NGO zone IV\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",2.5],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   5 ] = CoordSys(   5, "27395", "NGO 1948 (Oslo) / NGO zone V", "PROJCS[\"NGO 1948 (Oslo) / NGO zone V\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",6.166666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   6 ] = CoordSys(   6, "27396", "NGO 1948 (Oslo) / NGO zone VI", "PROJCS[\"NGO 1948 (Oslo) / NGO zone VI\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",10.16666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   7 ] = CoordSys(   7, "27397", "NGO 1948 (Oslo) / NGO zone VII", "PROJCS[\"NGO 1948 (Oslo) / NGO zone VII\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",14.16666666666667],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   8 ] = CoordSys(   8, "27398", "NGO 1948 (Oslo) / NGO zone VIII", "PROJCS[\"NGO 1948 (Oslo) / NGO zone VIII\",GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",58],PARAMETER[\"central_meridian\",18.33333333333333],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[   9 ] = CoordSys(   9,  "4817", "NGO 1948 (Oslo)", "GEOGCS[\"NGO 1948 (Oslo)\",DATUM[\"D_NGO_1948\",SPHEROID[\"Bessel_Modified\",6377492.018,299.1528128]],PRIMEM[\"Oslo\",10.72291666666667],UNIT[\"Degree\",0.017453292519943295]]" );
        mCoordSysTable[  19 ] = CoordSys(  19, "25829", "ETRS89 / UTM zone 29N", "PROJCS[\"ETRS89 / UTM zone 29N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  20 ] = CoordSys(  20, "25830", "ETRS89 / UTM zone 30N", "PROJCS[\"ETRS89 / UTM zone 30N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  21 ] = CoordSys(  21, "25831", "ETRS89 / UTM zone 31N", "PROJCS[\"ETRS89 / UTM zone 31N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  22 ] = CoordSys(  22, "25832", "ETRS89 / UTM zone 32N", "PROJCS[\"ETRS89 / UTM zone 32N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  23 ] = CoordSys(  23, "25833", "ETRS89 / UTM zone 33N", "PROJCS[\"ETRS89 / UTM zone 33N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",15],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  24 ] = CoordSys(  24, "25834", "ETRS89 / UTM zone 34N", "PROJCS[\"ETRS89 / UTM zone 34N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",21],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  25 ] = CoordSys(  25, "25835", "ETRS89 / UTM zone 35N", "PROJCS[\"ETRS89 / UTM zone 35N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",27],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  26 ] = CoordSys(  26, "25836", "ETRS89 / UTM zone 36N", "PROJCS[\"ETRS89 / UTM zone 36N\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",33],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  31 ] = CoordSys(  31, "23031", "ED50 / UTM zone 31N", "PROJCS[\"ED50 / UTM zone 31N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  32 ] = CoordSys(  32, "23032", "ED50 / UTM zone 32N", "PROJCS[\"ED50 / UTM zone 32N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  33 ] = CoordSys(  33, "23033", "ED50 / UTM zone 33N", "PROJCS[\"ED50 / UTM zone 33N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",15],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  34 ] = CoordSys(  34, "23034", "ED50 / UTM zone 34N", "PROJCS[\"ED50 / UTM zone 34N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",21],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  35 ] = CoordSys(  35, "23035", "ED50 / UTM zone 35N", "PROJCS[\"ED50 / UTM zone 35N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",27],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  36 ] = CoordSys(  36, "23036", "ED50 / UTM zone 36N", "PROJCS[\"ED50 / UTM zone 36N\",GEOGCS[\"ED50\",DATUM[\"D_European_1950\",SPHEROID[\"International_1924\",6378388,297]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",33],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  59 ] = CoordSys(  59, "32629", "WGS_1984_UTM_Zone_29N", "PROJCS[\"WGS_1984_UTM_Zone_29N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  60 ] = CoordSys(  60, "32630", "WGS_1984_UTM_Zone_30N", "PROJCS[\"WGS_1984_UTM_Zone_30N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",-3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  61 ] = CoordSys(  61, "32631", "WGS_1984_UTM_Zone_31N", "PROJCS[\"WGS_1984_UTM_Zone_31N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",3],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  62 ] = CoordSys(  62, "32632", "WGS_1984_UTM_Zone_32N", "PROJCS[\"WGS_1984_UTM_Zone_32N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",9],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  63 ] = CoordSys(  63, "32633", "WGS_1984_UTM_Zone_33N", "PROJCS[\"WGS_1984_UTM_Zone_33N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",15],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  64 ] = CoordSys(  64, "32634", "WGS_1984_UTM_Zone_34N", "PROJCS[\"WGS_1984_UTM_Zone_34N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",21],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  65 ] = CoordSys(  65, "32635", "WGS_1984_UTM_Zone_35N", "PROJCS[\"WGS_1984_UTM_Zone_35N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",27],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  66 ] = CoordSys(  66, "32636", "WGS_1984_UTM_Zone_36N", "PROJCS[\"WGS_1984_UTM_Zone_36N\",GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",33],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  73 ] = CoordSys(  73,  "3035", "ETRS89 / ETRS-LAEA", "PROJCS[\"ETRS89 / ETRS-LAEA\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Azimuthal_Equal_Area\"],PARAMETER[\"latitude_of_origin\",52],PARAMETER[\"central_meridian\",10],PARAMETER[\"false_easting\",4321000],PARAMETER[\"false_northing\",3210000],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  74 ] = CoordSys(  74,  "3034", "ETRS89 / ETRS-LCC", "PROJCS[\"ETRS89 / ETRS-LCC\",GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Lambert_Conformal_Conic\"],PARAMETER[\"standard_parallel_1\",35],PARAMETER[\"standard_parallel_2\",65],PARAMETER[\"latitude_of_origin\",52],PARAMETER[\"central_meridian\",10],PARAMETER[\"false_easting\",4000000],PARAMETER[\"false_northing\",2800000],UNIT[\"Meter\",1]]" );
        mCoordSysTable[  84 ] = CoordSys(  84,  "4258", "ETRS89", "GEOGCS[\"ETRS89\",DATUM[\"D_ETRS_1989\",SPHEROID[\"GRS_1980\",6378137,298.257222101]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]]" );
        mCoordSysTable[ 184 ] = CoordSys( 184,  "4326", "GCS_WGS_1984", "GEOGCS[\"GCS_WGS_1984\",DATUM[\"D_WGS_1984\",SPHEROID[\"WGS_1984\",6378137,298.257223563]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]]" );
    }
}
