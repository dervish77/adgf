#
#  makefile for stereographics animation demo
#
#
#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callback.o story.o drawing.o vecmath.o

default: story

story : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callback.h story.h libsx.h

callback.o : callback.c main.h story.h libsx.h 

story.o : story.c main.h callback.h story.h vecmath.h libsx.h

drawing.o : drawing.c main.h callback.h story.h drawing.h vecmath.h libsx.h

vecmath.o : vecmath.c vecmath.h

clean :
	rm -f *.o *% *~

realclean :
	rm -f *.o *% *~ core story
