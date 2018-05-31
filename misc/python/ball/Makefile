# makefile for python programs
#

PY  = /cygdrive/c/Python27/python
EXE = /cygdrive/c/Python27/python

#-------------------------------------------------------------------------

TARGET = bounce

#-------------------------------------------------------------------------

default: execute

all: execute

execute: $(TARGET).py
	$(EXE) $(TARGET).py

idle: 
	/usr/bin/idle $(TARGET).py

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core 

