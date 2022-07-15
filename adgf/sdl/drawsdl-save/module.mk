#*
#*     Module Name:  module.mk
#*
#*
#*	Make file definitions for the this module.
#*
#*
#*/

# set to "yes" to enable text support
HAS_TEXT = yes

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

PREFIX = 

#------------------------------------------------------------------------
# Define some tools
#------------------------------------------------------------------------

CPP = g++
AR  = ar

STRIP = strip
LINT  = lint

TAR  = tar
GZIP = gzip

CP = cp
MV = mv
RM = rm -f


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
EXTRA_DEBUG 	= -W -Wall -ggdb -O2
#EXTRA_DEBUG 	= -g

EXTRA_DEFINES   = 
ifeq ($(HAS_TEXT), yes)
EXTRA_DEFINES   = -DHAS_TEXT
endif

MOD_CFLAGS 		= $(EXTRA_DEBUG) $(EXTRA_DEFINES)

MOD_CPPFLAGS 	= $(EXTRA_DEBUG) $(EXTRA_DEFINES) -Wno-deprecated
#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) $(EXTRA_DEFINES) -fexceptions -lang-c++


#------------------------------------------------------------------------
# Define local library variables
#------------------------------------------------------------------------

#MOD_LDFLAGS 	= -lang-c++ -static
#MOD_LDFLAGS 	= -static
MOD_LDFLAGS 	= 

MOD_LIB_PATHS 	= -L/usr/local/lib

MOD_LIBS 		= -lSDL
ifeq ($(HAS_TEXT), yes)
MOD_LIBS 		= -lSDL -lSDL_ttf
endif

MOD_ARFLAGS 	= -rc



