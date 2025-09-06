# makefile for C64 bcd display in assembly
#

SOURCE1  := main.asm
SOURCE2  := outnum.asm

OBJ1     := main.o
OBJ2     := outnum.o

PROGRAM  := main.prg

ADDR     := 0x1000

#------------------------------------------

AS = ca65
CC = cl65
CL = cl65

EMU = x64sc

########################################

.SUFFIXES:
.PHONY: all run clean realclean

default: all

all: $(PROGRAM)

$(OBJ1): $(SOURCE1)
	$(AS) --cpu 65C02 $(SOURCE1) -o $(OBJ1)

$(OBJ2): $(SOURCE2)
	$(AS) --cpu 65C02 $(SOURCE2) -o $(OBJ2)

$(PROGRAM): $(OBJ2) $(OBJ1)
	$(CL) --start-addr $(ADDR) -t c64 -C c64-asm.cfg $(OBJ1) $(OBJ2) -o $(PROGRAM)

#$(PROGRAM): $(SOURCE)
#	$(CC) --start-addr $(ADDR) -o $(PROGRAM) -t c64 -C c64-asm.cfg $(SOURCE)

clean:
	rm -f *.o *.s *% *~

realclean: clean
	rm -f core $(PROGRAM)

#------------------------------------------

test: run

run: all
	$(EMU) -autostart $(PROGRAM) &
	-@echo "Type 'sys 4096' to run program"

#------------------------------------------

