# Object files wiil go in this subdirectory
OBJ_DIR	     =  objects
INC_DIR	     =  ../../include


# An ANSI C compiler: gnu's "gcc"
CC = gcc

# The UNIX flag must be defined for UNIX implementations
CPPFLAGS = -DUNIX -DX11 -I$(INC_DIR) -I/usr/openwin/include -I/usr/openwin/share/include


# User-defined; to pass options in to the compilation, say things
#   like 'make CFLAGS=-g'.  Put flags here to make them permanent.

#CFLAGS 	= 

# Very important!  The first flag (struct-return) makes it safe to link
#  gcc objects with cc objects.
GCCFLAGS = -fpcc-struct-return 


#####################################################################

TARGET = libsrgp.a

HFILES = 		\
srgplocal.h		\
srgp_sphigs.h		\
srgppublic.h		\
srgp_errtypes.h		\
macros.h		\
geom.h			\
default_patterns.h

OBJECTS = 		\
srgp_attrib.o		\
srgp_canvas.o		\
srgp_color_X.o		\
srgp_cursor.o		\
srgp_echo_X.o		\
srgp_error.o		\
srgp_font.o		\
srgp_input.o		\
srgp_input_X.o		\
srgp_inquire.o		\
srgp_marker.o		\
srgp_output.o		\
srgp_pattern.o		\
srgp_raster.o		\
srgp_state.o		\
srgp_state_X.o		\
geom.o

#####################################################################


PATH_OBJECTS =  $(OBJECTS:%=$(OBJ_DIR)/%)
PATH_HEADERS =  $(HFILES:%=$(INC_DIR)/%)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(GCCFLAGS) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/$*.o $*.c

$(TARGET):  $(PATH_OBJECTS)
	echo $(PATH_OBJECTS)
	ar rv $(TARGET) $(PATH_OBJECTS)
	ranlib $(TARGET)
	cp $(TARGET) ../../lib
	mv $(TARGET) $(OBJ_DIR)

remove:
	/bin/rm -f $(PATH_OBJECTS)
	/bin/rm -f *~

clean:  remove $(TARGET)

$(PATH_OBJECTS): $(PATH_HEADERS)

