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
                       std::string dbTable,
                       FieldsListCollection& fields ) {

    std::stringstream ss;
    std::string geomField = dbTable + "_geom";
    ss << "CREATE TABLE " + dbSchema + "." + dbTable +  "(id_" + dbTable +  " INT DEFAULT nextval('" + dbSchema + "." + dbTable +  "_serial')";
    FieldsList::iterator itrFields;

    for( itrFields = fields[ sosi::sosi_element_point ]->begin(); itrFields != fields[ sosi::sosi_element_point ]->end(); itrFields++ ) {
       std::string field = itrFields->first;
       std::string::size_type len = itrFields->second;
       if( field != geomField ) {
           ss << "," << field << " VARCHAR(" << std::fixed << len << ")";
       }
    }

    ss << ");\n";
    ss << "SELECT AddGeometryColumn( '" + dbSchema + "', '" + dbTable +  "', '" + geomField + "', " + sridDest + ", 'POINT', 2 );\n";

    return ss.str();
}

std::string sosicon::ConverterSosi2psql::
buildInsertStatements( std::string dbSchema,
                       std::string dbTable,
                       FieldsListCollection& fields,
                       RowsListCollection& rows ) {

    std::string sqlInsert;
    std::string sqlValues;
    std::string sqlComposite;

    RowsList::iterator itrRows;
    FieldsList::iterator itrFields;

    FieldsList* f = fields[ sosi::sosi_element_point ];
    RowsList* r = rows[ sosi::sosi_element_point ];

    std::string geomField = dbTable + "_geom";

    for( itrFields = f->begin(); itrFields != f->end(); itrFields++ ) {
        if( sqlInsert.empty() ) {
            sqlInsert = "INSERT INTO " + dbSchema + "." + dbTable +  " (" + itrFields->first;
        }
        else {
            sqlInsert += ( "," + itrFields->first );
        }
    }

    sqlInsert += ") VALUES\n";

    int rowCount = 0;
    RowsList::size_type len = r->size();
    std::cout << "    > Processing 0 of " << len;

    for( itrRows = r->begin(); itrRows != r->end(); itrRows++ ) {

        std::map<std::string,std::string>* row = *itrRows;

        if( !sqlValues.empty() && ++rowCount % 250000 == 0 ) {
            sqlValues = sqlValues.substr( 0, sqlValues.length() - 2 );
            sqlValues += ";\n";
            sqlComposite += ( sqlInsert + sqlValues );
            sqlValues.clear();
        }

        if( rowCount % 1000 == 0 ) {
            std::cout << "\r    > Processing " << rowCount << " of " << len;
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
    std::cout << "\r    > " << rowCount << " points processed               \n";

    sqlValues.pop_back();
    sqlValues.pop_back();
    sqlValues += ";\n";
    sqlComposite += ( sqlInsert + sqlValues );

    return sqlComposite;
}

void sosicon::ConverterSosi2psql::
cleanup( FieldsListCollection& fields,
         RowsListCollection& rows ) {

    std::cout << "    > Clean-up...\n";
    RowsList::iterator i;
    for( i = rows[ sosi::sosi_element_point ]->begin(); i != rows[ sosi::sosi_element_point ]->end(); i++ ) {
        delete *i;
    }
    delete rows[ sosi::sosi_element_point ];
    rows[ sosi::sosi_element_point ] = 0;
    delete fields[ sosi::sosi_element_point ];
    fields[ sosi::sosi_element_point ] = 0;
}

void sosicon::ConverterSosi2psql::
extractData( ISosiElement* parent,
             FieldsListCollection& fields,
             std::map<std::string,std::string>*& row ) {

    sosi::SosiElementSearch srcData;
    while( parent->getChild( srcData ) ) {

        ISosiElement* dataElement = srcData.element();

        extractData( dataElement, fields, row );

        std::string field = utils::toFieldname( dataElement->getName() );
        std::string data = dataElement->getData();
        
        if( data.empty() ) {
            continue;
        }

        if( fields[ sosi::sosi_element_point ]->find( field ) == fields[ sosi::sosi_element_point ]->end() ) {
            ( *fields[ sosi::sosi_element_point ] )[ field ] = data.length();
        }
        else {
            ( *fields[ sosi::sosi_element_point ] )[ field ] = std::max( ( *fields[ sosi::sosi_element_point ] )[ field ], data.length() );
        }

        ( *row )[ field ] = data;
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
             std::string geomField,
             FieldsListCollection& fields,
             RowsListCollection& rows ) {

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
        ( *fields[ sosi::sosi_element_point ] )[ geomField ] = std::max( ( *fields[ sosi::sosi_element_point ] )[ geomField ], data.length() );

        extractData( point, fields, row );
        rows[ sosi::sosi_element_point ]->push_back( row );
    }
}

void sosicon::ConverterSosi2psql::
makePsql( ISosiElement* sosiTree,
          std::string sridDest,
          std::string dbSchema,
          std::string dbTable,
          FieldsListCollection& fields,
          RowsListCollection& rows ) {

    std::string sridSource = getSrid( sosiTree );
    std::string geomField = dbTable + "_geom";
    sosi::SosiTranslationTable ttbl;
    sosi::SosiElementSearch srcPoint = sosi::SosiElementSearch( sosi::sosi_element_point );

    while( sosiTree->getChild( srcPoint ) ) {
        insertPoint( srcPoint.element(), sridSource, sridDest, geomField, fields, rows );
    }
}

void sosicon::ConverterSosi2psql::
run() {

    FieldsListCollection fields;
    fields[ sosi::sosi_element_point ] = new FieldsList();

    RowsListCollection rows;
    rows[ sosi::sosi_element_point ] = new RowsList();

    std::string sridDest = mCmd->mSrid.empty() ? "4326" : mCmd->mSrid;

    std::string dbSchema = mCmd->mDbSchema.empty() ? "sosicon" : mCmd->mDbSchema;
    std::string dbTable = mCmd->mDbTable.empty() ? "point" : mCmd->mDbTable;
    std::string geomField = dbTable + "_geom";

    ( *fields[ sosi::sosi_element_point ] )[ geomField ] = 0;

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
            makePsql( root, sridDest, dbSchema, dbTable, fields, rows );
        }
    }
    writePsql( sridDest, dbSchema, dbTable, fields, rows );
    cleanup( fields, rows );
    std::cout << "Done!\n";
}

void sosicon::ConverterSosi2psql::
writePsql( std::string sridDest,
           std::string dbSchema,
           std::string dbTable,
           FieldsListCollection& fields,
           RowsListCollection& rows ) {

    std::ofstream fs;
    std::string defaultOutputFile = mCmd->mOutputFile.empty() ? "postgis_dump.sql" : mCmd->mOutputFile;
    std::string fileName = utils::nonExistingFilename( defaultOutputFile );
    std::cout << "    > Converting SOSI data to SQL...\n";
    fs.open( fileName.c_str(), std::ios::out | std::ios::trunc );
    fs.precision( 0 );
    fs << "SET NAMES 'LATIN1';\n";
    fs << "DO\n";
    fs << "$$\n";
    fs << "BEGIN\n";
    fs << "CREATE SCHEMA " + dbSchema + ";\n";
    fs << "EXCEPTION WHEN duplicate_table THEN\n";
    fs << "END\n";
    fs << "$$ LANGUAGE plpgsql;\n";
    fs << "DO\n";
    fs << "$$\n";
    fs << "BEGIN\n";
    fs << "CREATE SEQUENCE " + dbSchema + "." + dbTable +  "_serial;\n";
    fs << "EXCEPTION WHEN duplicate_table THEN\n";
    fs << "END\n";
    fs << "$$ LANGUAGE plpgsql;\n";
    fs <<  buildCreateStatements( sridDest, dbSchema, dbTable, fields );
    fs <<  buildInsertStatements( dbSchema, dbTable, fields, rows );
    fs.close();
    std::cout << "    > " << fileName << " written\n";
}
