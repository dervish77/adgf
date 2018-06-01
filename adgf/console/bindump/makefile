# makefile for bindump program

# pick your favorite compiler
CC=gcc

# set to your chosen install location
INSTALL_DIR = $(HOME)/bin

# set to your chosen man page location
INSTALL_MAN_DIR = $(HOME)/man/man1

#
# --------------------------------------------------------------------
# you shouldn't need to change anything below this line

VER = 0.9

OBJECTS = bindump.o  

TARGET = bindump

LIBS	= -lm
CFLAGS  = -O

default: $(TARGET)

all: $(TARGET) install realclean

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(TARGET).o : $(TARGET).c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGET) $(TARGET).exe

install:
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )
	( cp $(TARGET).man $(INSTALL_MAN_DIR)/$(TARGET).1 )

uninstall:
	( rm -f $(INSTALL_DIR)/$(TARGET) )
	( rm -f $(INSTALL_MAN_DIR)/$(TARGET).1 )


#
# make distribution file
#

BINDUMP_HOME = $(TARGET)
BINDUMP_NAME = $(TARGET)-$(VER)

TAR_FILES = 	\
	$(BINDUMP_HOME)/README		\
	$(BINDUMP_HOME)/COPYING		\
	$(BINDUMP_HOME)/REVISION	\
	$(BINDUMP_HOME)/makefile	\
	$(BINDUMP_HOME)/$(TARGET).man	\
	$(BINDUMP_HOME)/$(TARGET).c

tar:
	cd .. ; \
	tar -cvf $(BINDUMP_NAME).tar $(TAR_FILES) ; \
	gzip $(BINDUMP_NAME).tar ; \
	mv $(BINDUMP_NAME).tar.gz $(BINDUMP_HOME)
