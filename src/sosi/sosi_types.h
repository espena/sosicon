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
#ifndef __SOSI_TYPES_H__
#define __SOSI_TYPES_H__

#include "../interface/i_coordinate.h"
#include <string>
#include <vector>
#include <map>

namespace sosicon {

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        //! List of SOSI element types
        enum ElementType {
            sosi_element_unknown = 0,           //!< Unknown element
            sosi_element_address_identifier,    //!< Street address identifier
            sosi_element_airport_roads,         //!< Airport roads
            sosi_element_airport_type,          //!< Airport type
            sosi_element_area,                  //!< Area
            sosi_element_charset,               //!< Character set
            sosi_element_coordsys,              //!< Grid type
            sosi_element_curve,                 //!< Curve
            sosi_element_data_collection_date,  //!< Data collection date
            sosi_element_eof,                   //!< End of file
            sosi_element_head,                  //!< Header
            sosi_element_height,                //!< Height
            sosi_element_iata_code,             //!< IATA code (aviation)
            sosi_element_icao_code,             //!< ICAO code (aviation)
            sosi_element_kp,                    //!< Junction point
            sosi_element_level,                 //!< SOSI level
            sosi_element_max_ne,                //!< Maximum north-east (bbox)
            sosi_element_min_ne,                //!< Minimum north-east (bbox)
            sosi_element_municipality,          //!< Municipality
            sosi_element_name,                  //!< Name
            sosi_element_ne,                    //!< North-east coordinate
            sosi_element_neh,                   //!< North-east/height coordinate
            sosi_element_objtype,               //!< Object type
            sosi_element_origo_ne,              //!< Origo north-east
            sosi_element_owner,                 //!< Dataset owner
            sosi_element_point,                 //!< Point
            sosi_element_quality,               //!< Quality of data
            sosi_element_ref,                   //!< Element reference
            sosi_element_surface,               //!< Surface
            sosi_element_text,                  //!< Text
            sosi_element_traffic_type,          //!< Traffic type
            sosi_element_transpar,              //!< Datum/projection/coordinate system
            sosi_element_unit,                  //!< Resolution (fraction of a metre)
            sosi_element_updatedate,            //!< Update date
            sosi_element_water_width,           //!< Water width
            sosi_element_vendor,                //!< Data vendor
            sosi_element_version                //!< SOSI version
        };

        //! List of SOSI OBJTYPEs
        enum ObjType {
            sosi_objtype_unknown = 0,                         //!< Unknown or no feature
            sosi_objtype_airport,                             //!< Airport
            sosi_objtype_airport_type,                        //!< Airport type
            sosi_objtype_baseline,                            //!< Baseline
            sosi_objtype_carriageway,                         //!< Carriageway
            sosi_objtype_cadastral_address,                   //!< Cadastral address
            sosi_objtype_coastline,                           //!< Coast line
            sosi_objtype_constituency_boundary,               //!< Constituency boundary
            sosi_objtype_county_boundary,                     //!< County boundary
            sosi_objtype_data_delineation,                    //!< Clipping path
            sosi_objtype_edge_view,                           //!< Edge view
            sosi_objtype_fictious_dividing_line,              //!< Line splitting large surfeces
            sosi_objtype_forest,                              //!< Forest
            sosi_objtype_developed_area,                      //!< Built up area
            sosi_objtype_golf_course,                         //!< Golf course
            sosi_objtype_industrial_area,                     //!< Industrial area
            sosi_objtype_lake,                                //!< Lake
            sosi_objtype_lane,                                //!< Driving lane
            sosi_objtype_lake_edge,                           //!< Lake edge
            sosi_objtype_lake_river_barrier,                  //!< Lake-to-river delimitation
            sosi_objtype_land_use_boundary,                   //!< Land use border
            sosi_objtype_level_crossing,                      //!< Track level crossing
            sosi_objtype_municipal_divide,                    //!< Municipal boundary crossing
            sosi_objtype_municipality,                        //!< Municipality
            sosi_objtype_municipality_boundary,               //!< Municipality boundary
            sosi_objtype_marsh,                               //!< Marsh
            sosi_objtype_national_border,                     //!< National border
            sosi_objtype_pedestrian_bicycle_road_centre_line, //!< mid-way line
            sosi_objtype_sea_river_delineation,               //!< Sea or river delineation
            sosi_objtype_snow_field,                          //!< Snow/glacier
            sosi_objtype_open_land,                           //!< Open land
            sosi_objtype_river_brook,                         //!< River or stream
            sosi_objtype_river_brook_edge,                    //!< River or stream bank
            sosi_objtype_road_block,                          //!< Road block
            sosi_objtype_road_centre_line,                    //!< Road centre line
            sosi_objtype_road_under_railway,                  //!< Road under railway
            sosi_objtype_sea_surface,                         //!< Sea surface
            sosi_objtype_sidewalk,                            //!< Sidewalk
            sosi_objtype_spelling,                            //!< Spelling of place name
            sosi_objtype_stone_quarry,                        //!< Area for stone quarry
            sosi_objtype_street_address,                      //!< Street address
            sosi_objtype_territorial_boundary,                //!< Territorial boundary (nautical)
            sosi_objtype_turn_connecting_segment              //!< Turn connection segment (artificial)
        };

        //! SOSI character encodings
        enum Charset {
            sosi_charset_undetermined, //!< Charset element not yet encountered
            sosi_charset_ansi,         //!< ANSI; equals ISO8859-1
            sosi_charset_decn7,        //!< Dec Norwegian 7-bit
            sosi_charset_dosn8,        //!< MS-Dos Norwegian 8-bit
            sosi_charset_iso8859_1,    //!< ISO 8859-1
            sosi_charset_iso8859_10,   //!< ISO 8859-10 with samii characters
            sosi_charset_nd7,          //!< Norsk Data 7-bit
            sosi_charset_utf8          //!< UTF-8
        };

        //! Default SOSI junction point layer types
        enum JunctionPoint {
            sosi_junction_node = 1,         //!< Node point (KP 1)
            sosi_junction_connection = 900, //!< Connection point (KP 900)
            sosi_junction_open_end = 999    //!< Valid open-ended point (KP 999)
        };

        //! SOSI reference number
        struct ReferenceData {
            std::string serial;  //!< The element ID.
            bool reverse;        //!< Minus sign = reverse coordinate sequence.
            bool subtract;       //!< Parenthesis = subtract shape.
        };

        //! SOSI coordinate system
        class CoordSys {

            int mSysCode;               //!< SOSI SYSKODE
            std::string mSrid;          //!< EPSG SRID
            std::string mPrjString;     //!< Projection string
            std::string mDisplayString; //!< Display string

        public:

            CoordSys( ) : mSysCode( 0 ) {}

            CoordSys( int sysCode,
                      std::string srid,
                      std::string displayString,
                      std::string prjString ) : mSysCode( sysCode ),
                                                mSrid( srid ),
                                                mPrjString( prjString ),
                                                mDisplayString( displayString )  {}

            std::string displayString() { return mDisplayString; }

            std::string prjString() { return mPrjString; }

            std::string srid() { return mSrid; }

            bool valid() { return mSysCode != 0; }

        };

        //! List of SOSI references
        typedef std::vector<ReferenceData*> GeometryRef;

        //! Collection of SOSI reference lists
        typedef std::vector<GeometryRef*> GeometryCollection;

       /*! @} end group sosi_elements */

    } // namespace sosi

} // namespace sosicon

#endif
