#
# Makefile for cc65 samples
#
# This Makefile requires GNU make
#

# Enter the target system here
SYS		= c64

CC65_HOME	= /cygdrive/c/cc65

VICE_HOME	= /cygdrive/c/Utils/WinVICE-2.4-x86

# Determine the path to the executables and libraries. If the samples
# directory is part of a complete source tree, use the stuff from that
# source tree; otherwise, use the "install" directories.

MOUS = $(CC65_HOME)/mou/$(SYS)*.mou
TGI  = $(CC65_HOME)/tgi/$(SYS)*.tgi


CLIB = --lib $(SYS).lib

CL   = $(CC65_HOME)/bin/cl65.exe
CC   = $(CC65_HOME)/bin/cc65.exe
AS   = $(CC65_HOME)/bin/ca65.exe
LD   = $(CC65_HOME)/bin/ld65.exe


CA65_INC = $(CC65_HOME)/asminc
CC65_INC = $(CC65_HOME)/include
LD65_CFG = $(CC65_HOME)/src/ld65/cfg
LD65_LIB = $(CC65_HOME)/libsrc
LD65_OBJ = $(CC65_HOME)/libsrc


#MY_INC = -I . -I $(CC65_INC)
MY_INC = --forget-inc-paths -I . -I $(CC65_INC)
MY_ASM = --forget-inc-paths -I . -I $(CA65_INC)


# This one comes with VICE
C1541  	= $(VICE_HOME)/c1541.exe


# --------------------------------------------------------------------------
# Generic rules

.c.o:
	@echo Compiling $<
	@echo CC is $(CC)
	@echo MY_INC is $(MY_INC)
	@echo SYS is $(SYS)
	@$(CC) $(MY_INC) -Oirs --codesize 500 -T -g -t $(SYS) $<
	@$(AS) $(basename $<).s

.s.o:
	@echo Assembling $<
	@$(AS) $(MY_ASM) -t $(SYS) $<

.o:
	@$(LD) -t $(SYS) -m $(basename $@).map -o $@ $^ $(CLIB)


# --------------------------------------------------------------------------
# List of executables. This list could be made target dependent by checking
# $(SYS).

EXELIST	=     	hello 		

# --------------------------------------------------------------------------
# Rules how to make each one of the binaries

.PHONY:	all
all:   	$(EXELIST)

ascii:		ascii.o

diodemo:	diodemo.o

fire:		fire.o

gunzip65:	gunzip65.o

hello:		hello.o

# The Apple machines need the start address adjusted for the mandelbrot demo
ifeq "$(SYS)" "apple2"
mandelbrot:	mandelbrot.o
	@$(LD) -t $(SYS) -m $(basename $@).map --start-addr 0x4000 -o $@ $^ $(CLIB)
else
ifeq "$(SYS)" "apple2enh"
mandelbrot:	mandelbrot.o
	@$(LD) -t $(SYS) -m $(basename $@).map --start-addr 0x4000 -o $@ $^ $(CLIB)
else
mandelbrot:	mandelbrot.o
endif
endif

# The Apple ][ needs the start address adjusted for the mousedemo
ifeq "$(SYS)" "apple2"
mousedemo:	mousedemo.o
	@$(LD) -t $(SYS) -m $(basename $@).map --start-addr 0x4000 -o $@ $^ $(CLIB)
else
mousedemo:	mousedemo.o
endif

nachtm:		nachtm.o

overlaydemo:	overlaydemo.o
	@$(LD) -C overlaydemo-$(SYS).cfg -m $(basename $@).map -o $@ $^ $(CLIB)

plasma:		plasma.o

sieve:		sieve.o

# The Apple machines need the start address adjusted for the tgidemo
ifeq "$(SYS)" "apple2"
tgidemo:	tgidemo.o
	@$(LD) -t $(SYS) -m $(basename $@).map --start-addr 0x4000 -o $@ $^ $(CLIB)
else
ifeq "$(SYS)" "apple2enh"
tgidemo:	tgidemo.o
	@$(LD) -t $(SYS) -m $(basename $@).map --start-addr 0x4000 -o $@ $^ $(CLIB)
else
tgidemo:	tgidemo.o
endif
endif

# --------------------------------------------------------------------------
# Rule to make a disk with all samples. Needs the c1541 program that comes
# with the VICE emulator.

.PHONY:	disk
disk:  	samples.d64

samples.d64:	all
	@echo C1541 is $(C1541)
	@$(C1541) -format samples,AA  d64 $@ > /dev/null
	@for exe in $(EXELIST); do\
	    $(C1541) -attach $@ -write $$exe > /dev/null || exit $$?;\
	done
	@for mod in $(TGI) $(MOUS); do\
	    $(C1541) -attach $@ -write $$mod > /dev/null || exit $$?;\
	done

# --------------------------------------------------------------------------
# Cleanup rules

.PHONY:	clean
clean:
	$(RM) *~ *.map *.o *.s *.lbl

.PHONY:	zap
zap:	clean
	$(RM) $(EXELIST) overlaydemo.* samples.d64



