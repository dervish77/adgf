README for SicDacLoe
--------------------

SicDacLoe is a version of Tic Tac Toe using LibSDL for drawing.  

----------------------------------------------------------------------------

Release Notes:
    - includes title screen
    - includes player mode selection screen
    - includes game play board and move selection
    - includes victory screen
    - includes single player and two player modes
    - includes support for computer skill level

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.c      - wrapper code for drawing with LibSDL
    draw-sdl.h      - function prototypes and useful defines

    game.c          - game logic code
    game.h

    main.c          - main program
    main.h

    screens.c       - screen drawing code
    screens.h

    module.mk	    - make include file

    Makefile	    - makefile to make target 'drawsdl' for Unix systems

    CHANGES.txt     - revision history
    README.txt      - this file

    *.bmp           - art assett bitmaps for in game use

    assetts.ppt     - original drawings for art assetts 

----------------------------------------------------------------------------

To make and install SicDacLoe executable:

	cd sicdacloe

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	sicdacloe [-h][-p <1,2>][-v]

                -h                  display help
                -p <1,2>            number of players
                -v                  display version

----------------------------------------------------------------------------

Usage Examples:

	% sicdacloe              {default - start single player game}

	% sicdacloe -p 2         {start two player game}

----------------------------------------------------------------------------
last update 
02/13/2009


