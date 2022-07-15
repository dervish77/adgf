#
#  makefile for particle systems demo program - particle
#
#
#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callback.o particle.o drawgen.o drwlibsx.o vecmath.o edit_cam.o editanim.o creq.o

default: particle

particle : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callback.h particle.h libsx.h

callback.o : callback.c main.h particle.h libsx.h 

edit_cam.o : edit_cam.c main.h libsx.h

editanim.o : editanim.c main.h libsx.h

creq.o : creq.c creq.h libsx.h

particle.o : particle.c main.h callback.h particle.h vecmath.h libsx.h

drawgen.o : drawgen.c main.h particle.h vecmath.h

drwlibsx.o : drwlibsx.c main.h particle.h vecmath.h libsx.h

vecmath.o : vecmath.c vecmath.h

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ core particle
