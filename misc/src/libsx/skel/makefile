#
#
include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callbacks.o

skel : $(OBJS)
	$(CC) -o skel $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callbacks.h libsx.h

callbacks.o : libsx.h callbacks.c

clean :
	rm -f *.o *~ core skel

