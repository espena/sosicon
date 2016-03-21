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
#ifndef __UTILS_H
#define __UTILS_H

#include "memory.h"
#include "common_types.h"
#include <sys/stat.h>
#include <locale>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>

namespace sosicon {

    //! String manipulation routines
    namespace utils {

        //! Converts Class name to file name string
        /*!
            Class names are written in pascal case (i.e. 'CarmineEntity', 'XMLParser').
            This method constructs a file name string for a given class name
            (i.e. 'carmine_entity', 'xml_parser'). The file names are always written
            in lower case, with underscores separating the words.
            \param className The pascal-cased class name to convert to a file name.
            \return The file name string without extension.
        */
        std::string className2FileName( const std::string &className );

        //! Split a string by a character
        /*!
            The source string str is split by the delimiter character, and each part 
            is put sequentially in a vector of strings, excluding the
            delimiter character.
            \param delimiter The delimiter character, typically a comma or a semicolon.
            \param str The source string to be split into a vector of substrings.
            \return A vector of strings, each of which are substrings of str.
        */
        std::vector<std::string> explode( char delimiter, std::string str );

        //! Test if file exists
        inline bool fileExists( const std::string& name ) {
          struct stat buffer;
          return ( stat( name.c_str(), &buffer ) == 0 );
        }

        //! Test if a string represents a numeric value
        /*!
            Returns true if the provided string contains numers only, and if the first
            digit is not zero. Numbers with leading zeros should be treated as strings,
            since they might be phone numbers, post numbers or municipal codes.
            \param str The string value to test.
            \return True if the string represents a numeric value with no leading zero,
                    otherwise false.
        */
        bool isNumeric( const std::string& str );

        //! Asserts output file name to be non-existing
        /*!
            Tests candidate file paths to find a unique output file name, appending
            and incrementing a serial number until a "free" name is encountered.
            \param defaultName If the output file name is not specified on the
                   command-line, the default file name will be used as
                   a starting point.
            \return Path to non-existing output file.
        */
        std::string nonExistingFilename( std::string defaultName );

        //! Asserts correct name of application classes
        /*!
            Application classes should always begin with the 'App' prefix. This method
            adds the prefix to the provided class name if it is missing.
            \param className The class name string to be resolved and normalized.
            \return Normalized and corrected class name string.
        */
        std::string normalizeAppClassName( const std::string &className );

        //! Remove carriage returns and line feeds
        /*!
            Removes newlines from the target string. The \r or \n characters may
            be anywhere in the string.
            \param str The string to be purged.
            \return The result string.
        */
        std::string purgeCrLf( std::string str );

        //! Repeat string N times
        /*!
            Creates a new string containing the provided string sequence for a
            predetermined number of repetitions.
            \param seq Reference to the string to be repeated.
            \param count The numner of times to repeat the string sequence.
            \return The result string.
        */
        std::string repeat( const std::string &seq, unsigned int count );

        //! Replace all occurences of one string witn another
        /*!
            Searches for a given string sequence, replacing all occurences by th
            provided substitution string.
            \param from The string sequence to be changed.
            \param to The string to replace the 'from' sequence with.
            \param subject The string to perform the search on.
            \return The new string, a copy of 'subject' where all occurences of
                    'from' are replaced with 'to'.
        */
        std::string replaceAll( const std::string &from, const std::string &to, const std::string &subject );

        //! Sanitizes SQL data string.
        /*!
            Escapes special characters in a string for use in an SQL statement.
            \param str The target string.
            \return A copy of the target string, with reserved characters escaped.
        */
        std::string sqlNormalize( const std::string &str );

        //! Removes leading and trailing space characters
        /*!
            Space characters in the beginning and at the end of the source 
            string are trimmed.
            \param str The target string.
            \return A copy of the target string, without leading and/or trailing 
                    space characters.
        */
        std::string trim( const std::string &str );

        std::string trimLeft( const std::string &str );

        std::string trimRight( const std::string &str );

        //! Substitutes Norwegian characters
        std::string toFieldname( const std::string &from );

        std::string toLower( const std::string &from );

        std::string ucFirst( const std::string &str );

        void getPathInfo( std::string path, std::string &dir, std::string &tit, std::string &ext );

        //! Get Well Known Text from Wkt enum
        std::string wktToStr( Wkt wktGeom );

    };
};

#endif
