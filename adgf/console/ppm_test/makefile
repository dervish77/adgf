# makefile for PPM_test program
#

CC=cc

OBJECTS1 = ppm_test.o ppm.o 

LIBS	= -lm
CFLAGS  = -O

TARGETS = ppm_test


# make test programs

default: $(TARGETS)

ppm_test: $(OBJECTS1)
	$(CC) -o $@ $(OBJECTS1) $(LIBS)

ppm_test.o : ppm_test.c ppm.h

ppm.o : ppm.c ppm.h

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGETS) *.log


# make distribution file

PPM_TEST_HOME = ppm_test
PPM_TEST_NAME = ppm_test_1.0

TAR_FILES = 	\
	$(PPM_TEST_HOME)/README		\
	$(PPM_TEST_HOME)/makefile	\
	$(PPM_TEST_HOME)/ppm_note.txt	\
	$(PPM_TEST_HOME)/*.c		\
	$(PPM_TEST_HOME)/*.h		\
	$(PPM_TEST_HOME)/*.ppm

tar:
	cd .. ; \
	tar -cvf $(PPM_TEST_NAME).tar $(TAR_FILES) ; \
	gzip $(PPM_TEST_NAME).tar ; \
	mv $(PPM_TEST_NAME).tar.gz $(PPM_TEST_HOME)
