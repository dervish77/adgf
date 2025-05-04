# makefile for C64 hello world in assembly
#

SOURCE  := main.asm
PROGRAM := main.prg
ADDR    := 0x1000

#------------------------------------------

CC = cl65

EMU = x64sc

########################################

.SUFFIXES:
.PHONY: all run clean realclean

default: all

all: $(PROGRAM)

$(PROGRAM): $(SOURCE)
	$(CC) --start-addr $(ADDR) -o $(PROGRAM) -t c64 -C c64-asm.cfg $(SOURCE)

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

