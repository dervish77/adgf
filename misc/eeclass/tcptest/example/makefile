# makefile for tcp example client/server
#

CC=gcc

OBJECTS1 = client.o

OBJECTS2 = server.o

TARGETS = client server

LIBS	= -lsocket -lnsl
CFLAGS  = -O



default: $(TARGETS)


client: $(OBJECTS1)
	$(CC) -o $@ $(OBJECTS1) $(LIBS)

server: $(OBJECTS2)
	$(CC) -o $@ $(OBJECTS2) $(LIBS)


client.o : client.c

server.o : server.c


clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGETS)
