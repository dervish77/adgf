# makefile for kata - programming exercises
#
# simply type 'make all' to make everything
#
# type 'make help' for help with targets
#
#

# pick your favorite compiler
CC=gcc

# set to your chosen install location
INSTALL_DIR = $(HOME)/bin

# set to your chosen man page location
INSTALL_MAN_DIR = $(HOME)/man/man1

#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

OBJECTS = kata.o main.o

TARGET = kata

LIBS	= -lm
#CFLAGS  = -O
CFLAGS  = -g

DISTVER = 0.1

# =================================================================

#
# make executables
#

default: $(TARGET)

all: $(TARGET) install realclean

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

file.o : kata.c kata.h

main.o : main.c kata.h


# =================================================================

ide: ide-cb

ide-cb:
	codeblocks $(TARGET).cbp &

# =================================================================

run: default
		$(TARGET)

# =================================================================

test: default
	-@echo "-------------"
	$(TARGET) -v
	-@echo "-------------"
	$(TARGET) -h
	-@echo "-------------"
	$(TARGET)
	-@echo "-------------"

# =================================================================

help:
	-@echo "Top Level Targets:"
	-@echo "  make help              - prints help"
	-@echo " "
	-@echo "  make                   - builds everything default"
	-@echo "  make all               - builds everything and installs"
	-@echo "  make install           - copies to INSTALL_DIR tree"
	-@echo "  make test              - builds and runs unit tests"
	-@echo " "
	-@echo "  make ide               - launch ide project"
	-@echo " "
	-@echo "  make clean             - cleans up all packages"
	-@echo "  make realclean         - pristine clean"
	-@echo " "
	-@echo "  make distro            - cleans then builds distro"
	-@echo "  make tar               - creates tar ball of entire tree"
	-@echo " "

version:
	-@echo "Kata Version is $(DISTVER)"

# remove all *.o and backup files

clean:
	rm -f *.o *% *~

# remove all *.o, executables, and library files

realclean:
	rm -rf *.o *% *~ core $(TARGET) bin obj *.depend

distclean: realclean


#
# make install
#

install:
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )
	( cp $(TARGET).man $(INSTALL_MAN_DIR)/$(TARGET).1 )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )
	( rm -f $(INSTALL_MAN_DIR)/$(TARGET).1 )


#
# make distribution file
#

distro: distclean archive version

PKG_HOME = kata
PKG_NAME = kata-$(DISTVER)

tar: realclean archive version

archive:
	cd .. ; \
	tar -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	gzip $(PKG_NAME).tar ; \
	mv $(PKG_NAME).tar.gz $(PKG_NAME).tgz

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.
