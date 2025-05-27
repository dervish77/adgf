#
#  makefile for Pong and NetPong Game 
#
#

INSTALL_DIR = $(HOME)/bin

include $(HOME)/include/libsx_defs
#include ../libsx_defs


# ===========================================================================
# you shouldn't need to change anything below this line
#

COMMON_OBJS = main.o callback.o pong.o drwlibsx.o

OBJS = $(COMMON_OBJS) stub.o

TARGET = pong

MOBJS = $(COMMON_OBJS) multi.o tcplib.o

MTARGET = netpong


#
# dependancies
#

default: $(TARGET)

all:	$(TARGET) install realclean

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

$(MTARGET) : $(MOBJS)
	$(CC) -o $@ $(MOBJS) $(SOCKLIBS)

main.o : main.c main.h callback.h pong.h libsx.h

callback.o : callback.c main.h pong.h libsx.h 

pong.o : pong.c main.h callback.h pong.h vecmath.h libsx.h

stub.o : stub.c main.h callback.h pong.h vecmath.h libsx.h

drwlibsx.o : drwlibsx.c main.h callback.h pong.h vecmath.h libsx.h

multi.o : multi.c multi.h tcplib.h main.h pong.h vecmath.h libsx.h

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

VERSION = 0.1

PONG_HOME = pong
PONG_NAME = pong-$(VERSION)

TAR_FILES = 	\
	$(PONG_HOME)/README		\
	$(PONG_HOME)/COPYING		\
	$(PONG_HOME)/REVISION		\
	$(PONG_HOME)/*.h		\
	$(PONG_HOME)/*.c		\
	$(PONG_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(PONG_NAME).tar $(TAR_FILES) ; \
	gzip $(PONG_NAME).tar ; \
	mv $(PONG_NAME).tar.gz pong.tgz
#	mv $(PONG_NAME).tar.gz $(PONG_HOME)
