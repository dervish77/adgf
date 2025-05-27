# makefile for LIBVM -- Vector and Matrix math library

#
# if you have trouble building, edit the file 'libvm_defs'
#
include ../libvm_defs

# 
# you should not need to edit below this line
#

OBJECTS = vecmath.o 

TARGET = libvm

# note that this compiler IS necessary when using GNU gcc
GCCFLAGS = -fpcc-struct-return

LIBS	= -lm
TEST_LIBS = -lm

LDFLAGS = $(LIBVM_LIB_LOC)

INCLUDE = $(LIBVM_INCLUDE_LOC) 

CFLAGS  = -O2 -D_POSIX_SOURCE $(DEBUG) $(INCLUDE)


# 
# begin dependancies
#

default: $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	rm -f $(TARGET).a
	ar rc $(TARGET).a $(OBJECTS) 

vecmath.o: vecmath.c ../include/vm.h
	$(CC) $(GCCFLAGS) $(CFLAGS) -c vecmath.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGET).a

