===============================================================================
                eZ80F91_DevBoard_Demo Sample Project Readme
===============================================================================

The eZ80F91_DevBoard_Demo sample project is provided to illustrate two typical
build configurations used by ZDS II - eZ80 developers.

The two typical build configurations are:
 1. Debug - RAM
 2. Release - Flash

1. The 'Debug - RAM' configuration is used for emulation with the eZ80F91 module
on the eZ80 Development Platform.  There are no target-resident program
dependencies for using this configuration with the emulator.

2. The 'Release - Flash' configuration is used to create an Intel Hex file for
loading internal flash with the ZDSII Integrated Flash Loader.  This
configuration's target memory range was designed to create a memory image that
will reside and start execution from internal flash starting at address 0000h.
This allows the program to be stored and executed from flash without any
other target-resident program dependencies.
   Use the internal flash device option in the ZDS II Integrated Flash Loader
for loading the program into flash.