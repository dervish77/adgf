README for HwSim
----------------

HwSim is a collection of program modules used to simulated physical hardware 
input and output devices such as buttons, LCD displays, and OLED displays.

The code uses the DrawSdl as a graphics interface library on top of LibSDL.


----------------------------------------------------------------------------

Release Notes:
    - skeleton of ButtonSim app to get build system framework working

----------------------------------------------------------------------------

Files within this directory:

    demo/           - combination demo

    buttonsim/      - simulation of physical buttons
    lcdsim/         - simulation of LCD character display
    oledsim/        - simulation of OLED graphic display

    fonts/          - fonts used by simulation apps
    images/         - images used by simulation apps

    bin/
    include/
    lib/
    
    module.mk	    - make include file

    Makefile	    - top level makefile

    CHANGES.txt     - revision history
    README.txt      - this file
    TODO.txt        - features left todo

----------------------------------------------------------------------------

To make and install HwSim executables:

	cd hwsim

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

	<this will build all libraries, modules, and executables>

----------------------------------------------------------------------------

Usage:
	hwsim [-h][-v]

                -h                  display help
                -v                  display version

----------------------------------------------------------------------------

Usage Examples:

	% bin/hwsim              {default - start demo}

----------------------------------------------------------------------------
last update 
02/23/2011


