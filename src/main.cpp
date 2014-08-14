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
#include "main.h"

int main ( int argc, char* argv[] ) {
	
    std::ios_base::sync_with_stdio( 0 );

    sosicon::CommandLine cmd;
	cmd.parse( argc, argv );

	int res;
	
	try {
		sosicon::IConverter* converter = 0;
		sosicon::Factory::get( converter, &cmd );
		if( converter ) {
			converter->run();
			sosicon::Factory::release( converter );
		}
		res = 0;
	}
	catch( std::exception ex ) {
		std::cout << ex.what() << "\n";
		res = -1;
	}
	
	return res;

}
