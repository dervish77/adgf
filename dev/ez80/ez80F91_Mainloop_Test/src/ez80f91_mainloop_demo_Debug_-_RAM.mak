#
# ZDS II Make File - ez80f91_mainloop_demo, Debug - RAM
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
CFLAGS = -sw:ez80f91_mainloop_demo_Debug_-_RAM.ccsw

# assembler options
#   -debug -genobj -NOigcase -list -NOlistmac -name -pagelen:56
#   -pagewidth:80 -quiet -warn -NOzmasm -sdiopt -cpu:EZ80F91
AFLAGS = -sw:ez80f91_mainloop_demo_Debug_-_RAM.asmsw

OUTDIR = C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\src

Debug - RAM: C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_devboard_demo.lod

dellib: 
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_devboard_demo.lod  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_devboard_demo.lod

clean: 
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_devboard_demo.lod  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_devboard_demo.lod
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Buttons.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Buttons.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Console.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Console.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\demo.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\demo.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedMatrix.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedMatrix.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedTimer.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedTimer.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\main.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\main.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mainloop.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mainloop.obj
	@if exist C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mloop.obj  \
            del C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mloop.obj

rebuildall: clean Debug - RAM

libonly: dellib Debug - RAM

LIBS = 

OBJS =  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Buttons.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Console.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\demo.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedMatrix.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedTimer.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\main.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mainloop.obj  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mloop.obj

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_devboard_demo.lod: $(OBJS)
	 $(LINK)  @C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\ez80f91_mainloop_demo.lnk

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Buttons.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Buttons.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Buttons.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Console.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Console.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\Console.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\Console.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\demo.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\demo.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\INCLUDE\demo.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\INCLUDE\mloop.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdlib.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\demo.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedMatrix.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedMatrix.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedMatrix.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedTimer.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedMatrix.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedTimer.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedTimer.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\Console.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedMatrix.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\LedTimer.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\main.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\main.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\Buttons.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\Console.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedMatrix.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\include\LedTimer.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\eZ80L92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80190.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F91.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F92.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ez80F93.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\main.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mainloop.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mainloop.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\INCLUDE\demo.h  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\INCLUDE\mloop.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\ctype.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mainloop.c

C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mloop.obj :  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mloop.c  \
            C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\INCLUDE\mloop.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\Stdarg.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdio.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\stdlib.h  \
            C:\PROGRA~1\ZILOG\ZDSII_~1.0\include\string.h
	 $(CC)  $(CFLAGS) C:\MYDOCU~1\BRIAN\DEV\EZ80\EZ80F9~3\SRC\mloop.c

