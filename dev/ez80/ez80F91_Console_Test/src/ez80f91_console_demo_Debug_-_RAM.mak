#
# ZDS II Make File - ez80f91_console_demo, Debug - RAM
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
CFLAGS = -sw:ez80f91_console_demo_Debug_-_RAM.ccsw

# assembler options
#   -debug -genobj -NOigcase -list -NOlistmac -name -pagelen:56
#   -pagewidth:80 -quiet -warn -NOzmasm -sdiopt -cpu:EZ80F91
AFLAGS = -sw:ez80f91_console_demo_Debug_-_RAM.asmsw

OUTDIR = C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\src

Debug - RAM: C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_devboard_demo.lod

dellib: 
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_devboard_demo.lod  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_devboard_demo.lod

clean: 
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_devboard_demo.lod  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_devboard_demo.lod
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Buttons.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Buttons.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Console.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Console.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedMatrix.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedMatrix.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedTimer.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedTimer.obj
	@if exist C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\main.obj  \
            del C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\main.obj

rebuildall: clean Debug - RAM

libonly: dellib Debug - RAM

LIBS = 

OBJS =  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Buttons.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Console.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedMatrix.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedTimer.obj  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\main.obj

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_devboard_demo.lod: $(OBJS)
	 $(LINK)  @C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\ez80f91_console_demo.lnk

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Buttons.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Buttons.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Buttons.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Console.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Console.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\Console.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\Console.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedMatrix.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedMatrix.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedTimer.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedMatrix.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedTimer.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedTimer.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\Console.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\LedTimer.c

C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\main.obj :  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\main.c  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\Buttons.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\Console.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\include\LedTimer.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\PROGRA~1\ZILOG\ZDSII_~1.0\SAMPLES\EZ80F9~6\SRC\main.c

