# makefile for java programs
#

JC  = javac
EXE = java

#-------------------------------------------------------------------------

TARGET = hello

#-------------------------------------------------------------------------

default: execute

execute: $(TARGET).class
	$(EXE) $(TARGET)

$(TARGET).class: $(TARGET).java
	$(JC) $(TARGET).java

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core *.class

