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
#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "utils.h"
#include "command_line.h"
#include "sosi/sosi_element.h"
#include "interface/i_sosi_element.h"

namespace sosicon {

    //! SOSI file parser
    /*!
        \author Espen Andersen
        \copyright GNU General Public License

        The file parser. Reads and organizes SOSI file input, preparing the data for conversion
        and output. This class wraps a Ragel-generated state machine set up to parse SOSI content
        line-by-line. For more information about the Ragel state machine compiler, visit
        http://www.complang.org/ragel/
        
        Specifically, the function parseSosiLine() is implemented in Ragel. The implementation
        script is located in parser/parser_sosi_line.rl. The file parser_ragel.cpp is generated
        on the basis of parser/parser.rl during pre-build processing.
        
        \note Since parser_ragel.cpp is automatically re-generated before each compile, no
              redacting may take place here. Any changes will be lost upon compile. Instead, its
              source script parser/parser_rl has to be edited.
    */
    class Parser {

        //! Working stack
        /*!
            Keeps track of element relationship while parsing the SOSI file. The root element
            is inserted at the front of the stack. When the parser has completed, the stack should
            contain the root element only.
         */
        std::vector<ISosiElement*> mElementStack;

        //! Index
        /*!
            Index elements by serial number. Lookup table to resolve SOSI references (REF element).
         */
        sosi::SosiElementMap mElementIndex;

        //! SOSI level of element currently in parser
        /*!
            Intermediate storage member.
         */
        int mPendingElementLevel;

        //! Name of element currently in parser
        /*!
            Intermediate storage member.
         */
        std::string mPendingElementName;

        //! Serial number of element currently in parser
        /*!
            Intermediate storage member.
         */
        std::string mPendingElementSerial;

        //! Attribute data of element currently in parser
        /*!
            Intermediate storage member.
         */
        std::string mPendingElementAttributes;

        //! Save current SOSI element
        /*!
            The parser stores intermediate data in the mPendingElementXXX member variables. When 
            a SOSI element had been fully parsed, this function is called to move the data into
            the element tree structure before carrying on.
         */
        void digestPendingElement();

    public:

        //! Constructor
        /*!
            Initializes internal iterators and pointers.
         */
        Parser();

        //! Destructor
        /*!
            Calls Parser::reset() for final clean-up.
         */
        ~Parser();

        //! Flush parsed data
        void complete() { digestPendingElement(); };

        //! Debug output
        void dump();

        //! Retrieve pointer to root element
        ISosiElement* getRootElement();

        //! Main parser routine
        /*!
            Processes one line from the SOSI file. This function is called repeatedly, consuming
            the input file line-by-line until EOF.

            \note This function is implemented in the ragel script at parser/parser_sosi_line.rl,
                  the c++ file parser_sosi_line.cpp is merely generated from the ragel script.
                  Thus, any changes to the implementation must be done in the ragel script, since
                  the c++ file will be automatically overwritten during the pre-build process.

            \param sosiLine Current line from the SOSI input file.
         */
        void ragelParseSosiLine( std::string sosiLine );
        
    };
};

#endif
