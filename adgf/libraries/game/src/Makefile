# makefile for LibGame game library
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../src
include $(MODROOT)/module.mk
##include depend.mk


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

FILES	= mymain.xxx main.xxx

LIB_FILES = animal.xxx cat.xxx dog.xxx zebra.xxx \
	  test.xxx boundstest.xxx inittest.xxx leaktest.xxx life.xxx 

LIBRARY	= libLibGame.a

TARGET	= unittest


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
all exe : $(LIB_OFILES) $(TARGET)
	$(CP) $(TARGET) ../bin
	$(CP) $(LIBRARY) ../lib

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
	$(TARGET) -h
	$(TARGET) -v

gcov-run: test-host
	$(GCOV) main.cpp
	$(GCOV) mymain.cpp
	$(GCOV) dynamic.cpp
	$(GCOV) test.cpp
	$(GCOV) boundstest.cpp
	$(GCOV) inittest.cpp
	$(GCOV) leaktest.cpp
	$(GCOV) animal.cpp
	$(GCOV) cat.cpp
	$(GCOV) dog.cpp

gcov: gcov-run
	-@echo "COVERAGE REPORT for $(TARGET)" > dyntest.gcov  
	cat main.cpp.gcov >> dyntest.gcov
	cat mymain.cpp.gcov >> dyntest.gcov
	cat dynamic.cpp.gcov >> dyntest.gcov
	cat test.cpp.gcov >> dyntest.gcov
	cat boundstest.cpp.gcov >> dyntest.gcov
	cat inittest.cpp.gcov >> dyntest.gcov
	cat leaktest.cpp.gcov >> dyntest.gcov
	cat animal.cpp.gcov >> dyntest.gcov
	cat cat.cpp.gcov >> dyntest.gcov
	cat dog.cpp.gcov >> dyntest.gcov
	-@echo "END REPORT for $(TARGET)" >> dyntest.gcov

#------------------------------------------------------------------------

install: all
	$(CP) $(TARGET) $(INSTALL_DIR)

clean:
	$(RM) *.o *% *~ *.bak depend.mk

realclean: clean
	$(RM) $(LIBRARY) $(TARGET) $(TARGET).exe 
	$(RM) *.gcov gmon.out *.gcno *.gcda *.perf callgrind.out.* *.log
	$(RM) ../bin/$(TARGET)
	$(RM) ../lib/$(LIBRARY)

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

