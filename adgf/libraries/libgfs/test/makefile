# makefile for test programs using LIBGFS

#
# if you have trouble building, edit the file 'libgfs_defs'
#
include ../libgfs_defs

# 
# you should not need to edit below this line
#

TARGETS = test testpush testtog testdraw testdrw2

# note that this compiler IS necessary when using GNU gcc
GCCFLAGS = -fpcc-struct-return

LIBS	= -lgfs -lsrgp -lX11 -lm

LDFLAGS = $(SRGP_LIB_LOC) $(LIBGFS_LIB_LOC)

INCLUDE = $(SRGP_INCLUDE_LOC) $(LIBGFS_INCLUDE_LOC) 

CFLAGS  = $(DEBUG)


# 
# begin dependancies
#

default: $(TARGETS)

test: test.o
	$(CC) -o $@ $(LDFLAGS) test.o $(LIBS) 

testpush: testpush.o
	$(CC) -o $@ $(LDFLAGS) testpush.o $(LIBS) 

testtog: testtog.o
	$(CC) -o $@ $(LDFLAGS) testtog.o $(LIBS) 

testdraw: testdraw.o
	$(CC) -o $@ $(LDFLAGS) testdraw.o $(LIBS) 

testdrw2: testdrw2.o
	$(CC) -o $@ $(LDFLAGS) testdrw2.o $(LIBS) 

test.o: test.c ../include/gspublic.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c test.c

testpush.o: testpush.c ../include/gspublic.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c testpush.c

testtog.o: testtog.c ../include/gspublic.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c testtog.c

testdraw.o: testdraw.c ../include/gspublic.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c testdraw.c

testdrw2.o: testdrw2.c ../include/gspublic.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c testdrw2.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ $(TARGETS) gsdebug.log
