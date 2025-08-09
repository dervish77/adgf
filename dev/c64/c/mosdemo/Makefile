# makefile for C64 mosdemo
#
# Builds MOS library then builds demo files
#
#

PLAT = c64
#PLAT = sim6502

FILES	  = tasks.xxx demo.xxx main.xxx

LIB_FILES = platform.xxx hw.xxx mos.xxx

LIBRARY	  = mos.lib

TARGET    = mosdemo

#------------------------------------------

OFILES	   = $(FILES:xxx=o)
CFILES	   = $(FILES:xxx=c)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_CFILES = $(LIB_FILES:.xxx=.c)

CC = cl65
AR = ar65

SIM = sim65

CFLAGS  = -t $(PLAT) --create-dep $(<:.c=.d) -O

LDFLAGS = -t $(PLAT) -m $(TARGET).map -L .

ARFLAGS = r

EMU = x64sc

#------------------------------------------

.SUFFIXES:
.PHONY: all clean realclean

default: all

all: $(TARGET)

$(TARGET): $(OFILES) $(LIBRARY) 
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBRARY): $(LIB_OFILES)

$(OFILES): %.o: %.c *.h
	$(CC) -c $(CFLAGS) -o $@ $<
	
$(LIB_OFILES): %.o: %.c *.h
	$(CC) -c $(CFLAGS) -o $@ $<
	$(AR) $(ARFLAGS) $(LIBRARY) $*.o

#------------------------------------------

test: run

run: all
	$(EMU) -autostart $(TARGET) &

#------------------------------------------

sim: all
	$(SIM) $(TARGET)

#------------------------------------------

clean:
	rm -f *.o *.s *.d *% *~

realclean: clean
	rm -f core *.a *.lib *.map $(TARGET)

