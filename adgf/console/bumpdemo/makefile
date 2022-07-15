# makefile for bump mapping demo
#
# to make main demo:	make bumpdemo
#
# to make simple demo:  make embdemo
#
# to make test program: make testimag
#
# to remove .o files:	make clean
#
# this code has been tested on Sun and DEC workstations

# pick your favorite compiler
CC=gcc
# CC=cc

OBJECTS1 =	bumpdemo.o emboss.o imagfile.o
OBJECTS2 = 	testimag.o
OBJECTS3 =	embdemo.o

GCCFLAGS = -fpcc-struct-return

CFLAGS   = -O

# use first define if running under BSD unix, use second define if under SysV
# DEFINES  = -D_USE_BSD_RANDOM
DEFINES  = 

LIBS     = -lm

default: bumpdemo

all:	bumpdemo \
	testimag

bumpdemo: $(OBJECTS1)
	$(CC) -o $@ $(GCCFLAGS) $(CFLAGS) $(OBJECTS1) $(LIBS)

testimag: $(OBJECTS2)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS2) $(LIBS)

embdemo: $(OBJECTS3)
	$(CC) -o $@ $(CFLAGS) $(DEFINES) $(OBJECTS3) $(LIBS)

bumpdemo.o: bumpdemo.c imagfile.h

emboss.o: emboss.c

imagfile.o: imagfile.c imagfile.h

testimag.o: testimag.c

embdemo.o: embdemo.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core bumpdemo testimag embdemo

