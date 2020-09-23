# makefile for MyMail program
#

# pick your favorite compiler
CC=gcc

OBJECTS = mymail.o menus.o user.o exec.o

GCCFLAGS = -fpcc-struct-return

CFLAGS   = -O

LIBS     = -lm

TARGET   = mymail


default: $(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(GCCFLAGS) $(CFLAGS) $(OBJECTS) $(LIBS)

clean:
	rm -f *% *~ *.o

realclean:
	rm -f *% *~ *.o core $(TARGET)


mymail.o: mymail.c mymail.h

menus.o: menus.c mymail.h

user.o: user.c mymail.h

exec.o: exec.c mymail.h

