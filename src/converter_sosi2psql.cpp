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
#include "converter_sosi2psql.h"

std::string sosicon::ConverterSosi2psql::
buildCreateStatements( std::string sridDest,
                       std::string dbSchema,
                       std::string dbTable ) {
    std::string sql;

    sql  = buildCreateStatement( sosi::sosi_element_point,
                                 sridDest,
                                 dbSchema,
                                 dbTable );

    sql += buildCreateStatement( sosi::sosi_element_curve,
                                 sridDest,
                                 dbSchema,
                                 dbTable );

    sql += buildCreateStatement( sosi::sosi_element_surface,
                                 sridDest,
                                 dbSchema,
                                 dbTable );
    return sql;
}

std::string sosicon::ConverterSosi2psql::
buildCreateStatement( sosi::ElementType elementType,
                      std::string sridDest,
                      std::string dbSchema,
                      std::string dbTable ) {

    std::string geometryType = wktFromSosiType( elementType );

    std::stringstream ss;
    if( !geometryType.empty() && mFieldsListCollection[ elementType ]->size() > 0 ) {

        std::string geomName = utils::toLower( geometryType );
        std::string geomField = dbTable + "_geom";

        ss << "CREATE TABLE "
           << dbSchema
           << "."
           << dbTable
           << "_"
           << geomName
           << "(id_" 
           << dbTable
           <<  "_"
           << geomName
           << " INT DEFAULT nextval('"
           << dbSchema
           << "."
           << dbTable
           << "_"
           << geomName
           << "_serial')";

        FieldsList* f = mFieldsListCollection[ elementType ];
        FieldsList::iterator itrFields;
        for( itrFields = f->begin(); itrFields != f->end(); itrFields++ ) {
           std::string field = itrFields->first;
           std::string::size_type len = itrFields->second;
           if( field != geomField ) {
               ss << ","
                  << field
                  << " VARCHAR("
                  << std::fixed
                  << len
                  << ")";
           }
        }

        ss << ");\n";
        ss << "SELECT AddGeometryColumn( '"
           << dbSchema
           << "','"
           << dbTable
           << "_"
           << geomName
           << "','"
           << geomField
           << "',"
           << sridDest
           << ",'"
           << geometryType
           << "',2);\n";
    }
    return ss.str();
}

std::string sosicon::ConverterSosi2psql::
buildInsertStatements( std::string dbSchema,
                       std::string dbTable ) {

    std::string sql;
    sql  = buildInsertStatement( sosi::sosi_element_point,
                                 dbSchema,
                                 dbTable );

    sql += buildInsertStatement( sosi::sosi_element_curve,
                                 dbSchema,
                                 dbTable );

    sql += buildInsertStatement( sosi::sosi_element_surface,
                                 dbSchema,
                                 dbTable );
    return sql;
}

std::string sosicon::ConverterSosi2psql::
buildInsertStatement( sosi::ElementType elementType,
                      std::string dbSchema,
                      std::string dbTable ) {

    std::string sqlComposite;
    std::string geometryType = wktFromSosiType( elementType );

    if( !geometryType.empty() && mRowsListCollection[ elementType ]->size() > 0 ) {

        std::string sqlInsert;
        std::string sqlValues;

        RowsList::iterator itrRows;
        FieldsList::iterator itrFields;

        FieldsList* f = mFieldsListCollection[ elementType ];
        RowsList* r = mRowsListCollection[ elementType ];

        std::string geomField = dbTable + "_geom";
        std::string geomName = utils::toLower( geometryType );

        for( itrFields = f->begin(); itrFields != f->end(); itrFields++ ) {
            if( sqlInsert.empty() ) {

                sqlInsert = "INSERT INTO "
                          + dbSchema
                          + "."
                          + dbTable
                          +  "_"
                          + geomName
                          + " (" + itrFields->first;
            }
            else {
                sqlInsert += ( "," + itrFields->first );
            }
        }

        sqlInsert += ") VALUES\n";

        int rowCount = 0;
        RowsList::size_type len = r->size();
        std::cout << "    > Processing 0 of " << len << std::flush;

        for( itrRows = r->begin(); itrRows != r->end(); itrRows++ ) {

            std::map<std::string,std::string>* row = *itrRows;

            if( !sqlValues.empty() && ++rowCount % 250000 == 0 ) {
                sqlValues = sqlValues.substr( 0, sqlValues.length() - 2 );
                sqlValues += ";\n";
                sqlComposite += ( sqlInsert + sqlValues );
                sqlValues.clear();
            }

            if( rowCount % 1000 == 0 ) {
                std::cout << "\r    > Processing " << rowCount << " of " << len << std::flush;
            }

            sqlValues += "(";

            for( itrFields = f->begin(); itrFields != f->end(); itrFields++ ) {
                std::string key = itrFields->first;
                if( row->find( key ) == row->end() ) {
                    ( *row )[ key ] = "";
                }
                if( key == geomField ) {
                    sqlValues += ( *row )[ key ] + ",";
                }
                else {
                    sqlValues += "'" + utils::sqlNormalize( ( *row )[ key ] ) + "',";
                }
            }

            sqlValues.pop_back();
            sqlValues += "),\n";
        }
        std::cout << "\r    > " << rowCount << " " << geomName << "s processed               \n" << std::flush;

        sqlValues.pop_back();
        sqlValues.pop_back();
        sqlValues += ";\n";
        sqlComposite += ( sqlInsert + sqlValues );
    }
    return sqlComposite;
}

void sosicon::ConverterSosi2psql::
cleanup() {

    std::cout << "    > Clean-up...\n";
    cleanup( sosi::sosi_element_point );
    cleanup( sosi::sosi_element_curve );
    cleanup( sosi::sosi_element_surface );
}

void sosicon::ConverterSosi2psql::
cleanup( sosi::ElementType type ) {

    RowsList* r = mRowsListCollection[ type ];
    RowsList::iterator i;

    for( i = r->begin(); i != r->end(); i++ ) {
        delete *i;
    }

    delete mRowsListCollection[ type ];
    mRowsListCollection[ type ] = 0;

    delete mFieldsListCollection[ type ];
    mFieldsListCollection[ type ] = 0;
}

void sosicon::ConverterSosi2psql::
extractData( ISosiElement* parent,
             sosi::ElementType type,
             std::map<std::string,std::string>*& row ) {

        FieldsList*& fieldsList = mFieldsListCollection[ type ];
    sosi::SosiElementSearch srcData;
    while( parent->getChild( srcData ) ) {

        ISosiElement* dataElement = srcData.element();

        extractData( dataElement, type, row );

        std::string fieldName = utils::toFieldname( dataElement->getName() );
        std::string data = dataElement->getData();
        
        if( data.empty() ) {
            continue;
        }

        if( fieldsList->find( fieldName ) == fieldsList->end() ) {
            ( *fieldsList )[ fieldName ] = data.length();
        }
        else {
            ( *fieldsList )[ fieldName ] = std::max( ( *fieldsList )[ fieldName ], data.length() );
        }

        ( *row )[ fieldName ] = data;
    }
}

std::string sosicon::ConverterSosi2psql::
getSrid( ISosiElement* sosiTree ) {

    // Path: .HODE/..TRANSPAR/...KOORDSYS
    ISosiElement* head = 0, * transpar = 0, * coordsys = 0;

    sosi::SosiElementSearch srcHead( sosi::sosi_element_head );
    sosi::SosiElementSearch srcTranspar( sosi::sosi_element_transpar );
    sosi::SosiElementSearch srcCoordsys( sosi::sosi_element_coordsys );

    if( sosiTree->getChild( srcHead ) ) {
        head = srcHead.element();
    }
    if( head && head->getChild( srcTranspar ) ) {
        transpar = srcTranspar.element();
    }
    if( transpar && transpar->getChild( srcCoordsys ) ) {
        coordsys = srcCoordsys.element();
    }

    std::string srid;

    if( coordsys ) {
        std::stringstream ss;
        ss << coordsys->getData();
        int sysCode;
        ss >> sysCode;
        sosi::SosiTranslationTable tt;
        sosi::CoordSys cs = tt.sysCodeToCoordSys( sysCode );
        srid = cs.srid();
        std::cout << "Coordinate system: " << cs.displayString() << "\n";
    }
    else {
        std::cout << "No KOORDSYS code found in sosi file.\nDefaults to 23 (EPSG:25833 - ETRS89 / UTM zone 33N)\n";
        srid = "25833";
    }

    return srid;
}

void sosicon::ConverterSosi2psql::
insertPoint( ISosiElement* point,
             std::string sridSource,
             std::string sridDest,
             std::string geomField ) {

    sosi::SosiElementSearch srcNe = sosi::SosiElementSearch( sosi::sosi_element_ne );

    if( point->getChild( srcNe ) ) {

        sosi::SosiNorthEast ne = sosi::SosiNorthEast( srcNe.element() );
        ICoordinate* coord = ne.front();
        std::stringstream ss;

        std::map<std::string,std::string>* row = new std::map<std::string,std::string>();

        ss.precision( 5 );
        ss  << std::fixed
            << "ST_Transform(ST_GeomFromText('POINT("
            << coord->getE()
            << " "
            << coord->getN()
            << ")',"
            << sridSource
            << "),"
            << sridDest
            << ")";

        std::string data = ss.str();
        ( *row )[ geomField ] = data;
        ( *mFieldsListCollection[ sosi::sosi_element_point ] )[ geomField ] = std::max( ( *mFieldsListCollection[ sosi::sosi_element_point ] )[ geomField ], data.length() );

        extractData( point, sosi::sosi_element_point, row );
        mRowsListCollection[ sosi::sosi_element_point ]->push_back( row );
    }
}

void sosicon::ConverterSosi2psql::
insertLineString( ISosiElement* lineString,
                  std::string sridSource,
                  std::string sridDest,
                  std::string geomField ) {

    CoordinateCollection cc;
    cc.discoverCoords( lineString );

    std::vector<ICoordinate*> theGeom = cc.getGeom();
    std::stringstream ssGeomCoord;

    ssGeomCoord.precision( 5 );
    ssGeomCoord << std::fixed;

    for( std::vector<ICoordinate*>::iterator i = theGeom.begin(); i != theGeom.end(); i++ ) {
        ICoordinate* c = *i;
        ssGeomCoord << c->getE()
                    << " "
                    << c->getN()
                    << ",";
    }

    std::string geom = ssGeomCoord.str();
    geom.pop_back();

    std::stringstream ss;
    ss << "ST_Transform(ST_GeomFromText('LINESTRING("
       << geom
       << ")',"
       << sridSource
       << "),"
       << sridDest
       << ")";

    std::string data = ss.str();
    std::map<std::string,std::string>* row = new std::map<std::string,std::string>();

    ( *row )[ geomField ] = data;
    ( *mFieldsListCollection[ sosi::sosi_element_surface ] )[ geomField ] = std::max( ( *mFieldsListCollection[ sosi::sosi_element_surface ] )[ geomField ], data.length() );

    extractData( lineString, sosi::sosi_element_curve, row );
    mRowsListCollection[ sosi::sosi_element_curve ]->push_back( row );
}

void sosicon::ConverterSosi2psql::
insertPolygon( ISosiElement* polygon,
               std::string sridSource,
               std::string sridDest,
               std::string geomField ) {

    CoordinateCollection cc;
    cc.discoverCoords( polygon );

    std::vector<ICoordinate*> theGeom = cc.getGeom();
    std::vector<ICoordinate*> theHoles = cc.getHoles();
    std::vector<int> holeSizes = cc.getHoleSizes();
    std::stringstream ssGeomCoord;

    ssGeomCoord.precision( 5 );
    ssGeomCoord << std::fixed 
                << "(";

    for( std::vector<ICoordinate*>::iterator i = theGeom.begin(); i != theGeom.end(); i++ ) {
        ICoordinate* c = *i;
        ssGeomCoord << c->getE()
                    << " "
                    << c->getN()
                    << ",";
    }

    std::string geom = ssGeomCoord.str();
    geom.pop_back();
    geom += ")";

    std::stringstream ssHolesCoord;
    ssHolesCoord.precision( 5 );
    ssHolesCoord << std::fixed;

    int offset = 0;
    ICoordinate* first, * last;
    const std::vector<ICoordinate*>::size_type numPoints = theHoles.size();
    for( std::vector<int>::iterator i = holeSizes.begin(); i != holeSizes.end(); i++ ) {
        ssHolesCoord << ",(";
        for( int j = 0; j < *i; j++ ) {
            ICoordinate* c = theHoles[ offset++ ];
            if( j == 0 ) {
                first = c;
            }
            else {
                ssHolesCoord << ",";
                last = c;
            }
            ssHolesCoord << c->getE()
                         << " "
                         << c->getN();
        }
        if( !first->equals( last ) ) {
            // Close polygon if open
            ssHolesCoord << ","
                         << first->getE()
                         << " "
                         << first->getN();
        }
        ssHolesCoord << ")";
    }
    geom += ssHolesCoord.str();

    std::stringstream ss;
    ss << "ST_Transform(ST_GeomFromText('POLYGON("
       << geom
       << ")',"
       << sridSource
       << "),"
       << sridDest
       << ")";

    std::string data = ss.str();
    std::map<std::string,std::string>* row = new std::map<std::string,std::string>();

    ( *row )[ geomField ] = data;
    ( *mFieldsListCollection[ sosi::sosi_element_surface ] )[ geomField ] = std::max( ( *mFieldsListCollection[ sosi::sosi_element_surface ] )[ geomField ], data.length() );

    extractData( polygon, sosi::sosi_element_surface, row );
    mRowsListCollection[ sosi::sosi_element_surface ]->push_back( row );
}

void sosicon::ConverterSosi2psql::
makePsql( ISosiElement* sosiTree,
          std::string sridDest,
          std::string dbSchema,
          std::string dbTable ) {

    std::string sridSource = getSrid( sosiTree );
    std::string geomField = dbTable + "_geom";
    sosi::SosiTranslationTable ttbl;
    sosi::SosiElementSearch srcPoint = sosi::SosiElementSearch( sosi::sosi_element_point );
    sosi::SosiElementSearch srcLineString = sosi::SosiElementSearch( sosi::sosi_element_curve );
    sosi::SosiElementSearch srcPolygon = sosi::SosiElementSearch( sosi::sosi_element_surface );

    while( sosiTree->getChild( srcPoint ) ) {
        insertPoint( srcPoint.element(), sridSource, sridDest, geomField );
    }

    while( sosiTree->getChild( srcLineString ) ) {
        insertLineString( srcLineString.element(), sridSource, sridDest, geomField );
    }

    while( sosiTree->getChild( srcPolygon ) ) {
        insertPolygon( srcPolygon.element(), sridSource, sridDest, geomField );
    }

}

void sosicon::ConverterSosi2psql::
run() {

    mFieldsListCollection[ sosi::sosi_element_point ] = new FieldsList();
    mFieldsListCollection[ sosi::sosi_element_curve ] = new FieldsList();
    mFieldsListCollection[ sosi::sosi_element_surface ] = new FieldsList();

    mRowsListCollection[ sosi::sosi_element_point ] = new RowsList();
    mRowsListCollection[ sosi::sosi_element_curve ] = new RowsList();
    mRowsListCollection[ sosi::sosi_element_surface ] = new RowsList();

    std::string sridDest = mCmd->mSrid.empty() ? "4326" : mCmd->mSrid;

    std::string dbSchema = mCmd->mDbSchema.empty() ? "sosicon" : mCmd->mDbSchema;
    std::string dbTable = mCmd->mDbTable.empty() ? "point" : mCmd->mDbTable;
    std::string geomField = dbTable + "_geom";

    ( *mFieldsListCollection[ sosi::sosi_element_point ] )[ geomField ] = 0;
    ( *mFieldsListCollection[ sosi::sosi_element_curve ] )[ geomField ] = 0;
    ( *mFieldsListCollection[ sosi::sosi_element_surface ] )[ geomField ] = 0;

    for( std::vector<std::string>::iterator f = mCmd->mSourceFiles.begin(); f != mCmd->mSourceFiles.end(); f++ ) {
        mCurrentSourcefile = *f;
        if( !utils::fileExists( mCurrentSourcefile ) ) {
            std::cout << mCurrentSourcefile << " not found\n";
        }
        else {
            std::cout << "Reading " << mCurrentSourcefile << "\n";
            Parser p;
            char ln[ 1024 ];
            std::ifstream ifs( mCurrentSourcefile.c_str() );
            int n = 0;
            while( !ifs.eof() ) {
                if( mCmd->mIsTtyOut && ++n % 100 == 0 ) {
                    std::cout << "\rParsing line " << n;
                }
                memset( ln, 0x00, sizeof ln );
                ifs.getline( ln, sizeof ln );
                p.ragelParseSosiLine( ln );
            }
            p.complete();

            ifs.close();
            std::cout << "\r" << n << " lines parsed        \n";
            std::cout << "Building postGIS export...\n";
            ISosiElement* root = p.getRootElement();
            makePsql( root, sridDest, dbSchema, dbTable );
        }
    }
    writePsql( sridDest, dbSchema, dbTable );
    cleanup();
    std::cout << "Done!\n";
}

std::string sosicon::ConverterSosi2psql::
wktFromSosiType( sosi::ElementType elementType ) {

    switch( elementType ) {
        case sosi::sosi_element_point:
            return "POINT";
        case sosi::sosi_element_curve:
            return "LINESTRING";
        case sosi::sosi_element_surface:
            return "POLYGON";
        default:
            return "";
    }
}

void sosicon::ConverterSosi2psql::
writePsql( std::string sridDest,
           std::string dbSchema,
           std::string dbTable ) {

    std::ofstream fs;
    std::string defaultOutputFile = mCmd->mOutputFile.empty() ? "postgis_dump.sql" : mCmd->mOutputFile;
    std::string fileName = utils::nonExistingFilename( defaultOutputFile );
    std::cout << "    > Converting SOSI data to SQL...\n";
    fs.open( fileName.c_str(), std::ios::out | std::ios::trunc );
    fs.precision( 0 );
    fs << "SET NAMES 'LATIN1';\n"
       << "DO\n"
       << "$$\n"
       << "BEGIN\n"
       << "CREATE SCHEMA " + dbSchema + ";\n"
       << "EXCEPTION WHEN duplicate_table THEN\n"
       << "END\n"
       << "$$ LANGUAGE plpgsql;\n"
       << "DO\n"
       << "$$\n"
       << "BEGIN\n"
       << "CREATE SEQUENCE " + dbSchema + "." + dbTable +  "_point_serial;\n"
       << "CREATE SEQUENCE " + dbSchema + "." + dbTable +  "_linestring_serial;\n"
       << "CREATE SEQUENCE " + dbSchema + "." + dbTable +  "_polygon_serial;\n"
       << "EXCEPTION WHEN duplicate_table THEN\n"
       << "END\n"
       << "$$ LANGUAGE plpgsql;\n"
       <<  buildCreateStatements( sridDest, dbSchema, dbTable )
       <<  buildInsertStatements( dbSchema, dbTable )
       << "SET NAMES 'UTF8';\n";
    fs.close();
    std::cout << "    > " << fileName << " written\n";
}
