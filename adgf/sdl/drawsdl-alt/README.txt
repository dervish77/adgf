README for DrawSdl
------------------

DrawSdl is a demo program for illustrating how to use LibSDL for drawing.  

DrawSdl is also a wrapper "library" to provide useful drawing functions that 
are not natively supplied by LibSDL.

----------------------------------------------------------------------------

Release Notes:

0.5.0
    - Supports demos for triangles, keys, mouse, and animation
    - Supports demos for boxes, circles, bitmaps, and blitters
    - Supports demos for pixels, lines, and a full "wow" demo

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.c      - wrapper code for drawing with LibSDL
    draw-sdl.h      - function prototypes and useful defines

    main.c          - main demo program

    module.mk	    - make include file

    Makefile	    - makefile to make target 'drawsdl' for Unix systems

    CHANGES.txt     - revision history
    README.txt      - this file

    fun.bmp         - bitmap images for bitmap demo and full demo
    odie.bmp
    texture.bmp
    triton.bmp
    ufo.bmp

----------------------------------------------------------------------------

To make and install DrawSdl executable:

	cd drawsdl

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	drawsdl [-h][-g][-v]

 		-h                  display help
		-g <demo>           display graphics demo
                -v                  display version banner

	  <demo>
		1   pixels 
		2   lines 
		3   boxes
		4   triangles
		5   circles
		6   bitmaps
		7   blitters
		8   keys
		9   mouse
		10  animation
		99  full demo

----------------------------------------------------------------------------

Usage Examples:

	% drawsdl		    {enter interactive menu}

	% drawsdl -g 2              {directly run specified demo}

----------------------------------------------------------------------------
last update 
02/12/2009


