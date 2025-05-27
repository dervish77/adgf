#
#  makefile for 3D modeling program - modeler
#
#

INSTALL_DIR = $(HOME)/bin

#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callback.o modeler.o translat.o drawgen.o drwlibsx.o vecmath.o add_prim.o del_prim.o edit_lit.o edit_cam.o editanim.o creq.o vrml.o

TARGET = modeler

default: $(TARGET)

all : $(TARGET) install

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callback.h
main.o : main.c main.h callback.h modeler.h libsx.h

callback.o : callback.c main.h callback.h modeler.h libsx.h 

add_prim.o : add_prim.c main.h libsx.h

del_prim.o : del_prim.c main.h libsx.h

edit_lit.o : edit_lit.c main.h libsx.h

edit_cam.o : edit_cam.c main.h libsx.h

editanim.o : editanim.c main.h libsx.h

creq.o : creq.c creq.h libsx.h

modeler.o : modeler.c main.h callback.h modeler.h vecmath.h libsx.h

translat.o : translat.c main.h modeler.h vecmath.h 

drawgen.o : drawgen.c main.h modeler.h vecmath.h

drwlibsx.o : drwlibsx.c main.h modeler.h callback.h vecmath.h libsx.h

vecmath.o : vecmath.c vecmath.h

vrml.o : vrml.c main.h modeler.h

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ core $(TARGET) dumpdata.log

install :
	( cp $(TARGET) $(INSTALL_DIR)/$(TARGET) )

uninstall :
	( rm -f $(INSTALL_DIR)/$(TARGET) )
