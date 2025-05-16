# makefile for C64 fibonaci
#

SOURCES=fib.c main.c

TARGET=fibo

#------------------------------------------

CC = cl65

CFLAGS  = -t c64 --create-dep $(<:.c=.d) -O
LDFLAGS = -t c64 -m $(TARGET).map

EMU = x64sc

#------------------------------------------

.SUFFIXES:
.PHONY: all clean realclean

default: all

all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(TARGET): $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^

#------------------------------------------

test: run

run: all
	$(EMU) -autostart $(TARGET) &

#------------------------------------------

clean:
	rm -f *.o *.s *.d *% *~

realclean: clean
	rm -f core *.map $(TARGET)

