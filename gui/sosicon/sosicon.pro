#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T13:23:04
#
#-------------------------------------------------

win32:RC_ICONS += ../graphics/sosicon_icon.ico
ICON = ../graphics/sosicon_icon.icns

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += no_batch

TARGET = sosicon
#TEMPLATE = app

#QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas
#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-variable
#QMAKE_CXXFLAGS_WARN_ON += -Wno-strict-aliasing

SOURCES += main.cpp\
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
    ../../src/shape/shapefile.cpp \
    ../../src/logger.cpp \
    worker.cpp \
    mainfrm.cpp

HEADERS  += \
    ../../src/common_types.h \
    ../../src/converter_sosi2tsv.h \
    ../../src/converter_sosi2xml.h \
    ../../src/coordinate.h \
    ../../src/factory.h \
    ../../src/inttypes.h \
    ../../src/utils.h \
    ../../src/parser.h \
    ../../src/sosi/sosi_element_search.h \
    ../../src/sosi/sosi_junction_point.h \
    ../../src/sosi/sosi_origo_ne.h \
    ../../src/sosi/sosi_ref_list.h \
    ../../src/sosi/sosi_unit.h \
    ../../src/sosi/sosi_charset_singleton.h \
    ../../src/sosi/sosi_translation_table.h \
    ../../src/sosi/sosi_types.h \
    ../../src/sosi/sosi_element.h \
    ../../src/sosi/sosi_north_east.h \
    ../../src/coordinate_collection.h \
    ../../src/converter_sosi2shp.h \
    ../../src/converter_sosi2psql.h \
    ../../src/converter_sosi_stat.h \
    ../../src/command_line.h \
    ../../src/byte_order.h \
    ../../src/shape/shapefile_types.h \
    ../../src/shape/shapefile.h \
    ../../src/interface/i_converter.h \
    ../../src/interface/i_coordinate.h \
    ../../src/interface/i_lookup_table.h \
    ../../src/interface/i_rectangle.h \
    ../../src/interface/i_shape_element_header.h \
    ../../src/interface/i_shape_element.h \
    ../../src/interface/i_shape_header.h \
    ../../src/interface/i_shapefile_dbf_part.h \
    ../../src/interface/i_shapefile_prj_part.h \
    ../../src/interface/i_shapefile_shp_part.h \
    ../../src/interface/i_shapefile_shx_part.h \
    ../../src/interface/i_shapefile.h \
    ../../src/interface/i_sosi_element.h \
    ../../src/interface/i_sosi_head_member.h \
    ../../src/interface/i_binary_streamable.h \
    ../../src/logger.h \
    ../../src/log_event.h \
    ../../src/event_dispatcher.h \
    worker.h \
    mainfrm.h

FORMS    += \
    mainfrm.ui
