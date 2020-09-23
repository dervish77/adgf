# makefile for SicDacLoe (aka tic tac toe)
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../sicdacloe
include $(MODROOT)/module.mk
##include depend.mk


VERSION=0.3.9


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

#PLATFILES = draw-sdl.xxx draw-text.xxx
PLATFILES = 

FILES	= $(PLATFILES) game.xxx screens.xxx random.xxx main.xxx 

TARGET	= sicdacloe

LIB_FILES = draw-sdl.xxx
LIBRARY	= libdrawsdl.a



#------------------------------------------------------------------------

INCLUDES 	=  

LIBLIST		= -ldrawsdl

LIBS		= $(LIBLIST) $(MOD_LIBS)

#------------------------------------------------------------------------

# OPTIMIZE 	= 

DEP_CPPFLAGS	= $(CFLAGS) $(MOD_CPPFLAGS) $(MOD_INCLUDES)

ALL_CPPFLAGS 	= $(CFLAGS) $(MOD_CPPFLAGS) $(MOD_INCLUDES)

ALL_LDFLAGS	= $(LDFLAGS) $(MOD_LDFLAGS) $(MOD_LIB_PATHS) -L$(MODROOT)

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

#all exe : depend.mk $(LIB_OFILES) $(TARGET) 
#all exe : $(LIB_OFILES) $(TARGET) strip1
all exe : $(LIB_OFILES) $(TARGET) 
strip1: $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=srec   -o $(TARGET).srec $(TARGET)
	$(STRIP) -v -s --strip-unneeded --output-target=binary -o $(TARGET).bin  $(TARGET)

$(TARGET): $(OFILES) $(LIBLIST)
	$(CPP) $(ALL_LDFLAGS) -o $(TARGET) $(OFILES) $(LIBS)

$(OFILES): %.o: %.cpp *.h
	$(CPP) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 

$(LIB_OFILES): %.o: %.cpp *.h
	$(CPP) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 
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
	$(CPP) -MM $(DEP_CPPFLAGS) $(CFILES) > $@

lint: $(CFILES)
	$(LINT) -preproc $(MOD_INCLUDES) -I$(ENV_PREFIX)/usr/include $<

.PHONY : exe

#------------------------------------------------------------------------
# make distribution file
#

version:
	-@echo " "
	-@echo "SicDacLoe Version is $(VERSION)"
	-@echo " "

PKG_HOME = sicdacloe
PKG_NAME = sicdacloe-$(VERSION)

distro: distclean tar

tar: realclean
	cd .. ; \
	$(TAR) -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	$(GZIP) $(PKG_NAME).tar ; \
	$(MV) $(PKG_NAME).tar.gz $(PKG_NAME).tgz
	-@echo "Distribution package is ../$(PKG_NAME).tgz" 

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

