#
#
include ../libsx_defs

# the object files which the program depends on
OBJS       = main.o callbacks.o

demo1 : $(OBJS)
	$(CC) -o demo1 $(OBJS) $(LIBS)


# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callbacks.h libsx.h

callbacks.o : libsx.h callbacks.c main.h


#
# A cleanup target.  Type `make clean' to remove all the junk.
#
clean :
	rm -f *.o *~ core demo1
