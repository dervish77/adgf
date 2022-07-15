#
#
include ../libsx_defs

frac : frac.o
	$(CC) -o frac frac.o $(LIBS)

frac.o : frac.c libsx.h

clean :
	rm -f *.o *~ core frac
