#*
#*     Module Name:  sdltest.mk
#*
#*
#*	Make file definitions for the sdltest module 
#*	within VOLOPRE project.
#*
#*
#*/

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

#include ../../common.mk

PREFIX = 

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



