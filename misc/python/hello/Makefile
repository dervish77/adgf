# makefile for python programs
#

PY  = python
EXE = python

IDLE = idle3

#-------------------------------------------------------------------------

TARGET = hello

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
