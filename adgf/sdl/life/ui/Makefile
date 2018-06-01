# makefile for MyLife demo program
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../ui
include $(MODROOT)/tools.mk
##include depend.mk


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

PLATFILES = draw-sdl.xxx

FILES	= $(PLATFILES) game.xxx screens.xxx random.xxx main.xxx

LIB_FILES = 

LIBRARY	= 

TARGET	= life


#------------------------------------------------------------------------

INCLUDES 	=  

LIBLIST		= 

LIBS		= $(LIBLIST) $(MOD_LIBS)

#------------------------------------------------------------------------

# OPTIMIZE 	= 

DEP_CPPFLAGS	= $(CFLAGS) $(MOD_CPPFLAGS) $(MOD_INCLUDES)

ALL_CPPFLAGS 	= $(CFLAGS) $(MOD_CPPFLAGS) $(MOD_INCLUDES)

ALL_LDFLAGS	= $(LDFLAGS) $(MOD_LDFLAGS) $(MOD_LIB_PATHS)

ALL_ARFLAGS	= $(MOD_ARFLAGS)

OFILES	   = $(FILES:xxx=o)
CFILES	   = $(FILES:xxx=cpp)
LINTFILES  = $(FILES:xxx=lint)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_CFILES = $(LIB_FILES:.xxx=.cpp)


#
# make executables
#

default: all

#all exe : depend.mk $(TARGET)
all exe : $(TARGET)

$(TARGET): $(OFILES) $(LIBLIST)
	$(CPP) $(ALL_LDFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

$(OFILES): %.o: %.cpp *.h
	$(CPP) $(OPTIMIZE) $(ALL_CPPFLAGS) -c $< 

$(LIB_OFILES): %.o: %.cpp *.h
	$(CPP) $(OPTIMIZE) $(ALL_CPPFLAGS) -c $< 
	$(AR) $(ALL_ARFLAGS) $(LIBRARY) $*.o
#	$(RM) $*.o

#------------------------------------------------------------------------

test-host: 



#------------------------------------------------------------------------

install: all
	$(CP) $(TARGET) $(INSTALL_DIR)

clean:
	$(RM) *.o *% *~ *.bak depend.mk

realclean: clean
	$(RM) $(TARGET) $(TARGET).exe 
	$(RM) *.gcov gmon.out *.gcno *.gcda *.perf callgrind.out.* *.log

distclean: realclean

depend:
	makedepend $(DEP_CPPFLAGS) $(CFILES)

depend.mk:
	$(CPP) -MM $(DEP_CPPFLAGS) $(CFILES) > $@

lint: $(CFILES)
	$(LINT) -preproc $(MOD_INCLUDES) -I$(ENV_PREFIX)/usr/include $<

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

