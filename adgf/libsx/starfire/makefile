#
#  makefile for StarFire Game - starfire
#
#

#INSTALL_DIR = $(HOME)/bin
INSTALL_DIR = /scratch/bl12960/bin

include $(HOME)/include/libsx_defs
#include ../libsx_defs


# ===========================================================================
# you shouldn't need to change anything below this line
#

OBJS = main.o callback.o starfire.o move.o anim.o icon.o drwlibsx.o

TARGET = starfire

VERSION = 0.3


#
# dependancies
#

default: $(TARGET)

all:	$(TARGET) install realclean

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

main.o : main.c main.h callback.h starfire.h icon.h libsx.h

callback.o : callback.c main.h callback.h starfire.h icon.h libsx.h 

starfire.o : starfire.c main.h callback.h starfire.h icon.h vecmath.h libsx.h
 
move.o : move.c main.h starfire.h icon.h vecmath.h libsx.h

anim.o : anim.c main.h starfire.h icon.h vecmath.h libsx.h

icon.o : icon.c main.h starfire.h icon.h vecmath.h libsx.h

drwlibsx.o : drwlibsx.c main.h starfire.h icon.h vecmath.h libsx.h


#
# cleans and installs
#

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ *.osg core $(TARGET)

install:
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )
	( cp icons/* $(INSTALL_DIR)/icons )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )


#
# make distribution file
#

STARFIRE_HOME = starfire
STARFIRE_NAME = starfire-$(VERSION)

TAR_FILES = 	\
	$(STARFIRE_HOME)/README		\
	$(STARFIRE_HOME)/COPYING		\
	$(STARFIRE_HOME)/REVISION	\
	$(STARFIRE_HOME)/icons/*.icn	\
	$(STARFIRE_HOME)/*.h		\
	$(STARFIRE_HOME)/*.c		\
	$(STARFIRE_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(STARFIRE_NAME).tar $(TAR_FILES) ; \
	gzip $(STARFIRE_NAME).tar ; \
	mv $(STARFIRE_NAME).tar.gz $(STARFIRE_HOME)
