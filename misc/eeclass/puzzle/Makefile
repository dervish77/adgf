#*
#*     Module Name:  makefile
#*
#*
#*     Puzzle solving program from grad school.
#*
#*	"make all" to build all utilities
#*	
#*	"make test" to build and unit test all utilities
#*
#*
#*/

# set distribution name
DIST = puzzle

# set distribution version
VERSION = 3.0

# set files to compile
#FILES = gencube.xxx cube.xxx newcube.xxx  
FILES = gencube.xxx cube.xxx

TARGETS = $(FILES:.xxx=)

TARGETS2 = $(FILES:.xxx=.exe)

#PREFIX		= $(CROSS_COMPILE)
PREFIX		= 

CC			= $(PREFIX)gcc
AS			= $(PREFIX)as
LD			= $(PREFIX)ld
AR			= $(PREFIX)ar
STRIP		= $(PREFIX)strip

CP			= cp
MV			= mv
RM			= rm
TAR			= tar
GZIP		= gzip

LOCAL_GCC_PATH = $(CC)


# ========================================================================

default: all

all : $(TARGETS)

help:
	@-echo "make all        - builds executables"
	@-echo "make install    - builds and installs to ./bin"
	@-echo "make test       - builds, installs, and runs unit tests"

cube : cube.c
	$(LOCAL_GCC_PATH) -o $@ $<

gencube : gencube.c
	$(LOCAL_GCC_PATH) -o $@ $<

newcube : newcube.c
	$(LOCAL_GCC_PATH) -o $@ $<


# ========================================================================

install: all
	@-echo "Install - installing to ./bin"
	cp $(TARGETS) bin
	rm -f $(TARGETS)

# ========================================================================

clean:
	rm -f *% *~ *.bak src/*% src/*~ src/*.bak

realclean: clean
	rm -f $(TARGETS) $(TARGETS2) *.bin *.uu bin/*
	rm -f *.init *.scram *.solve *.log

distclean: realclean

# ========================================================================

#test: install testhdr testgencube testcube testnewcube
test: testhdr testgencube testcube testnewcube

testhdr:
	@-echo " "
	@-echo "Testing puzzle apps ..."
	@-echo " "

testgencube:
	@-echo "-- testing gencube ..."
	gencube 8 temp8.log
	gencube 16 temp16.log

testcube:
	@-echo "-- testing cube ..."

testnewcube:
	@-echo "-- testing newcube ..."


# ========================================================================

#------------------------------------------------------------------------
# Make distribution file
#------------------------------------------------------------------------

TAR_HOME = $(DIST)
TAR_NAME = $(DIST)-$(VERSION)

TAR_FILES = 	\
	$(TAR_HOME)/COPYING.txt		\
	$(TAR_HOME)/README.txt		\
	$(TAR_HOME)/REVISION.txt	\
	$(TAR_HOME)/Makefile		\
	$(TAR_HOME)/bin				\
	$(TAR_HOME)/man/*			\
	$(TAR_HOME)/src/*		

tar: distclean
	cd .. ; \
	$(TAR) -cvf $(TAR_NAME).tar $(TAR_FILES) ; \
	$(GZIP) $(TAR_NAME).tar ; \
	$(MV) $(TAR_NAME).tar.gz $(TAR_HOME)

# ========================================================================
# end of bintools makefile


