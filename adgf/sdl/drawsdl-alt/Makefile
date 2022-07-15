# makefile for VidTest Demo program
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../drawsdl
include $(MODROOT)/module.mk
##include depend.mk


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

#PLATFILES = draw-dfb.xxx
#PLATFILES = draw-fb.xxx
PLATFILES = draw-sdl.xxx

FILES	= $(PLATFILES) main.xxx

TARGET	= drawsdl

#LIB_FILES = tbd.xxx
#LIBRARY	= libtbd.a



#------------------------------------------------------------------------

INCLUDES 	= 

#LIBLIST		= -ltbd
LIBLIST		= 

LIBS		= $(LIBLIST) $(MOD_LIBS) 

#------------------------------------------------------------------------

# OPTIMIZE 	= 

DEP_CFLAGS	= $(CFLAGS) $(MOD_CFLAGS) $(MOD_INCLUDES)

ALL_CFLAGS 	= $(CFLAGS) $(MOD_CFLAGS) $(MOD_INCLUDES)

ALL_LDFLAGS	= $(LDFLAGS) $(MOD_LDFLAGS) $(MOD_LIB_PATHS) -L$(MODROOT)

ALL_ARFLAGS	= $(MOD_ARFLAGS)

OFILES	   = $(FILES:xxx=o)
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

strip1: $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=srec   -o $(TARGET).srec $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=binary -o $(TARGET).bin  $(TARGET)

$(TARGET): $(OFILES) $(LIBLIST)
	$(CC) $(ALL_LDFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

$(OFILES): %.o: %.c draw-sdl.h 
	$(CC) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 

$(LIB_OFILES): %.o: %.c
	$(CC) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 
	$(AR) $(ALL_ARFLAGS) $(LIBRARY) $*.o
#	$(RM) $*.o

file: $(TARGET)
	file $(TARGET)

#------------------------------------------------------------------------

install: all
	$(CP) $(TARGET) $(INSTALL_BIN_DIR)

clean:
	$(RM) *.o *% *~ *.bak depend.mk

realclean: clean
	$(RM) $(LIBRARY) 
	$(RM) $(TARGET) $(TARGET).exe
	$(RM) *.srec *.bin config.h

distclean: realclean

depend:
	makedepend $(DEP_CPPFLAGS) $(CFILES)

depend.mk:
	$(CC) -MM $(DEP_CPPFLAGS) $(CFILES) > $@

lint: $(CFILES)
	$(LINT) -preproc $(MOD_INCLUDES) -I$(ENV_PREFIX)/usr/include $<

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

