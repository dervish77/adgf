# makefile for PI test program
#

CC=gcc

# set to your chosen install location
INSTALL_DIR = $(HOME)/bin

# set to your chosen man page location
INSTALL_MAN_DIR = $(HOME)/man/man1

#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

OBJECTS = pi.o main.o 

TARGET = pi

LIBS	= -lm
CFLAGS  = -O

# =================================================================

default: all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

pi.o : pi.c pi.h

main.o : main.c pi.h

# =================================================================

clean:
	rm -f *.o *% *~ core $(TARGET)

realclean: clean

# =================================================================

test: all
	$(TARGET) 
	$(TARGET) -h
	$(TARGET) -d -i 10
	$(TARGET) -g -i 50000
	$(TARGET) -n -i 500

run: all
	$(TARGET) -n -i 500

# =================================================================

install: $(TARGET)
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )
#	( cp $(TARGET).man $(INSTALL_MAN_DIR)/$(TARGET).1 )

# =================================================================

#
# make distribution file
#

VERSION = 0.2

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

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.
