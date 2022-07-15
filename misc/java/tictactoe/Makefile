# makefile for java programs
#

JC  = javac
EXE = java

#-------------------------------------------------------------------------

TARGET = TicTacToeApp

#TARGET2 = TicTacToeApp

#-------------------------------------------------------------------------

default: execute

all: execute applet

execute: $(TARGET).class
	$(EXE) $(TARGET)

$(TARGET).class: $(TARGET).java
	$(JC) $(TARGET).java

applet: $(TARGET).class
	appletviewer $(TARGET).html

#$(TARGET2).class: $(TARGET2).java
#	$(JC) $(TARGET2).java

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core *.class

