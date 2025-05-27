#
# makefile for TCP MSGDEMO client/server programs
#
#


# modify for install directory
INSTALL_DIR = $(HOME)/bin

# pick your favorite compiler
#CC = cc
CC = gcc

# pick which LIBS is appropriate
LIBS_IRIX    =  
LIBS_SOLARIS = -lsocket -lnsl
LIBS_LINUX   = -lnsl

#LIBS = $(LIBS_IRIX)
#LIBS = $(LIBS_SOLARIS)
LIBS = $(LIBS_LINUX)

TH_LIBS = $(LIBS) -lpthread


# ===========================================================================
# you shouldn't need to change anything below this line
#

OBJECTS1 = msg.o common.o tcplib.o  	# MSG client

OBJECTS2 = msgd.o common.o tcplib.o  	# MSG server - using fork

OBJECTS3 = thmsgd.o common.o tcplib.o  	# MSG server - using pthreads

OBJECTS4 = game.o common.o tcplib.o	# GAME client

OBJECTS5 = gamed.o common.o tcplib.o	# GAME server - using pthreads

TARGET1 = msg 
TARGET2 = msgd
TARGET3 = thmsgd
TARGET4 = game
TARGET5 = gamed

CFLAGS  = -O


#
# dependancies
#

all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

$(TARGET1): $(OBJECTS1)
	$(CC) -o $@ $(OBJECTS1) $(LIBS)

$(TARGET2): $(OBJECTS2)
	$(CC) -o $@ $(OBJECTS2) $(LIBS)

$(TARGET3): $(OBJECTS3)
	$(CC) -o $@ $(OBJECTS3) $(TH_LIBS)

$(TARGET4): $(OBJECTS4)
	$(CC) -o $@ $(OBJECTS4) $(LIBS)

$(TARGET5): $(OBJECTS5)
	$(CC) -o $@ $(OBJECTS5) $(TH_LIBS)


msg.o : msg.c msg.h tcplib.h

msgd.o : msgd.c msg.h tcplib.h

thmsgd.o : thmsgd.c msg.h tcplib.h

game.o : game.c msg.h tcplib.h

gamed.o : gamed.c msg.h tcplib.h

common.o : common.c msg.h tcplib.h

tcplib.o : tcplib.c tcplib.h


#
# cleans and installs
#

clean:
	rm -f *.o *% *~

realclean: clean
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)

install:
	( cp $(TARGET1) $(INSTALL_DIR)/$(TARGET1) )
	( cp $(TARGET2) $(INSTALL_DIR)/$(TARGET2) )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET1) )
	( rm -f $(INSTALL_DIR)/$(TARGET2) )


#
# make distribution file
#

VERSION = 0.1

MSG_HOME = msgdemo
MSG_NAME = msgdemo-$(VERSION)

TAR_FILES = 	\
	$(MSG_HOME)/README	\
	$(MSG_HOME)/COPYING	\
	$(MSG_HOME)/REVISION	\
	$(MSG_HOME)/*.h		\
	$(MSG_HOME)/*.c		\
	$(MSG_HOME)/makefile

tar:
	@cd .. ; \
	tar -cvf $(MSG_NAME).tar $(TAR_FILES) ; \
	gzip $(MSG_NAME).tar ; \
	mv $(MSG_NAME).tar.gz msgdemo.tgz
#	mv $(MSG_NAME).tar.gz $(MSG_HOME)

