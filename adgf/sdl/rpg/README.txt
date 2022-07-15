README for RPG
--------------

RPG is a version of a 2D tile-based role playing game using LibSDL for 
drawing.  

----------------------------------------------------------------------------

Release Notes:
    - includes title screen
    - includes current level screen
    - includes game over screen
    - includes game play screens and support functions 

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.cpp    - wrapper code for drawing with LibSDL
    draw-sdl.h      - function prototypes and useful defines

    game.cpp        - game logic code
    game.h

    main.cpp        - main program
    main.h

    random.cpp      - random number routines
    random.h

    screens.cpp     - screen drawing code
    screens.h

    vecmath.cpp     - vector math routines
    vecmath.h

    version.h       - version header

    module.mk	    - make include file

    Makefile	    - makefile to make target 'drawsdl' for Unix systems

    CHANGES.txt     - revision history
    README.txt      - this file

    art/*.bmp       - art assett bitmaps for in game use

    assetts.ppt     - original drawings for art assetts 

----------------------------------------------------------------------------

To make and install RPG executable:

	cd rpg

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	rpg [-h][-v]

                -h                  display help
                -v                  display version

----------------------------------------------------------------------------

Usage Examples:

	% rpg              {default - start single player game}

----------------------------------------------------------------------------
last update 
04/08/2012


