# makefile for MOS library source code
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../../../../mos
include $(MODROOT)/mos.mk
##include depend.mk


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

FILES	= 

LIB_FILES = hw.xxx platform.xxx  

LIBRARY	= $(MODROOT)/lib/libmos.lib

TARGET	= 

HEADER  = *.h


#------------------------------------------------------------------------

INCLUDES 	= -I../common

LIBLIST		= -lmos

LIBS		= $(LIBLIST) $(MOD_LIBS) 

#------------------------------------------------------------------------
# override settings obtained from mos.mk

SYS	= c64

CC65_BASE = /scratch/bl12960/src/cc65-2.13.2

CC65_INC = $(CC65_BASE)/include
CA65_INC = $(CC65_BASE)/asminc

MOUS = $(CC65_BASE)/libsrc/$(SYS)*.mou
TGI  = $(CC65_BASE)/libsrc/$(SYS)*.tgi
CLIB = $(CC65_BASE)/libsrc/$(SYS).lib

MY_INC = --forget-inc-paths -I . -I $(CC65_INC) -I ../common
MY_ASM = --forget-inc-paths -I . -I $(CA65_INC)

MOD_ARFLAGS 	= a

#------------------------------------------------------------------------

OPTIMIZE 	= 

DEP_CFLAGS	= $(CFLAGS) $(MOD_CFLAGS) $(MOD_INCLUDES)

ALL_CFLAGS 	= $(CFLAGS) $(MOD_CFLAGS) $(MOD_INCLUDES) $(INCLUDES)

ALL_LDFLAGS	= $(LDFLAGS) $(MOD_LDFLAGS) $(MOD_LIB_PATHS) -L$(MODROOT)

ALL_ARFLAGS	= $(MOD_ARFLAGS)

OFILES	   = $(FILES:xxx=o)
SFILES	   = $(FILES:xxx=s)
CFILES	   = $(FILES:xxx=c)

LINTFILES  = $(FILES:xxx=lint)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_CFILES = $(LIB_FILES:.xxx=.c)


#
# make executables
#

default: all

#all exe : depend.mk $(LIB_OFILES) $(TARGET) $(TARGET2)
#all exe : $(LIB_OFILES) $(TARGET) $(TARGET2) strip1
all exe : $(LIB_OFILES) $(TARGET) $(TARGET2) 
	cp $(HEADER) $(MODROOT)/include
#	cp $(LIBRARY) $(MODROOT)/lib

strip1: $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=srec   -o $(TARGET).srec $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=binary -o $(TARGET).bin  $(TARGET)

$(TARGET): $(OFILES) $(LIBLIST)
	$(CC) $(ALL_LDFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

$(OFILES): %.o: %.s
	$(AS) $(basename $<).s

$(SFILES): %.s: %.c
	$(CC) $(MY_INC) -Oirs --codesize 500 -T -g -t $(SYS) $< 

$(LIB_OFILES): %.o: %.c *.h
	$(CC) $(MY_INC) -Oirs --codesize 500 -T -g -t $(SYS) $< 
	$(AS) $(basename $<).s
	$(AR) $(ALL_ARFLAGS) $(LIBRARY) $*.o


#	$(CC) $(MY_INC) -Oirs --codesize 500 -T -g -t $(SYS) $<
#	$(AS) $(basename $<).s


#------------------------------------------------------------------------

install: all
	$(CP) $(TARGET) $(INSTALL_DIR)
	
clean:
	$(RM) *.s *.o *% *~ *.bak depend.mk

realclean: clean
	$(RM) $(LIBRARY) $(TARGET) $(TARGET).exe $(TARGET2) $(TARGET2).exe
	$(RM) *.srec *.bin
	$(RM) *.gcov *.gcda *.gcno

depend:
	makedepend $(DEP_CPPFLAGS) $(CFILES)

depend.mk:
	$(CC) -MM $(DEP_CPPFLAGS) $(CFILES) > $@

lint: $(CFILES)
	$(LINT) -preproc $(MOD_INCLUDES) -I$(ENV_PREFIX)/usr/include $<

gcov:
	$(GCOV) platform.c
	$(GCOV) mos.c

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

