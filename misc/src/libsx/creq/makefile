#
#
include ../libsx_defs


OBJS       = main.o creq.o

all : creq

creq : $(OBJS) 
	$(CC) -o $@ $(OBJS) $(LIBS)

main.o : main.c libsx.h creq.h

creq.o : creq.c

clean:
	rm -f *.o *~ core creq
