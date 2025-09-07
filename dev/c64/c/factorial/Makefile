# makefile for C64 factorial
#

PLAT = c64
#PLAT = sim6502

FILES	  = fact.xxx main.xxx

LIB_FILES = 

LIBRARY	  = 

SOURCES=fact.c main.c

TNAME=fact
TARGET=$(TNAME).prg


#------------------------------------------

OFILES	   = $(FILES:xxx=o)
CFILES	   = $(FILES:xxx=c)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_CFILES = $(LIB_FILES:.xxx=.c)

CC = cl65
AR = ar65

SIM = sim65

C1541 = c1541

CFLAGS  = -t $(PLAT) --create-dep $(<:.c=.d) -O

LDFLAGS = -t $(PLAT) -m $(TNAME).map -L .

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

disk: d64

d64: all
	$(C1541) -format $(TNAME)disk,01 d64 $(TNAME).d64 -attach $(TNAME).d64 -write $(TARGET) $(TNAME)

#------------------------------------------

clean:
	rm -f *.o *.s *.d *% *~

realclean: clean
	rm -f core *.a *.lib *.map *.d64 $(TARGET)

