#*
#*     Module Name:  tools.mk
#*
#*
#*	Make file definitions for the life library module 
#*	within life project.
#*
#*
#*/

include ../common.mk

#PREFIX		= 

#------------------------------------------------------------------------
# Define some extras
#------------------------------------------------------------------------

MOD_OUT_DIR	= .


#------------------------------------------------------------------------
# Define local includes
#------------------------------------------------------------------------
EXTRA_INCLUDE	= 

MOD_INCLUDES	= -I. -I../include $(EXTRA_INCLUDE)


#------------------------------------------------------------------------
# Define local cflags
#------------------------------------------------------------------------
#EXTRA_DEBUG 	= 
EXTRA_DEBUG 	= -g $(PROF_OPT)

MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -Wno-deprecated
#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -fexceptions -lang-c++


#------------------------------------------------------------------------
# Define local library variables
#------------------------------------------------------------------------

#MOD_LDFLAGS 	= -lang-c++ -static
#MOD_LDFLAGS 	= -static
MOD_LDFLAGS 	= $(PROF_OPT)

MOD_LIB_PATHS 	= -L.
MOD_LIBS 		= -lLibGame
MOD_ARFLAGS 	= -rc



