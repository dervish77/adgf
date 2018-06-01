# makefile for geturl test program

# uncomment next line if you are using a BSD Unix
# DEFINE = -D_USE_BSD

DEBUG = -D_DEBUG

CC=gcc

OBJECTS = geturl.o  

TARGET = geturl

# GCCFLAGS = -fpcc-struct-return

#LIBS	= -lsocket -lnsl -lm
LIBS	= -lnsl -lm
CFLAGS  = -O $(DEFINE) $(DEBUG)

default: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

geturl.o : geturl.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGET)
