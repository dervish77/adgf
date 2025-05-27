#
#  makefile for Survival Game - survival
#
#

INSTALL_DIR = $(HOME)/bin

include $(HOME)/include/libsx_defs
#include ../libsx_defs


# ===========================================================================
# you shouldn't need to change anything below this line
#

OBJS = main.o callback.o survival.o move.o icon.o drwlibsx.o

TARGET = survival


#
# dependancies
#

default: $(TARGET)

all:	$(TARGET) install realclean

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

main.o : main.c main.h callback.h survival.h icon.h libsx.h

callback.o : callback.c main.h callback.h survival.h icon.h libsx.h 

survival.o : survival.c main.h callback.h survival.h icon.h vecmath.h libsx.h
 
move.o : move.c main.h survival.h icon.h vecmath.h libsx.h

icon.o : icon.c main.h survival.h icon.h vecmath.h libsx.h

drwlibsx.o : drwlibsx.c main.h survival.h icon.h vecmath.h libsx.h


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

SURVIVAL_HOME = survival
SURVIVAL_NAME = survival-$(VERSION)

TAR_FILES = 	\
	$(SURVIVAL_HOME)/README		\
	$(SURVIVAL_HOME)/COPYING		\
	$(SURVIVAL_HOME)/REVISION	\
	$(SURVIVAL_HOME)/icons/*.icn	\
	$(SURVIVAL_HOME)/*.h		\
	$(SURVIVAL_HOME)/*.c		\
	$(SURVIVAL_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(SURVIVAL_NAME).tar $(TAR_FILES) ; \
	gzip $(SURVIVAL_NAME).tar ; \
	mv $(SURVIVAL_NAME).tar.gz $(SURVIVAL_HOME)
