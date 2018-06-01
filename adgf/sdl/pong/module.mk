#*
#*     Module Name:  module.mk
#*
#*
#*	Make file definitions.
#*
#*
#*/

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

#include ../../common.mk

PREFIX = 

#------------------------------------------------------------------------
# Define some tools
#------------------------------------------------------------------------

CC = gcc
AR = ar

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
#EXTRA_INCLUDE	= -I../../packages/build-$(CPU)/include
EXTRA_INCLUDE	= 

MOD_INCLUDES	= -I. $(EXTRA_INCLUDE)


#------------------------------------------------------------------------
# Define local cflags
#------------------------------------------------------------------------
EXTRA_DEBUG 	= -W -Wall -ggdb -O2
#EXTRA_DEBUG 	= -g

MOD_CFLAGS 		= $(EXTRA_DEBUG)

#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -Wno-deprecated
MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -fexceptions -lang-c++


#------------------------------------------------------------------------
# Define local library variables
#------------------------------------------------------------------------

#MOD_LDFLAGS 	= -static
MOD_LDFLAGS 	= 

#MOD_LIB_PATHS 	= -L../../packages/build-$(CPU)/lib
MOD_LIB_PATHS 	= -L/usr/local/lib
MOD_LIBS 		= -lSDL
MOD_ARFLAGS 	= -rc



