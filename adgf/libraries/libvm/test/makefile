# makefile for test programs using LIBVM

#
# if you have trouble building, edit the file 'libvm_defs'
#
include ../libvm_defs

# 
# you should not need to edit below this line
#

TARGETS = testvec2 testvec3

# note that this compiler IS necessary when using GNU gcc
GCCFLAGS = -fpcc-struct-return

LIBS	= -lvm -lm

LDFLAGS = $(LIBVM_LIB_LOC)

INCLUDE = $(LIBVM_INCLUDE_LOC) 

CFLAGS  = -O $(DEBUG)


# 
# begin dependancies
#

default: $(TARGETS) 

all: $(TARGETS) regress

regress: $(TARGETS)
	@echo ""
	@echo "Regressing 2D vector functions...."
	testvec2 testvec2.in
	@echo ""
	@echo "Regressing 3D vector functions...."
	testvec3 testvec3.in


testvec2: testvec2.o
	$(CC) -o $@ $(LDFLAGS) testvec2.o $(LIBS) 

testvec3: testvec3.o
	$(CC) -o $@ $(LDFLAGS) testvec3.o $(LIBS) 


testvec2.o: testvec2.c ../include/vm.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c testvec2.c

testvec3.o: testvec3.c ../include/vm.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c testvec3.c


clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ $(TARGETS) vmdebug.log
