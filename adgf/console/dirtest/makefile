# makefile for dir_test program

CC=gcc

OBJECTS = dirt.o  

TARGET = dirt

# GCCFLAGS = -fpcc-struct-return

LIBS	= -lm
CFLAGS  = -O

default: dirt

dirt: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

dirt.o : dirt.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGET)
