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
#ifndef __PARSER_H__
#define __PARSER_H__

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "command_line.h"
#include "interface/i_sosi_element.h"
#include "sosi/coord_sys.h"
#include "sosi/sosi_element_head.h"
#include "sosi/sosi_element_curve.h"
#include "sosi/sosi_element_point.h"
#include "sosi/sosi_element_text.h"

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
        script is located in parser/parser_sosi_line.rl. The file parser_sosi_line.cpp is generated
        on the basis of parser/parser_sosi_line.rl during pre-build processing.
        
        \note Since parser_sosi_line.cpp is automatically re-generated before each compile, no
              redacting mat take place here. Any changes will be lost upon compile. Instead, its
              source script parser/parser_sosi_line.rl have to be edited.
    */
    class Parser {

        //! SOSI elements container
        /*!
            Stores pointers to all recognized and parsed SOSI file elements, except for the
            head element which is stored in Parser::mHeadElement. SOSI elements selected for output
            are pointed to by the items in Parser::mSosiElementsSelection.
        */
        std::vector<ISosiElement*> mSosiElements;

        //! SOSI elements selected for output
        /*!
            Sosicon may schedule only certain SOSI object types for output, ignoring other object
            types in current file. This member variable keeps track of the elements matching the
            current object type filter. The filtering is determined by the contents of
            Parser::mObjTypes.

            \sa mObjTypes
        */
        std::vector<ISosiElement*> mSosiElementsSelection;

        //! Current position within Parser::mSosiElements
        /*!
            Used internally by Parser::getNextSosiElement(). Keeps track of current position while
            iterating the list of SOSI elements for output.

            \sa Parser::getNextSosiElement()
        */
        std::vector<ISosiElement*>::iterator mSosiElementsIterator;

        //! List containing all encountered SOSI fields in file
        /*!
            Overview of all fields present in current SOSI file, regardless of object type.
            
            When exporting to certain file formats, such as tab separated values (tsv), this field
            overview determines what columns should be present in the output file - unless
            a custom field list is specified via the command-line interface
            (sosicon command-line parameter -f).

            \sa sosicon::ConverterSosi2tsv::run()
        */
        std::vector<std::string> mSosiElementsFields;

        //! Object type filter
        /*!
            SOSI object types scheduled for output. The vector is populated by the comma-separated
            values given by the command-line parameter -t. If the list is empty, all available 
            objects will be exported without filtering.

            \sa Parser::setObjTypeSelection()
        */
        std::vector<std::string> mObjTypeFilter;

        //! Pointer to the head element
        /*!
            The head element is not stored in the Parser::mSosiElements list because it contains
            data which is globally relevant to all elements in the SOSI file. Instead, it is
            available directly through this member. Parser::getHeadElement() provides external
            access to this member.
            
            \sa Parser::getHeadElement()
        */
        ISosiElement* mHeadElement;

        //! Pointer to last encountered SOSI element
        /*!
            Used internally by Parser::parseSosiLine() during file consumption.

            The Ragel implemented parser consumes the SOSI file one line at the time. When
            encountering a new SOSI object, a corresponding ISosiElement implementation is created
            and placed in Parser::mSosiElements and possibly Parser::mSosiElementsSelection.
            
            A pointer to the new object is assigned to this member in order to keep track of to
            the SOSI element currently in process.
            
            \sa Parser::parseSosiLine()
        */
        ISosiElement* mCurrentElement;

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

        //! Retrieve next SOSI element for output
        /*!
            Iterates through the list of SOSI elements to be exported for output.
            
            Takes a reference to a ISosiElement pointer and assigns it to the next SOSI element in
            list. If the pointer is 0, the iteration will start at the beginning, otherwise it will
            continue to the next element, until reaching the end of the list.
            
            If Parser::mSosiElementsSelection is populated, it will be promoted as the source list,
            thus emitting object types selected from the command-line only.
            
            If Parser::mSosiElementsSelection is empty, Parser::mSosiElements will be used instad, 
            emitting all encountered SOSI elements (except for the head element).
            
            \sa Parser::mSosiElements, Parser::mSosiElementsSelection
            \sa Parser::mSosiElementsIterator
            
            \note The pointer reference sosiElement must be initialized to zero before the first
                  call to this function, but not between calls. It will be reset to zero once the
                  iteration goes past the last element in list.

            Example of usage:

            \code

                ISosiElement* e = 0; // Must be initialized to zero!

                // p is instance of Parser:
                while( p.getNextSosiElement( e ) ) {

                    std::cout << e->getType() << "\n";

                }

            \endcode

            \param sosiElement Reference to a pointer receiving the address of the next element
                   in list. If the pointer's initial value is zero, the iteration will start at the
                   beginning of the list. When the iteration passes the last element, the pointer
                   will be reset to zero.

            \return Status of the iteration. Use the return value in a while-loop to retrieve all
                    values in sequence.
            \retval true Iteration is in progress. There are still more items to retrieve and the
                    loop may go on.
            \retval false The iteration reached the end of the list. There are no more items 
                    to retrieve and the loop must be terminated.
            
        */
        bool getNextSosiElement( ISosiElement*& sosiElement );

        //! Retrieve SOSI head
        /*!
            The SOSI head element is special, since it contains global information about all other
            elements in the file.
            
            This function returns a pointer to the head element.
            
            \sa Parser::mHeadElement
            
            \return Pointer to a ISosiElement representing the file head.
        */
        ISosiElement* getHeadElement();
        
        //! Retrieve list of encountered SOSI fields
        /*!
            Returns a summary of all fields encountered within current file. This function will
            iterate through every field in every SOSI element to build the field list. The list
            is lazy initialized and the build process is performed only once since it can be time
            consumng. Complexity is T(n) = O(n^2) and depends on the size of the input file.
            
            \return A reference to a string vector containing encountered field keys.
        */
        std::vector<std::string>& getSosiElementsFields();
        
        //! Get total number of SOSI elements
        /*!
            Returns total count of SOSI elements minus the head element.
            
            \return The count of all SOSI elements except the head element.
         */
        std::vector<std::string>::size_type getCountSosiElements();
        
        //! Get number of selected SOSI elements
        /*!
            Returns number of SOSI elements scheduled for output. If no object type selection was
            specified, or the Parser::mObjTypeFilter list is emtpy, the count of all SOSI elements
            minus the head element will be returned.
            
            \sa Parser::setObjTypeSelection(), Parser::mObjTypeFilter
            
            \return The number of SOSI elements scheduled for output.
         */
        std::vector<std::string>::size_type getCountSosiElementsSelection();
        
        //! Apply output selection filter
        /*!
            Which SOSI elements to export is governed by the Parser::mObjTypeFilter member. This
            string vector is initialized here. If the list contains one or more strings, only
            SOSI elements with a corresponding OBJTYPE will be scheduled for output.
            
            The list of OBJTYPE strings are populated from the command-line interface, more
            specifically the -t parameter. It takes a comma-separated list of OBJTYPE names to
            specify which SOSI elements should be included in the target file. The comma-separated
            string is parsed and converted to a string vector by the sosicon::CommandLine class
            before it is passed on to the parser through this function.
            
            \sa Parser::mObjTypeFilter, sosicon::CommandLine::parse()
            
            \param objTypes String vector containing the SOSI OBJTYPE identitifers for elements
                   to include in the output.
         */
        void setObjTypeSelection( std::vector<std::string>& objTypes );
        
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
        void parseSosiLine( std::string sosiLine );
        
        //! Dump file content to stdout
        /*!
            Writes a string representation of the SOSI file to stdout, for debugging purposes.
            
            \param all Dump all items in file. If this parameter is true, each SOSI element in
                   the source file will be output. This may cause a lot of text to be output if
                   the SOSI file is large.
         */
        void dump( bool all = false );
        
        //! Reset parser, free allocated resources
        /*!
            Empties element lists, frees allocated resources, resets iterators and re-initializes
            internal pointers. After calling this function, the parser is ready to start consuming
            a new SOSI file from the beginning.
         */
        void reset();

    };
};

#endif
