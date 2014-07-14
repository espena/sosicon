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
#include "shapefile.h"

sosicon::shape::Shapefile::
Shapefile() { }

sosicon::shape::Shapefile::
~Shapefile() {

}

void sosicon::shape::Shapefile::
build( ISosiElement* sosiTree, sosi::ElementType selection ) {
    ShapeType shapeTypeEquivalent = getShapeEquivalent( selection );
    if( shape_type_none != shapeTypeEquivalent ) {
        ISosiElement* sosi = 0;
        while( sosiTree->getChild( sosi ) ) {
            if( selection == sosi->getType() ) {
                buildElement( sosi );
            }
        }
    }
}

void sosicon::shape::Shapefile::
buildElement( ISosiElement* sosi ) {

    ISosiElement* sosiHead = 0;
    ISosiElement* sosiOrigo = 0;
    sosi->getRoot()->getChild( sosiHead, sosi::sosi_element_head );
    sosiHead->getChild( sosiOrigo, sosi::sosi_element_origo_ne );
    std::cout << "Origo: " << sosiOrigo->getData() << "\n";

    CoordinateCollection cc;
    cc.discoverCoords( sosi );
    ICoordinate* c = 0;
    while( cc.getNextInGeom( c ) ) {
        
    }
}

void sosicon::shape::Shapefile::
insert( ISosiElement* sosiElement ) {

}

void sosicon::shape::Shapefile::
writeShp( std::ostream &os ) {

}

void sosicon::shape::Shapefile::
writeShx( std::ostream &os ) {

}

void sosicon::shape::Shapefile::
writeDbf( std::ostream &os ) {

}

void sosicon::shape::Shapefile::
writePrj( std::ostream &os ) {

}

sosicon::shape::ShapeType sosicon::shape::
getShapeEquivalent( sosi::ElementType sosiType ) {
    switch( sosiType ) {
        case sosi::sosi_element_area:
            return shape_type_polygon;
        case sosi::sosi_element_curve:
            return shape_type_polyLine;
        case sosi::sosi_element_point:
        case sosi::sosi_element_text:
            return shape_type_point;
        default:
            return shape_type_none;
    }
}