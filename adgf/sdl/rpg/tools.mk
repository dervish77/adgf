#*
#*     Module Name:  tools.mk
#*
#*
#*	Make file definitions for the life ui module 
#*	within life project.
#*
#*
#*/

include ./common.mk

#PREFIX		= 

#------------------------------------------------------------------------
# Define some extras
#------------------------------------------------------------------------

MOD_OUT_DIR	= .


#------------------------------------------------------------------------
# Define local includes
#------------------------------------------------------------------------
EXTRA_INCLUDE	= -I/usr/local/include 

MOD_INCLUDES	= -I. -I../include -I../src $(EXTRA_INCLUDE)


#------------------------------------------------------------------------
# Define local cflags
#------------------------------------------------------------------------
EXTRA_DEBUG 	= -W -Wall -ggdb -O2
#EXTRA_DEBUG 	= -g

MOD_CFLAGS 		= $(EXTRA_DEBUG)

MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -Wno-deprecated
#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -fexceptions -lang-c++


#------------------------------------------------------------------------
# Define local library variables
#------------------------------------------------------------------------

#MOD_LDFLAGS 	= -lang-c++ -static
#MOD_LDFLAGS 	= -static
#MOD_LDFLAGS 	= $(PROF_OPT)
MOD_LDFLAGS 	= 

MOD_LIB_PATHS 	= -L/usr/local/lib
MOD_LIBS 		= -lSDL
MOD_ARFLAGS 	= -rc



