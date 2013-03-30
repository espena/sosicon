CC = g++

UNAME := $(shell uname)

PROJ = sosicon

ifeq ($(UNAME), Darwin)
OUTDIR = ../bin/osx
RAGEL = parser/ragel_bin/osx/ragel
endif
ifeq ($(UNAME), Linux)
OUTDIR = ../bin/linux
RAGEL = parser/ragel_bin/linux/ragel
endif

SOURCEFILES =	main.cpp                        \
				command_line.cpp                \
				factory.cpp                     \
                string_utils.cpp                \
                byte_order.cpp                  \
                sosi/sosi_element.cpp           \
				sosi/sosi_element_point.cpp     \
				sosi/cadastral_unit.cpp         \
                sosi/address_unit.cpp           \
                sosi/coord_sys.cpp              \
				converter_sosi2shp.cpp          \
				converter_sosi2tsv.cpp          \
                shape/shapefile.cpp             \
                shape/shape_header.cpp          \
                shape/shape_element_header.cpp  \
                shape/shape_element_point.cpp   \
                shape/shape_index.cpp           \
                shape/shape_database.cpp        \
                shape/bounding_box.cpp          \
                parser.cpp                      \
				parser_sosi_line.cpp

HEADERFILES = 	*.h

COMPILER_OPTS = 

mine: $(SOURCEFILES) $(HEADERFILES)


	@echo "** Pre build steps..."
	$(RAGEL) -C -L -o parser_sosi_line.cpp parser/parser_sosi_line.rl

	@echo "** Compiling..."
	$(CC) -o $(OUTDIR)/$(PROJ) $(SOURCEFILES) $(COMPILER_OPTS);
	@echo "Done."