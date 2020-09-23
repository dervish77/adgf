README for Emboss
-----------------

Emboss demo program using LibSDL for drawing.  

Demonstrates using bump mapping technique for embossing a graphics file.

----------------------------------------------------------------------------

Release Notes:
    - mocked up behavior to statically show input, map, and output images

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.cpp    - wrapper code for drawing with LibSDL
    draw-sdl.h      - function prototypes and useful defines

    emboss.cpp      - embossing functions
    emboss.h

    image.cpp       - image file input and output (BMP only)
    image.h

    main.cpp        - main program
    main.h

    module.mk	    - make include file

    Makefile	    - makefile to make target for Unix systems

    CHANGES.txt     - revision history
    LICENSE.txt     - license/copying policy
    README.txt      - this file
    TODO.txt        - todo list

----------------------------------------------------------------------------

To make and install target executable:

	cd emboss

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	emboss [-h][-v] [-i input-file] [-m map-file] [-o output-file]

                -h                  display help
                -v                  display version

                -i input-file       input image {default "input.bmp"}
                -m map-file         bump map file {default "map.bmp"}
                -o output-file      output image {default "output.bmp"}

----------------------------------------------------------------------------

Usage Examples:

	% emboss              {default - emboss using default file names}

----------------------------------------------------------------------------

Short cut keys:

    a       view all images

    i       view input image

    m       view map image

    o       view output image

    q,x     quit/exit program

    r       repeat processing

----------------------------------------------------------------------------

Screen layout:


  view all mode
    +-----------------------------------------------------------+
    |                                                           |
    |                                                           |
    |                                                           |
    |     Input                 Map                Output       |
    |     Image                Image               Image        |
    |                                                           |
    |                                                           |
    |                                                           |
    +-----------------------------------------------------------+


  view individual mode
    +-----------------------------------------------------------+
    |                                                           |
    |                                                           |
    |                                                           |
    |                        Individual                         |
    |                          Image                            |
    |                                                           |
    |                                                           |
    |                                                           |
    +-----------------------------------------------------------+


----------------------------------------------------------------------------
last update 
04/07/2011


