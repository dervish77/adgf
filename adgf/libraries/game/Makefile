# makefile for life directory tree
#
# simply type 'make all' to make everything
#
# type 'make help' for help with targets
#
#


include ./common.mk

include ./timing.mk


VERSION=0.0.4


#------------------------------------------------------------------------
# absolute base path

BASE_DIR_ABSOLUTE = $(PWD)

ifeq ($(OS),Windows_NT)
BASE_DIR_ABSOLUTE = $(shell cygpath -m $(CURDIR))
endif

#------------------------------------------------------------------------
# platform models dirs

BOUML_BIN=bouml
XVFB_BIN=xvfb-run

MODEL_DIR=./model/libgame
MODEL=$(MODEL_DIR)/libgame.prj

#------------------------------------------------------------------------
# platform build dirs 

SRC_DIR=src

DEMO_DIR=demo

BUILDS_DIR=builds
HOST_BUILDS_DIR=$(BUILDS_DIR)/$(HOST_NAME)
TARGET_BUILDS_DIR=$(BUILDS_DIR)/$(TARGET_NAME)


#------------------------------------------------------------------------

#
# make all programs
#

default: help

all: 
	$(header)
	$(MAKE) buildall
	$(footer)

buildall: liball

#liball: model exe-host exe-target
#liball: model exe-host
liball: lib-host demo-host

# model: modelexport modelimport modelgen 

test:
	$(MAKE) lib-host  
	$(MAKE) -i lib-host-err

game: lib-host

demo: demo-host

machine:
	-@echo "machine is $(HOST_NAME)"

docs: doc

doc:
	firefox docs/index.html

#------------------------------------------------------------------------

ide: cb-ide-ui

cb-ide-ui:
	codeblocks ide/CB/LifeUi/LifeUi.cbp &

cb-ide-test:
	codeblocks ide/CB/LifeTest/LifeTest.cbp &

#------------------------------------------------------------------------
#
# help targets
#

help:
	-@echo "Top Level Targets:"
	-@echo "  make help        - prints help"
	-@echo "  make targets     - prints more targets help"
	-@echo " "
	-@echo "  make all         - builds everything for all targets"
	-@echo " "
	-@echo "  make game        - builds LibGame library only"
	-@echo "  make demo        - builds demo game only"
	-@echo " "
	-@echo "  make bouml       - invokes BOUML tool for platform model"
	-@echo "  make model       - generates platform code from BOUML models"
	-@echo " "
	-@echo "  make test        - executes selected unit test programs"
	-@echo " "
	-@echo "  make clean       - cleans up intermediate objects"
	-@echo "  make realclean   - removes final build products"
	-@echo "  make distclean   - pristine clean"
	-@echo " "
	-@echo "  make tar         - creates tar ball of entire tree"
	-@echo " "

targets:
	-@echo "More Targets:"
	-@echo " "
	-@echo "  make gcov        - runs gcov profiler"
	-@echo " "
	-@echo "  make gprof       - runs gprof profiler"
	-@echo " "


#------------------------------------------------------------------------
#
# build all UML models
#
# Notes:
# 1. "xvfb-run" is used to keep "bouml" tool from popping up a graphical window 
# during a command line build
#
.PHONY: model bouml
# The following targets just get passed down to the model directories' Makefiles
bouml:
	@$(BOUML_BIN) $(MODEL) &
	@sleep 1

model:
	-@echo "Generating code from UML model..."
	$(XVFB_BIN) $(BOUML_BIN) $(MODEL) -exec cpp_generator -exit
#	$(BOUML_BIN) $(MODEL) -exec cpp_generator -exit


#------------------------------------------------------------------------
#
# build all libaries and executables
#

lib-host: 
	$(header)
	cd $(SRC_DIR) && $(MAKE) PREFIX=/usr/bin/ all
	$(footer)

demo-host: 
	$(header)
	cd $(DEMO_DIR) && $(MAKE) PREFIX=/usr/bin/ all
	$(footer)


#------------------------------------------------------------------------
#
# creates missing dirs on the fly
#



#------------------------------------------------------------------------
# install targets
#

install:
	cp bin/game $(INSTALL_BIN_DIR)


#------------------------------------------------------------------------
# executes unit tests
#

test-host: 
	-@echo "Starting host tests..."
	src/life -b
	src/life -i
	src/life -l
	src/life -h
	src/life -v
	-@echo "Completed host tests."

test-host-err:
	-@echo "Starting host error tests..."
	src/life
	src/life -z
	-@echo "Completed host error tests."

test-target: 
	-@echo "Target tests cannot run on host"

#------------------------------------------------------------------------

gcov: host 
	cd $(SRC_DIR) && $(MAKE) gcov
	cp $(SRC_DIR)/life.gcov .

coverage: realclean gcov
	./coverage.sh life.gcov

#------------------------------------------------------------------------
# these targets must use local copy of binary in current directory

prof-test: host
	cp src/life .
	life -b
	life -b -d
	life -i
	life -i -d
	life -l
	life -l -d

gprof: prof-test
	$(GPROF) -b ./life

kprof: prof-test
	$(KPROF) -f ./life &

#------------------------------------------------------------------------
# remove all *.o and backup files

clean: clean-host

clean-host:
	-cd $(SRC_DIR) && $(MAKE) clean  
	-cd $(DEMO_DIR) && $(MAKE) clean  


#------------------------------------------------------------------------
# remove all *.o, executables, and library files

realclean:
	$(header)
	$(MAKE) clean
	-cd $(SRC_DIR) && $(MAKE) realclean  
	-cd $(DEMO_DIR) && $(MAKE) realclean  
	$(footer)	
	$(RM) buildtimes
	$(RM) .buildtime.*
	$(RM) include/*~
	$(RM) *~

#------------------------------------------------------------------------
# remove all build trees, output trees, and generated source code

distclean:
	$(header)
	-cd $(SRC_DIR) && $(MAKE) distclean  
	-cd $(DEMO_DIR) && $(MAKE) distclean  
#	cd models/platform && $(MAKE) $@
	$(RM) $(SRC_DIR)/*.h
	$(RM) $(SRC_DIR)/*.cpp
	$(RM) *.gcov gmon.out *.gcno *.gcda *.perf callgrind.out.* *.log *.dot
	$(footer)
	$(RM) buildtimes
	$(RM) .buildtime.*
	$(RM) include/*~
	$(RM) *~

#------------------------------------------------------------------------
# make distribution file
#

PKG_HOME = game
PKG_NAME = game-$(VERSION)

#tar: distclean
tar: realclean
	cd .. ; \
	$(TAR) -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	$(GZIP) $(PKG_NAME).tar ; \
	$(MV) $(PKG_NAME).tar.gz $(PKG_NAME).tgz
	-@echo "Distribution package is ../$(PKG_NAME).tgz" 

#------------------------------------------------------------------------
# EOF
