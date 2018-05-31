# makefile for java programs
#

JC  = javac
EXE = java
DDD = ddd

#-------------------------------------------------------------------------

TARGET = test

#-------------------------------------------------------------------------

default: execute

execute: $(TARGET).class
	$(EXE) $(TARGET)

$(TARGET).class: $(TARGET).java
	$(JC) -g $(TARGET).java

debug:
	$(DDD) -jdb $(TARGET) &

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core *.class

