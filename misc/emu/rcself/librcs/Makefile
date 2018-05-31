OBJS = awlib$(OEXT) \
	complex$(OEXT) \
	date$(OEXT) \
	db$(OEXT) \
	vector$(OEXT) \
	math$(OEXT) \
	matrix$(OEXT) \
	file$(OEXT) \
	kernel$(OEXT) \
	mstring$(OEXT)\
	mterm$(OEXT) \
	options$(OEXT) \
	random$(OEXT) \
	rgb$(OEXT) \
	vmem$(OEXT) \
	widgets$(OEXT) \
	xhelpers$(OEXT) \
	xml$(OEXT)
#	graph3d$(OEXT) \
#	graph$(OEXT)\

# Unix
PROJECT = libRcs.so.1
CC = gcc
CCPP = g++
LINK = gcc
LIBPATH = -L/usr/lib
CFLAGS = -Wall
LFLAGS = 
OEXT = .o
SOURCE = .c
INCPATH = -I/usr/include -I/usr/X11/include
RMCMD = rm
CP = cp
LIBCMD = tlib libRcs @libcmds
DEFS = -DUNIX -DX
LIBCMD = $(CC) -shared -Xlinker -h -Xlinker libRcs.so.1 $(OBJS) -o libRcs.so.1
#DEFS = -DUNIX -DSOLARIS -DX
#LIBCMD = $(CC) -Xlinker -G -h $(PROJECT) $(OBJS) -o $(PROJECT)

# Borland C
#PROJECT = libRcs.lib
#CC = bcc
#CCPP = bcc
#LINK = bcc
#LIBPATH = -L\usr\lib
#CFLAGS = -k -mh
#LFLAGS = -lx
#OEXT = .obj
#SOURCE = .c
#INCPATH = -I\usr\include
#RMCMD = command /c erase
#CP = command /c copy
#LIBCMD = tlib libRcs @libcmds
#DEFS = -Dmsdos -DMSDOS


#libRcs.so.1: $(MEMBERS)
#    $(CC) -shared -Xlinker -h -Xlinker libRcs.so.1 $(MEMBERS) -o libRcs.so.1

$(PROJECT): $(OBJS)
	-$(RMCMD) $(PROJECT)
	$(LIBCMD)

.c$(OEXT):
	$(CC) $(LIBPATH) $(INCPATH) $(CFLAGS) $(DEFS) -c $<

.cpp$(OEXT):
	$(CCPP) $(LIBPATH) $(INCPATH) $(CFLAGS) $(DEFS) -c $<

install:
	$(CP) $(PROJECT) /usr/local/lib
	$(CP) librcs.h /usr/local/include
	chmod a+r /usr/local/lib/$(PROJECT)
	chmod a+r /usr/local/include/librcs.h

clean:
	-$(RMCMD) *$(OEXT)
	-$(RMCMD) $(PROJECT)

awlib.o: awlib.c librcs.h

