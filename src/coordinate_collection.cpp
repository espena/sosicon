/*
 *  This file is part of the command-line tool sosicon.
 *  Copyright (C) 2014  Espen Andersen
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
#include "coordinate_collection.h"

void sosicon::CoordinateCollection::
discoverCoords( ISosiElement* e ) {
    switch( e->getType() ) {
        case sosi::sosi_element_area:
            {
                ISosiElement* reference = 0;
                std::vector<ISosiElement*> references;
                while( e->getChild( reference, sosi::sosi_element_ref ) ) {
                    sosi::SosiRef ref( reference );
                    
                }
            }
            break;
        case sosi::sosi_element_charset:
        case sosi::sosi_element_coordsys:
        case sosi::sosi_element_curve:
        case sosi::sosi_element_head:
        case sosi::sosi_element_ne:
        case sosi::sosi_element_objtype:
        case sosi::sosi_element_origo_ne:
        case sosi::sosi_element_other:
        case sosi::sosi_element_point:
        case sosi::sosi_element_ref:
        case sosi::sosi_element_text:
        case sosi::sosi_element_unit:
        case sosi::sosi_element_updatedate:
            {
                
            }
            break;
    }
}