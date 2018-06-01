#
# ZDS II Make File - ez80f91_thuria_demo, Debug - RAM
#

CC = @C:\PROGRA~1\ZILOG\ZDSII_~1.0\bin\eZ80cc
ASM = @C:\PROGRA~1\ZILOG\ZDSII_~1.0\bin\eZ80asm
LINK = @C:\PROGRA~1\ZILOG\ZDSII_~1.0\bin\eZ80link
LIB = @C:\PROGRA~1\ZILOG\ZDSII_~1.0\bin\eZ80lib
WEBTOC = @C:\PROGRA~1\ZILOG\ZDSII_~1.0\bin\mkwebpage

# compiler options
#   -alias -asm -const:ROM -debug -define:_EZ80F91 -NOexpmac -NOfplib
#   -intsrc -intrinsic -keepasm -NOkeeplst -NOlist -NOlistinc
#   -maxerrs:50 -NOmodsect -promote -quiet -strict -NOwatch -optsize
#   -localopt -localcse -localfold -localcopy -peephole -globalopt
#   -NOglobalcse -NOglobalfold -NOglobalcopy -NOloopopt -NOsdiopt
#   -NOjmpopt -usrinc:"..\include" -cpu:EZ80F91 -bitfieldsize:24
#   -charsize:8 -doublesize:32 -floatsize:32 -intsize:24 -longsize:32
#   -shortsize:16 -asmsw:"-cpu:EZ80F91"
CFLAGS = -sw:ez80f91_thuria_demo_Debug_-_RAM.ccsw

# assembler options
#   -debug -genobj -NOigcase -list -NOlistmac -name -pagelen:56
#   -pagewidth:80 -quiet -warn -NOzmasm -sdiopt -cpu:EZ80F91
AFLAGS = -sw:ez80f91_thuria_demo_Debug_-_RAM.asmsw

OUTDIR = C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\src

Debug - RAM: C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_devboard_demo.lod

dellib: 
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_devboard_demo.lod  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_devboard_demo.lod

clean: 
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_devboard_demo.lod  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_devboard_demo.lod
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Buttons.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Buttons.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\cmds.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\cmds.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Console.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Console.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\debug.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\debug.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\game.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\game.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\intro.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\intro.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedMatrix.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedMatrix.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedTimer.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedTimer.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\magic.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\magic.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\main.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\main.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\map.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\map.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\object.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\object.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\rank.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\rank.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\room.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\room.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\special.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\special.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\thuria.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\thuria.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\verb.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\verb.obj

rebuildall: clean Debug - RAM

libonly: dellib Debug - RAM

LIBS = 

OBJS =  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Buttons.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\cmds.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Console.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\debug.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\game.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\intro.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedMatrix.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedTimer.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\magic.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\main.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\map.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\object.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\rank.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\room.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\special.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\thuria.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\verb.obj

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_devboard_demo.lod: $(OBJS)
	 $(LINK)  @C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\ez80f91_thuria_demo.lnk

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Buttons.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Buttons.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Buttons.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\cmds.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\cmds.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdlib.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\cmds.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Console.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Console.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\Console.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\Console.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\debug.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\debug.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdlib.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\debug.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\game.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\game.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\game.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\intro.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\intro.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\intro.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedMatrix.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedMatrix.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedTimer.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedMatrix.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedTimer.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedTimer.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\Console.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\LedTimer.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\magic.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\magic.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\magic.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\main.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\main.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\Buttons.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\Console.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\include\LedTimer.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\main.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\map.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\map.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\map.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\object.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\object.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\object.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\rank.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\rank.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\rank.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\room.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\room.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\room.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\special.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\special.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\special.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\thuria.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\thuria.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdlib.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\thuria.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\verb.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\verb.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\magic.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\object.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\rank.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\room.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\special.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\verb.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\INCLUDE\main.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~7\SRC\verb.c

