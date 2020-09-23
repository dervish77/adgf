# makefile for Dev8085 package -- A development package for 8085 micros
#
# simply type 'make' to make everything
#
#
#
# Note:  You may want to edit "dev8085.mk" before making the package.
#

DIRS = src test

REV  = 0.1

INSTALL_BIN_PATH     = $(HOME)/bin
INSTALL_MAN_PATH     = $(HOME)/man/man1


#
# make binaries, library and test programs
#

default: all

all:
	-@echo Making ... Dev8085 Tools
	(cd src ; $(MAKE) )
	-@echo Making ... Dev8085 Test Programs
	(cd test ; $(MAKE) )

help:



# remove all *.o and backup files

clean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make clean ; cd ..;     \
	done;
	(rm -f *% *~)
	(cd docs; rm -f *% *~)
	(cd man; rm -f *% *~)
	(cd include; rm -f *% *~)


# remove all *.o, executables, and library files

realclean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make realclean ; cd ..; \
	done;
	(rm -f *% *~)
	(cd bin; rm -f *85)
	(cd docs; rm -f *% *~)
	(cd man; rm -f *% *~)
	(cd include; rm -f *% *~)


#
# install binaries and man pages
#

install: 
	(cp man/asm85.man $(INSTALL_MAN_PATH/asm85.1)
	(cp man/dump85.man $(INSTALL_MAN_PATH/dump85.1)
	(cp man/emu85.man $(INSTALL_MAN_PATH/emu85.1)
	(cp man/link85.man $(INSTALL_MAN_PATH/link85.1)
	(cp man/srec85.man $(INSTALL_MAN_PATH/srec85.1)
	(cp bin/*85 $(INSTALL_BIN_PATH)/.)

uninstall:
	(rm -f $(INSTALL_BIN_PATH)/asm85)
	(rm -f $(INSTALL_BIN_PATH)/dump85)
	(rm -f $(INSTALL_BIN_PATH)/emu85)
	(rm -f $(INSTALL_BIN_PATH)/link85)
	(rm -f $(INSTALL_BIN_PATH)/srec85)
	(rm -f $(INSTALL_MAN_PATH)/asm85.1)
	(rm -f $(INSTALL_MAN_PATH)/dump85.1)
	(rm -f $(INSTALL_MAN_PATH)/emu85.1)
	(rm -f $(INSTALL_MAN_PATH)/link85.1)
	(rm -f $(INSTALL_MAN_PATH)/srec85.1)

#
# show docs
#

doc:
	more docs/dev8085.txt


#
# execute regression tests
#

test:
	-@echo "Running Dev8085 regression tests..."
	-@echo "Done."


#
# make distribution file
#

DEV8085_HOME = dev8085
DEV8085_NAME = dev8085-$(REV)

TAR_FILES = 	\
	$(DEV8085_HOME)/README			\
	$(DEV8085_HOME)/COPYING			\
	$(DEV8085_HOME)/REVISION		\
	$(DEV8085_HOME)/Makefile		\
	$(DEV8085_HOME)/dev8085.mk		\
	$(DEV8085_HOME)/include/*.h		\
	$(DEV8085_HOME)/bin/README.txt  \
	$(DEV8085_HOME)/bin/emu85.cfg	\
	$(DEV8085_HOME)/src/*.c			\
	$(DEV8085_HOME)/src/makefile	\
	$(DEV8085_HOME)/docs/*.txt		\
	$(DEV8085_HOME)/man/*.man		\
	$(DEV8085_HOME)/test/*.c		\
	$(DEV8085_HOME)/test/makefile

tar:
	cd .. ; \
	tar -cvf $(DEV8085_NAME).tar $(TAR_FILES) ; \
	gzip $(DEV8085_NAME).tar ; \
	mv $(DEV8085_NAME).tar.gz $(DEV8085_HOME)

