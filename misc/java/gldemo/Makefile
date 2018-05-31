# makefile for java programs
#

JC  = javac
EXE = java

#-------------------------------------------------------------------------

TARGET = OpenGlDemo

TARGET2 = FramerApplet

#-------------------------------------------------------------------------

default: execute

all: execute

execute: $(TARGET).class
	$(EXE) $(TARGET)

$(TARGET).class: $(TARGET).java
	$(JC) $(TARGET).java

applet: $(TARGET2).class
	appletviewer $(TARGET2).html

$(TARGET2).class: $(TARGET2).java
	$(JC) $(TARGET2).java

#-------------------------------------------------------------------------

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core *.class

