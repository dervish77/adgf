rem A eZ80Acclaim! Assembler Feature--Relist--Example.
rem ================================================================
rem regenerates the listing files with the absolute addresses
rem ----------------------------------------------------------------
rem Instructions:
rem 1. Completely Build the 'eZ80F91_DevBoard_Demo' sample project
rem    using the following build tool parameters:
rem    a. C Compiler
rem       - Generate Assembly Source(.src)
rem    b. Linker
rem       - Generate Map File
rem 2. place this batch file in the source(src) directory in the
rem    the 'eZ80F91_DevBoard_Demo' sample directory.
rem 3. execute this batch file
rem ----------------------------------------------------------------
rem
rem relist application source files
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map .\Buttons.src
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map .\Console.src
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map .\LedMatrix.src
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map .\LedTimer.src
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map .\main.src

rem relist boot module source files
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map ..\..\..\src\rtl\common\cstartup.asm
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map ..\..\..\src\rtl\common\vectors24.asm
..\..\..\bin\ez80asm -NOgenobj -cpu:EZ80F91 -relist:ez80f91_devboard_demo.map ..\..\..\src\rtl\eZ80F91\init_params_f91.asm
