# makefile for elfld program

# pick your favorite compiler
CC=gcc

# set to your chosen install location
INSTALL_DIR = $(HOME)/bin

#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

OBJECTS = elfld.o main.o  

TARGET = elfld

LIBS	= 
CFLAGS  = -O

default: $(TARGET)

all: $(TARGET) install realclean

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

main.o: main.c
	gcc -c -I. main.c -o main.o

elfld.o: elfld.c
	gcc -c -I. elfld.c -o elfld.o

clean:
	rm -f *.o *% *~

realclean: clean
	rm -f *.o *% *~ core $(TARGET) 

install:
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )

#
# make distribution file
#

ELFLD_HOME = $(TARGET)src
ELFLD_NAME = $(TARGET)

TAR_FILES = 	\
	$(ELFLD_HOME)/README		\
	$(ELFLD_HOME)/Makefile		\
	$(ELFLD_HOME)/*.h		\
	$(ELFLD_HOME)/*.c		\
	$(ELFLD_HOME)/diag24.elf

tar:
	cd .. ; \
	tar -cvf $(ELFLD_NAME).tar $(TAR_FILES) ; \
	gzip $(ELFLD_NAME).tar ; \
	mv $(ELFLD_NAME).tar.gz $(ELFLD_HOME)
