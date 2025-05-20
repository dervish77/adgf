# makefile for MOS directory tree
#
# simply type 'make all' to make everything
#
# type 'make help' for help with targets
#
#

include ./mos.mk

DISTVER = 0.80


# "src/ports/xxx" must be first
MODDIRS = src/ports/$(PORT) src/ports/common 

APPDIRS = demo test unit

UNITDIRS = unit

CLEANDIRS = src/ports/arduino src/ports/arm src/ports/avr \
			src/ports/common src/ports/cygwin src/ports/c64 \
			src/ports/ez80 src/ports/linux src/ports/sh4


#
# make all programs
#

default: build_all

all: build_all install

build_all:
	-@echo " "
	-@echo "Building MOS library ..."
	-@for dir in $(MODDIRS);  do               \
	   cd $$dir ; $(MAKE) ; cd ../../..;     \
	done;
	-@echo " "
	-@echo "Building test programs ..."
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) ; cd ..;     \
	done;
	-@echo " "
	-@echo "MOS Version is $(DISTVER)"
	-@echo " "

install: build_all 
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) install ; cd ..;     \
	done;

test: realclean mosunit
	
avr:
	-@echo "avr cross compile is not supported"

c64:
	-@echo "c64 cross compile is not supported"

ez80:
	-@echo "ez80 cross compile is not supported"

sh4:
	-@echo "sh4 cross compile is not supported"


# =================================================================

mosdemo: all
	-@echo " "
	-@echo "Testing mosdemo ..."
	demo/mosdemo -h
	demo/mosdemo -l
	demo/mosdemo -d
	demo/mosdemo -v
	demo/mosdemo -z
	demo/mosdemo -z 55
	demo/mosdemo 1 2 3
	demo/mosdemo
	-@echo " "
	-@echo "Done."

mosapp: all
	-@echo " "
	-@echo "Testing mosapp ..."
	test/mosapp -d
	test/mosapp -z
	test/mosapp -z 55
	test/mosapp 1 2 3
	-@echo " "
	-@echo "Done."

mosunit: all
	-@echo " "
	-@echo "Testing mosunit ..."
	unit/mosunit -d
	unit/mosunit -c 1
	unit/mosunit -z
	unit/mosunit -z 55
	unit/mosunit 1 2 3
	unit/mosunit
	-@echo " "
	-@echo "Done."

# =================================================================

gcov-run: mosdemo mosapp mosunit
	-@echo "Creating gcov files ..."
	-@for dir in $(MODDIRS);  do               \
	   cd $$dir ; $(MAKE) gcov ; cd ../../..;     \
	done;
	-@for dir in $(APPDIRS);  do               \
	   cd $$dir ; $(MAKE) gcov ; cd ..;     \
	done;

gcov-run-unit: mosunit
	-@echo "Creating gcov files ..."
	-@for dir in $(MODDIRS);  do               \
	   cd $$dir ; $(MAKE) gcov ; cd ../../..;     \
	done;
	-@for dir in $(UNITDIRS);  do               \
	   cd $$dir ; $(MAKE) gcov ; cd ..;     \
	done;

GCOVREPORT = mos.gcov

gcovunit: gcov-run-unit
	-@echo "Creating gcov report ..."
	-@echo "COVERAGE REPORT (UNIT)" > $(GCOVREPORT)
	-@echo "src/library  ===========" >> $(GCOVREPORT)
	cat src/ports/$(PORT)/platform.c.gcov >> $(GCOVREPORT)
	cat src/ports/$(PORT)/hw.c.gcov >> $(GCOVREPORT)
	cat src/ports/common/mos.c.gcov >> $(GCOVREPORT)
	-@echo "unit/mosunit ==========" >> $(GCOVREPORT)
	cat unit/unittasks.c.gcov >> $(GCOVREPORT)
	cat unit/unitmain.c.gcov >> $(GCOVREPORT)
	-@echo "END REPORT" >> $(GCOVREPORT)

gcovfull: gcov-run
	-@echo "Creating gcov report ..."
	-@echo "COVERAGE REPORT (FULL)" > $(GCOVREPORT)
	-@echo "src/library  ===========" >> $(GCOVREPORT)
	cat src/ports/$(PORT)/platform.c.gcov >> $(GCOVREPORT)
	cat src/ports/$(PORT)/hw.c.gcov >> $(GCOVREPORT)
	cat src/ports/common/mos.c.gcov >> $(GCOVREPORT)
	-@echo "demo/mosdemo ===========" >> $(GCOVREPORT)
	cat demo/tasks.c.gcov >> $(GCOVREPORT)
	cat demo/demo.c.gcov >> $(GCOVREPORT)
	cat demo/main.c.gcov >> $(GCOVREPORT)
	-@echo "test/mosapp ==========" >> $(GCOVREPORT)
	cat test/apptasks.c.gcov >> $(GCOVREPORT)
	cat test/appmain.c.gcov >> $(GCOVREPORT)
	-@echo "unit/mosunit ==========" >> $(GCOVREPORT)
	cat unit/unittasks.c.gcov >> $(GCOVREPORT)
	cat unit/unitmain.c.gcov >> $(GCOVREPORT)
	-@echo "END REPORT (FULL)" >> $(GCOVREPORT)

coverage : realclean gcovunit
	./coverage.sh $(GCOVREPORT)

coveragefull : realclean gcovfull
	./coverage.sh $(GCOVREPORT)

profile: realclean gcov
	./coverage.sh $(GCOVREPORT)
#	/usr/bin/gvim $(GCOVREPORT)

# =================================================================

prof-test: all
	unit/mosunit -c 100

GPROFREPORT = mos.gprof

gprof: prof-test
	-@echo "GPROF REPORT" > $(GPROFREPORT)
	$(GPROF) -b unit/mosunit >> $(GPROFREPORT)
	-@echo "END REPORT" >> $(GPROFREPORT)

kprof: prof-test
	cp gmon.out unit
	$(KPROF) -f unit/mosunit &

# =================================================================

valcache: all
	$(VALGRIND) $(VG_CACHE) unit/mosunit -c 1000
	kcachegrind callgrind.out.*

valmem: all
	$(VALGRIND) $(VG_MEM) unit/mosunit -c 100

# =================================================================

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
	-@echo "  linux                  - Linux host sim"
	-@echo "  cygwin                 - Cygwin host sim"
	-@echo " "

version:
	-@echo "MOS Version is $(DISTVER)"


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
	rm -f bin/mos* lib/*.a lib/*.lib include/*.h 

distclean: realclean

#
# make distribution file
#

distro: distclean archive version

PKG_HOME = mos
PKG_NAME = mos-$(DISTVER)

tar: realclean archive version

archive:
	cd .. ; \
	tar -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	gzip $(PKG_NAME).tar ; \
	mv $(PKG_NAME).tar.gz $(PKG_NAME).tgz

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

