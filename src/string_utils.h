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
#ifndef __STRING_UTILS_H
#define __STRING_UTILS_H

#include "memory.h"
#include <string>
#include <ctype.h>

namespace sosicon {

    //! String manipulation routines
    namespace stringUtils {

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

        //! Asserts correct name of application classes
        /*!
            Application classes should always begin with the 'App' prefix. This method
            adds the prefix to the provided class name if it is missing.
            \param className The class name string to be resolved and normalized.
            \return Normalized and corrected class name string.
        */
        std::string normalizeAppClassName( const std::string &className );

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

        std::string toLower( const std::string &from );

        std::string ucFirst( const std::string &str );

        void getPathInfo( std::string path, std::string &dir, std::string &tit, std::string &ext );
    };
};

#endif
