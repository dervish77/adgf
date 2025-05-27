# makefile for render program

CC=gcc

OBJECTS = render.o clipping.o drawsrgp.o mathutls.o rendutls.o shading.o viewing.o sorting.o

GCCFLAGS = -fpcc-struct-return

LIBS	= -lsrgp -lX11 -lm
LDFLAGS = -L/scratch/bl12960/misc/src/SRGP_DISTRIB/lib
CFLAGS  = -O -I/scratch/bl12960/misc/src/SRGP_DISTRIB/include

all:	render

render: $(OBJECTS)
	$(CC) -o $@ $(GCCFLAGS) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS)

render.o: render.c render.h

clipping.o: clipping.c render.h 

drawsrgp.o: drawsrgp.c render.h shading.h

mathutls.o: mathutls.c render.h

rendutls.o: rendutls.c render.h

shading.o: shading.c render.h shading.h

sorting.o: sorting.c render.h

viewing.o: viewing.c render.h

clean:
	rm -f *% *~ *.o

realclean:
	rm -f *% *~ *.o *.log core render
