README for DspDemo
------------------

DspDemo is a simulation of DSP functions with a graphical display for 
showing the effects on waveforms before and after processing by DSP 
algorithms.

----------------------------------------------------------------------------

Release Notes:
    - none

----------------------------------------------------------------------------

Files within this directory:

    draw-sdl.cpp    - wrapper code for drawing with LibSDL
    draw-sdl.h      - function prototypes and useful defines

    filter.cpp      - implementation of DSP filters
    filter.h

    main.cpp        - main program, including demo function
    main.h

    mixer.cpp       - waveform mixing functions
    mixer.h

    random.cpp      - random number utlities
    random.h

    waveform.cpp    - waveform generation functions
    waveform.h

    module.mk	    - make include file

    Makefile	    - makefile to make target 'dspdemo' for Unix systems

    CHANGES.txt     - revision history
    README.txt      - this file

----------------------------------------------------------------------------

To make and install DspDemo executable:

	cd dsp

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	dspdemo [-h][-v]

                -h                  display help
                -v                  display version

----------------------------------------------------------------------------

Usage Examples:

	% dspdemo              {default - start demo}

----------------------------------------------------------------------------
last update 
06/30/2011


