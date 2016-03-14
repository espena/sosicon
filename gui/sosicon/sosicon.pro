#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T13:23:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sosicon
TEMPLATE = app

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-variable

SOURCES += main.cpp\
        dlgmain.cpp \
    ../../src/byte_order.cpp \
    ../../src/command_line.cpp \
    ../../src/converter_sosi_stat.cpp \
    ../../src/converter_sosi2tsv.cpp \
    ../../src/converter_sosi2xml.cpp \
    ../../src/factory.cpp \
    ../../src/utils.cpp \
    ../../src/converter_sosi2psql.cpp \
    ../../src/converter_sosi2shp.cpp \
    ../../src/coordinate_collection.cpp \
    ../../src/parser.cpp \
    ../../src/parser_ragel.cpp \
    ../../src/sosi_north_east_height_ragel.cpp \
    ../../src/sosi_north_east_ragel.cpp \
    ../../src/sosi_origo_ne_ragel.cpp \
    ../../src/sosi_ref_ragel.cpp \
    ../../src/sosi/sosi_element_search.cpp \
    ../../src/sosi/sosi_element.cpp \
    ../../src/sosi/sosi_north_east.cpp \
    ../../src/sosi/sosi_origo_ne.cpp \
    ../../src/sosi/sosi_ref_list.cpp \
    ../../src/sosi/sosi_unit.cpp \
    ../../src/sosi/sosi_charset_singleton.cpp \
    ../../src/sosi/sosi_translation_table.cpp \
    ../../src/shape/shapefile.cpp

HEADERS  += dlgmain.h

FORMS    += dlgmain.ui
