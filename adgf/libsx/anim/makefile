#
#  makefile for inverse kinematics animation demo
#
#
#
include $(HOME)/include/libsx_defs
#include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callbcks.o invkine.o vecmath.o

default: anim

anim : $(OBJS)
	$(CC) -o anim $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callbcks.h
main.o : main.c main.h callbcks.h invkine.h libsx.h

callbcks.o : callbcks.c main.h invkine.h libsx.h 

invkine.o : invkine.c main.h callbcks.h invkine.h vecmath.h libsx.h

vecmath.o : vecmath.c vecmath.h

clean :
	rm -f *.o *% *~ 

realclean :
	rm -f *.o *% *~ core anim
