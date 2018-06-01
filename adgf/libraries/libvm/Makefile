# makefile for LIBVM package -- a Vector and Matrix math library
#
# simply type 'make' to make everything
#

DIRS = src test

#
# make library and test programs
#

default:
	@echo ""
	@echo "Making ... LIBVM library"
	(cd src ; $(MAKE) )
	(cp src/libvm.a lib/libvm.a)
	@echo ""
	@echo "Making ... test programs"
	(cd test ; $(MAKE) )
	@echo ""
	@echo "Making ... running regression tests"
	(cd test ; $(MAKE) regress )



# remove all *.o and backup files

clean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make clean ; cd ..;     \
	done;
	(cd docs; rm -f *% *~)
	(cd include; rm -f *% *~)
	(rm -f *% *~)


# remove all *.o, executables, and library files

realclean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make realclean ; cd ..; \
	done;
	(cd lib; rm -f libvm.a *% *~)
	(cd docs; rm -f *% *~)
	(cd include; rm -f *% *~)
	(rm -f *% *~)

#
# install library and include files
#

INSTALL_LIB_PATH     = $(HOME)/lib
INSTALL_INCLUDE_PATH = $(HOME)/include

install: 
	(cp include/*.h $(INSTALL_INCLUDE_PATH)/.)
	(cp lib/libvm.a $(INSTALL_LIB_PATH)/.)

uninstall:
	(rm -f $(INSTALL_INCLUDE_PATH)/vm.h)
	(rm -f $(INSTALL_LIB_PATH)/libvm.a)

#
# make distribution file
#

LIBVM_REVISION = 0.1

LIBVM_HOME = libvm
LIBVM_NAME = libvm-$(LIBVM_REVISION)

TAR_FILES = 	\
	$(LIBVM_HOME)/README		\
	$(LIBVM_HOME)/COPYING		\
	$(LIBVM_HOME)/REVISION		\
	$(LIBVM_HOME)/Makefile		\
	$(LIBVM_HOME)/libvm_defs	\
	$(LIBVM_HOME)/include/*.h	\
	$(LIBVM_HOME)/lib/README.lib	\
	$(LIBVM_HOME)/src/*.c		\
	$(LIBVM_HOME)/src/makefile	\
	$(LIBVM_HOME)/docs/*.txt	\
	$(LIBVM_HOME)/test/*.c		\
	$(LIBVM_HOME)/test/*.in		\
	$(LIBVM_HOME)/test/makefile

tar:
	@cd .. ; \
	tar -cvf $(LIBVM_NAME).tar $(TAR_FILES) ; \
	gzip $(LIBVM_NAME).tar ; \
	mv $(LIBVM_NAME).tar.gz $(LIBVM_HOME)
	@echo "Created $(LIBVM_NAME).tar.gz"
