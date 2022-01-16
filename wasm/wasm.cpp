#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cerrno>
#include <memory>
#include <filesystem>
#include <emscripten.h>
#include "../src/main.h"
#include "../src/utils.h"

extern "C" {

  extern void sosicon_done( const char* file_id );

  EMSCRIPTEN_KEEPALIVE int sosicon_get_file_length( std::string filename )
  {
    return std::filesystem::exists( filename );
  }

  EMSCRIPTEN_KEEPALIVE void sosicon_get_file_data( std::string filename, char* buffer, int length )
  {

    sosicon::logstream << "File exists? " << std::filesystem::exists( filename );

    std::ifstream ifs( filename, std::ios::in | std::ios::binary );
    ifs.read( buffer, length );
    ifs.close();
  }

  EMSCRIPTEN_KEEPALIVE int sosicon_run( void )
  {

    std::ios_base::sync_with_stdio( 0 );
    sosicon::CommandLine cmd;
    std::string exec_str;

    const std::string unique_name = sosicon::utils::randomString( 32 );

    exec_str = "sosicon -2shp -ttyexpand -l " + unique_name + ".txt -o /sosicon_input_data /sosicon_input_data.sos";
    cmd.parse( exec_str );

    int res;

    try {

        sosicon::IConverter* converter = 0;
        sosicon::Factory::get( converter, &cmd );

        if( converter ) {
            converter->run();
            sosicon::Factory::release( converter );
        }

        res = 0;
    }
    catch( std::exception ex ) {
        sosicon::logstream << ex.what() << "\n";
        res = -1;
    }

    std::ifstream logfile;
    std::string outfile;
    std::string outfile_list;

    logfile.open( "/" + unique_name + ".txt" );

    while ( logfile >> outfile ) {
      outfile_list.append( outfile + ';' );
    }

    logfile.close();

    sosicon_done( outfile_list.c_str() );

    return res;
  }

} // extern "C"
