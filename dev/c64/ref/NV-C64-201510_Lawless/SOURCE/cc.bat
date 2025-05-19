@echo off
: CC65 compile batch file.
: Target system is commodore 64

if !%CC65_INC%x == x goto compile

set CC65_INC=c:\c64\cc65\include
set CC65_LIB=c:\c64\cc65\lib

:compile
c:\c64\cc65\bin\cl65 -v -O -t c64 %1.c
copy %1 c:\c64\drive8






