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
#include "converter_sosi2shp.h"

void sosicon::ConverterSosi2shp::
makeShp( ISosiElement* sosiTree ) {

    sosi::SosiTranslationTable ttbl;

    std::map<std::string,int> objTypes;

    sosi::SosiElementSearch src;

    while( sosiTree->getChild( src ) ) {
        ISosiElement* sosi = src.element();
        std::string objType = sosi->getObjType();
        if( !objType.empty() ) {
            if( objTypes.find( objType ) == objTypes.end() ) {
                objTypes[ objType ] = 1;
            }
            else {
                objTypes[ objType ]++;
            }
        }
    }

    sosicon::logstream << "Processing OBJTYPE";

    sosi::ElementType geometries[ 4 ] = {
        sosi::sosi_element_text,
        sosi::sosi_element_point,
        sosi::sosi_element_curve,
        sosi::sosi_element_surface };

    if( objTypes.size() > 0 ) {
        for( std::map<std::string,int>::iterator i = objTypes.begin(); i != objTypes.end(); i++ ) {

            std::vector<std::string>& ot = mCmd->mObjTypes;
            if( ot.size() > 0 && std::find( ot.begin(), ot.end(), i->first ) == ot.end() )
            {
                continue;
            }

            std::string objTypeName = i->first;
            sosicon::logstream << "\rProcessing OBJTYPE " << objTypeName << "\n";

            for( unsigned int j = 0; j < sizeof geometries; j++ ) {

                sosi::ElementType geometry = geometries[ j ];
                shape::Shapefile f;
                if( !mCmd->mFilterSosiId.empty() ) {
                    f.filterSosiId( mCmd->mFilterSosiId );
                }

                std::string geometryName = ttbl.sosiTypeToName( geometry );

                std::vector<std::string>& gt = mCmd->mGeomTypes;
                if( gt.size() > 0 && std::find( gt.begin(), gt.end(), geometryName ) == gt.end() )
                {
                    continue;
                }

                std::string basePath = makeBasePath( objTypeName + "_" + geometryName );

                int count = f.build( sosiTree, i->first, geometry );

                if( count > 0 ) {
                    sosicon::logstream << "  (" << count << " elements of type " << geometryName << ")\n";
                    writeFile<IShapefileShpPart>( f, basePath, "shp" );
                    writeFile<IShapefileShxPart>( f, basePath, "shx" );
                    writeFile<IShapefileDbfPart>( f, basePath, "dbf" );
                    writeFile<IShapefilePrjPart>( f, basePath, "prj" );
                }
            }
        }
        sosicon::logstream << "\rProcessing OBJTYPEs done\n";
    }
    else {

        sosicon::logstream << "\rProcessing GEOMETRIES \n";

        for( int j = 0; j < 4; j++ ) {

            shape::Shapefile f;
            sosi::ElementType geometry = geometries[ j ];
            std::string geometryName = ttbl.sosiTypeToName( geometry );
            std::string basePath = makeBasePath( geometryName );

            int count = f.build( sosiTree, "", geometry );

            if( count > 0 ) {
                sosicon::logstream << "  (" << count << " elements of type " << geometryName << ")\n";
                writeFile<IShapefileShpPart>( f, basePath, "shp" );
                writeFile<IShapefileShxPart>( f, basePath, "shx" );
                writeFile<IShapefileDbfPart>( f, basePath, "dbf" );
                writeFile<IShapefilePrjPart>( f, basePath, "prj" );
            }
        }
    }
}

std::string sosicon::ConverterSosi2shp::
makeBasePath( std::string objTypeName ) {

    std::string candidatePath = mCmd->mOutputFile.empty() ? mCurrentSourcefile : mCmd->mOutputFile;
    std::string dir, tit, ext;
    utils::getPathInfo( candidatePath, dir, tit, ext );

    std::string subdir = dir + tit;
    char separator;

    if( mCmd->mMakeSubDir ) {
        if( !utils::fileExists( subdir ) ) {
#ifdef _WIN32
            mkdir( subdir.c_str() );
#else
            mkdir( subdir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
#endif
        }
        separator = '/';
        candidatePath = subdir + separator + objTypeName;
    }
    else {
        separator = '_';
        candidatePath = dir + tit + separator + objTypeName;
    }
    int sequence = 0;

    while( utils::fileExists( candidatePath + ".shp" ) ||
           utils::fileExists( candidatePath + ".shx" ) ||
           utils::fileExists( candidatePath + ".dbf" ) ||
           utils::fileExists( candidatePath + ".prj" ) )
    {
        std::stringstream ss;
        ss << subdir << separator << objTypeName << "_" << std::setw( 2 ) << std::setfill( '0' ) << ++sequence;
        candidatePath = ss.str();
    }

    return candidatePath;
}

void sosicon::ConverterSosi2shp::
run() {
    Parser* pp;
    for( std::vector<std::string>::iterator f = mCmd->mSourceFiles.begin(); f != mCmd->mSourceFiles.end(); f++ ) {
        mCurrentSourcefile = *f;
        if( !utils::fileExists( mCurrentSourcefile ) ) {
            sosicon::logstream << mCurrentSourcefile << " not found\n";
        }
        else {
            sosicon::logstream << "Reading " << mCurrentSourcefile << "\n";
            Parser p;
            pp = &p;
            char ln[ 1024 ];
            std::ifstream ifs( ( mCurrentSourcefile ).c_str() );
            int n = 0;
            while( !ifs.eof() ) {
                if( mCmd->mIsTtyOut && ++n % 100 == 0 ) {
                    sosicon::logstream << "\rParsing line " << n;
                }
                memset( ln, 0x00, sizeof ln );
                ifs.getline( ln, sizeof ln );
                p.ragelParseSosiLine( ln );
            }
            p.complete();
            ifs.close();
            sosicon::logstream << "\r" << n << " lines parsed        \n";
            sosicon::logstream << "Building shape file...\n";
            ISosiElement* root = p.getRootElement();
            makeShp( root );
        }
    }
}
