# makefile for PI test program
#

CC=gcc

OBJECTS = pi.o  

TARGET = pi

LIBS	= -lm
CFLAGS  = -O



default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

pi.o : pi.c pi.h

clean:
	rm -f *.o *% *~ core $(TARGET)


#
# make distribution file
#

VERSION = 0.1

PKG_HOME = pi
PKG_NAME = pi-$(VERSION)

TAR_FILES = 	\
	$(PKG_HOME)/README	\
	$(PKG_HOME)/*.h		\
	$(PKG_HOME)/*.c		\
	$(PKG_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(PKG_NAME).tar $(TAR_FILES) ; \
	gzip $(PKG_NAME).tar ; \
	mv $(PKG_NAME).tar.gz $(PKG_HOME)
