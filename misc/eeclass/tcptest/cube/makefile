# makefile for cube puzzle demo client/server programs
#

CC=gcc

OBJECTS1 = cubeclient.o tcplib.o  	# cube client

OBJECTS2 = cubeserver.o tcplib.o  	# cube server

OBJECTS3 = cubeserver2.o tcplib.o  	# cube server 2

OBJECTS4 = cubeserver3.o tcplib.o  	# cube server 3

TARGETS = cubeclient cubeserver cubeserver2 cubeserver3

LIBS	= -lsocket -lnsl
CFLAGS  = -O



default: $(TARGETS)


cubeclient: $(OBJECTS1)
	$(CC) -o $@ $(OBJECTS1) $(LIBS)

cubeserver: $(OBJECTS2)
	$(CC) -o $@ $(OBJECTS2) $(LIBS)

cubeserver2: $(OBJECTS3)
	$(CC) -o $@ $(OBJECTS3) $(LIBS)

cubeserver3: $(OBJECTS4)
	$(CC) -o $@ $(OBJECTS4) $(LIBS)


cubeclient.o : cubeclient.c tcplib.h

cubeserver.o : cubeserver.c tcplib.h

cubeserver2.o : cubeserver2.c tcplib.h

cubeserver3.o : cubeserver3.c tcplib.h

tcplib.o : tcplib.c tcplib.h


clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGETS)
