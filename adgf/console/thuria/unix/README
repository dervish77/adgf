Welcome to Dungeons Of Thuria - version 1.1 
__________________________________________________________________________


1.0 Introduction

   This is a game of interactive fiction in the spirit of those wonderful
games from Infocom.  This game began life as a tribute to the games like
Zork(tm) and others back when the author's only computer was a lowly
Commodore 64.  It was originally written in Basic, and somewhat limited
due to the 64's small memory size.


2.0 The Story of Dungeons of Thuria

   The story of "Thuria" is should be familiar to those who spent countless
hours painstakingly drawing maps for Adventure or Zork in the wee hours
of the morning when they should have been studying or sleeping.  

   You are deposited in a mysterious land with only a single clue as to 
how to get home.  You find a ragged note which describes how to find a portal
which will take you back to your own world.  Of course, the way home is 
riddled with puzzles and deadly traps.


3.0 Playing the Game

   The section below called "Commands:" describes most the available 
commands.  There are several undocumented commands which will only work
with specific objects.  The current command parser cannot cope with 
a natural language style of commands.  Instead, nearly all commands 
are either one or two words.  Single word commands are usually movement
commands (i.e. "n" meaning go north) or implied object commands (i.e. "on"
meaning turn lamp on).  Two words commands are used to do something with
an object (i.e. "take nail" or "wave wand").  There are also commands for 
saving and loading your current game, listing the objects you are carrying, 
and toggling room description modes. 


4.0 Special Note to Code Hackers

   The intent was to develop this game using something of a generic game
engine and command parser, so that other games could be created just
by editing the game data files:

	map.c, room.c, object.c, special.c, magic.c, rank.c, verb.c

There is some support for special effects type objects like magic words, 
spells, and magical objects.  Please refer to the header of each game 
data file for more information on these effects.  Warning, altering these 
effects will require hacking the game engine source code (i.e. cmds.c).  
Also note that only the source to the Unix version is provided.


Hope you enjoy the game!

Brian Lingard
November 06, 1998

__________________________________________________________________________

To unpack and build the game (Unix version):

	mv thuria.tgz thuria.tar.gz
	gunzip thuria.tar.gz
	tar xvf thuria.tar
	cd thuria/unix
	{edit thuria.mk for which C compiler to use, if necessary}
	make

To install the game (Unix version):

	cd thuria/unix
	{edit thuria.mk for which C compiler to use, if necessary}
	make install

To uninstall the game (Unix version):

	cd thuria/unix
	make uninstall

This code has been successfully compiled on the following Unix systems:

	Linux         1.2.x, 2.0.x
	SunOs/Solaris 5.3, 5.4, 5.5
	SGI Irix      6.2, 6.3
	GnuWin32      b18
	LynxOS        3.0.0

__________________________________________________________________________

Running the game (Unix version):

    usage

	thuria [-h] [-n] [-s file.save]

    options

	-h		- show help screen

	-n		- suppress introduction

	-s file.sav	- load saved game

__________________________________________________________________________

Commands:

	quit			- quit game

	save			- save current game

	load			- load saved game

	new			- start a new game (abort current game)

	take			- take an object

	drop			- drop an object

	n,s,e,w,u,d		- compass directions, up, down

	run			- run in a random direction

	on			- turn lamp on

	off			- turn lamp off (default)

	look			- repeat room description

	inv			- show inventory

	brief			- enable brief mode (default)

	verbose			- enable verbose mode

	score			- show current score

	diagnose		- show current health

	???			- magic words and other odd actions

{there are single letter equivalents for several commands}

__________________________________________________________________________

Distribution Contents:

	README.unx		- readme for unix version
	READWIN.txt		- readme for windows version

	cheats/map.ppt		- PowerPoint map for cheaters
	cheats/walk.txt		- walkthrough text for cheaters

	win/readme.txt		- this file
	win/revision.txt	- revision history summary
	win/copying.txt		- copying policy and copyleft statement

	win/thuria.exe		- Windows executable

	win/install.bat		- install script
	win/uninstall.bat	- un-install script

	win/Dungeons_of_Thuria.lnk	- shortcut to game
	win/Readme.lnk			- shortcut to readme file

	unix/README		- this file
	unix/REVISION		- revision history summary
	unix/COPYING		- copying policy and copyleft statement

	unix/Makefile		- top level makefile
	unix/thuria.mk		- make file defs

	unix/man/thuria.man	- man page for dungeons of thuria

	unix/src/main.c		- source for main game program
	unix/src/cmds.c		- source for command routines
	unix/src/game.c		- source for game routines
	unix/src/debug.c	- source for debug routines

	unix/src/makefile	- makefile for src directory

	unix/src/intro.c	- game introduction data
	unix/src/map.c		- map data
	unix/src/room.c		- room description data
	unix/src/object.c	- object description data
	unix/src/special.c	- special effects data
	unix/src/magic.c	- magic word data
	unix/src/rank.c		- ranks data
	unix/src/verb.c		- verbs data

	unix/src/main.h		- main header file
	unix/src/room.h		- room id's header file
	unix/src/object.h	- object id's header file
	unix/src/special.h	- special id's header file
	unix/src/magic.h	- magic id's header file
	unix/src/rank.h		- rank id's header file
	unix/src/verb.h		- verb id's header file

__________________________________________________________________________

Last Updated:  November 06, 1998

