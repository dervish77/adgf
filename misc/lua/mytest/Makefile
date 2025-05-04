# makefile for lua programs
#

PY  = lua
EXE = /usr/bin/lua

#-------------------------------------------------------------------------

TARGET = mytest

#-------------------------------------------------------------------------

default: execute

all: execute

execute: $(TARGET).lua
	-@$(EXE) $(TARGET).lua

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core 

