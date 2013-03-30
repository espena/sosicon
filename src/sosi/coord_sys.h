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
#ifndef __COORD_SYS_H__
#define __COORD_SYS_H__

#include <string>
#include <sstream>

namespace sosicon {

    namespace sosi {

        /*!
            \addtogroup gis_entities
            @{
        */
        //! Coordinate system
        /*!
            Resolves SOSI KOORDSYS codes and converts them to corresponting SRID identifiers if
            applicable. In SOSI, KOORDSYS is the equivalent to SRID, describing a set of predefined
            combinations of unit, datum and projection etc.
         */
    	class CoordSys {

        private:

            //! KOORDSYS id
            /*!
                The SOSI identifier for current reference system, named KOORDSYS in the file head.
             */
            int mId;

            //! KOORDSYS id
            /*!
                String representation of the SOSI identifier for current reference system, named
                KOORDSYS in the file head.
             */
            std::string mSosiId;

            //! SRID
            /*!
                Spatial reference system identifier, translation of the SOSI KOORDSYS ID. If no
                SRID exists for current KOORDSYS, this field will be empty. The SRID is a widely
                adopted standard for referencing various combinations of coordinate system, projection
                and datum.
             */
            std::string mSrid;

            //! Description of current reference
            /*!
                Textual description of current KOORDSYS (grid reference system), as stated in
                the SOSI standard.
             */
            std::string mDescription;

            //! Grid datum
            /*!
                Datum of current grid reference system. For instance "WGS84".
             */
            std::string mDatum;

            //! Map projection
            /*!
                Description of the current projection. For instance "Gauss-Krüger".
             */
            std::string mProjection;

            //! UTM zone / axis
            /*!
                The NGO axis or the UTM zone, dependent of current reference system.
             */
            std::string mZone;

        public:
        
            CoordSys( std::string id );
            virtual ~CoordSys();
        
            //! Retrieve mSosiId
            /*!
                \sa sosicon::CoordSys::mSosiId
             */
            std::string getSosiId()      { return mSosiId;      }

            //! Retrieve mDescription
            /*!
                \sa sosicon::CoordSys::mDescription
             */
            std::string getDescription() { return mDescription; }

            //! Retrieve mDatum
            /*!
                \sa sosicon::CoordSys::mDatum
             */
            std::string getDatum()       { return mDatum;       }

            //! Retrieve mProjection
            /*!
                \sa sosicon::CoordSys::mProjection
             */
            std::string getProjection()  { return mProjection;  }

            //! Retrieve mZone
            /*!
                \sa sosicon::CoordSys::mZone
             */
            std::string getZone()        { return mZone;        }

            //! Retrieve mSrid
            /*!
                \sa sosicon::CoordSys::mSrid
             */
            std::string getSrid()        { return mSrid;        }

    	}; // class coordsys
       /*! @} end group gis_entities */

    }; // namespace sosi

}; // namespace sosicon

#endif