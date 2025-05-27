# makefile for 3D modeler

CC=gcc

OBJECTS1 = modeler.o 

# GCCFLAGS = -fpcc-struct-return

LIBS	= -lm
CFLAGS  = -O

all:	modeler

modeler: $(OBJECTS1)
	gcc -o $@ $(OBJECTS1) $(LIBS)

clean:
	rm -f *~ *% *.o core modeler

