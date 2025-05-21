# makefile for C64 thuria
#

#SOURCES=main.c intro.c game.c cmds.c debug.c map.c \
#		object.c room.c special.c magic.c rank.c verb.c

SOURCES=main.c intro.c map.c room.c game.c cmds.c magic.c object.c rank.c special.c

TARGET=thuria

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

