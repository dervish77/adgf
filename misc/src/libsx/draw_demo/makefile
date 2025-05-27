#
#
include ../libsx_defs

draw_demo : draw_demo.o
	$(CC) -o draw_demo draw_demo.o $(LIBS)

draw_demo.o : draw_demo.c libsx.h

clean:
	rm -f *.o *~ core draw_demo
