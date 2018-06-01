# makefile for MOS test application
#
# simple client/server app using two MOS tasks
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../../mos
include $(MODROOT)/mos.mk
##include depend.mk


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

FILES	= apptasks.xxx appmain.xxx

LIB_FILES = 

LIBRARY	= libmos.a

TARGET	= mosapp


#------------------------------------------------------------------------

INCLUDES 	= -I../include

LIBLIST		= -lmos

LIBS		= $(LIBLIST) $(MOD_LIBS)

#------------------------------------------------------------------------

OPTIMIZE 	=  

DEP_CFLAGS	= $(CFLAGS) $(MOD_CFLAGS) $(INCLUDES) $(MOD_INCLUDES)

ALL_CFLAGS 	= $(CFLAGS) $(MOD_CFLAGS) $(INCLUDES) $(MOD_INCLUDES)

ALL_LDFLAGS	= $(LDFLAGS) $(MOD_LDFLAGS) $(MOD_LIB_PATHS) -L../lib

ALL_ARFLAGS	= $(MOD_ARFLAGS)

OFILES	   = $(FILES:xxx=o)
CFILES	   = $(FILES:xxx=c)

OFILES2	   = $(FILES2:xxx=o)
CFILES2	   = $(FILES2:xxx=c)

LINTFILES  = $(FILES:xxx=lint)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_CFILES = $(LIB_FILES:.xxx=.c)


#
# make executables
#

default: all

#all exe : depend.mk $(LIB_OFILES) $(TARGET) $(TARGET2)
#all exe : $(LIB_OFILES) $(TARGET) $(TARGET2) strip1
all exe : $(LIB_OFILES) $(TARGET) 

strip1: $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=srec   -o $(TARGET).srec $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=binary -o $(TARGET).bin  $(TARGET)

$(TARGET): $(OFILES) ../lib/$(LIBRARY)
	$(CC) $(ALL_LDFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

$(OFILES): %.o: %.c *.h
	$(CC) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 

$(LIB_OFILES): %.o: %.c
	$(CC) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 
	$(AR) $(ALL_ARFLAGS) $(LIBRARY) $*.o
#	$(RM) $*.o

#------------------------------------------------------------------------

install: all
	$(CP) $(TARGET) $(INSTALL_DIR)
	
clean:
	$(RM) *.o *% *~ *.bak depend.mk

realclean: clean
	$(RM) $(LIBRARY) $(TARGET) $(TARGET).exe $(TARGET2) $(TARGET2).exe
	$(RM) *.srec *.bin
	$(RM) *.gcov *.gcda *.gcno gmon.out

depend:
	makedepend $(DEP_CPPFLAGS) $(CFILES)

depend.mk:
	$(CC) -MM $(DEP_CPPFLAGS) $(CFILES) > $@

lint: $(CFILES)
	$(LINT) -preproc $(MOD_INCLUDES) -I$(ENV_PREFIX)/usr/include $<

gcov:
	$(GCOV) apptasks.c
	$(GCOV) appmain.c

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

