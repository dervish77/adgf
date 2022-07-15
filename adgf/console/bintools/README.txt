README for BinTools
-----------------------------------------

This directory contains various binary file utilities.


Contents:

	COPYING.txt	- copying policy

	Makefile	- makefile

	README.txt	- this file

	REVISION.txt	- revision history

	bin/		- binary output directory

	man/		- man pages

	src/append.c	- append binary file with specified num bytes
	
	src/bincat.c	- concatenates two binary files

	src/bindiff.c	- diff's two binary files

	src/bindump.c	- display contents of binary file

	src/bingen.c	- generate binary file

	src/binjoin.c	- joins binary chunks

	src/binsplit.c	- splits binary file into chunks

	src/bintoc.c	- convert raw binary to "C" array

	src/crcgen.c	- generates CRC of binary file

	src/prepend.c	- prepend binary file with specified num bytes

	src/srectoc.c	- convert SREC file to "C" array


--------------------------------------------------------------------

Building:

	- "make all" to build all utilities

	- "make test" to build and unit test all utilities

	- "make install" to build and install utilities to ./bin

Notes:

	- currently optimized to build under Cygwin

--------------------------------------------------------------------

Usage:

	append [-h] [-n bytes] [-d data] [-i file] [-o file]

	bincat [-h] [-a file] [-b file] [-o file]

	bindiff file1 file2

	bindump [-h] [-a] [-n NNN] [-r BB] file

	bingen [-h] [-n bytes] [-a | -c | -d data] [-o file]

	binjoin [-h] [-r file] [-o file]

	binsplit [-h] [-n bytes] [-i file] [-r file]

	bintoc [-h] [-i file] [-o file] [-a name]

	crcgen file

	prepend [-h] [-n bytes] [-d data] [-i file] [-o file]

	srectoc -I <srecord-infile> -O <cfileout> -A <arrayname>

--------------------------------------------------------------------

last updated:
August 10, 2004 - BSL
