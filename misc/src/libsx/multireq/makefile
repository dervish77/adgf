#
#
include ../libsx_defs

OBJS       = main.o multireq.o

all : multireq

multireq : $(OBJS) 
	$(CC) -o $@ $(OBJS) $(LIBS)

main.o : main.c libsx.h multireq.h

multireq.o : multireq.c multireq.h

clean:
	rm -f *.o *~ core multireq

