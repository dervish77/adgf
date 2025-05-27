# makefile for tcp echo client/server programs
#

CC=gcc

OBJECTS1 = tcpecho.o tcplib.o  		# echo client

OBJECTS2 = tcpechod.o tcplib.o  	# echo server

TARGETS = tcpecho tcpechod

LIBS	= -lsocket -lnsl
CFLAGS  = -O



default: $(TARGETS)


tcpecho: $(OBJECTS1)
	$(CC) -o $@ $(OBJECTS1) $(LIBS)

tcpechod: $(OBJECTS2)
	$(CC) -o $@ $(OBJECTS2) $(LIBS)


tcpecho.o : tcpecho.c tcplib.h

tcpechod.o : tcpechod.c tcplib.h

tcplib.o : tcplib.c tcplib.h


clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGETS)
