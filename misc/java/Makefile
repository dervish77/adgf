# makefile for java directory tree
#
# simply type 'make' to make everything
#
#
#

DIRS = balldemo counter framer hello keytest menu stopwatch test tictactoe


#
# make all programs
#

default: all

all:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make ; cd ..;     \
	done;


# remove all *.o and backup files

clean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make clean ; cd ..;     \
	done;


# remove all *.o, executables, and library files

realclean: clean
	for dir in $(DIRS);  do               \
	   cd $$dir ; make realclean ; cd ..; \
	done;
	rm -f *~

distclean: realclean

#
# make distribution file
#

PKG_HOME = java
PKG_NAME = java

tar:
	cd .. ; \
	tar -cvf $(PKG_NAME).tar $(PKG_HOME) ; \
	gzip $(PKG_NAME).tar ; \
	mv $(PKG_NAME).tar.gz $(PKG_NAME).tgz

