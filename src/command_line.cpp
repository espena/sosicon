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
#include "command_line.h"

sosicon::CommandLine::
CommandLine() {
    mVerbose = 0;   
    mIsTtyIn = isatty( fileno( stdin ) ) != 0;
    mIsTtyOut = isatty( fileno( stdout ) ) != 0;
    mMakeSubDir = false;
#if defined( __APPLE__ ) || defined( __linux__ )
    if( mIsTtyOut ) {
        std::cout << "\e[?25l"; // Cursor off
    }
#endif
    std::cout << "\n";
    std::cout << "Sosicon, Copyright (C) 2014 Espen Andersen.\n";
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details type `sosicon -w'\n";
    std::cout << "This is free software, and you are welcome to redistribute it under certain\n";
    std::cout << "conditions; type `sosicon -c' for details.\n";
    std::cout << "\n";
}

sosicon::CommandLine::
~CommandLine() {
#if defined( __APPLE__ ) || defined( __linux__ )
    if( mIsTtyOut ) {
        std::cout << "\e[?25h"; // Cursor on
    }
#endif
}

void sosicon::CommandLine::
parse( int argc, char* argv[] ) {

    bool inputExpected = true;
    std::string inputLine = "";
    if( !mIsTtyIn ) {
        while( std::cin ) {
            std::cin >> inputLine;
            mSourceFiles.push_back( inputLine );
        }       
    }

    for( int i = 1; i < argc; i++ ) {
        std::string param( argv[ i ] );
        if( param.at( 0 ) != '-' ) {
            while( i < argc ) {
                mSourceFiles.push_back( argv[ i ] );
                i++;
            }
        }
        else {

            if( "-a" == param ) {
                mAppend = true;
            }
            else if( "-id" == param && argc > ( ++i ) ) {
                mFilterSosiId = utils::explode( ',', argv[ i ] );
            }
            else if( "-d" == param && argc > ( ++i ) ) {
                mDestinationDirectory = argv[ i ];
            }
            else if( "-f" == param && argc > ( ++i ) ) {
                mFieldSelection = utils::explode( ',', argv[ i ] );
            }
            else if( "-g" == param && argc > ( ++i ) ) {
                mGeomTypes = utils::explode( ',', argv[ i ] );
            }
            else if( "-h" == param ) {
                mIncludeHeader = true;
            }
            else if( "-o" == param && argc > ( ++i ) ) {
                mOutputFile = argv[ i ];
            }
            else if( "-s" == param ) {
                mMakeSubDir = true;
            }
            else if( "-t" == param && argc > ( ++i ) ) {
                mObjTypes = utils::explode( ',', argv[ i ] );
            }
            else if( "-V" == param ) {
                mVerbose = 2;
            }
            else if( "-v" == param ) {
                mVerbose = 1;
            }
            else if( "-2shp" == param ) {
                mCommand = param;
            }
            else if( "-2tsv" == param ) {
                mCommand = param;
            }
            else if( "-stat" == param ) {
                mCommand = param;
            }
            else if( "-help" == param ) {
                inputExpected = false;
                mCommand = param;
                outputHelpText();
                break;
            }
            else if( "-w" == param ) {
                inputExpected = false;
                mCommand = param;
                outputDisclaimer();
                break;
            }
            else if( "-c" == param ) {
                inputExpected = false;
                mCommand = param;
                outputLicense();
                break;
            }
        }
    }

    if( mCommand.empty() || ( inputExpected && mSourceFiles.size() == 0 ) ) {
        std::cout << "Missing input parameters.\n";
        std::cout << "Type sosicon -help for instructions.\n\n";
        return;
    }
}

void sosicon::CommandLine::
outputHelpText() {
    std::cout << "Usage: sosicon [OPERATION] [OPTIONS]... [FILES]...\n";
    std::cout << "\n";
    std::cout << "Converts SOSI files to other output formats.\n";
    std::cout << "\n";
    std::cout << "Example:\n";
    std::cout << "\n";
    std::cout << "  sosicon -2shp cities.sos poi.sos\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "OPERATION:\n";
    std::cout << "\n";
    std::cout << "  -2shp\n";
    std::cout << "      Convert SOSI source to ESRI Shape (shp).\n";
    std::cout << "\n";
    std::cout << "  -stat\n";
    std::cout << "      Print out statistics for a SOSI file.\n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "OPTIONS:\n";
    std::cout << "\n";
    std::cout << "  -t <OBJTYPES>\n";
    std::cout << "      Export features of given OBJTYPES only, where\n";
    std::cout << "      <OBJTYPES> is a comma-separated list of SOSI object\n";
    std::cout << "      types. Use the -stat OPERATION to obtain a list of\n";
    std::cout << "      OBJTYPEs contained in a SOSI file.\n";
    std::cout << "\n";
    std::cout << "  -g <GEOMETRIES>\n";
    std::cout << "      Export features of given GEOMETRIES only, where\n";
    std::cout << "      <GEOMETRIES> is a comma-separated list of SOSI geometry\n";
    std::cout << "      types. Use the -stat OPERATION to obtain a list of\n";
    std::cout << "      GEOMETRIES contained in a SOSI file.\n";
    std::cout << "\n";
}

void sosicon::CommandLine::
outputDisclaimer() {
    std::cout << "\n";
    std::cout << "  15. Disclaimer of Warranty.\n";
    std::cout << "\n";
    std::cout << "  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n";
    std::cout << "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n";
    std::cout << "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n";
    std::cout << "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n";
    std::cout << "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n";
    std::cout << "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n";
    std::cout << "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n";
    std::cout << "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n";
    std::cout << "\n";
    std::cout << "  16. Limitation of Liability.\n";
    std::cout << "\n";
    std::cout << "  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n";
    std::cout << "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS\n";
    std::cout << "THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY\n";
    std::cout << "GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE\n";
    std::cout << "USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF\n";
    std::cout << "DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD\n";
    std::cout << "PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),\n";
    std::cout << "EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF\n";
    std::cout << "SUCH DAMAGES.\n";
    std::cout << "\n";
    std::cout << "  17. Interpretation of Sections 15 and 16.\n";
    std::cout << "\n";
    std::cout << "  If the disclaimer of warranty and limitation of liability provided\n";
    std::cout << "above cannot be given local legal effect according to their terms,\n";
    std::cout << "reviewing courts shall apply local law that most closely approximates\n";
    std::cout << "an absolute waiver of all civil liability in connection with the\n";
    std::cout << "Program, unless a warranty or assumption of liability accompanies a\n";
    std::cout << "copy of the Program in return for a fee.\n";
    std::cout << "\n";
}

void sosicon::CommandLine::
outputLicense() {
    std::cout << "\n";
    std::cout << "                       TERMS AND CONDITIONS\n";
    std::cout << "\n";
    std::cout << "  0. Definitions.\n";
    std::cout << "\n";
    std::cout << "  \"This License\" refers to version 3 of the GNU General Public License.\n";
    std::cout << "\n";
    std::cout << "  \"Copyright\" also means copyright-like laws that apply to other kinds of\n";
    std::cout << "works, such as semiconductor masks.\n";
    std::cout << "\n";
    std::cout << "  \"The Program\" refers to any copyrightable work licensed under this\n";
    std::cout << "License.  Each licensee is addressed as \"you\".  \"Licensees\" and\n";
    std::cout << "\"recipients\" may be individuals or organizations.\n";
    std::cout << "\n";
    std::cout << "  To \"modify\" a work means to copy from or adapt all or part of the work\n";
    std::cout << "in a fashion requiring copyright permission, other than the making of an\n";
    std::cout << "exact copy.  The resulting work is called a \"modified version\" of the\n";
    std::cout << "earlier work or a work \"based on\" the earlier work.\n";
    std::cout << "\n";
    std::cout << "  A \"covered work\" means either the unmodified Program or a work based\n";
    std::cout << "on the Program.\n";
    std::cout << "\n";
    std::cout << "  To \"propagate\" a work means to do anything with it that, without\n";
    std::cout << "permission, would make you directly or secondarily liable for\n";
    std::cout << "infringement under applicable copyright law, except executing it on a\n";
    std::cout << "computer or modifying a private copy.  Propagation includes copying,\n";
    std::cout << "distribution (with or without modification), making available to the\n";
    std::cout << "public, and in some countries other activities as well.\n";
    std::cout << "\n";
    std::cout << "  To \"convey\" a work means any kind of propagation that enables other\n";
    std::cout << "parties to make or receive copies.  Mere interaction with a user through\n";
    std::cout << "a computer network, with no transfer of a copy, is not conveying.\n";
    std::cout << "\n";
    std::cout << "  An interactive user interface displays \"Appropriate Legal Notices\"\n";
    std::cout << "to the extent that it includes a convenient and prominently visible\n";
    std::cout << "feature that (1) displays an appropriate copyright notice, and (2)\n";
    std::cout << "tells the user that there is no warranty for the work (except to the\n";
    std::cout << "extent that warranties are provided), that licensees may convey the\n";
    std::cout << "work under this License, and how to view a copy of this License.  If\n";
    std::cout << "the interface presents a list of user commands or options, such as a\n";
    std::cout << "menu, a prominent item in the list meets this criterion.\n";
    std::cout << "\n";
    std::cout << "  1. Source Code.\n";
    std::cout << "\n";
    std::cout << "  The \"source code\" for a work means the preferred form of the work\n";
    std::cout << "for making modifications to it.  \"Object code\" means any non-source\n";
    std::cout << "form of a work.\n";
    std::cout << "\n";
    std::cout << "  A \"Standard Interface\" means an interface that either is an official\n";
    std::cout << "standard defined by a recognized standards body, or, in the case of\n";
    std::cout << "interfaces specified for a particular programming language, one that\n";
    std::cout << "is widely used among developers working in that language.\n";
    std::cout << "\n";
    std::cout << "  The \"System Libraries\" of an executable work include anything, other\n";
    std::cout << "than the work as a whole, that (a) is included in the normal form of\n";
    std::cout << "packaging a Major Component, but which is not part of that Major\n";
    std::cout << "Component, and (b) serves only to enable use of the work with that\n";
    std::cout << "Major Component, or to implement a Standard Interface for which an\n";
    std::cout << "implementation is available to the public in source code form.  A\n";
    std::cout << "\"Major Component\", in this context, means a major essential component\n";
    std::cout << "(kernel, window system, and so on) of the specific operating system\n";
    std::cout << "(if any) on which the executable work runs, or a compiler used to\n";
    std::cout << "produce the work, or an object code interpreter used to run it.\n";
    std::cout << "\n";
    std::cout << "  The \"Corresponding Source\" for a work in object code form means all\n";
    std::cout << "the source code needed to generate, install, and (for an executable\n";
    std::cout << "work) run the object code and to modify the work, including scripts to\n";
    std::cout << "control those activities.  However, it does not include the work's\n";
    std::cout << "System Libraries, or general-purpose tools or generally available free\n";
    std::cout << "programs which are used unmodified in performing those activities but\n";
    std::cout << "which are not part of the work.  For example, Corresponding Source\n";
    std::cout << "includes interface definition files associated with source files for\n";
    std::cout << "the work, and the source code for shared libraries and dynamically\n";
    std::cout << "linked subprograms that the work is specifically designed to require,\n";
    std::cout << "such as by intimate data communication or control flow between those\n";
    std::cout << "subprograms and other parts of the work.\n";
    std::cout << "\n";
    std::cout << "  The Corresponding Source need not include anything that users\n";
    std::cout << "can regenerate automatically from other parts of the Corresponding\n";
    std::cout << "Source.\n";
    std::cout << "\n";
    std::cout << "  The Corresponding Source for a work in source code form is that\n";
    std::cout << "same work.\n";
    std::cout << "\n";
    std::cout << "  2. Basic Permissions.\n";
    std::cout << "\n";
    std::cout << "  All rights granted under this License are granted for the term of\n";
    std::cout << "copyright on the Program, and are irrevocable provided the stated\n";
    std::cout << "conditions are met.  This License explicitly affirms your unlimited\n";
    std::cout << "permission to run the unmodified Program.  The output from running a\n";
    std::cout << "covered work is covered by this License only if the output, given its\n";
    std::cout << "content, constitutes a covered work.  This License acknowledges your\n";
    std::cout << "rights of fair use or other equivalent, as provided by copyright law.\n";
    std::cout << "\n";
    std::cout << "  You may make, run and propagate covered works that you do not\n";
    std::cout << "convey, without conditions so long as your license otherwise remains\n";
    std::cout << "in force.  You may convey covered works to others for the sole purpose\n";
    std::cout << "of having them make modifications exclusively for you, or provide you\n";
    std::cout << "with facilities for running those works, provided that you comply with\n";
    std::cout << "the terms of this License in conveying all material for which you do\n";
    std::cout << "not control copyright.  Those thus making or running the covered works\n";
    std::cout << "for you must do so exclusively on your behalf, under your direction\n";
    std::cout << "and control, on terms that prohibit them from making any copies of\n";
    std::cout << "your copyrighted material outside their relationship with you.\n";
    std::cout << "\n";
    std::cout << "  Conveying under any other circumstances is permitted solely under\n";
    std::cout << "the conditions stated below.  Sublicensing is not allowed; section 10\n";
    std::cout << "makes it unnecessary.\n";
    std::cout << "\n";
    std::cout << "  3. Protecting Users' Legal Rights From Anti-Circumvention Law.\n";
    std::cout << "\n";
    std::cout << "  No covered work shall be deemed part of an effective technological\n";
    std::cout << "measure under any applicable law fulfilling obligations under article\n";
    std::cout << "11 of the WIPO copyright treaty adopted on 20 December 1996, or\n";
    std::cout << "similar laws prohibiting or restricting circumvention of such\n";
    std::cout << "measures.\n";
    std::cout << "\n";
    std::cout << "  When you convey a covered work, you waive any legal power to forbid\n";
    std::cout << "circumvention of technological measures to the extent such circumvention\n";
    std::cout << "is effected by exercising rights under this License with respect to\n";
    std::cout << "the covered work, and you disclaim any intention to limit operation or\n";
    std::cout << "modification of the work as a means of enforcing, against the work's\n";
    std::cout << "users, your or third parties' legal rights to forbid circumvention of\n";
    std::cout << "technological measures.\n";
    std::cout << "\n";
    std::cout << "  4. Conveying Verbatim Copies.\n";
    std::cout << "\n";
    std::cout << "  You may convey verbatim copies of the Program's source code as you\n";
    std::cout << "receive it, in any medium, provided that you conspicuously and\n";
    std::cout << "appropriately publish on each copy an appropriate copyright notice;\n";
    std::cout << "keep intact all notices stating that this License and any\n";
    std::cout << "non-permissive terms added in accord with section 7 apply to the code;\n";
    std::cout << "keep intact all notices of the absence of any warranty; and give all\n";
    std::cout << "recipients a copy of this License along with the Program.\n";
    std::cout << "\n";
    std::cout << "  You may charge any price or no price for each copy that you convey,\n";
    std::cout << "and you may offer support or warranty protection for a fee.\n";
    std::cout << "\n";
    std::cout << "  5. Conveying Modified Source Versions.\n";
    std::cout << "\n";
    std::cout << "  You may convey a work based on the Program, or the modifications to\n";
    std::cout << "produce it from the Program, in the form of source code under the\n";
    std::cout << "terms of section 4, provided that you also meet all of these conditions:\n";
    std::cout << "\n";
    std::cout << "    a) The work must carry prominent notices stating that you modified\n";
    std::cout << "    it, and giving a relevant date.\n";
    std::cout << "\n";
    std::cout << "    b) The work must carry prominent notices stating that it is\n";
    std::cout << "    released under this License and any conditions added under section\n";
    std::cout << "    7.  This requirement modifies the requirement in section 4 to\n";
    std::cout << "    \"keep intact all notices\".\n";
    std::cout << "\n";
    std::cout << "    c) You must license the entire work, as a whole, under this\n";
    std::cout << "    License to anyone who comes into possession of a copy.  This\n";
    std::cout << "    License will therefore apply, along with any applicable section 7\n";
    std::cout << "    additional terms, to the whole of the work, and all its parts,\n";
    std::cout << "    regardless of how they are packaged.  This License gives no\n";
    std::cout << "    permission to license the work in any other way, but it does not\n";
    std::cout << "    invalidate such permission if you have separately received it.\n";
    std::cout << "\n";
    std::cout << "    d) If the work has interactive user interfaces, each must display\n";
    std::cout << "    Appropriate Legal Notices; however, if the Program has interactive\n";
    std::cout << "    interfaces that do not display Appropriate Legal Notices, your\n";
    std::cout << "    work need not make them do so.\n";
    std::cout << "\n";
    std::cout << "  A compilation of a covered work with other separate and independent\n";
    std::cout << "works, which are not by their nature extensions of the covered work,\n";
    std::cout << "and which are not combined with it such as to form a larger program,\n";
    std::cout << "in or on a volume of a storage or distribution medium, is called an\n";
    std::cout << "\"aggregate\" if the compilation and its resulting copyright are not\n";
    std::cout << "used to limit the access or legal rights of the compilation's users\n";
    std::cout << "beyond what the individual works permit.  Inclusion of a covered work\n";
    std::cout << "in an aggregate does not cause this License to apply to the other\n";
    std::cout << "parts of the aggregate.\n";
    std::cout << "\n";
    std::cout << "  6. Conveying Non-Source Forms.\n";
    std::cout << "\n";
    std::cout << "  You may convey a covered work in object code form under the terms\n";
    std::cout << "of sections 4 and 5, provided that you also convey the\n";
    std::cout << "machine-readable Corresponding Source under the terms of this License,\n";
    std::cout << "in one of these ways:\n";
    std::cout << "\n";
    std::cout << "    a) Convey the object code in, or embodied in, a physical product\n";
    std::cout << "    (including a physical distribution medium), accompanied by the\n";
    std::cout << "    Corresponding Source fixed on a durable physical medium\n";
    std::cout << "    customarily used for software interchange.\n";
    std::cout << "\n";
    std::cout << "    b) Convey the object code in, or embodied in, a physical product\n";
    std::cout << "    (including a physical distribution medium), accompanied by a\n";
    std::cout << "    written offer, valid for at least three years and valid for as\n";
    std::cout << "    long as you offer spare parts or customer support for that product\n";
    std::cout << "    model, to give anyone who possesses the object code either (1) a\n";
    std::cout << "    copy of the Corresponding Source for all the software in the\n";
    std::cout << "    product that is covered by this License, on a durable physical\n";
    std::cout << "    medium customarily used for software interchange, for a price no\n";
    std::cout << "    more than your reasonable cost of physically performing this\n";
    std::cout << "    conveying of source, or (2) access to copy the\n";
    std::cout << "    Corresponding Source from a network server at no charge.\n";
    std::cout << "\n";
    std::cout << "    c) Convey individual copies of the object code with a copy of the\n";
    std::cout << "    written offer to provide the Corresponding Source.  This\n";
    std::cout << "    alternative is allowed only occasionally and noncommercially, and\n";
    std::cout << "    only if you received the object code with such an offer, in accord\n";
    std::cout << "    with subsection 6b.\n";
    std::cout << "\n";
    std::cout << "    d) Convey the object code by offering access from a designated\n";
    std::cout << "    place (gratis or for a charge), and offer equivalent access to the\n";
    std::cout << "    Corresponding Source in the same way through the same place at no\n";
    std::cout << "    further charge.  You need not require recipients to copy the\n";
    std::cout << "    Corresponding Source along with the object code.  If the place to\n";
    std::cout << "    copy the object code is a network server, the Corresponding Source\n";
    std::cout << "    may be on a different server (operated by you or a third party)\n";
    std::cout << "    that supports equivalent copying facilities, provided you maintain\n";
    std::cout << "    clear directions next to the object code saying where to find the\n";
    std::cout << "    Corresponding Source.  Regardless of what server hosts the\n";
    std::cout << "    Corresponding Source, you remain obligated to ensure that it is\n";
    std::cout << "    available for as long as needed to satisfy these requirements.\n";
    std::cout << "\n";
    std::cout << "    e) Convey the object code using peer-to-peer transmission, provided\n";
    std::cout << "    you inform other peers where the object code and Corresponding\n";
    std::cout << "    Source of the work are being offered to the general public at no\n";
    std::cout << "    charge under subsection 6d.\n";
    std::cout << "\n";
    std::cout << "  A separable portion of the object code, whose source code is excluded\n";
    std::cout << "from the Corresponding Source as a System Library, need not be\n";
    std::cout << "included in conveying the object code work.\n";
    std::cout << "\n";
    std::cout << "  A \"User Product\" is either (1) a \"consumer product\", which means any\n";
    std::cout << "tangible personal property which is normally used for personal, family,\n";
    std::cout << "or household purposes, or (2) anything designed or sold for incorporation\n";
    std::cout << "into a dwelling.  In determining whether a product is a consumer product,\n";
    std::cout << "doubtful cases shall be resolved in favor of coverage.  For a particular\n";
    std::cout << "product received by a particular user, \"normally used\" refers to a\n";
    std::cout << "typical or common use of that class of product, regardless of the status\n";
    std::cout << "of the particular user or of the way in which the particular user\n";
    std::cout << "actually uses, or expects or is expected to use, the product.  A product\n";
    std::cout << "is a consumer product regardless of whether the product has substantial\n";
    std::cout << "commercial, industrial or non-consumer uses, unless such uses represent\n";
    std::cout << "the only significant mode of use of the product.\n";
    std::cout << "\n";
    std::cout << "  \"Installation Information\" for a User Product means any methods,\n";
    std::cout << "procedures, authorization keys, or other information required to install\n";
    std::cout << "and execute modified versions of a covered work in that User Product from\n";
    std::cout << "a modified version of its Corresponding Source.  The information must\n";
    std::cout << "suffice to ensure that the continued functioning of the modified object\n";
    std::cout << "code is in no case prevented or interfered with solely because\n";
    std::cout << "modification has been made.\n";
    std::cout << "\n";
    std::cout << "  If you convey an object code work under this section in, or with, or\n";
    std::cout << "specifically for use in, a User Product, and the conveying occurs as\n";
    std::cout << "part of a transaction in which the right of possession and use of the\n";
    std::cout << "User Product is transferred to the recipient in perpetuity or for a\n";
    std::cout << "fixed term (regardless of how the transaction is characterized), the\n";
    std::cout << "Corresponding Source conveyed under this section must be accompanied\n";
    std::cout << "by the Installation Information.  But this requirement does not apply\n";
    std::cout << "if neither you nor any third party retains the ability to install\n";
    std::cout << "modified object code on the User Product (for example, the work has\n";
    std::cout << "been installed in ROM).\n";
    std::cout << "\n";
    std::cout << "  The requirement to provide Installation Information does not include a\n";
    std::cout << "requirement to continue to provide support service, warranty, or updates\n";
    std::cout << "for a work that has been modified or installed by the recipient, or for\n";
    std::cout << "the User Product in which it has been modified or installed.  Access to a\n";
    std::cout << "network may be denied when the modification itself materially and\n";
    std::cout << "adversely affects the operation of the network or violates the rules and\n";
    std::cout << "protocols for communication across the network.\n";
    std::cout << "\n";
    std::cout << "  Corresponding Source conveyed, and Installation Information provided,\n";
    std::cout << "in accord with this section must be in a format that is publicly\n";
    std::cout << "documented (and with an implementation available to the public in\n";
    std::cout << "source code form), and must require no special password or key for\n";
    std::cout << "unpacking, reading or copying.\n";
    std::cout << "\n";
    std::cout << "  7. Additional Terms.\n";
    std::cout << "\n";
    std::cout << "  \"Additional permissions\" are terms that supplement the terms of this\n";
    std::cout << "License by making exceptions from one or more of its conditions.\n";
    std::cout << "Additional permissions that are applicable to the entire Program shall\n";
    std::cout << "be treated as though they were included in this License, to the extent\n";
    std::cout << "that they are valid under applicable law.  If additional permissions\n";
    std::cout << "apply only to part of the Program, that part may be used separately\n";
    std::cout << "under those permissions, but the entire Program remains governed by\n";
    std::cout << "this License without regard to the additional permissions.\n";
    std::cout << "\n";
    std::cout << "  When you convey a copy of a covered work, you may at your option\n";
    std::cout << "remove any additional permissions from that copy, or from any part of\n";
    std::cout << "it.  (Additional permissions may be written to require their own\n";
    std::cout << "removal in certain cases when you modify the work.)  You may place\n";
    std::cout << "additional permissions on material, added by you to a covered work,\n";
    std::cout << "for which you have or can give appropriate copyright permission.\n";
    std::cout << "\n";
    std::cout << "  Notwithstanding any other provision of this License, for material you\n";
    std::cout << "add to a covered work, you may (if authorized by the copyright holders of\n";
    std::cout << "that material) supplement the terms of this License with terms:\n";
    std::cout << "\n";
    std::cout << "    a) Disclaiming warranty or limiting liability differently from the\n";
    std::cout << "    terms of sections 15 and 16 of this License; or\n";
    std::cout << "\n";
    std::cout << "    b) Requiring preservation of specified reasonable legal notices or\n";
    std::cout << "    author attributions in that material or in the Appropriate Legal\n";
    std::cout << "    Notices displayed by works containing it; or\n";
    std::cout << "\n";
    std::cout << "    c) Prohibiting misrepresentation of the origin of that material, or\n";
    std::cout << "    requiring that modified versions of such material be marked in\n";
    std::cout << "    reasonable ways as different from the original version; or\n";
    std::cout << "\n";
    std::cout << "    d) Limiting the use for publicity purposes of names of licensors or\n";
    std::cout << "    authors of the material; or\n";
    std::cout << "\n";
    std::cout << "    e) Declining to grant rights under trademark law for use of some\n";
    std::cout << "    trade names, trademarks, or service marks; or\n";
    std::cout << "\n";
    std::cout << "    f) Requiring indemnification of licensors and authors of that\n";
    std::cout << "    material by anyone who conveys the material (or modified versions of\n";
    std::cout << "    it) with contractual assumptions of liability to the recipient, for\n";
    std::cout << "    any liability that these contractual assumptions directly impose on\n";
    std::cout << "    those licensors and authors.\n";
    std::cout << "\n";
    std::cout << "  All other non-permissive additional terms are considered \"further\n";
    std::cout << "restrictions\" within the meaning of section 10.  If the Program as you\n";
    std::cout << "received it, or any part of it, contains a notice stating that it is\n";
    std::cout << "governed by this License along with a term that is a further\n";
    std::cout << "restriction, you may remove that term.  If a license document contains\n";
    std::cout << "a further restriction but permits relicensing or conveying under this\n";
    std::cout << "License, you may add to a covered work material governed by the terms\n";
    std::cout << "of that license document, provided that the further restriction does\n";
    std::cout << "not survive such relicensing or conveying.\n";
    std::cout << "\n";
    std::cout << "  If you add terms to a covered work in accord with this section, you\n";
    std::cout << "must place, in the relevant source files, a statement of the\n";
    std::cout << "additional terms that apply to those files, or a notice indicating\n";
    std::cout << "where to find the applicable terms.\n";
    std::cout << "\n";
    std::cout << "  Additional terms, permissive or non-permissive, may be stated in the\n";
    std::cout << "form of a separately written license, or stated as exceptions;\n";
    std::cout << "the above requirements apply either way.\n";
    std::cout << "\n";
    std::cout << "  8. Termination.\n";
    std::cout << "\n";
    std::cout << "  You may not propagate or modify a covered work except as expressly\n";
    std::cout << "provided under this License.  Any attempt otherwise to propagate or\n";
    std::cout << "modify it is void, and will automatically terminate your rights under\n";
    std::cout << "this License (including any patent licenses granted under the third\n";
    std::cout << "paragraph of section 11).\n";
    std::cout << "\n";
    std::cout << "  However, if you cease all violation of this License, then your\n";
    std::cout << "license from a particular copyright holder is reinstated (a)\n";
    std::cout << "provisionally, unless and until the copyright holder explicitly and\n";
    std::cout << "finally terminates your license, and (b) permanently, if the copyright\n";
    std::cout << "holder fails to notify you of the violation by some reasonable means\n";
    std::cout << "prior to 60 days after the cessation.\n";
    std::cout << "\n";
    std::cout << "  Moreover, your license from a particular copyright holder is\n";
    std::cout << "reinstated permanently if the copyright holder notifies you of the\n";
    std::cout << "violation by some reasonable means, this is the first time you have\n";
    std::cout << "received notice of violation of this License (for any work) from that\n";
    std::cout << "copyright holder, and you cure the violation prior to 30 days after\n";
    std::cout << "your receipt of the notice.\n";
    std::cout << "\n";
    std::cout << "  Termination of your rights under this section does not terminate the\n";
    std::cout << "licenses of parties who have received copies or rights from you under\n";
    std::cout << "this License.  If your rights have been terminated and not permanently\n";
    std::cout << "reinstated, you do not qualify to receive new licenses for the same\n";
    std::cout << "material under section 10.\n";
    std::cout << "\n";
    std::cout << "  9. Acceptance Not Required for Having Copies.\n";
    std::cout << "\n";
    std::cout << "  You are not required to accept this License in order to receive or\n";
    std::cout << "run a copy of the Program.  Ancillary propagation of a covered work\n";
    std::cout << "occurring solely as a consequence of using peer-to-peer transmission\n";
    std::cout << "to receive a copy likewise does not require acceptance.  However,\n";
    std::cout << "nothing other than this License grants you permission to propagate or\n";
    std::cout << "modify any covered work.  These actions infringe copyright if you do\n";
    std::cout << "not accept this License.  Therefore, by modifying or propagating a\n";
    std::cout << "covered work, you indicate your acceptance of this License to do so.\n";
    std::cout << "\n";
    std::cout << "  10. Automatic Licensing of Downstream Recipients.\n";
    std::cout << "\n";
    std::cout << "  Each time you convey a covered work, the recipient automatically\n";
    std::cout << "receives a license from the original licensors, to run, modify and\n";
    std::cout << "propagate that work, subject to this License.  You are not responsible\n";
    std::cout << "for enforcing compliance by third parties with this License.\n";
    std::cout << "\n";
    std::cout << "  An \"entity transaction\" is a transaction transferring control of an\n";
    std::cout << "organization, or substantially all assets of one, or subdividing an\n";
    std::cout << "organization, or merging organizations.  If propagation of a covered\n";
    std::cout << "work results from an entity transaction, each party to that\n";
    std::cout << "transaction who receives a copy of the work also receives whatever\n";
    std::cout << "licenses to the work the party's predecessor in interest had or could\n";
    std::cout << "give under the previous paragraph, plus a right to possession of the\n";
    std::cout << "Corresponding Source of the work from the predecessor in interest, if\n";
    std::cout << "the predecessor has it or can get it with reasonable efforts.\n";
    std::cout << "\n";
    std::cout << "  You may not impose any further restrictions on the exercise of the\n";
    std::cout << "rights granted or affirmed under this License.  For example, you may\n";
    std::cout << "not impose a license fee, royalty, or other charge for exercise of\n";
    std::cout << "rights granted under this License, and you may not initiate litigation\n";
    std::cout << "(including a cross-claim or counterclaim in a lawsuit) alleging that\n";
    std::cout << "any patent claim is infringed by making, using, selling, offering for\n";
    std::cout << "sale, or importing the Program or any portion of it.\n";
    std::cout << "\n";
    std::cout << "  11. Patents.\n";
    std::cout << "\n";
    std::cout << "  A \"contributor\" is a copyright holder who authorizes use under this\n";
    std::cout << "License of the Program or a work on which the Program is based.  The\n";
    std::cout << "work thus licensed is called the contributor's \"contributor version\".\n";
    std::cout << "\n";
    std::cout << "  A contributor's \"essential patent claims\" are all patent claims\n";
    std::cout << "owned or controlled by the contributor, whether already acquired or\n";
    std::cout << "hereafter acquired, that would be infringed by some manner, permitted\n";
    std::cout << "by this License, of making, using, or selling its contributor version,\n";
    std::cout << "but do not include claims that would be infringed only as a\n";
    std::cout << "consequence of further modification of the contributor version.  For\n";
    std::cout << "purposes of this definition, \"control\" includes the right to grant\n";
    std::cout << "patent sublicenses in a manner consistent with the requirements of\n";
    std::cout << "this License.\n";
    std::cout << "\n";
    std::cout << "  Each contributor grants you a non-exclusive, worldwide, royalty-free\n";
    std::cout << "patent license under the contributor's essential patent claims, to\n";
    std::cout << "make, use, sell, offer for sale, import and otherwise run, modify and\n";
    std::cout << "propagate the contents of its contributor version.\n";
    std::cout << "\n";
    std::cout << "  In the following three paragraphs, a \"patent license\" is any express\n";
    std::cout << "agreement or commitment, however denominated, not to enforce a patent\n";
    std::cout << "(such as an express permission to practice a patent or covenant not to\n";
    std::cout << "sue for patent infringement).  To \"grant\" such a patent license to a\n";
    std::cout << "party means to make such an agreement or commitment not to enforce a\n";
    std::cout << "patent against the party.\n";
    std::cout << "\n";
    std::cout << "  If you convey a covered work, knowingly relying on a patent license,\n";
    std::cout << "and the Corresponding Source of the work is not available for anyone\n";
    std::cout << "to copy, free of charge and under the terms of this License, through a\n";
    std::cout << "publicly available network server or other readily accessible means,\n";
    std::cout << "then you must either (1) cause the Corresponding Source to be so\n";
    std::cout << "available, or (2) arrange to deprive yourself of the benefit of the\n";
    std::cout << "patent license for this particular work, or (3) arrange, in a manner\n";
    std::cout << "consistent with the requirements of this License, to extend the patent\n";
    std::cout << "license to downstream recipients.  \"Knowingly relying\" means you have\n";
    std::cout << "actual knowledge that, but for the patent license, your conveying the\n";
    std::cout << "covered work in a country, or your recipient's use of the covered work\n";
    std::cout << "in a country, would infringe one or more identifiable patents in that\n";
    std::cout << "country that you have reason to believe are valid.\n";
    std::cout << "\n";
    std::cout << "  If, pursuant to or in connection with a single transaction or\n";
    std::cout << "arrangement, you convey, or propagate by procuring conveyance of, a\n";
    std::cout << "covered work, and grant a patent license to some of the parties\n";
    std::cout << "receiving the covered work authorizing them to use, propagate, modify\n";
    std::cout << "or convey a specific copy of the covered work, then the patent license\n";
    std::cout << "you grant is automatically extended to all recipients of the covered\n";
    std::cout << "work and works based on it.\n";
    std::cout << "\n";
    std::cout << "  A patent license is \"discriminatory\" if it does not include within\n";
    std::cout << "the scope of its coverage, prohibits the exercise of, or is\n";
    std::cout << "conditioned on the non-exercise of one or more of the rights that are\n";
    std::cout << "specifically granted under this License.  You may not convey a covered\n";
    std::cout << "work if you are a party to an arrangement with a third party that is\n";
    std::cout << "in the business of distributing software, under which you make payment\n";
    std::cout << "to the third party based on the extent of your activity of conveying\n";
    std::cout << "the work, and under which the third party grants, to any of the\n";
    std::cout << "parties who would receive the covered work from you, a discriminatory\n";
    std::cout << "patent license (a) in connection with copies of the covered work\n";
    std::cout << "conveyed by you (or copies made from those copies), or (b) primarily\n";
    std::cout << "for and in connection with specific products or compilations that\n";
    std::cout << "contain the covered work, unless you entered into that arrangement,\n";
    std::cout << "or that patent license was granted, prior to 28 March 2007.\n";
    std::cout << "\n";
    std::cout << "  Nothing in this License shall be construed as excluding or limiting\n";
    std::cout << "any implied license or other defenses to infringement that may\n";
    std::cout << "otherwise be available to you under applicable patent law.\n";
    std::cout << "\n";
    std::cout << "  12. No Surrender of Others' Freedom.\n";
    std::cout << "\n";
    std::cout << "  If conditions are imposed on you (whether by court order, agreement or\n";
    std::cout << "otherwise) that contradict the conditions of this License, they do not\n";
    std::cout << "excuse you from the conditions of this License.  If you cannot convey a\n";
    std::cout << "covered work so as to satisfy simultaneously your obligations under this\n";
    std::cout << "License and any other pertinent obligations, then as a consequence you may\n";
    std::cout << "not convey it at all.  For example, if you agree to terms that obligate you\n";
    std::cout << "to collect a royalty for further conveying from those to whom you convey\n";
    std::cout << "the Program, the only way you could satisfy both those terms and this\n";
    std::cout << "License would be to refrain entirely from conveying the Program.\n";
    std::cout << "\n";
    std::cout << "  13. Use with the GNU Affero General Public License.\n";
    std::cout << "\n";
    std::cout << "  Notwithstanding any other provision of this License, you have\n";
    std::cout << "permission to link or combine any covered work with a work licensed\n";
    std::cout << "under version 3 of the GNU Affero General Public License into a single\n";
    std::cout << "combined work, and to convey the resulting work.  The terms of this\n";
    std::cout << "License will continue to apply to the part which is the covered work,\n";
    std::cout << "but the special requirements of the GNU Affero General Public License,\n";
    std::cout << "section 13, concerning interaction through a network will apply to the\n";
    std::cout << "combination as such.\n";
    std::cout << "\n";
    std::cout << "  14. Revised Versions of this License.\n";
    std::cout << "\n";
    std::cout << "  The Free Software Foundation may publish revised and/or new versions of\n";
    std::cout << "the GNU General Public License from time to time.  Such new versions will\n";
    std::cout << "be similar in spirit to the present version, but may differ in detail to\n";
    std::cout << "address new problems or concerns.\n";
    std::cout << "\n";
    std::cout << "  Each version is given a distinguishing version number.  If the\n";
    std::cout << "Program specifies that a certain numbered version of the GNU General\n";
    std::cout << "Public License \"or any later version\" applies to it, you have the\n";
    std::cout << "option of following the terms and conditions either of that numbered\n";
    std::cout << "version or of any later version published by the Free Software\n";
    std::cout << "Foundation.  If the Program does not specify a version number of the\n";
    std::cout << "GNU General Public License, you may choose any version ever published\n";
    std::cout << "by the Free Software Foundation.\n";
    std::cout << "\n";
    std::cout << "  If the Program specifies that a proxy can decide which future\n";
    std::cout << "versions of the GNU General Public License can be used, that proxy's\n";
    std::cout << "public statement of acceptance of a version permanently authorizes you\n";
    std::cout << "to choose that version for the Program.\n";
    std::cout << "\n";
    std::cout << "  Later license versions may give you additional or different\n";
    std::cout << "permissions.  However, no additional obligations are imposed on any\n";
    std::cout << "author or copyright holder as a result of your choosing to follow a\n";
    std::cout << "later version.\n";
    std::cout << "\n";
    std::cout << "  15. Disclaimer of Warranty.\n";
    std::cout << "\n";
    std::cout << "  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n";
    std::cout << "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n";
    std::cout << "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n";
    std::cout << "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n";
    std::cout << "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n";
    std::cout << "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n";
    std::cout << "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n";
    std::cout << "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n";
    std::cout << "\n";
    std::cout << "  16. Limitation of Liability.\n";
    std::cout << "\n";
    std::cout << "  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n";
    std::cout << "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS\n";
    std::cout << "THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY\n";
    std::cout << "GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE\n";
    std::cout << "USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF\n";
    std::cout << "DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD\n";
    std::cout << "PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),\n";
    std::cout << "EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF\n";
    std::cout << "SUCH DAMAGES.\n";
    std::cout << "\n";
    std::cout << "  17. Interpretation of Sections 15 and 16.\n";
    std::cout << "\n";
    std::cout << "  If the disclaimer of warranty and limitation of liability provided\n";
    std::cout << "above cannot be given local legal effect according to their terms,\n";
    std::cout << "reviewing courts shall apply local law that most closely approximates\n";
    std::cout << "an absolute waiver of all civil liability in connection with the\n";
    std::cout << "Program, unless a warranty or assumption of liability accompanies a\n";
    std::cout << "copy of the Program in return for a fee.\n";
    std::cout << "\n";
}
