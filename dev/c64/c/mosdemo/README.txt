README for MOS (Mainloop OS)
----------------------------


MOS is an example of how to create a mainloop type of tasking OS
loop.  This example is a bit more advanced than simply calling 
a series of function calls within a while loop.  This example uses a
task list where each entry in the list has a pointer to a task control
block for that task.  Thus this example supports dynamic task creation
and deletion, tasks can suspend and resume, and can be blocked by i/o.
Though far from a real RTOS it has the basics to support a small 
application that has a need to create tasks on the fly. 


----------------------------------------------------------------------------

Features:

    - complete source code
    - create and delete tasks
    - suspend and resume tasks
    - block and unblock tasks
	
    - allocate memory block per task
    - send and receive messages between tasks
    - broadcast messages to all tasks
	
    - user tunable OS task parameters
    - user controllable OS timer tick
	
    - sequence task list once mode
    - sequence task list forever mode
    - sequence task list via timeslice
	
    - built-in keyboard input support
    - built-in LCD output support
    - built-in terminal output support


----------------------------------------------------------------------------

Files within this directory:

	CHANGES.txt			- revision history
	LICENSE.txt			- license and copying requirements
	README.txt			- this file
	TODO.txt			- todo list

	coverage.sh  		- unit test coverage script 

	Makefile			- makefile to make target 'MOS' for Unix systems

	mos.mk              - make include file

	bin/                - output directory for MOS executables

	demo/		        - demo program for MOS library (Linux/Cygwin only)

	include/            - output directory for MOS library headers

	lib/                - output directory for MOS library

	src/ports/common/   - source code for MOS library

	src/ports/arduino/	- port for Arduino Uno
	src/ports/arm/		- port for ARM processor
	src/ports/avr/		- port for AVR micro (AVR Butterfly Board)
	src/ports/c64/		- port for C64 emulator 
	src/ports/cygwin/	- port for Cygwin host
	src/ports/ez80/		- port for EZ80 development board
	src/ports/linux/	- port for Linux host
	src/ports/sh4/		- port for SH4 eval board
	
	test/               - source code for MOS Test App (Linux/Cygwin only)

	unit/		        - unit test program for MOS library (Linux/Cygwin only)

----------------------------------------------------------------------------

To unpack distribution file:

	gunzip mos.tar.gz

	tar xvf mos.tar
	
----------------------------------------------------------------------------

To make and install MOS library and executables:

	cd mos

	<edit Makefile to change installed directory if desired>
	<edit mos.mk to change compilers if necessary>

    make                                builds default PORT=linux	

	make PORT=<port>                    builds specified port

	make PORT=<port> all                builds and installs to "bin"

	make PORT=<port> coverage           builds and runs code coverage analysis

    make help                           get additional build help

----------------------------------------------------------------------------

To use MOS demos and test programs

	demo/mosdemo [ -i ]

    test/mosapp

	unit/mosunit

----------------------------------------------------------------------------

Examples:

ARG_STRUCT dummyargs = 
{
	1,
	2,
	3
};

void task1( void *args )
{
   int id = mosGetTaskId( "task1" );
   mosPrint("task1 task, id = %d\n", id);
}

void task2( void *args )
{
   int id = mosGetTaskId( "task2" );
   int size = mosGetTaskMemSize( id );
   mosPrint("task2 task, id = %d, memsize = %d\n", id, size);
}

int main(int argc, char **argv)
{
   int taskid;

   mosInitTasking();

   taskid = mosCreateTask( "task1", &task1, &dummyargs, 32 );
   taskid = mosCreateTask( "task2", &task2, &dummyargs, 64 );

   mosSequenceTaskListOnce();

   mosFreeTasking();
   exit(0);
}


----------------------------------------------------------------------------

Notes:


----------------------------------------------------------------------------
last update 
09/21/2012

