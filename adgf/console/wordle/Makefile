# makefile for Wordle - word guessing game
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

OBJECTS = words.o game.o main.o

TARGET = wordle

LIBS	= -lm
#CFLAGS  = -O
CFLAGS  = -g

DISTVER = 0.3

# =================================================================

LUA = lua

SCRIPT = genwords.lua

# =================================================================

#
# make executables
#

default: $(TARGET)

all: $(TARGET) install realclean

$(TARGET): wordlist $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

words.o : words.c words.h

game.o : game.c game.h words.h

main.o : main.c game.h


# =================================================================

NPP = /cygdrive/c/Utils/Notepad++/notepad++.exe

ide: ide-npp

ide-atom:
	atom . &

ide-cb:
	codeblocks $(TARGET).cbp &

ide-vsc:
	code -a . &
	
ide-npp:
	$(NPP) Makefile words.h words.c game.h game.c main.c &

# =================================================================

wordlist: 
	$(LUA) $(SCRIPT) words.txt words.c

testlua:
	$(LUA) $(SCRIPT) test.txt test2.c
	diff test.c test2.c
	rm -f test2.c

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
	$(TARGET) -s

# =================================================================

install: $(TARGET)
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )
	( cp $(TARGET).man $(INSTALL_MAN_DIR)/$(TARGET).1 )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )
	( rm -f $(INSTALL_MAN_DIR)/$(TARGET).1 )

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
	-@echo "$(TARGET) version is $(DISTVER)"

# =================================================================

# remove all *.o and backup files

clean:
	rm -f *.o *% *~

# remove all *.o, executables, and library files

realclean:
	rm -rf *.o *% *~ core $(TARGET) *.depend

distclean: realclean

# =================================================================

#
# make distribution file
#

distro: distclean archive version

PKG_HOME = $(TARGET)
PKG_NAME = $(TARGET)-$(DISTVER)

tar: realclean archive version

archive:
	cd .. ; \
	tar -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	gzip $(PKG_NAME).tar ; \
	mv $(PKG_NAME).tar.gz $(PKG_NAME).tgz

.PHONY : exe

#------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- make depend depends on it.
