# makefile for LIBGFS package -- a GUI For SRGP
#
# simply type 'make' to make everything
#

DIRS = src test

#
# make library and test programs
#

default: 
	@echo Making ... LIBGFS library
	(cd src ; $(MAKE) )
	(cp src/libgfs.a lib/libgfs.a)
	@echo Making ... test programs
	(cd test ; $(MAKE) )


# remove all *.o and backup files

clean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make clean ; cd ..;     \
	done;
	rm -f *~ *%
	(cd docs; rm -f *% *~)
	(cd include; rm -f *% *~)


# remove all *.o, executables, and library files

realclean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make realclean ; cd ..; \
	done;
	rm -f *~ *%
	(cd lib; rm -f libgfs.a)
	(cd docs; rm -f *% *~)
	(cd include; rm -f *% *~)

#
# install library and include files
#

INSTALL_LIB_PATH     = /home/bl12960/lib
INSTALL_INCLUDE_PATH = /home/bl12960/include

install: 
	(cp include/*.h $(INSTALL_INCLUDE_PATH)/.)
	(cp lib/libgfs.a $(INSTALL_LIB_PATH)/.)

uninstall:
	(rm -f $(INSTALL_INCLUDE_PATH)/gsprivat.h)
	(rm -f $(INSTALL_INCLUDE_PATH)/gspublic.h)
	(rm -f $(INSTALL_LIB_PATH)/libgfs.a)

#
# make distribution file
#

LIBGFS_HOME = libgfs
LIBGFS_NAME = libgfs-0.9

TAR_FILES = 	\
	$(LIBGFS_HOME)/README		\
	$(LIBGFS_HOME)/COPYING		\
	$(LIBGFS_HOME)/REVISION		\
	$(LIBGFS_HOME)/Makefile		\
	$(LIBGFS_HOME)/libgfs_defs	\
	$(LIBGFS_HOME)/include/*.h	\
	$(LIBGFS_HOME)/lib/README.lib	\
	$(LIBGFS_HOME)/src/*.c		\
	$(LIBGFS_HOME)/src/makefile	\
	$(LIBGFS_HOME)/docs/*.txt	\
	$(LIBGFS_HOME)/docs/*.txt	\
	$(LIBGFS_HOME)/test/*.c		\
	$(LIBGFS_HOME)/test/makefile

tar:
	cd .. ; \
	tar -cvf $(LIBGFS_NAME).tar $(TAR_FILES) ; \
	gzip $(LIBGFS_NAME).tar ; \
	mv $(LIBGFS_NAME).tar.gz $(LIBGFS_HOME)
