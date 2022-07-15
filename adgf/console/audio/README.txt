README for AudioDemo
--------------------

AudioDemo is an implementation of an audio processing library for use on a 
integer based DSP device such as TI's C5515.  This code tree is a simulation 
of such a system mainly intended for unit testing the audio library functions.


----------------------------------------------------------------------------

Release Notes:
    - none

----------------------------------------------------------------------------

Files within this directory:

    audioCore.cpp      - interface functions to audio processing library
    audioCore.h

    audioBlocks.cpp    - processing blocks for audio processing library
    audioBlocks.h

    audioFilter.cpp    - filter functions for audio processing library
    audioFilter.h

    audioMixer.cpp     - mixer functions for audio processing library
    audioMixer.h

    audioModel.cpp     - model functions for audio processing library
    audioModel.h

    audioUtils.cpp     - utility functions for audio processing library
    audioUtils.h

    audioWaveform.cpp  - waveform generation functions for audio processing library
    audioWaveform.h

    main.cpp           - main program, including demo functions
    main.h

    random.cpp         - random number utlities
    random.h

    module.mk	       - make include file

    Makefile	       - makefile to make target 'audiodemo' for Unix systems

    CHANGES.txt        - revision history
    README.txt         - this file

----------------------------------------------------------------------------

To make and install AudioDemo executable:

	cd audio

	<edit Makefile to change installed directory if desired>
	<edit module.mk to change compilers if necessary>
	
	make realclean
	make all

----------------------------------------------------------------------------

Usage:
	dspdemo [-h][-v] [-f|-s|-w]

                -h                  display help
                -v                  display version
   
                -f                  run audio filter test
                -s                  run audio sample test
                -w                  run audio waveform test

----------------------------------------------------------------------------

Usage Examples:

	% dspdemo              {default - run all demos}

----------------------------------------------------------------------------
last update 
02/29/2012


