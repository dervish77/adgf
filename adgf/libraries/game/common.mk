#*
#*     Module Name:  common.mk
#*
#*
#*	Make file definitions for the "common" tools within this project.
#*
#*
#*/


#------------------------------------------------------------------------
# Define some path variables
#
# Your environment must define the following:
#
#   CROSS_COMPILE     
#   CROSS_PATH        
#   INSTALL_DIR       example "/scratch/install"
# 
# or set them here.
#
#------------------------------------------------------------------------

CROSS_COMPILE = 

# temp set this here
CROSS_PATH = 

CROSS_BIN_PATH = $(CROSS_PATH)/bin
CROSS_INC_PATH = $(CROSS_PATH)/target/usr/include
CROSS_LIB_PATH = $(CROSS_PATH)/target/usr/lib

CROSS_TOOL_CC  = $(CROSS_BIN_PATH)/$(CROSS_COMPILE)gcc
CROSS_TOOL_CPP = $(CROSS_BIN_PATH)/$(CROSS_COMPILE)g++


#------------------------------------------------------------------------
# Define path vars used by CMake based build system (see Makefile)
#------------------------------------------------------------------------

HOST_BIN_PATH = /usr/bin
HOST_INC_PATH = /usr/include
HOST_LIB_PATH = /usr/lib

TARGET_PATH = $(CROSS_PATH)/target/usr
TARGET_INC_PATH = $(TARGET_PATH)/include
TARGET_LIB_PATH = $(TARGET_PATH)/lib

#------------------------------------------------------------------------
# Define target vars used by CMake based build system (see Makefile)
#------------------------------------------------------------------------

# use uname's machine name for HOST_NAME, this allows cluster builds to work 
HW_PLAT_NAME := $(shell uname -m)
#HW_PLAT_NAME = i386

HOST_NAME=$(HW_PLAT_NAME)
TARGET_NAME=

#------------------------------------------------------------------------
# Define install paths (for host installs to NFS exported root fs tree)
#------------------------------------------------------------------------

INSTALL_BIN_DIR = $(INSTALL_DIR)/bin
INSTALL_ETC_DIR = $(INSTALL_DIR)/etc
INSTALL_LIB_DIR = $(INSTALL_DIR)/lib
INSTALL_SRC_DIR = $(INSTALL_DIR)/src


#------------------------------------------------------------------------
# Define cross target platform
#------------------------------------------------------------------------

CPU	= 


#------------------------------------------------------------------------
# Build tool definitions
#------------------------------------------------------------------------

#PREFIX		= $(CROSS_COMPILE)
#PREFIX		= /usr/bin/ 
PREFIX		= 

CC			= $(PREFIX)gcc
CPP			= $(PREFIX)g++
AS			= $(PREFIX)as
LD			= $(PREFIX)ld
AR			= $(PREFIX)ar
STRIP		= $(PREFIX)strip

CD			= cd
CP			= cp
RM			= rm -rf
MKDIR		= mkdir
MV			= mv
TAR			= tar
GZIP		= gzip
LINT		= lint

#------------------------------------------------------------------------
# Profiling tool definitions
#------------------------------------------------------------------------

GPROF		= gprof
KPROF		= /opt/kde3/bin/kprof
GCOV		= gcov

GPROF_OPT	= -pg
GCOV_OPT	= -fprofile-arcs -ftest-coverage

PROF_OPT	=
#PROF_OPT	= $(GPROF_OPT)
#PROF_OPT	= $(GCOV_OPT)
#PROF_OPT	= $(GPROF_OPT) $(GCOV_OPT)

#------------------------------------------------------------------------
# Build tool definitions
#------------------------------------------------------------------------

LOCAL_CC	= gcc
LOCAL_CPP	= g++
LOCAL_AS	= as
LOCAL_LD	= ld
LOCAL_AR	= ar


#
# EOF
