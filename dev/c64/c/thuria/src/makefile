# makefile for  Dungeons of Thuria - interactive fiction game

#
# if you have trouble building, edit the file '../thuria.mk'
#
include ../thuria.mk

#
# you should not need to edit below this line
#

OBJS    = main.o intro.o game.o cmds.o debug.o map.o \
          object.o room.o special.o magic.o rank.o verb.o

TARGET  = thuria


# compiler options

# LIBS = -lm
LIBS =

CFLAGS  = -O -Wno-unused-result $(DEBUG)

INCLUDE = -I.


#
# begin dependancies
#

default: $(TARGET)


# executables

thuria: $(OBJS)
	$(CC) -o thuria $(OBJS) $(LIBS)


# object file dependancies

main.o : main.c main.h object.h room.h special.h magic.h rank.h verb.h
	$(CC) $(INCLUDE) $(CFLAGS) -c main.c

game.o : game.c main.h object.h room.h special.h magic.h rank.h verb.h
	$(CC) $(INCLUDE) $(CFLAGS) -c game.c

cmds.o : cmds.c main.h object.h room.h special.h magic.h rank.h verb.h
	$(CC) $(INCLUDE) $(CFLAGS) -c cmds.c

debug.o : debug.c main.h object.h room.h special.h magic.h rank.h verb.h
	$(CC) $(INCLUDE) $(CFLAGS) -c debug.c

intro.o : intro.c main.h
	$(CC) $(INCLUDE) $(CFLAGS) -c intro.c

map.o : map.c main.h
	$(CC) $(INCLUDE) $(CFLAGS) -c map.c

object.o : object.c main.h object.h
	$(CC) $(INCLUDE) $(CFLAGS) -c object.c

special.o : special.c main.h special.h
	$(CC) $(INCLUDE) $(CFLAGS) -c special.c

magic.o : magic.c main.h magic.h
	$(CC) $(INCLUDE) $(CFLAGS) -c magic.c

rank.o : rank.c main.h rank.h
	$(CC) $(INCLUDE) $(CFLAGS) -c rank.c

verb.o : verb.c main.h verb.h
	$(CC) $(INCLUDE) $(CFLAGS) -c verb.c

room.o : room.c main.h room.h
	$(CC) $(INCLUDE) $(CFLAGS) -c room.c


# clean targets

clean:
	rm -f *.o *% *~

realclean:
	rm -f *.o *% *~ *.sav core $(TARGET) $(TARGET).exe
