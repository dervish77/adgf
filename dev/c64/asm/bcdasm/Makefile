# makefile for C64 bcd display in assembly
#

PLAT = c64

FILES	  = main.xxx outnum.xxx

LIB_FILES = 

LIBRARY	  = 

PNAME = main
PROGRAM = $(PNAME).prg

#------------------------------------------

ADDR      = 0x1000

AS = ca65
CC = cl65
CL = cl65
AR = ar65

EMU = x64sc

SIM = sim65

C1541 = c1541

#------------------------------------------

OFILES	   = $(FILES:xxx=o)
AFILES	   = $(FILES:xxx=asm)

LIB_OFILES = $(LIB_FILES:.xxx=.o)
LIB_AFILES = $(LIB_FILES:.xxx=.asm)

ASFLAGS = -t $(PLAT)

LDFLAGS = -t $(PLAT) -C c64-asm.cfg -m $(PNAME).map -L .

ARFLAGS = r

########################################

.SUFFIXES:
.PHONY: all run clean realclean

default: all

all: $(PROGRAM)

$(PROGRAM): $(OFILES) $(LIBRARY) 
	$(CL) --start-addr $(ADDR) $(LDFLAGS) -o $@ $^

$(LIBRARY): $(LIB_OFILES)

$(OFILES): %.o: %.asm 
	$(AS) $(ASFLAGS) -o $@ $<

$(LIB_OFILES): %.o: %.asm 
	$(AS) $(ASFLAGS) -o $@ $<
	$(AR) $(ARFLAGS) $(LIBRARY) $*.o

#------------------------------------------

test: run

run: all
	$(EMU) -autostart $(PROGRAM) &
	-@echo "Type 'sys 4096' to run program"

#------------------------------------------

disk: d64

d64: all
	$(C1541) -format $(PNAME)disk,01 d64 $(PNAME).d64 -attach $(PNAME).d64 -write $(TARGET) $(PNAME)

#------------------------------------------

clean:
	rm -f *.o *.s *% *~

realclean: clean
	rm -f core *.map *.d64 $(PROGRAM)

