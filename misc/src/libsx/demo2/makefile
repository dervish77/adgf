#
#
include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callbacks.o

demo2 : $(OBJS)
	$(CC) -o demo2 $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callbacks.h libsx.h

callbacks.o : libsx.h callbacks.c main.h


clean :
	rm -f *.o *~ core demo2
