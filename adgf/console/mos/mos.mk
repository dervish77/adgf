#*
#*     Module Name:  mos.mk
#*
#*
#*	Make file definitions for this project.
#*
#*
#*/

#------------------------------------------------------------------------
# Define targets based on 'PORT'
#------------------------------------------------------------------------

PORT ?= cygwin

ifeq ($(PORT), linux)
CPU              = x86
CROSS_COMPILE    = 
CROSS_TOOL       = 
CROSS_TOOL_PATH  = /usr
CROSS_OS_PATH    = /usr
TARGET_NAME      = x86-unknown-linux
ARCH             = x86
endif

ifeq ($(PORT), cygwin)
CPU              = x86
CROSS_COMPILE    = 
CROSS_TOOL       = 
CROSS_TOOL_PATH  = /usr
CROSS_OS_PATH    = /usr
TARGET_NAME      = x86-unknown-cygwin
ARCH             = x86
endif

ifeq ($(PORT), arduino)
CPU              = avr
CROSS_COMPILE    = 
CROSS_TOOL       = 
CROSS_TOOL_PATH  = /usr
CROSS_OS_PATH    = /usr
TARGET_NAME      = avr-unknown-linux
ARCH             = avr
endif

ifeq ($(PORT), arm)
CPU              = arm
CROSS_COMPILE    = arm-none-linux-gnueabi-
CROSS_TOOL       = arm-none-linux-gnueabi-
CROSS_TOOL_PATH  = /opt/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi
CROSS_OS_PATH    = /scratch/freescale/ltib/rootfs/usr
TARGET_NAME      = arm-none-linux
ARCH             = arm
endif

ifeq ($(PORT), avr)
CPU              = avr
CROSS_COMPILE    = 
CROSS_TOOL       = 
CROSS_TOOL_PATH  = /usr
CROSS_OS_PATH    = /usr
TARGET_NAME      = avr-unknown-linux
ARCH             = avr
endif

ifeq ($(PORT), c64)
CPU              = 6502
CROSS_COMPILE    = 
CROSS_TOOL       = 
CROSS_TOOL_PATH  = /cygdrive/c/Utils/cc65-snapshot-win32
CROSS_OS_PATH    = 
TARGET_NAME      = 6502-unknown-c64
ARCH             = 6502
endif

ifeq ($(PORT), ez80)
CPU              = z80
CROSS_COMPILE    = 
CROSS_TOOL       = 
CROSS_TOOL_PATH  = /usr
CROSS_OS_PATH    = /usr
TARGET_NAME      = z80-unknown-linux
ARCH             = z80
endif

ifeq ($(PORT), sh4)
CPU              = sh4
CROSS_COMPILE    = sh4-linux-
CROSS_TOOL       = sh4-linux-
CROSS_TOOL_PATH  = /opt/STM/STLinux-2.3/devkit/sh4
CROSS_OS_PATH    = /opt/STM/STLinux-2.3/devkit/sh4/target/usr
TARGET_NAME      = sh4-unknown-linux
ARCH             = sh4
endif

INSTALL_DIR = ../bin

#------------------------------------------------------------------------
# Build tool definitions
#------------------------------------------------------------------------

CROSS_BIN_PATH = $(CROSS_TOOL_PATH)/bin
CROSS_LIB_PATH = $(CROSS_OS_PATH)/lib
CROSS_INC_PATH = $(CROSS_OS_PATH)/include

CROSS_TOOL_CC  = $(CROSS_BIN_PATH)/$(CROSS_TOOL)gcc
CROSS_TOOL_CPP = $(CROSS_BIN_PATH)/$(CROSS_TOOL)g++

PREFIX		= $(CROSS_BIN_PATH)/$(CROSS_TOOL)

ifeq ($(PORT), c64)
CC		    = $(PREFIX)cl65
AS		    = $(PREFIX)ca65
LD		    = $(PREFIX)ld65
AR		    = $(PREFIX)ar65
STRIP       = 
else
CC		    = $(PREFIX)gcc
AS		    = $(PREFIX)as
LD		    = $(PREFIX)ld
AR		    = $(PREFIX)ar
STRIP       = $(PREFIX)strip
endif

CP          = cp
RM          = rm -f
MV          = mv
TAR	        = tar
GZIP		= gzip
LINT		= lint

GPROF		= gprof
KPROF		= kprof
GCOV		= gcov

VALGRIND	= valgrind
VG_CACHE	= --tool=callgrind
VG_MEM		= --tool=memcheck --leak-check=yes -v

GPROF_OPT	= -pg
GCOV_OPT	= -fprofile-arcs -ftest-coverage

DEBUG       = 
#DEBUG       = -g

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
EXTRA_INCLUDE	= 

MOD_INCLUDES	= -I. $(EXTRA_INCLUDE)


#------------------------------------------------------------------------
# Define local cflags
#------------------------------------------------------------------------
EXTRA_DEBUG 	= $(DEBUG) $(OPT)

ifeq ($(PORT), c64)
MOD_CFLAGS      = -t c64 $(EXTRA_DEBUG)
else
MOD_CFLAGS      = $(EXTRA_DEBUG)
endif

#MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -Wno-deprecated
MOD_CPPFLAGS 	= $(EXTRA_DEBUG) -fexceptions -lang-c++


#------------------------------------------------------------------------
# Define local library variables
#------------------------------------------------------------------------

#MOD_LDFLAGS 	= -static
MOD_LDFLAGS 	= $(OPT)

MOD_LIB_PATHS 	= 
MOD_LIBS        = 
ifeq ($(PORT), c64)
MOD_ARFLAGS 	= r
else
MOD_ARFLAGS 	= -rc
endif

#------------------------------------------------------------------------
# Define make command
#------------------------------------------------------------------------

MAKE = make --no-print-directory

