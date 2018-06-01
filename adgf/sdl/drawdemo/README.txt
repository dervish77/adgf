README for DrawDemo
-------------------

DrawDemo program using LibSDL for drawing.  Basically it's a really simple
paint program.  But it does illustrate the basics of how to create an 
interactive graphics program using DrawSdl as the graphics interface library.

----------------------------------------------------------------------------

Release Notes:
    - includes demo of drawing and user events

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.c      - wrapper code for drawing with LibSDL
    draw-sdl.h      - function prototypes and useful defines

    main.c          - main program, including demo function
    main.h

    module.mk	    - make include file

    Makefile	    - makefile to make target 'drawdemo' for Unix systems

    CHANGES.txt     - revision history
    README.txt      - this file

----------------------------------------------------------------------------

To make and install SicDacLoe executable:

	cd drawdemo

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	drawdemo [-h][-v]

                -h                  display help
                -v                  display version

----------------------------------------------------------------------------

Usage Examples:

	% drawdemo              {default - start demo}

----------------------------------------------------------------------------
last update 
02/23/2011


