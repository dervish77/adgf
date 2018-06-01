README for DrawSdl
------------------

DrawSdl is a demo program for illustrating how to use LibSDL for drawing.  

DrawSdl is also a wrapper "library" to provide useful drawing functions that 
are not natively supplied by LibSDL.

----------------------------------------------------------------------------

Release Notes:

0.7.0
    - Supports demos for triangles, keys, mouse, and animation
    - Supports demos for boxes, circles, bitmaps, and blitters
    - Supports demos for pixels, lines, and a full "wow" demo
    - Supports demos for text (via draw-text.cpp)
    - Supports demos for polygons
    - Supports demos for sprites

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.cpp    - wrapper code for drawing with LibSDL
    draw-sdl.h

    draw-text.cpp   - wrapper code for drawing text with SDL_ttf
    draw-text.h

    main.cpp        - main demo program
    main.h

    demo.cpp        - demo routines
    demo.h

    module.mk	    - make include file

    Makefile	    - makefile to make target 'drawsdl' for Unix systems

    CHANGES.txt     - revision history
    README.txt      - this file

    fonts/          - fonts directory for ttf fonts

    images/         - images directory for bitmap images


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
		11  text
                12  polygons
		99  full demo

----------------------------------------------------------------------------

Usage Examples:

	% drawsdl                   {enter interactive menu}

	% drawsdl -g 2              {directly run specified demo}

----------------------------------------------------------------------------

Developer Examples:

Basic Usage
-----------

#include <stdio.h>
#include "draw-sdl.h"

int main()
{
    int w, h;       
  
    // initialize the drawing package
    // set screen size of 640x480 at 16 bits per pixel
    drawInit(640, 480, 16);
    
    // retrieve screen width and height for later use
    w = drawGetWidth();
    h = drawGetHeight();

    // clear the background
    drawBackground(CLR_BLACK);

    // draw diagonal line
    drawLine( CLR_WHITE,  0, 0,  w, h );

    // call this to make everything appear on the screen
    drawSwapBuffers();
  
    // call this to wait for user to 'X' out
    drawWaitQuit();

    return(0);
}


----------------------------------------------------------------------------
last update 
11/12/2010


