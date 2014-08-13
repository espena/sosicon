CC = g++

UNAME := $(shell uname)

PROJ = sosicon

ifeq ($(UNAME), Darwin)
OUTDIR = ../bin/osx
RAGEL = ragel/bin/osx/ragel
endif
ifeq ($(UNAME), Linux)
OUTDIR = ../bin/linux
RAGEL = ragel/bin/linux/ragel
endif

SOURCEFILES =										\
				main.cpp							\
				command_line.cpp					\
				factory.cpp							\
				utils.cpp							\
				byte_order.cpp						\
				sosi/sosi_ref_list.cpp				\
				sosi_ref_ragel.cpp			    	\
				sosi/sosi_element.cpp				\
				sosi/sosi_north_east.cpp			\
				sosi_north_east_ragel.cpp	    	\
				sosi_north_east_height_ragel.cpp	\
				sosi/sosi_origo_ne.cpp				\
				sosi_origo_ne_ragel.cpp	        	\
				sosi/sosi_unit.cpp					\
				sosi/sosi_translation_table.cpp		\
				shape/shapefile.cpp					\
				converter_sosi2shp.cpp				\
				converter_sosi2xml.cpp				\
				converter_sosi2tsv.cpp				\
				converter_sosi_stat.cpp				\
				coordinate_collection.cpp			\
				parser.cpp							\
				parser_ragel.cpp

HEADERFILES = *.h

COMPILER_OPTS = 

sosicon: $(SOURCEFILES) $(HEADERFILES)


	@echo "** Pre build steps..."
	$(RAGEL) -C -L -o parser_ragel.cpp ragel/parser.rl
	$(RAGEL) -C -L -o sosi_north_east_ragel.cpp ragel/sosi_north_east.rl
	$(RAGEL) -C -L -o sosi_north_east_height_ragel.cpp ragel/sosi_north_east_height.rl
	$(RAGEL) -C -L -o sosi_origo_ne_ragel.cpp ragel/sosi_origo_ne.rl
	$(RAGEL) -C -L -o sosi_ref_ragel.cpp ragel/sosi_ref.rl

	@echo "** Compiling..."
	$(CC) -o $(OUTDIR)/$(PROJ) $(SOURCEFILES) $(COMPILER_OPTS);
	@echo "Done."