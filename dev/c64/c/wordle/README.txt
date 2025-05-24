README for Wordle Program
-------------------------

Wordle is a clone of the popular word guessing game.

----------------------------------------------------------------------------

Files within this directory:

	README.txt	    - this file
	CHANGES.txt	    - revision history
	LICENSE.txt	    - copying/license terms

	main.c		    - main program 

	game.c	        - game functions
	game.h

	Makefile	    - makefile to make target 'wordle' for Unix systems

----------------------------------------------------------------------------

To unpack distribution file:

	gunzip wordle_0.1.tar.gz

	tar xvf wordle_0.1.tar
	
----------------------------------------------------------------------------

To make executable:

	cd wordle
	
	make

----------------------------------------------------------------------------

To make and run unit test:

	cd wordle
	
	make test

----------------------------------------------------------------------------

To make and install executable and man page:

	cd wordle

	<edit makefile to change installed directory if desired>
	
	make all

----------------------------------------------------------------------------

To use program:

	wordle [-h]|[-v]]


----------------------------------------------------------------------------
last update: May 17, 2025

