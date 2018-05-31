# since the code is ANSI we use gcc
CC     = gcc

# These CFLAGS put in debugging, profiling, and optimization
#CFLAGS = -g -p -O -fstrength-reduce -finline-functions 

# These CFLAGS put in debugging, and optimization
#CFLAGS = -g -O -fstrength-reduce -finline-functions 

# This just puts in debugging, which is normally what we want
CFLAGS = -g 

# libraries we need to link with (order makes a difference)...
LIBSX = /cs/courses/cs4731/software/libsx/src/libsx.a
LIBS   =  $(LIBSX) -lXaw -lXmu -lXt -lX11 -lXext -lm

OBJSZB       = renderzb.o callbacks.o

renderzb : $(OBJSZB)
	gcc -o renderzb $(OBJSZB) $(LIBS)


renderzb.o : renderzb.c main.h callbacks.h libsx.h

callbacks.o : libsx.h callbacks.c main.h

