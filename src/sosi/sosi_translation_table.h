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
#ifndef __SOSI_TRANSLATION_TABLE_H__
#define __SOSI_TRANSLATION_TABLE_H__

#include <map>
#include <vector>
#include "sosi_types.h"
#include "sosi_charset_singleton.h"

namespace sosicon {

    //! SOSI
    namespace sosi {

        /*!
            \addtogroup sosi_elements SOSI Elements
            Implemented representation of SOSI file elements.
            @{
        */

        class SosiTranslationTable {

            //! Character encoding element
            SosiCharsetSingleton* mSosiCharset;

            //! Number of entries in KOORDSYS lookup table
            static const int MAX_COORDSYS_TABLE = 184;

            // ---- the tables ----

            //! SOSI element name map
            /*!
                STL map with string key.
            */
            static std::map<std::string, ElementType> mTypeNameMap;

            //! OBJTYPE name lookup table
            /*!
                STL map with string key.
            */
            static std::map<std::string, ObjType> mObjTypeNameMap;

            //! KOORDSYS code lookup table
            /*!
                Primitive array, int key.
            */
            static CoordSys mCoordSysTable[ MAX_COORDSYS_TABLE + 1 ];

            //! Scan container looking for value, returning key
            template<typename Key, typename Val>
            Key reverseLookup( std::map<Key, Val>& c, Val v ) {
                for( typename std::map<Key, Val>::iterator i = c.begin(); i != c.end(); i++ ) {
                    if( i->second == v ) return i->first;
                }
                return Key(); // empty
            }

        public:

            SosiTranslationTable();

            CoordSys& sysCodeToCoordSys( int sysCode ) {
                if( sysCode <= MAX_COORDSYS_TABLE && sysCode > 0 ) return mCoordSysTable[ sysCode ];
                else return mCoordSysTable[ 0 ];
            };

            ElementType sosiNameToType( std::string typeName ) {
                try { return mTypeNameMap[ mSosiCharset->toIso8859_1( typeName ) ]; }
                catch( ... ) { return sosi_element_unknown; }
            };

            std::string sosiTypeToName( ElementType elementType ) {
                return reverseLookup<std::string, ElementType>( mTypeNameMap, elementType );
            };

            ObjType sosiObjNameToType( std::string objTypeName ) {
                try { return mObjTypeNameMap[ mSosiCharset->toIso8859_1( objTypeName ) ]; }
                catch( ... ) { return sosi_objtype_unknown; }
            };

            std::string sosiTypeToObjName( ObjType objType ) {
                return reverseLookup<std::string, ObjType>( mObjTypeNameMap, objType );
            };

        }; // class SosiTranslationTable

       /*! @} end group sosi_elements */

    }; // namespace sosi

}; // namespace sosicon

#endif
