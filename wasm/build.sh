#!/bin/bash
docker run -v $(realpath ../):/srv -it emscripten/emsdk bash -c "\
  SOURCEFILES='\
    ../wasm/wasm.cpp \
    command_line.cpp \
    factory.cpp \
    logger.cpp \
    utils.cpp \
    byte_order.cpp \
    sosi/sosi_ref_list.cpp \
    sosi_ref_ragel.cpp \
    sosi/sosi_element.cpp \
    sosi/sosi_element_search.cpp \
    sosi/sosi_north_east.cpp \
    sosi_north_east_ragel.cpp \
    sosi_north_east_height_ragel.cpp \
    sosi/sosi_origo_ne.cpp \
    sosi_origo_ne_ragel.cpp \
    sosi/sosi_charset_singleton.cpp \
    sosi/sosi_unit.cpp \
    sosi/sosi_translation_table.cpp \
    shape/shapefile.cpp \
    converter_sosi2shp.cpp \
    converter_sosi2xml.cpp \
    converter_sosi2tsv.cpp \
    converter_sosi2psql.cpp \
    converter_sosi2mysql.cpp \
    converter_sosi_stat.cpp \
    coordinate_collection.cpp \
    parser.cpp \
    parser_ragel.cpp'
  cd /srv/src &&\
  ragel/bin/linux64/ragel -C -L -o parser_ragel.cpp ragel/parser.rl &&\
  ragel/bin/linux64/ragel -C -L -o sosi_north_east_ragel.cpp ragel/sosi_north_east.rl &&\
  ragel/bin/linux64/ragel -C -L -o sosi_north_east_height_ragel.cpp ragel/sosi_north_east_height.rl &&\
  ragel/bin/linux64/ragel -C -L -o sosi_origo_ne_ragel.cpp ragel/sosi_origo_ne.rl &&\
  ragel/bin/linux64/ragel -C -L -o sosi_ref_ragel.cpp ragel/sosi_ref.rl &&\
  emcc -std=c++17 -Os --no-entry --pre-js ../wasm/preamble.js --js-library ../wasm/mergeinto.js \$SOURCEFILES -s BUILD_AS_WORKER=1 -s MODULARIZE=1 -s EXPORT_NAME=SosiconModule -s INITIAL_MEMORY=200MB -s ALLOW_MEMORY_GROWTH=1 -s FORCE_FILESYSTEM=1 -s EXPORTED_RUNTIME_METHODS=['ccall','FS_createDataFile','FS_readFile'] -o ../wasm/sosicon.js"
wasm2wat sosicon.wasm | grep "(import"
