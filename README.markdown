# Sosicon v 0.1 (prerelease)
Converts SOSI files to a number of other formats, including TSV (tab delimited text file) and shape
files. Support for shape and other formats is yet to be implemented. TSV is well supported for some
features, but the parser is still under development.

Contributors are most welcome!

## Features
*  Swift conversion
*  Selectable feature/objtype/field export
*  Supports command-line piping on OS X/Linux
*  Written in ANSI C++
*  Compiles and runs on OS X, Linux and Windows

## Quick demo
To convert a SOSI file to tab delimited text, run sosicon from the directory where the SOSI file
resides. Use the -2tsv parameter to emit tab delimited values and the -o parameter to specify
output file:

`sosicon -2tsv -o output.tsv input.sos`

On Linux and OS X, batch conversion is supported by piping:

`ls *.sos | sosicon -2tsv`

The above command will convert every *.sos file in current directory to corresponding .tsv files.
The files will be written to the same directory with the same file title with tsv extension.
NOTE: Existing tsv-files will be overwritten.

To specify which SOSI fields to be included in the TSV output, use the -f parameter like this:

`ls *.sos | sosicon -2tsv -f "komm, post_nr, gatenavn, aid_husnr, aid_bokstav, hode:koordsys, koord_n, koord_o"`

The comma separated list of field names will be matched and their corresponding values will be
exported. Use the prefix `hode:` to address fields from the file header, such as `hode:koordsys`
(applied coordinate system).

If no fields are specified, all available fields will be exported except head element fields.

## Development
Sosicon is not ready for release, although TSV conversion works well with some SOSI features like
address points. The parser needs to be extended to include more features in accordance with the
SOSI specification.

### Ragel parser
The parser in sosicon is based on the [Ragel state machine compiler](http://www.complang.org/ragel/).
The ragel script is located in the src/parser directory. Ragel binaries for OS X, Linux and Win32
is precompiled and stored in /src/parser/ragel_bin/. The makefile is set up to reference the
correct binary when compiling on Linux or OS X.

Ragel was designed and written by Adrian Thurston and released under the
[GNU General Public License](http://www.gnu.org/licenses/gpl.txt) in 2002. Sosicon relies heavily
on the excellent work of Thurston and [his team of contributors](http://www.complang.org/ragel/CREDITS).

## License
Sosicon is written by Espen Andersen and released under the
[GNU General Public License](http://www.gnu.org/licenses/gpl.txt).
