README for Kata Program
-----------------------

Kata is a program for trying out coding exercises.  Each new coding exercise can be
invoked by running the program with a coding exercise number as the argument.

----------------------------------------------------------------------------

Files within this directory:

	README.txt	    - this file
	CHANGES.txt	    - revision history
	LICENSE.txt	    - copying/license terms

	main.c		    - main program 

	kata.c	            - kata functions
	kata.h

	Makefile	    - makefile to make target 'soundex' for Unix systems

----------------------------------------------------------------------------

To unpack distribution file:

	gunzip kata_0.1.tar.gz

	tar xvf kata_0.1.tar
	
----------------------------------------------------------------------------

To make executable:

	cd kata
	
	make

----------------------------------------------------------------------------

To make and run unit test:

	cd kata
	
	make test

----------------------------------------------------------------------------

To make and install executable and man page:

	cd kata

	<edit makefile to change installed directory if desired>
	
	make all

----------------------------------------------------------------------------

To use program:

	kata [<kata_number> | [-h]|[-v]]


----------------------------------------------------------------------------
last update: January 22, 2021

