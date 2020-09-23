#
#  makefile for Othello Game - othello
#
#

INSTALL_DIR = $(HOME)/bin

include $(HOME)/include/libsx_defs
#include ../libsx_defs


# ===========================================================================
# you shouldn't need to change anything below this line
#

COMMON_OBJS = main.o callback.o othello.o scan.o flip.o count.o drwlibsx.o

OBJS = $(COMMON_OBJS) stub.o

TARGET = othello

MOBJS = $(COMMON_OBJS) multi.o tcplib.o

MTARGET = mothello


#
# dependancies
#

default: $(TARGET)

all:	$(TARGET) install realclean

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

$(MTARGET) : $(MOBJS)
	$(CC) -o $@ $(MOBJS) $(SOCKLIBS)

main.o : main.c main.h callback.h othello.h libsx.h

callback.o : callback.c main.h othello.h libsx.h 

othello.o : othello.c main.h callback.h othello.h vecmath.h libsx.h

scan.o : scan.c main.h callback.h othello.h vecmath.h libsx.h

flip.o : flip.c main.h callback.h othello.h vecmath.h libsx.h

count.o : count.c main.h callback.h othello.h vecmath.h libsx.h

stub.o : stub.c main.h callback.h othello.h vecmath.h libsx.h

drwlibsx.o : drwlibsx.c main.h callback.h othello.h vecmath.h libsx.h

multi.o : multi.c multi.h tcplib.h main.h othello.h vecmath.h libsx.h

tcplib.o : tcplib.c tcplib.h
	$(CC) -O -c tcplib.c

#
# cleans and installs
#

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ *.osg core $(TARGET) $(MTARGET)

install:
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )


#
# make distribution file
#

VERSION = 1.0

OTHELLO_HOME = othello
OTHELLO_NAME = othello-$(VERSION)

TAR_FILES = 	\
	$(OTHELLO_HOME)/README		\
	$(OTHELLO_HOME)/COPYING		\
	$(OTHELLO_HOME)/REVISION	\
	$(OTHELLO_HOME)/*.h		\
	$(OTHELLO_HOME)/*.c		\
	$(OTHELLO_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(OTHELLO_NAME).tar $(TAR_FILES) ; \
	gzip $(OTHELLO_NAME).tar ; \
	mv $(OTHELLO_NAME).tar.gz othello.tgz
#	mv $(OTHELLO_NAME).tar.gz $(OTHELLO_HOME)
