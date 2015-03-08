# Sosicon v 0.1 (under development)
For Linux, OS X and Windows. Converts SOSI files to a number of other formats, including shapefile and
PostGIS database import files. The parser is still under development.

SOSI is a data format used for exchanging geographical information in Norway. The name is an acronym
for _"Samordnet Opplegg for Stedfestet Informasjon"_, which translates into something like
_"Coordinated Approach for Geospatial Information"_. [Wikipedia](https://en.wikipedia.org/wiki/SOSI)
has more.

Project home page: [sosicon.espenandersen.no](http://sosicon.espenandersen.no/).

Contributors are most welcome!

## Features
*  Swift conversion
*  Selectable feature/objtype/field export
*  Supports command-line piping on OS X/Linux
*  Written in ANSI C++
*  Compiles and runs on OS X, Linux (32 and 64 bit) and Windows

## Quick demo
Prebuilt Sosicon binaries are located in the /bin directory of the repo. Choose your OS and put the
executable in a location where it can be run from the command line.

* [Linux 32-bit executable](https://github.com/espena/sosicon/tree/master/bin/linux32)
* [Linux 64-bit executable](https://github.com/espena/sosicon/tree/master/bin/linux64)
* [OS X executable](https://github.com/espena/sosicon/tree/master/bin/osx)
* [Windows executable](https://github.com/espena/sosicon/tree/master/bin/win)

You can inspect the content of a SOSI file by using the -stat command, like this:

`sosicon -stat input.sos`

This command will render a list of SOSI elements (geometry types among other things) and SOSI
object types (OBJTYPE).

## Shapefile conversion

To convert a SOSI file to shape, run Sosicon from the directory where the SOSI file
resides. Use the -2shp parameter to emit the three required files: Shape file (shp), database
file (dbf) and index file (shx). A projection file (prj) will also be created if the
reference grid is recognized by Sosicon.

`sosicon -2shp input.sos`

On Linux and OS X, batch conversion is supported by piping:

`ls *.sos | sosicon -2shp`

The above command will convert every *.sos file in current directory to corresponding shapefiles.
The files will be written to the same directory, keeping the file title extended with feature name,
geometry type and shp/shx/dbf extensions.

Use the -o parameter to specify optional output file basename:

`sosicon -2shp -o ~/myfolder/arealdekke input.sos`

## PostGIS conversion

Use the -2psql parameter to make a PostGIS import file (SQL script) from a SOSI file. The generated
SQL file can be run against any PostgreSQL database with PostGIS installed. Use the
[psql command-line utility](http://www.postgresql.org/docs/9.3/static/app-psql.html) to import the file.

`sosicon -2psql input.sos`

This command will create a default SQL file named "postgis_dump.sql". When imported to PostgreSQL, the
data tables will be put in the schema "sosicon" by default. There will be one table for each recognized
geometry in the SOSI file. The tables will be named "object_point", "object_polygon" and "object_linestring".

The "-schema" and "-table" parameters can be used to customize the schema and table base name:

`sosicon -2psql -schema topo -table arealdekke input.sos`

When imported to PostgreSQL, the tables will be named "arealdekke_point", "arealdekke_polygon" and
"arealdekke_linestring". The tables will be put in a schema named "topo".

By default, the SOSI geometries are converted to [EPSG:4326](http://spatialreference.org/ref/epsg/4623/)
grid when imported to PostgreSQL. Use the "-srid" parameter to specify another target grid, for example
Google mercator; SRID 900913:

`sosicon -2psql -schema topo -table arealdekke -srid 900913 input.sos`

PostGIS takes care of the actual grid conversion when the data is inserted into the table(s). The user
must assert that the target srid exists in PostGIS' spatial_ref_sys table.

## Build from source code

###Linux/OS X
You need g++ to compile Sosicon. To build from source code, check out the git repository, enter the
src directory and run `make`. There's no `configure` or `make install` yet. On 32-bit Linux systems, the
binaries will be output to [bin/linux32](https://github.com/espena/sosicon/tree/master/bin/linux32).
On 64-bit Linux systems, the binaries will be output to
[bin/linux64](https://github.com/espena/sosicon/tree/master/bin/linux64). On OS X, the binaries will be
output in <em>[bin/osx](https://github.com/espena/sosicon/tree/master/bin/osx)</em>.

###Windows
Project files for Visual Studio is included in the repository. Open src/sosicon.sln solution
file in Visual Studio (Express) 2013 and build the project from there.

## Development
Sosicon is not ready for release, although SHP conversion works reasonably well with some SOSI features.

## Source documentation
Documentation exists in html, rtf and pdf formats. See the doc directory within the repository or visit [sosicon.espenandersen.no](http://sosicon.espenandersen.no/) for an online version.

The source code documentation for sosicon is generated by the brilliant [Doxygen](http://www.stack.nl/~dimitri/doxygen/) code documentation tool written by Dimitri van Heesch.

### Ragel parser
The parser in sosicon is based on the [Ragel state machine compiler](http://www.complang.org/ragel/).
The ragel script is located in the src/ragel directory. Ragel binaries for OS X, Linux 32- and 64-bit and
Win32 is precompiled and stored in /src/ragel/bin/. The makefile is set up to reference the correct binary
when compiling on Linux or OS X.

Ragel was designed and written by Adrian Thurston and released under the
[GNU General Public License](http://www.gnu.org/licenses/gpl.txt) in 2002. Sosicon relies heavily
on the excellent work of Thurston and [his team of contributors](http://www.complang.org/ragel/CREDITS).

## License and disclaimer
Sosicon is written by Espen Andersen, and released under the [GNU General Public License](http://www.gnu.org/licenses/gpl.txt).

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

Although the author has attempted to find and correct any bugs in the free software programs, the author is not responsible for any damage or losses of any kind caused by the use or misuse of the programs. The author is under no obligation to provide support, service, corrections, or upgrades to the free software programs.
