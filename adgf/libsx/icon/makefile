#
#  makefile for icon editor program - icon
#
#

INSTALL_DIR = $(HOME)/bin

#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS   = main.o callbcks.o icon.o drwlibsx.o creq.o iconset.o
TARGET = icon

OBJS2   = icon2ppm.o ppm.o
LIBS2	= 
TARGET2 = icon2ppm

# dependancies
default: $(TARGET) $(TARGET2)

all : $(TARGET) install

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

$(TARGET2) : $(OBJS2)
	$(CC) -o $@ $(OBJS2) $(LIBS2)

# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callbcks.h icon.h libsx.h

callbcks.o : callbcks.c main.h icon.h libsx.h 

creq.o : creq.c creq.h libsx.h

iconset.o : iconset.c main.h icon.h libsx.h

icon.o : icon.c main.h callbcks.h icon.h vecmath.h libsx.h

drwlibsx.o : drwlibsx.c main.h icon.h vecmath.h libsx.h

# utility targets
icon2ppm.o : icon2ppm.c icon.h

ppm.o : ppm.c ppm.h

# clean targets
clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ core $(TARGET) $(TARGET2)

# install targets
install :
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )

uninstall :
	( rm -f $(INSTALL_DIR)/$(TARGET) )
