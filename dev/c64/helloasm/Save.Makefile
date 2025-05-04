# makefile for C64 hello world
#

CC = cc65
AS = ca65
LD = ld65

CFLAGS  = -O -t c64

ASFLAGS = -t c64

LDFLAGS = -t c64

LIBS = c64.lib

EMU = x64sc

#------------------------------------------

CFILES=helloc.c

OBJECTS=helloc.o

TARGET=helloc

#------------------------------------------

.SUFFIXES:
.PHONY: all clean realclean

default: all

all: $(TARGET)

$(TARGET): $(CFILES)
	$(CC) -O -t c64 helloc.c
	$(AS) -t c64 helloc.s
	$(LD) -o $(TARGET) -t c64 helloc.o $(LIBS)

#------------------------------------------

test: run

run: all
	$(EMU) -autostart $(TARGET) &

#------------------------------------------

clean:
	rm -f *.o *.s *% *~

realclean: clean
	rm -f core $(TARGET)

