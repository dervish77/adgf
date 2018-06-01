# makefile for DrawSdl directory tree
#
# simply type 'make all' to make everything
#
# type 'make help' for help with targets
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../drawsdl
include $(MODROOT)/module.mk
##include depend.mk


DISTVER=0.7.5


#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODDIRS = src 

APPDIRS = demo unit

GCOVDIRS = unit

CLEANDIRS = src


#
# make all programs
#

default: build_all

all: build_all install

test: dounit

build_all:
	-@echo " "
	-@echo "Building DrawSdl library ..."
	-@for dir in $(MODDIRS);  do               \
	   cd $$dir ; $(MAKE) ; cd ../../..;     \
	done;
	-@echo " "
	-@echo "Building test programs ..."
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) ; cd ..;     \
	done;
	$(MAKE) version

install: build_all 
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) install ; cd ..;     \
	done;

#------------------------------------------------------------------------

dounit: install
	-@echo " "
	-@echo "Testing drawunit ..."
	./bin/drawunit -h
	./bin/drawunit -v
	./bin/drawunit
	-@echo " "
	-@echo "Done."

#------------------------------------------------------------------------
# enable gcov via OPT in module.mk

gcov-run: dounit
	-@for dir in $(MODDIRS);  do               \
	   cd $$dir ; $(MAKE) gcov ; cd ..;     \
	done;
	-@for dir in $(GCOVDIRS);  do               \
	   cd $$dir ; $(MAKE) gcov ; cd ..;     \
	done;

GCOVREPORT = drawsdl.gcov

gcov: gcov-run
	-@echo "COVERAGE REPORT" > $(GCOVREPORT)
	-@echo "src/library  ===========" >> $(GCOVREPORT)
	cat src/draw-sdl.cpp.gcov >> $(GCOVREPORT)
	cat src/draw-text.cpp.gcov >> $(GCOVREPORT)
	-@echo "unit/drawunit ==========" >> $(GCOVREPORT)
	cat unit/unit.cpp.gcov >> $(GCOVREPORT)
	cat unit/main.cpp.gcov >> $(GCOVREPORT)
	-@echo "END REPORT" >> $(GCOVREPORT)

coverage : realclean gcov
	./coverage.sh $(GCOVREPORT)

#------------------------------------------------------------------------
# enable gprof via OPT in module.mk

prof-test: install
	./bin/drawunit

GPROFREPORT = drawsdl.gprof

gprof: prof-test
	-@echo "GPROF REPORT" > $(GPROFREPORT)
	$(GPROF) -b ./bin/drawunit >> $(GPROFREPORT)
	-@echo "END REPORT" >> $(GPROFREPORT)

kprof: prof-test
	cp gmon.out unit
	$(KPROF) -f ./bin/drawunit &

#------------------------------------------------------------------------

help:
	-@echo "Top Level Targets:"
	-@echo "  make help              - prints help"
	-@echo " "
	-@echo "  make PORT=<port>       - builds everything for default PORT"
	-@echo "  make PORT=<port> all   - builds everything and installs"
	-@echo "  make install           - copies to INSTALL_DIR tree"
	-@echo "  make test              - builds and runs unit tests"
	-@echo " "
	-@echo "  make clean             - cleans up all packages"
	-@echo "  make realclean         - pristine clean"
	-@echo " "
	-@echo "  make distro            - cleans then builds distro"
	-@echo "  make tar               - creates tar ball of entire tree"
	-@echo " "
	-@echo "Supported Ports:"
	-@echo "  linux                  - Linux host build"
	-@echo "  cygwin                 - Cygwin host build"
	-@echo " "

#------------------------------------------------------------------------

version:
	-@echo " "
	-@echo "DrawSdl Version is $(DISTVER)"
	-@echo " "

#------------------------------------------------------------------------

# remove all *.o and backup files

clean:
	-@for dir in $(CLEANDIRS);  do               \
	   cd $$dir ; $(MAKE) clean ; cd ../../..;     \
	done;
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) clean ; cd ..;     \
	done;


# remove all *.o, executables, and library files

realclean:
	-@for dir in $(CLEANDIRS);  do               \
	   cd $$dir ; $(MAKE) realclean ; cd ../../..; \
	done;
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) realclean ; cd ..; \
	done;
	rm -f *~ *.gcov *.gprof gmon.out callgrind.out.*
	rm -f bin/draw* lib/*.a include/*.h 
	rm -f images/shipcopy.bmp 

distclean: realclean

#------------------------------------------------------------------------
# make distribution file
#

distro: distclean archive version

PKG_HOME = drawsdl
PKG_NAME = drawsdl-$(DISTVER)

tar: realclean archive version

archive:
	cd .. ; \
	tar -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	gzip $(PKG_NAME).tar ; \
	mv $(PKG_NAME).tar.gz $(PKG_NAME).tgz
	-@echo "Distribution package is ../$(PKG_NAME).tgz" 

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

