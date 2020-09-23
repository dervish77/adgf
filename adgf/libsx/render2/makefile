#
#  makefile for 3D modeling and rendering program - render
#
#
#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callback.o render.o vecmath.o

all:	render

render : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callback.h
main.o : main.c main.h callback.h render.h libsx.h

callback.o : callback.c main.h render.h libsx.h 

render.o : render.c main.h callback.h render.h vecmath.h libsx.h

vecmath.o : vecmath.c vecmath.h

clean :
	rm -f *.o *~ *%

realclean :
	rm -f *.o *~ *% core render

