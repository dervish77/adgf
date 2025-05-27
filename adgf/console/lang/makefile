# makefile for language test program
#

CC=gcc

OBJECTS = lang.o  

TARGET = lang

LIBS	= -lm
CFLAGS  = -O



default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

lang.o : lang.c lang.h

clean:
	rm -f *.o *% *~ core $(TARGET)


#
# make distribution file
#

VERSION = 0.1

LANG_HOME = lang
LANG_NAME = lang-$(VERSION)

TAR_FILES = 	\
	$(LANG_HOME)/README		\
	$(LANG_HOME)/def_dict		\
	$(LANG_HOME)/*.h		\
	$(LANG_HOME)/*.c		\
	$(LANG_HOME)/makefile

tar:
	cd .. ; \
	tar -cvf $(LANG_NAME).tar $(TAR_FILES) ; \
	gzip $(LANG_NAME).tar ; \
	mv $(LANG_NAME).tar.gz $(LANG_HOME)
