@echo off
rem Install script for Dungeons of Thuria game
rem --------------------------------------------------------------
rem

echo ...
echo ... Installing Dungeons of Thuria game executable ...
if not exist c:\thuria mkdir c:\thuria
copy thuria.exe c:\thuria\thuria.exe
copy readme.txt c:\thuria\readme.txt
copy uninstall.bat c:\thuria\uninstall.bat

:group
echo ... Adding program group ...
if exist c:\WINDOWS\"Start Menu"\Programs\Thuria goto skip2
mkdir c:\WINDOWS\"Start Menu"\Programs\Thuria
copy Dungeons_of_Thuria.lnk c:\WINDOWS\"Start Menu"\Programs\Thuria
copy Readme.lnk c:\WINDOWS\"Start Menu"\Programs\Thuria
goto done

:skip2
echo ... program group already exists ...

:done
echo ...
echo ... Installation is complete.