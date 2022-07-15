#
#  makefile for 8085 Emulator - emu85
#
#

INSTALL_DIR = $(HOME)/bin

include $(HOME)/include/libsx_defs
#include ../libsx_defs


# ===========================================================================
# you shouldn't need to change anything below this line
#

OBJS = main.o callback.o emu.o drwlibsx.o

TARGET = emu


#
# dependancies
#

default: $(TARGET)

all:	$(TARGET) install realclean

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

main.o : main.c main.h callback.h emu.h libsx.h

callback.o : callback.c main.h callback.h emu.h libsx.h 

emu.o : emu.c main.h callback.h emu.h vecmath.h libsx.h
 
drwlibsx.o : drwlibsx.c main.h emu.h vecmath.h libsx.h


#
# cleans and installs
#

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ *.osg core $(TARGET)

install:
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )


#
# make distribution file
#

VERSION = 0.1

EMU_HOME = emu85
EMU_NAME = emu85-$(VERSION)

TAR_FILES = 	\
	$(EMU_HOME)/README		\
	$(EMU_HOME)/COPYING		\
	$(EMU_HOME)/REVISION	\
	$(EMU_HOME)/*.h		\
	$(EMU_HOME)/*.c		\
	$(EMU_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(EMU_NAME).tar $(TAR_FILES) ; \
	gzip $(EMU_NAME).tar ; \
	mv $(EMU_NAME).tar.gz $(EMU_HOME) ; \
	cd $(EMU_HOME) ; \
	cp $(EMU_NAME).tar.gz ../$(EMU_HOME).tgz
