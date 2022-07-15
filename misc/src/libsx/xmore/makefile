#
#  If you have trouble building, edit the file ../libsx_defs and
# change stuff there.  That file gets included everywhere else, so
# you only need to change things there once.
#
include ../libsx_defs

xmore : xmore.c
	$(CC) -O -o xmore xmore.c ../freq/libfreq.a $(LIBS)


clean:
	rm -f *.o *~ core xmore
