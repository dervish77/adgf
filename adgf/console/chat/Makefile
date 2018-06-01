# makefile for Chat example using ENet
#

#------------------------------------------------------------------------
# Include system make include files
#------------------------------------------------------------------------

MODROOT	= ../chat
include $(MODROOT)/module.mk
##include depend.mk


VERSION=0.1.0


#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

PLATFILES = 

FILES1	= $(PLATFILES) chat.xxx 

TARGET1	= enetchat

FILES2	= $(PLATFILES) chatd.xxx 

TARGET2	= enetchatd


LIB_FILES = 
LIBRARY	  =



#------------------------------------------------------------------------

INCLUDES 	=  

LIBLIST		= 

LIBS		= $(LIBLIST) $(MOD_LIBS)

#------------------------------------------------------------------------

# OPTIMIZE 	= 

DEP_CFLAGS	= $(CFLAGS) $(MOD_CFLAGS) $(MOD_INCLUDES)

ALL_CFLAGS 	= $(CFLAGS) $(MOD_CFLAGS) $(MOD_INCLUDES)

ALL_LDFLAGS	= $(LDFLAGS) $(MOD_LDFLAGS) $(MOD_LIB_PATHS) -L$(MODROOT)

ALL_ARFLAGS	= $(MOD_ARFLAGS)

OFILES1	   = $(FILES1:xxx=o)
CFILES1	   = $(FILES1:xxx=c)
LINTFILES1  = $(FILES1:xxx=lint)

OFILES2	   = $(FILES2:xxx=o)
CFILES2	   = $(FILES2:xxx=c)
LINTFILES2  = $(FILES2:xxx=lint)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_CFILES = $(LIB_FILES:.xxx=.c)


#
# make executables
#

default: all

#all exe : depend.mk $(LIB_OFILES) $(TARGET) 
#all exe : $(LIB_OFILES) $(TARGET) strip1
all exe : $(LIB_OFILES) $(TARGET1) $(TARGET2)

$(TARGET1): $(OFILES1) $(LIBLIST)
	$(CPP) $(ALL_LDFLAGS) -o $(TARGET1) $(OFILES1) $(LIBS)

$(OFILES1): %.o: %.c *.h
	$(CPP) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 


$(TARGET2): $(OFILES2) $(LIBLIST)
	$(CPP) $(ALL_LDFLAGS) -o $(TARGET2) $(OFILES2) $(LIBS)

$(OFILES2): %.o: %.c *.h
	$(CPP) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 


$(LIB_OFILES): %.o: %.cpp *.h
	$(CPP) $(OPTIMIZE) $(ALL_CFLAGS) -c $< 
	$(AR) $(ALL_ARFLAGS) $(LIBRARY) $*.o
#	$(RM) $*.o

file: $(TARGET)
	file $(TARGET)

#------------------------------------------------------------------------

test: server client

server:
	./enetchatd 7000 &

client:
	./enetchat brian localhost 7000

#------------------------------------------------------------------------

install: all
	$(CP) $(TARGET) $(INSTALL_BIN_DIR)

clean:
	$(RM) *.o *% *~ *.bak depend.mk

realclean: clean
	$(RM) $(LIBRARY) 
	$(RM) $(TARGET1) $(TARGET1).exe $(TARGET2) $(TARGET2).exe
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
	-@echo "Chat Version is $(VERSION)"
	-@echo " "

PKG_HOME = chat
PKG_NAME = chat-$(VERSION)

distro: distclean tar

tar: realclean
	cd .. ; \
	$(TAR) -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	$(GZIP) $(PKG_NAME).tar ; \
	$(MV) $(PKG_NAME).tar.gz $(PKG_NAME).tgz
	-@echo "Distribution package is ../$(PKG_NAME).tgz" 

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.

