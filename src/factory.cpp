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
#include "factory.h"

void sosicon::Factory::
get( sosicon::IConverter* &converter, sosicon::CommandLine cmd ) {
    if( cmd.mCommand == "-2shp" ) {
        converter = new ConverterSosi2shp();
        converter->init( cmd );
    }
    else if( cmd.mCommand == "-2xml" ) {
        converter = new ConverterSosi2xml();
        converter->init( cmd );
    }
    else if( cmd.mCommand == "-2tsv" ) {
        converter = new ConverterSosi2tsv();
        converter->init( cmd );
    }
}

void sosicon::Factory::
release( sosicon::IConverter* &converter ) {
	delete converter;
	converter = 0;
}