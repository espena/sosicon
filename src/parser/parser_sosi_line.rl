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
#include "parser.h"
#pragma warning ( disable: 4244 )

namespace sosicon {

    //! \cond 
    %%{
        machine parseSosiLine;
        write data;
    }%%
    //! \endcond

}

void sosicon::Parser::
parseSosiLine( std::string sosiLine )
{
    int cs = 0;
    const char* s = sosiLine.c_str();
    const char* p = s;
    const char* pe = p + sosiLine.size();
    const char* eof = pe;

    %%{

        action filter_by_objtype {
            if( mCurrentElement && 
                std::find( mObjTypeFilter.begin(),
                           mObjTypeFilter.end(),
                           mCurrentElement->getData( "objtype" ) ) != mObjTypeFilter.end() ) {
                mSosiElementsSelection.push_back( mCurrentElement );
            }           
        }
        
        action resolve_coordinates {
            if( mCurrentElement && mHeadElement && !mHeadElement->getData( "enhet" ).empty() ) {
                float flUnit = 0.0, flNorth = 0.0, flEast = 0.0;
                std::stringstream ssUnit, ssNorth, ssEast;
                ssUnit  << mHeadElement->getData( "enhet" );
                ssNorth << mCurrentElement->getData( "koord_n" );
                ssEast  << mCurrentElement->getData( "koord_o" );
                if( ssUnit.good() && ssNorth.good() && ssEast.good() ) {
                    ssUnit   >> flUnit;
                    ssNorth  >> flNorth;
                    ssEast   >> flEast;
                    flNorth  *= flUnit;
                    flEast   *= flUnit;
                    std::stringstream ssNorth2, ssEast2;
                    ssNorth2.unsetf( std::stringstream::scientific );
                    ssNorth2.setf( std::stringstream::fixed );
                    ssNorth2.precision( 2 );
                    ssEast2.unsetf( std::stringstream::scientific );
                    ssEast2.setf( std::stringstream::fixed );
                    ssEast2.precision( 2 );
                    ssNorth2 << flNorth;
                    ssEast2  << flEast;
                    mCurrentElement->set( "koord_n", ssNorth2.str() );
                    mCurrentElement->set( "koord_o", ssEast2.str() );
                }
            }
        }
        
        action resolve_koordsys {
            if( mCurrentElement ) {
                ::sosicon::sosi::CoordSys c( mCurrentElement->getData( "koordsys" ) );
                mCurrentElement->set( "koordsys_srid",        c.getSrid()        );
                mCurrentElement->set( "koordsys_beskrivelse", c.getDescription() );
                mCurrentElement->set( "koordsys_datum",       c.getDatum()       );
                mCurrentElement->set( "koordsys_projeksjon",  c.getProjection()  );
                mCurrentElement->set( "koordsys_sone",        c.getZone()        );                
            }
        }
        
        action see_address_unit {
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet", ' ' );
            }
        }
        
        action see_address_unit_door_number {
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet_lopenummer", fc );
            }
        }

        action see_address_unit_floor_level {
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet_etasjeplan", fc );
            }
        }

        action see_address_unit_floor_number {
            if( mCurrentElement ) {
                mCurrentElement->append( "adressebruksenhet_etasjenummer", fc );
            }
        }

        action see_aid {
            if( mCurrentElement ) {
                mCurrentElement->append( "aid", fc );
            }
        }

        action see_aid_letter {
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_bokstav", fc );
            }
        }
        
        action see_aid_number {
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_husnr", fc );
            }
        }
        
        action see_aid_street {
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_gate", fc );
            }
        }
        
        action see_aid_subnumber {
            if( mCurrentElement ) {
                mCurrentElement->append( "aid_unr", fc );
            }
        }

        action see_building_number {
            if( mCurrentElement ) {
                mCurrentElement->append( "byggnr", fc );
            }
        }

        action see_building_status {
            if( mCurrentElement ) {
                mCurrentElement->append( "byggstat", fc );
            }
        }

        action see_building_type {
            if( mCurrentElement ) {
                mCurrentElement->append( "byggtyp_nbr", fc );
            }
        }

        action see_cadastral_unit_cadastre {
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_gardsnr", fc );
            }
        }

        action see_cadastral_unit_leasehold {
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_festenr", fc );
            }
        }

        action see_cadastral_unit_municipality {
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_kommunenr", fc );
            }
        }

        action see_cadastral_unit_property {
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_bruksnr", fc );
            }
        }

        action see_cadastral_unit_section {
            if( mCurrentElement ) {
                mCurrentElement->append( "matrikkelnummer_seksjonsnr", fc );
            }
        }

        action see_charset {
            if( mCurrentElement ) {
                mCurrentElement->append( "tegnsett", fc );
            }
        }

        action see_coord_n {
            if( mCurrentElement ) {
                mCurrentElement->append( "koord_n", fc );
            }
        }

        action see_coord_o {
            if( mCurrentElement ) {
                mCurrentElement->append( "koord_o", fc );
            }
        }

        action see_coord_sys {
            if( mCurrentElement ) {
                mCurrentElement->append( "koordsys", fc );
            }
        }

        action see_head {
            mCurrentElement = new ::sosicon::sosi::SosiElementHead();
            mHeadElement = mCurrentElement;
        }

        action see_id {
            if( mCurrentElement ) {
                mCurrentElement->append( "id", fc );
            }
        }

        action see_max_n {
            if( mCurrentElement ) {
                mCurrentElement->append( "max_n", fc );
            }
        }

        action see_max_o {
            if( mCurrentElement ) {
                mCurrentElement->append( "max_o", fc );
            }
        }

        action see_min_n {
            if( mCurrentElement ) {
                mCurrentElement->append( "min_n", fc );
            }
        }

        action see_min_o {
            if( mCurrentElement ) {
                mCurrentElement->append( "min_o", fc );
            }
        }

        action see_municipality_number {
            if( mCurrentElement ) {
                mCurrentElement->append( "komm", fc );
            }
        }
        
        action see_objtype {
            if( mCurrentElement ) {
                mCurrentElement->append( "objtype", fc );
            }
        }

        action see_origo_n {
            if( mCurrentElement ) {
                mCurrentElement->append( "origo_n", fc );
            }
        }

        action see_origo_o {
            if( mCurrentElement ) {
                mCurrentElement->append( "origo_o", fc );
            }
        }

        action see_point {
            mCurrentElement = new sosicon::sosi::SosiElementPoint();
            mSosiElements.push_back( mCurrentElement );
        }
        
        action see_post_name {
            if( mCurrentElement ) {
                mCurrentElement->append( "post_sted", fc );
            }
        }
        
        action see_post_number {
            if( mCurrentElement ) {
                mCurrentElement->append( "post_nr", fc );
            }
        }
        
        action see_product_spec {
            if( mCurrentElement ) {
                mCurrentElement->append( "produktspek", fc );
            }
        }

        action see_ptema {
            if( mCurrentElement ) {
                mCurrentElement->append( "ptema", fc );
            }
        }

        action see_sosi_version {
            if( mCurrentElement ) {
                mCurrentElement->append( "sosi_versjon", fc );
            }
        }

        action see_ssr_id {
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_id", fc );
            }
        }
        
        action see_ssr_snavn {
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_snavn", fc );
            }
        }
        
        action see_ssr_snforek {
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_snforek", fc );
            }
        }
        
        action see_ssr_snregdato {
            if( mCurrentElement ) {
                mCurrentElement->append( "ssr_snregdato", fc );
            }
        }
        
        action see_street_name {
            if( mCurrentElement ) {
                mCurrentElement->append( "gatenavn", fc );
            }
        }
        
        action see_text {
            mCurrentElement = new sosicon::sosi::SosiElementText();
            mSosiElements.push_back( mCurrentElement );
        }

        action see_unit {
            if( mCurrentElement ) {
                mCurrentElement->append( "enhet", fc );
            }
        }

        action see_unknown {
            mCurrentElement = 0;
        }
        
        crlf          = ( space* . [\n\r]+ );

        crlfq         = ( space* . [\n\r"]+ );

        digits        = ( [0-9]+ );
        
        digits4       = ( [0-9]{4} );

        float         = ( [0-9]+ . [0-9\.]+ );

        letter        = ( [A-Z] );

        ncrlf         = ( [^\n\r]+ );

        ncrlfq        = ( [^\n\r"]+ );

        spaceq        = ( space . ["]? );

        adressebruk   = ( ( '..ADRESSEBRUKSENHET' )@see_address_unit ) |
                        ( ( '...L' . alnum . 'PENR' ) . space . ( digits )$see_address_unit_door_number ) |
                        ( ( '...ETASJENUMMER' ) . space . ( digits )$see_address_unit_floor_number ) |
                        ( ( '...ETASJEPLAN' ) . space . ( letter )$see_address_unit_floor_level );

        aid           = ( ( '..AID' ) . space+ . ( ( digits )$see_aid_street ) . 
                                       space+ . ( ( digits )$see_aid_number ) .
                                       space+ . ( ( letter )$see_aid_letter ) .
                                       space+ . ( ( digits )$see_aid_subnumber ) );

        byggnr        = ( ( '..BYGGNR' ) . space . ( ( digits )$see_building_number ) );

        byggstat      = ( ( '..BYGGSTAT' ) . spaceq . ( ( ncrlfq )$see_building_status ) . crlfq );

        byggtyp       = ( ( '..BYGGTYP_NBR' ) . space . ( ( digits )$see_building_type ) );

        enhet         = ( ( '...ENHET' ) . space+ . ( ( ncrlf )$see_unit ) . crlf );

        gatenavn      = ( ( '..GATENAVN' ) . spaceq . ( ( ncrlfq )$see_street_name ) . crlfq );

        hode          = ( ( '.HODE' )@see_head );

        komm          = ( ( '..KOMM' ) . space . ( digits4 )$see_municipality_number );

        kommentar     = ( '!' . any* );

        koordinater   = ( ( float )$see_coord_n . space+ . ( float )$see_coord_o . crlf@resolve_coordinates );

        koordsys      = ( ( '...KOORDSYS' ) . space . ( digits )$see_coord_sys . crlf@resolve_koordsys );

        matrikkel     = ( ( '..MATRIKKELNUMMER' ) . space . ( digits )$see_cadastral_unit_municipality .
                                                    space . ( digits )$see_cadastral_unit_cadastre .
                                                    space . ( digits )$see_cadastral_unit_property .
                                                    space . ( digits )$see_cadastral_unit_leasehold .
                                                    space . ( digits )$see_cadastral_unit_section );

        max_no        = ( ( '...MAX-N' . extend ) . space+ . ( float )$see_max_n . space+ . ( float )$see_max_o . crlf );

        min_no        = ( ( '...MIN-N' . extend ) . space+ . ( float )$see_min_n . space+ . ( float )$see_min_o . crlf );

        objtype       = ( ( '..OBJTYPE' ) . spaceq . ( ( ncrlfq )$see_objtype ) . crlfq@filter_by_objtype );

        origo_no      = ( ( '...ORIGO-N' . extend ) . space+ . ( float )$see_origo_n . space+ . ( float )$see_origo_o . crlf );

        post          = ( ( ( '..POST' ) . space . ( digits4 )$see_post_number ) .
                                          spaceq . ( ( ( ncrlfq )+ )$see_post_name ) . crlfq );

        produktspek   = ( ( '...PRODUKTSPEK' ) . space . ( ( ncrlf )$see_product_spec ) . crlf );

        ptema         = ( ( '..PTEMA' ) . space . ( digits )$see_ptema );

        punkt         = ( ( '.PUNKT' )@see_point . space . ( [^:]+ )$see_id . ':' );

        sosi_versjon  = ( ( '..SOSI-VERSJON' ) . spaceq . ( ncrlfq )$see_sosi_version );

        ssr_id        = ( ( '...SSR-ID' ) . space . ( digits )$see_ssr_id );

        ssr_snavn      = ( ( '...SNAVN' ) . spaceq . ( ( ncrlfq )$see_ssr_snavn ) . crlfq );

        ssr_snforek   = ( ( '...SSR-FOREK' ) . space . ( ncrlf )$see_ssr_snforek );

        ssr_snregdato = ( ( '...SSR-SNREGDATO' ) . space . ( digits )$see_ssr_snregdato );

        tegnsett      = ( ( '..TEGNSETT' ) . spaceq . ( ( ncrlfq )$see_charset ) . crlfq );

        tekst         = ( ( '.TEKST' )@see_text );

        ukjent        = ( ( '.' . [^.] )@see_unknown ) . extend*;

        main := ( adressebruk    |
                  aid            |
                  byggnr         |
                  byggstat       |
                  byggtyp        |
                  enhet          |
                  gatenavn       |
                  hode           |
                  komm           |
                  kommentar      |
                  koordinater    |
                  koordsys       |
                  matrikkel      |
                  max_no         |
                  min_no         |
                  objtype        |
                  origo_no       |
                  post           |
                  produktspek    |
                  ptema          |
                  punkt          |
                  sosi_versjon   |
                  ssr_id         |
                  ssr_snavn      |
                  ssr_snforek    |
                  ssr_snregdato  |
                  tekst          |
                  tegnsett       |
                  ukjent         );

        write init;
        write exec;

    }%%

};