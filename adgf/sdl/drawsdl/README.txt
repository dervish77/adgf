README for DrawSdl
------------------

DrawSdl is a wrapper "library" to provide useful drawing functions that 
are not natively supplied by LibSDL, such as lines, circles, etc.  The intent
is to enable the development of graphics for games in an easy to use and 
easy to understand manner.

----------------------------------------------------------------------------

Features:
    - Supports demos for triangles, keys, mouse, and animation
    - Supports demos for boxes, circles, bitmaps, and blitters
    - Supports demos for pixels, lines, and a full "wow" demo
    - Supports demos for text (via draw-text.cpp)
    - Supports demos for polygons
    - Supports demos for sprites

----------------------------------------------------------------------------

Files within this directory:

    CHANGES.txt          - revision history
    LICENSE.txt          - license/copying policy
    README.txt           - this file
    TODO.txt             - todo list

    coverage.sh          - unit test coverage script 

    Makefile	         - makefile to make target 'drawsdl' for Unix systems

    module.mk	         - make include file

    bin/                 - output directory for MOS executables

    demo/main.cpp        - main demo program
    demo/main.h
    demo/demo.cpp        - demo routines
    demo/demo.h

    fonts/               - fonts directory for ttf fonts

    images/              - images directory for bitmap images

    include/             - output directory for MOS library headers

    lib/                 - output directory for MOS library

    src/draw-sdl.cpp     - library source code for drawing with LibSDL
    src/draw-sdl.h
    src/draw-text.cpp    - library source code for drawing text with SDL_ttf
    src/draw-text.h

    unit/main.cpp        - main unit test program
    unit/main.h
    unit/unit.cpp        - unit test routines
    unit/unit.h

----------------------------------------------------------------------------

To make and install DrawSdl executable:

	cd drawsdl

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all
	make install

----------------------------------------------------------------------------

To make and run DrawSdl unit tests, code coverage, code profiling:

	cd drawsdl

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make test

	make realclean
	make gcov

	make realclean
    make gprof

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
        13  sprites
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
04/19/2011


