# makefile for  Dev8085  - 8085 development package

#
# if you have trouble building, edit the file 'dev8085.mk'
#
include ../dev8085.mk

# 
# you should not need to edit below this line
#

ASM_OBJS    = asm85.o instr.o parse.o
DUMP_OBJS   = dump85.o
EMU_OBJS    = emu85.o instr.o
LINK_OBJS   = link85.o
SREC_OBJS   = srec85.o

TARGETS = asm85 dump85 emu85 link85 srec85 


# compiler options

LIBS = -lm

INCLUDE = $(LIBDEV8085_INCLUDE_LOC) 

CFLAGS  = -O $(DEBUG) 


# 
# begin dependancies
#

default: $(TARGETS)


# executables

asm85: $(ASM_OBJS)
	$(CC) -o asm85 $(ASM_OBJS) $(LIBS)
	cp asm85 ../bin/.

dump85: $(DUMP_OBJS)
	$(CC) -o dump85 $(DUMP_OBJS) $(LIBS)
	cp dump85 ../bin/.

emu85: $(EMU_OBJS)
	$(CC) -o emu85 $(EMU_OBJS) $(LIBS)
	cp emu85 ../bin/.

link85: $(LINK_OBJS)
	$(CC) -o link85 $(LINK_OBJS) $(LIBS)
	cp link85 ../bin/.

srec85: $(SREC_OBJS)
	$(CC) -o srec85 $(SREC_OBJS) $(LIBS)
	cp srec85 ../bin/.


# object file dependancies

asm85.o : asm85.c ../include/dev8085.h
	$(CC) $(INCLUDE) $(CFLAGS) -c asm85.c

dump85.o : dump85.c ../include/dev8085.h
	$(CC) $(INCLUDE) $(CFLAGS) -c dump85.c

emu85.o : emu85.c ../include/dev8085.h
	$(CC) $(INCLUDE) $(CFLAGS) -c emu85.c

link85.o : link85.c ../include/dev8085.h
	$(CC) $(INCLUDE) $(CFLAGS) -c link85.c

srec85.o : srec85.c ../include/dev8085.h
	$(CC) $(INCLUDE) $(CFLAGS) -c srec85.c

instr.o : instr.c ../include/dev8085.h
	$(CC) $(INCLUDE) $(CFLAGS) -c instr.c

parse.o : parse.c
	$(CC) $(INCLUDE) $(CFLAGS) -c parse.c


# clean targets

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ $(TARGETS) ../bin/*85

