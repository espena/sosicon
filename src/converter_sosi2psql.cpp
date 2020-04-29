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

    sql  = buildCreateStatement( wkt_point,
                                 sridDest,
                                 dbSchema,
                                 dbTable );

    sql += buildCreateStatement( wkt_linestring,
                                 sridDest,
                                 dbSchema,
                                 dbTable );

    sql += buildCreateStatement( wkt_polygon,
                                 sridDest,
                                 dbSchema,
                                 dbTable );
    return sql;
}

std::string sosicon::ConverterSosi2psql::
buildCreateStatement( Wkt wktGeom,
                      std::string sridDest,
                      std::string dbSchema,
                      std::string dbTable ) {

    std::string geometryType = utils::wktToStr( wktGeom );

    std::stringstream ss;
    if( !geometryType.empty() && mFieldsListCollection[ wktGeom ]->size() > 0 ) {

        std::string geomName = utils::toLower( geometryType );
        std::string geomField = dbTable + "_geom";

        ss << "CREATE TABLE IF NOT EXISTS "
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

        FieldsList* f = mFieldsListCollection[ wktGeom ];
        FieldsList::iterator itrFields;
        for( itrFields = f->begin(); itrFields != f->end(); itrFields++ ) {
           std::string field = itrFields->first;
           std::string::size_type len = itrFields->second.length();
           bool isNumeric = itrFields->second.isNumeric();
           if( field != geomField ) {
               if( isNumeric && len < 10 ) {
                   ss << ","
                      << field
                      << " INTEGER";
               }
               else if( isNumeric && len < 19 ) {
                   ss << ","
                      << field
                      << " BIGINT";
               }
               else if( len > 255 ) {
                   ss << ","
                      << field
                      << " TEXT";
               }
               else {
                   ss << ","
                      << field
                      << " VARCHAR("
                      << std::fixed
                      << len
                      << ")";
               }
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
    sql  = buildInsertStatement( wkt_point,
                                 dbSchema,
                                 dbTable );

    sql += buildInsertStatement( wkt_linestring,
                                 dbSchema,
                                 dbTable );

    sql += buildInsertStatement( wkt_polygon,
                                 dbSchema,
                                 dbTable );
    return sql;
}

std::string sosicon::ConverterSosi2psql::
buildInsertStatement( Wkt wktGeom,
                      std::string dbSchema,
                      std::string dbTable ) {

    std::string sqlComposite;
    std::string geometryType = utils::wktToStr( wktGeom );

    if( !geometryType.empty() && mRowsListCollection[ wktGeom ]->size() > 0 ) {

        std::string sqlInsert;
        std::string sqlValues;

        RowsList::iterator itrRows;
        FieldsList::iterator itrFields;

        FieldsList* f = mFieldsListCollection[ wktGeom ];
        RowsList* r = mRowsListCollection[ wktGeom ];

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
        sosicon::logstream << "    > Processing 0 of " << len << sosicon::flush;
        for( itrRows = r->begin(); itrRows != r->end(); itrRows++ ) {
            std::map<std::string,std::string>* row = *itrRows;
            if( !sqlValues.empty() && ++rowCount % 50000 == 0 ) {
                sqlValues = sqlValues.substr( 0, sqlValues.length() - 2 );
                sqlValues += ";\n";
                sqlComposite += ( sqlInsert + sqlValues );
                sqlValues.clear();
            }
            if( rowCount % 1000 == 0 ) {
                sosicon::logstream << "\r    > Processing " << rowCount << " of " << len << sosicon::flush;
            }
            sqlValues += "(";
            for( itrFields = f->begin(); itrFields != f->end(); itrFields++ ) {
                std::string key = itrFields->first;
                if( row->find( key ) == row->end() ) {
                    ( *row )[ key ] = "";
                }
                std::string val = utils::trim( ( *row )[ key ] );
                if( val.empty() ) {
                    sqlValues += itrFields->second.isNumeric() ? "NULL," : "'',";
                }
                else if( key == geomField ) {
                    sqlValues += val + ",";
                }
                else if( itrFields->second.isNumeric() ) {
                    sqlValues += utils::sqlNormalize( val ) + ",";
                }
                else {
                    sqlValues += "'" + utils::sqlNormalize( val ) + "',";
                }
            }
            sqlValues.erase( sqlValues.size() - 1 );
            sqlValues += "),\n";
        }
        sosicon::logstream << "\r    > " << rowCount << " " << geomName << "s processed               \n" << sosicon::flush;
        sqlValues.erase( sqlValues.size() - 2 );
        sqlValues += ";\n";
        sqlComposite += ( sqlInsert + sqlValues );
    }
    return sqlComposite;
}

void sosicon::ConverterSosi2psql::
cleanup() {
    sosicon::logstream << "    > Clean-up...\n";
    cleanup( wkt_point );
    cleanup( wkt_linestring );
    cleanup( wkt_polygon );
}

void sosicon::ConverterSosi2psql::
cleanup( Wkt wktGeom ) {

    RowsList* r = mRowsListCollection[ wktGeom ];
    RowsList::iterator i;

    for( i = r->begin(); i != r->end(); i++ ) {
        delete *i;
    }

    delete mRowsListCollection[ wktGeom ];
    mRowsListCollection[ wktGeom ] = 0;

    delete mFieldsListCollection[ wktGeom ];
    mFieldsListCollection[ wktGeom ] = 0;
}

void sosicon::ConverterSosi2psql::
extractData( ISosiElement* parent,
             FieldsList& hdr,
             std::map<std::string,std::string>*& row ) {

    sosi::SosiElementSearch srcData;
    while( parent->getChild( srcData ) ) {

        ISosiElement* dataElement = srcData.element();

        extractData( dataElement, hdr, row );

        std::string fieldName = utils::toFieldname( dataElement->getName() );
        std::string data = dataElement->getData();

        if( data.empty() ) {
            continue;
        }

        if( hdr.find( fieldName ) == hdr.end() ) {
            hdr[ fieldName ] = Field( data );
        }
        else {
          hdr[ fieldName ].expand( data );
        }

        if( row ) {
          if( row->find( fieldName ) == row->end() ) {
            ( *row )[ fieldName ] = data;
          }
          else {
            ( *row )[ fieldName ] += ( "|" + data );
            hdr[ fieldName ].expand( ( *row )[ fieldName ] );
          }
        }
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
        sosicon::logstream << "Coordinate system: " << cs.displayString() << "\n";
    }
    else {
        sosicon::logstream << "No KOORDSYS code found in sosi file.\nDefaults to 23 (EPSG:25833 - ETRS89 / UTM zone 33N)\n";
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

        std::map<std::string,std::string>* row = 0;

        if( mCmd->mInsertStatements ) {
            row = new std::map<std::string,std::string>();
        }

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

        if( mCmd->mInsertStatements ) {
            ( *row )[ geomField ] = data;
        }

        FieldsList& hdr = ( *mFieldsListCollection[ wkt_point ] );
        hdr[ geomField ].expand( data );

        extractData( point, hdr, row );

        if( mCmd->mInsertStatements ) {
            mRowsListCollection[ wkt_point ]->push_back( row );
        }
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
    geom.erase( geom.size() - 1 );

    std::stringstream ss;
    ss << "ST_Transform(ST_GeomFromText('LINESTRING("
       << geom
       << ")',"
       << sridSource
       << "),"
       << sridDest
       << ")";

    std::string data = ss.str();

    std::map<std::string,std::string>* row = 0;
    if( mCmd->mInsertStatements ) {
        row = new std::map<std::string,std::string>();
        ( *row )[ geomField ] = data;
    }

    FieldsList& hdr = ( *mFieldsListCollection[ wkt_linestring ] );
    hdr[ geomField ].expand( data );

    extractData( lineString, hdr, row );

    if( mCmd->mInsertStatements ) {
        mRowsListCollection[ wkt_linestring ]->push_back( row );
    }
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
    geom.erase( geom.size() - 1 );
    geom += ")";

    std::stringstream ssHolesCoord;
    ssHolesCoord.precision( 5 );
    ssHolesCoord << std::fixed;

    int offset = 0;
    ICoordinate* first = 0, * last = 0;
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

    std::map<std::string,std::string>* row = 0;
    if( mCmd->mInsertStatements ) {
        row = new std::map<std::string,std::string>();
        ( *row )[ geomField ] = data;
    }

    FieldsList& hdr = ( *mFieldsListCollection[ wkt_polygon ] );
    hdr[ geomField ].expand( data );

    extractData( polygon, hdr, row );

    if( mCmd->mInsertStatements ) {
        mRowsListCollection[ wkt_polygon ]->push_back( row );
    }
}

void sosicon::ConverterSosi2psql::
makePsql( ISosiElement* sosiTree,
          std::string sridDest,
          std::string,
          std::string dbTable ) {

    std::string sridSource = getSrid( sosiTree );
    std::string geomField = dbTable + "_geom";
    sosi::SosiTranslationTable ttbl;

    std::vector<sosi::ElementType> pointTypes;
    pointTypes.push_back( sosi::sosi_element_point );
    pointTypes.push_back( sosi::sosi_element_text );
    sosi::SosiElementSearch srcPoint = sosi::SosiElementSearch( pointTypes );
    while( sosiTree->getChild( srcPoint ) ) {
        if( objTypeExcluded( srcPoint ) ) continue;
        insertPoint( srcPoint.element(), sridSource, sridDest, geomField );
    }

    std::vector<sosi::ElementType> lineStringTypes;
    lineStringTypes.push_back( sosi::sosi_element_curve );
    sosi::SosiElementSearch srcLineString = sosi::SosiElementSearch( lineStringTypes );
    while( sosiTree->getChild( srcLineString ) ) {
        if( objTypeExcluded( srcLineString ) ) continue;
        insertLineString( srcLineString.element(), sridSource, sridDest, geomField );
    }

    std::vector<sosi::ElementType> polygonTypes;
    polygonTypes.push_back( sosi::sosi_element_surface );
    sosi::SosiElementSearch srcPolygon = sosi::SosiElementSearch( polygonTypes );
    while( sosiTree->getChild( srcPolygon ) ) {
        if( objTypeExcluded( srcPolygon ) ) continue;
        insertPolygon( srcPolygon.element(), sridSource, sridDest, geomField );
    }
}

bool sosicon::ConverterSosi2psql::
objTypeExcluded( sosi::SosiElementSearch& src )
{
    std::vector<std::string>& ot = mCmd->mObjTypes;
    return ot.size() > 0 && std::find( ot.begin(), ot.end(), utils::toLower( src.element()->getObjType() ) ) == ot.end();
}

void sosicon::ConverterSosi2psql::
run( bool* ) {

    mFieldsListCollection[ wkt_point ] = new FieldsList();
    mFieldsListCollection[ wkt_linestring ] = new FieldsList();
    mFieldsListCollection[ wkt_polygon ] = new FieldsList();

    mRowsListCollection[ wkt_point ] = new RowsList();
    mRowsListCollection[ wkt_linestring ] = new RowsList();
    mRowsListCollection[ wkt_polygon ] = new RowsList();

    std::string sridDest = mCmd->mSrid.empty() ? "4326" : mCmd->mSrid;

    std::string dbSchema = mCmd->mDbSchema.empty() ? "sosicon" : utils::toLower( mCmd->mDbSchema );
    std::string dbTable = mCmd->mDbTable.empty() ? "object" : utils::toLower( mCmd->mDbTable );
    std::string geomField = dbTable + "_geom";

    ( *mFieldsListCollection[ wkt_point ] )[ geomField ] = Field();
    ( *mFieldsListCollection[ wkt_linestring ] )[ geomField ] = Field();
    ( *mFieldsListCollection[ wkt_polygon ] )[ geomField ] = Field();

    for( std::vector<std::string>::iterator f = mCmd->mSourceFiles.begin(); f != mCmd->mSourceFiles.end(); f++ ) {
        mCurrentSourcefile = *f;
        if( !utils::fileExists( mCurrentSourcefile ) ) {
            sosicon::logstream << mCurrentSourcefile << " not found\n";
        }
        else {
            sosicon::logstream << "Reading " << mCurrentSourcefile << "\n";
            Parser p;
            char ln[ 1024 ];
            std::ifstream ifs( mCurrentSourcefile.c_str() );
            int n = 0;
            while( !ifs.eof() ) {
                if( ++n % 100 == 0 ) {
                    sosicon::logstream << "\rParsing line " << n;
                }
               memset( ln, 0x00, sizeof ln );
                ifs.getline( ln, sizeof ln );
                p.ragelParseSosiLine( ln );
            }
            p.complete();

            ifs.close();
            sosicon::logstream << "\r" << n << " lines parsed        \n";
            sosicon::logstream << "Building postGIS export...\n";
            ISosiElement* root = p.getRootElement();
            makePsql( root, sridDest, dbSchema, dbTable );
        }
    }
    writePsql( sridDest, dbSchema, dbTable );
    cleanup();
    sosicon::logstream << "Done!\n";
}

void sosicon::ConverterSosi2psql::
writePsql( std::string sridDest,
           std::string dbSchema,
           std::string dbTable ) {

    std::ofstream fs;
    std::string defaultOutputFile = mCmd->mOutputFile.empty() ? "postgis_dump.sql" : mCmd->mOutputFile;
    std::string fileName = utils::nonExistingFilename( defaultOutputFile );
    sosicon::logstream << "    > Converting SOSI data to SQL...\n";
    fs.open( fileName.c_str(), std::ios::out | std::ios::trunc );
    fs.precision( 0 );
    const sosi::SosiCharsetSingleton* cs = sosi::SosiCharsetSingleton::getInstance();
    const sosi::Charset sosiCharset = cs->getEncoding();
    const std::string encoding = utils::sosiEncodingToPsqlEncoding( sosiCharset );
    if( sosiCharset != sosi::Charset::sosi_charset_utf8 ) {
      fs << "SET NAMES '" << encoding << "';\n";
    }
    if( mCmd->mCreateStatements ) {
        fs << "DO\n"
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
           << "$$ LANGUAGE plpgsql;\n";
    }
    fs <<  ( mCmd->mCreateStatements ? buildCreateStatements( sridDest, dbSchema, dbTable ) : "" )
       <<  ( mCmd->mInsertStatements ? buildInsertStatements( dbSchema, dbTable ) : "" )
       << "SET NAMES 'UTF8';\n";
    fs.close();
    sosicon::logstream << "    > " << fileName << " written\n";
}
