# makefile for remote command execution test
#

CC=gcc

OBJECTS1 = remtest.o   			# remtest client

OBJECTS2 = rcmdtest.o			# rcmdtest client

OBJECTS3 = test.o 		  	# test application

TARGETS = remtest rcmdtest test

LIBS	= -lsocket -lnsl
CFLAGS  = -O



default: $(TARGETS)


remtest: $(OBJECTS1)
	$(CC) -o $@ $(OBJECTS1) $(LIBS)

rcmdtest: $(OBJECTS2)
	$(CC) -o $@ $(OBJECTS2) $(LIBS)

test: $(OBJECTS3)
	$(CC) -o $@ $(OBJECTS3) $(LIBS)


remtest.o : remtest.c

rcmdtest.o : rcmdtest.c

test.o : test.c


clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGETS)
