# makefile for python programs
#

PY  = python
EXE = /cygdrive/c/Python27/python

IDLEDIR = /cygdrive/c/Python27/Lib/idlelib

#-------------------------------------------------------------------------

TARGET = cribbage

#-------------------------------------------------------------------------

default: execute

all: execute

execute: $(TARGET).py
	-@$(EXE) $(TARGET).py

idle: 
	/usr/bin/idle $(TARGET).py

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core 

