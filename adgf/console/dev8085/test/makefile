# makefile for test programs for Dev8085 

#
# if you have trouble building, edit the file 'dev8085.mk'
#
include ../dev8085.mk

# 
# you should not need to edit below this line
#

TARGETS = test 

LIBS	= -lm

LDFLAGS = $(LIBDEV8085_LIB_LOC)

INCLUDE = $(LIBDEV8085_INCLUDE_LOC) 

CFLAGS  = -O $(DEBUG)


# 
# begin dependancies
#

default: $(TARGETS)

test: test.o
	$(CC) -o $@ $(LDFLAGS) test.o $(LIBS) 

test.o: test.c 
	$(CC) $(INCLUDE) $(CFLAGS) -c test.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ $(TARGETS) 
