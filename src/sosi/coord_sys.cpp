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
#include "coord_sys.h"

sosicon::sosi::CoordSys::
CoordSys( std::string id ) {
    mSosiId = id;
    std::stringstream tmp( mSosiId );
    tmp >> mId;

    switch( mId ) {

    case 1:
        mSrid = "27391";
        mDescription = "NGO-akse I";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "1";
        break;
            
    case 2:
        mSrid = "27392";
        mDescription = "NGO-akse II";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "2";
        break;
            
    case 3:
        mSrid = "27393";
        mDescription = "NGO-akse III";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "3";
        break;
           
    case 4:
        mSrid = "27394";
        mDescription = "NGO-akse IV";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "4";
        break;
            
    case 5:
        mSrid = "27395";
        mDescription = "NGO-akse V";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "5";
        break;
            
    case 6:
        mSrid = "27396";
        mDescription = "NGO-akse VI";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "6";
        break;
            
    case 7:
        mSrid = "27397";
        mDescription = "NGO-akse VII";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "7";
        break;
            
    case 8:
        mSrid = "27398";
        mDescription = "NGO-akse VIII";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "8";
        break;
            
    case 9:
        mSrid = "";
        mDescription = "NGO 48";
        mDatum = "NGO48 Geografisk";
        mProjection = "";
        mZone = "";
        break;
            
    case 21:
        mSrid = "32631";
        mDescription = "UTM-Sone 31";
        mDatum = "EUREF89/WGS84";
        mProjection = "UTM";
        mZone = "31";
        break;
            
    case 22:
        mSrid = "32632";
        mDescription = "UTM-Sone 32";
        mDatum = "EUREF89/WGS84";
        mProjection = "UTM";
        mZone = "32";
        break;
            
    case 23:
        mSrid = "32633";
        mDescription = "UTM-Sone 33";
        mDatum = "EUREF89/WGS84";
        mProjection = "UTM";
        mZone = "33";
        break;
            
    case 24:
        mSrid = "32634";
        mDescription = "UTM-Sone 34";
        mDatum = "EUREF89/WGS84";
        mProjection = "UTM";
        mZone = "34";
        break;
            
    case 25:
        mSrid = "32635";
        mDescription = "UTM-Sone 35";
        mDatum = "EUREF89/WGS84";
        mProjection = "UTM";
        mZone = "35";
        break;
            
    case 26:
        mSrid = "32636";
        mDescription = "UTM-Sone 36";
        mDatum = "EUREF89/WGS84";
        mProjection = "UTM";
        mZone = "36";
        break;
            
    case 31:
        mSrid = "23031";
        mDescription = "UTM-Sone 31";
        mDatum = "ED50";
        mProjection = "UTM";
        mZone = "31";
        break;
            
    case 32:
        mSrid = "23032";
        mDescription = "UTM-Sone 32";
        mDatum = "ED50";
        mProjection = "UTM";
        mZone = "32";
        break;
            
    case 33:
        mSrid = "23033";
        mDescription = "UTM-Sone 33";
        mDatum = "ED50";
        mProjection = "UTM";
        mZone = "33";
        break;
            
    case 34:
        mSrid = "23034";
        mDescription = "UTM-Sone 34";
        mDatum = "ED50";
        mProjection = "UTM";
        mZone = "34";
        break;
            
    case 35:
        mSrid = "23035";
        mDescription = "UTM-Sone 35";
        mDatum = "ED50";
        mProjection = "UTM";
        mZone = "35";
        break;
            
    case 36:
        mSrid = "23036";
        mDescription = "UTM-Sone 36";
        mDatum = "ED50";
        mProjection = "UTM";
        mZone = "36";
        break;

    case 41:
        mSrid = "Lokalnett uspes.";
        mDescription = "";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 42:
        mSrid = "Lokalnett uspes.";
        mDescription = "";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 50:
        mSrid = "";
        mDescription = "ED50 Geografisk";
        mDatum = "ED50";
        mProjection = "";
        mZone = "";
        break;
            
    case 51:
        mSrid = "";
        mDescription = "NGO-56A (Møre)";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "";
        break;
            
    case 52:
        mSrid = "";
        mDescription = "NGO-56B (Møre)";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "";
        break;
            
    case 53:
        mSrid = "";
        mDescription = "NGO-64A (Møre)";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "";
        break;
            
    case 54:
        mSrid = "";
        mDescription = "NGO-64B (Møre)";
        mDatum = "NGO1948";
        mProjection = "Gauss-Krüger";
        mZone = "";
        break;
            
    case 72:
        mSrid = "";
        mDescription = "WGS72 Geografisk";
        mDatum = "WGS72";
        mProjection = "";
        mZone = "";
        break;
            
    case 84:
        mSrid = "";
        mDescription = "WGS84 Geografisk";
        mDatum = "WGS84";
        mProjection = "";
        mZone = "";
        break;
            
    case 87:
        mSrid = "";
        mDescription = "ED87 Geografisk";
        mDatum = "ED87";
        mProjection = "";
        mZone = "";
        break;
            
    case 99:
        mSrid = "";
        mDescription = "Egendefinert";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 101:
        mSrid = "";
        mDescription = "Lokalnett, Oslo";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 102:
        mSrid = "";
        mDescription = "Lokalnett, Bærum";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 103:
        mSrid = "";
        mDescription = "Lokalnett, Asker";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 104:
        mSrid = "";
        mDescription = "Lokalnett, Lillehammer";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 105:
        mSrid = "";
        mDescription = "Lokalnett, Drammen";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 106:
        mSrid = "";
        mDescription = "Lokalnett, Bergen / Askøy";
        mDatum = "";
        mProjection = "";
        mZone = "";
        break;
            
    case 107:
        mSrid = "";
        mDescription = "";
        mDatum = "Lokalnett, Trondheim";
        mProjection = "";
        mZone = "";
        break;
            
    default:
        mSrid = "";
        mDescription = "";
        mDatum = "Ukjent koordinatsystem";
        mProjection = "";
        mZone = "";
        break;            
    }
}

sosicon::sosi::CoordSys::
~CoordSys() { }
