//****************************************************************************
//
//  Demo implementation of Conway's Game of Life.
//
//	File:	main.h
//
//	Usage:	life [-h|-v]|[-f <file>|-p #|-r #]
//
//	Options:
//	        -h	    - get options help
//              -v          - display version
//
//              -f <file>   - use custom pattern from file
//
//	        -p #        - use pre-defined pattern
//
//              -r #        - use alternate rules
//
//	Revisions:
//	  0.0 09/25/2008  Originated
//
//****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"

int main(int argc, char *argv[])
{
   mymain myMain;

   myMain.parseArgs(argc, argv);
   myMain.printBanner(argv[0],VERSION);
   myMain.doProgram();
   
   exit(0);
};

// EOF
