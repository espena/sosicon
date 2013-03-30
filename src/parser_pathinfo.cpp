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
#include "parser.h"

void sosicon::Parser::
getPathInfo( std::string path, std::string &dir, std::string &tit, std::string &ext ) {
	std::string::size_type len = path.length();
	std::string tmp;
	while( len > 0 ) {
		const char c = path.at( --len );
		switch( c ) {
			case '.':
				tmp = ( c + tmp );
				if( ext.empty() ) {
					ext = tmp;
					tmp = "";
				}
				break;
			case '\\':
			case '/':
				if( tit.empty() ) {
					tit = tmp;
					tmp = c;
				}
				else {
					tmp = ( c + tmp );
				}
				break;
			default:
				tmp = ( c + tmp );
				break;
		}
	}
	if( tit.empty() ) {
		tit = tmp;
	}
	else {
		dir = tmp;
	}
}
