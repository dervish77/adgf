#
#  makefile for image processing demo program - image
#
#

INSTALL_DIR = $(HOME)/bin

#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS   = main.o callback.o image.o drwlibsx.o vecmath.o creq.o ppm.o

TARGET = image


default : $(TARGET)

all : $(TARGET) install

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callback.h
main.o : main.c main.h callback.h image.h libsx.h ppm.h

callback.o : callback.c main.h image.h libsx.h ppm.h

ppm.o : ppm.c ppm.h

creq.o : creq.c creq.h libsx.h

image.o : image.c main.h callback.h image.h vecmath.h libsx.h ppm.h

drwlibsx.o : drwlibsx.c main.h image.h vecmath.h libsx.h ppm.h

vecmath.o : vecmath.c vecmath.h

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ core $(TARGET) dumpdata.log

install :
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )

uninstall :
	( rm -f $(INSTALL_DIR)/$(TARGET) )
