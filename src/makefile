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

SOURCEFILES =									\
				main.cpp						\
				command_line.cpp				\
				factory.cpp						\
				string_utils.cpp				\
				sosi/sosi_element.cpp			\
				shape/shapefile.cpp				\
				converter_sosi2shp.cpp			\
				converter_sosi2xml.cpp			\
				converter_sosi2tsv.cpp			\
				parser.cpp						\
				parser_sosi_line.cpp

HEADERFILES = *.h

COMPILER_OPTS = 

sosicon: $(SOURCEFILES) $(HEADERFILES)


	@echo "** Pre build steps..."
	$(RAGEL) -C -L -o parser_sosi_line.cpp parser/parser_sosi_line.rl

	@echo "** Compiling..."
	$(CC) -o $(OUTDIR)/$(PROJ) $(SOURCEFILES) $(COMPILER_OPTS);
	@echo "Done."