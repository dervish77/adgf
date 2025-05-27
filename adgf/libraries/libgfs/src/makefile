# makefile for LIBGFS -- a GUI for SRGP

#
# if you have trouble building, edit the file 'libgfs_defs'
#
include ../libgfs_defs

# 
# you should not need to edit below this line
#

OBJECTS = gsdraw.o gsevent.o gsgadget.o gsprivat.o

TARGET = libgfs

# note that this compiler IS necessary when using GNU gcc
GCCFLAGS = -fpcc-struct-return

LIBS	= -lsrgp -lX11 -lm
TEST_LIBS = -lgfs -lsrgp -lX11 -lm

LDFLAGS = $(SRGP_LIB_LOC) $(LIBGFS_LIB_LOC)

INCLUDE = $(SRGP_INCLUDE_LOC) $(LIBGFS_INCLUDE_LOC) 

CFLAGS  = -D_POSIX_SOURCE $(DEBUG) 


# 
# begin dependancies
#

default: $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	rm -f $(TARGET).a
	ar rc $(TARGET).a $(OBJECTS) 

gsdraw.o: gsdraw.c ../include/gspublic.h ../include/gsprivat.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c gsdraw.c

gsevent.o: gsevent.c ../include/gspublic.h ../include/gsprivat.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c gsevent.c

gsgadget.o: gsgadget.c ../include/gspublic.h ../include/gsprivat.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c gsgadget.c

gsprivat.o: gsprivat.c ../include/gspublic.h ../include/gsprivat.h
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) -c gsprivat.c

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ core $(TARGET).a

