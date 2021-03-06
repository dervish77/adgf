@echo off
REM compile.bat
REM
REM Compile C code using cc65 for C64 emulators
REM

REM SETLOCAL ENABLEDELAYEDEXPANSION

set COMPILER=C:\cc65\bin\cc65
set ASSEMBLER=C:\cc65\bin\ca65
set LINKER=C:\cc65\bin\ld65

REM Compile each .C file into assembler.
for /f %%a IN ('dir /b *.c') do %COMPILER% -g -O -I C:\cc65\include -t c64 %%a -o .\Debug\%%~na.s

REM Assemble each .S file an object file.
for /f %%a IN ('dir /b .\Debug\*.s') do %ASSEMBLER% .\Debug\%%a
for /f %%a IN ('dir /b *.s') do %ASSEMBLER% -t c64 %%a -o .\Debug\%%~na.o

REM Link all the .O files together
set FILES=
for /f %%a IN ('dir /b .\Debug\*.o') do set FILES=!FILES! .\Debug\%%a
%LINKER% -t c64 -Ln .\Debug\Commodore.lbl -m .\Debug\Commodore.map -o .\Debug\Commodore C:\cc65\lib\c64.o %FILES% C:\cc65\lib\c64.lib

