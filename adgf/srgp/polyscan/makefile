# Makefile for scantest, test program for generic convex polygon scan conversion
#
# Note: fancytest.c needs a main routine and several auxiliary routines
# in order to be compiled.

CC = gcc

CFLAGS = $(GENCFLAGS)

default: scantest

scantest: scantest.o polyscan.o poly.o
	$(CC) $(CFLAGS) -o scantest scantest.o polyscan.o poly.o -lm

poly.o: poly.c poly.h

polyscan.o: polyscan.c poly.h

scantest.o: scantest.c poly.h

clean:
	/bin/rm -f scantest.o polyclip.o polyscan.o poly.o scantest

