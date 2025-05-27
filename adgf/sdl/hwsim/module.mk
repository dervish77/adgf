#*
#*     Module Name:  module.mk
#*
#*
#*	Make file definitions for the this module.
#*
#*
#*/


#------------------------------------------------------------------------
# Define targets based on 'PORT'
#------------------------------------------------------------------------

PORT ?= linux

ifeq ($(PORT), linux)
HAS_TEXT = yes
PREFIX = /usr/bin/
endif

ifeq ($(PORT), cygwin)
HAS_TEXT = yes
PREFIX = /usr/bin/
endif

INSTALL_DIR = ../bin

#------------------------------------------------------------------------
# Define some tools
#------------------------------------------------------------------------

CPP         = $(PREFIX)g++
AR          = $(PREFIX)ar
AS		    = $(PREFIX)as
LD		    = $(PREFIX)ld
AR		    = $(PREFIX)ar
STRIP       = $(PREFIX)strip

CP          = cp
RM          = rm -f
MV          = mv
TAR	        = tar
GZIP		= gzip
LINT		= lint

GPROF		= gprof
KPROF		= kprof
#GCOV		= gcov -l -c
GCOV		= gcov

VALGRIND	= valgrind
VG_CACHE	= --tool=callgrind
VG_MEM		= --tool=memcheck --leak-check=yes -v

GPROF_OPT	= -pg

#GCOV_OPT	= -fprofile-arcs -ftest-coverage
GCOV_OPT	= --coverage

OPT         =
#OPT         = $(GPROF_OPT)
#OPT         = $(GCOV_OPT)
#OPT         = $(GPROF_OPT) $(GCOV_OPT)

#------------------------------------------------------------------------
# Define some extras
#------------------------------------------------------------------------

MOD_OUT_DIR	= .


#------------------------------------------------------------------------
# Define local includes
#------------------------------------------------------------------------
EXTRA_INCLUDE	= -I/usr/local/include 

MOD_INCLUDES	= -I.  $(EXTRA_INCLUDE)


#------------------------------------------------------------------------
# Define local cflags
#------------------------------------------------------------------------
#EXTRA_DEBUG 	= -W -Wall -ggdb -O2 $(OPT)
EXTRA_DEBUG 	= -g $(OPT)
#EXTRA_DEBUG 	= $(OPT)

EXTRA_DEFINES   = 
ifeq ($(HAS_TEXT), yes)
EXTRA_DEFINES   += -DHAS_TEXT
endif

MOD_CFLAGS 		= $(EXTRA_DEBUG) $(EXTRA_DEFINES)

MOD_CPPFLAGS 	= $(EXTRA_DEBUG) $(EXTRA_DEFINES)
#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) $(EXTRA_DEFINES) -Wno-deprecated
#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) $(EXTRA_DEFINES) -fexceptions -lang-c++


#------------------------------------------------------------------------
# Define local library variables
#------------------------------------------------------------------------

#MOD_LDFLAGS 	= -lang-c++ -static
#MOD_LDFLAGS 	= -static
MOD_LDFLAGS 	= $(OPT)
#MOD_LDFLAGS 	= 

MOD_LIB_PATHS 	= -L/usr/local/lib

MOD_LIBS 		= -lSDL
ifeq ($(HAS_TEXT), yes)
MOD_LIBS 		+= -lSDL_ttf
endif

MOD_ARFLAGS 	= -rc



