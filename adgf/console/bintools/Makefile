#*
#*     Module Name:  makefile
#*
#*
#*     These are general purpose utilities for building images.
#*
#*	"make all" to build all utilities
#*
#*	"make test" to build and unit test all utilities
#*
#*
#*/

# set distribution name
DIST = bintools

# set distribution version
VERSION = 2.0

# set files to compile
FILES = append.xxx bincat.xxx bindiff.xxx bindump.xxx bingen.xxx \
	binjoin.xxx binsplit.xxx bintoc.xxx crcgen.xxx prepend.xxx \
	srectoc.xxx

TARGETS = $(FILES:.xxx=)

TARGETS2 = $(FILES:.xxx=.exe)

#PREFIX		= $(CROSS_COMPILE)
PREFIX		=

CC			= $(PREFIX)gcc
AS			= $(PREFIX)as
LD			= $(PREFIX)ld
AR			= $(PREFIX)ar
STRIP		= $(PREFIX)strip

CP			= cp
MV			= mv
RM			= rm
TAR			= tar
GZIP		= gzip

LOCAL_GCC_PATH = $(CC)


# ========================================================================

default: all

all : $(TARGETS)

help:
	@-echo "make all        - builds executables"
	@-echo "make install    - builds and installs to ./bin"
	@-echo "make test       - builds, installs, and runs unit tests"

append : src/append.c
	$(LOCAL_GCC_PATH) -o $@ $<

bincat : src/bincat.c
	$(LOCAL_GCC_PATH) -o $@ $<

bindiff : src/bindiff.c
	$(LOCAL_GCC_PATH) -o $@ $<

bindump : src/bindump.c
	$(LOCAL_GCC_PATH) -o $@ $<

bingen : src/bingen.c
	$(LOCAL_GCC_PATH) -o $@ $<

binjoin : src/binjoin.c
	$(LOCAL_GCC_PATH) -o $@ $<

binsplit : src/binsplit.c
	$(LOCAL_GCC_PATH) -o $@ $<

bintoc : src/bintoc.c
	$(LOCAL_GCC_PATH) -o $@ $<

crcgen : src/crcgen.c
	$(LOCAL_GCC_PATH) -o $@ $<

prepend : src/prepend.c
	$(LOCAL_GCC_PATH) -o $@ $<

srectoc : src/srectoc.c
	$(LOCAL_GCC_PATH) -o $@ $<

# ========================================================================

install: all
	@-echo "Install - installing to ./bin"
	mkdir ./bin
	cp $(TARGETS) bin
	rm -f $(TARGETS)

# ========================================================================

clean:
	rm -f *% *~ *.bak src/*% src/*~ src/*.bak

realclean: clean
	rm -f $(TARGETS) $(TARGETS2) *.bin *.uu testout.c bin/*

distclean: realclean

# ========================================================================

test: testhdr install testapp testcat testc testcrc testdiff

testhdr:
	@-echo " "
	@-echo "Testing binary utilities..."
	@-rm -rf ./bin
	@-rm -f *.bin *.uu
	@-echo " "

testapp:
	@-echo "-- testing append/prepend ..."
	./bin/bingen  -n 128 -d 255 -o file1.bin
	./bin/prepend -n 16  -d 0   -i file1.bin -o file2.bin
	./bin/append  -n 16  -d 128 -i file2.bin -o file3.bin
	./bin/bindump file3.bin

testcat:
	@-echo "-- testing bincat ..."
	./bin/bingen  -n 64  -d 0   -o cat1.bin
	./bin/bingen  -n 64  -d 255 -o cat2.bin
	./bin/bincat  -a cat1.bin -b cat2.bin -o cat3.bin
	./bin/bindump cat3.bin

testdiff:
	@-echo "-- testing bindiff ..."
	./bin/bingen  -n 16  -d 0  -o diff1.bin
	./bin/bingen  -n 16  -d 0  -o diff2.bin
	./bin/append  -n 1   -d 1  -i diff1.bin -o diff1a.bin
	./bin/append  -n 1   -d 2  -i diff2.bin -o diff2a.bin
	./bin/bindiff diff1a.bin diff2a.bin

testc:
	@-echo "-- testing bintoc ..."
	./bin/bingen  -n 32  -d 55  -o c.bin
	./bin/bintoc  -i c.bin -o testout.c -a catdata
	cat testout.c

testcrc:
	@-echo "-- testing crcgen ..."
	./bin/bingen  -n 64  -d 77  -o crc1.bin
	./bin/prepend -n 16  -d 0   -i crc1.bin -o crc2.bin
	./bin/crcgen crc2.bin
	./bin/bindump crc2.bin

testuu:
	@-echo "-- testing uuencode/uudecode ..."
	./bin/bingen  -n 1024  -c  -o uu.bin
	cat uu.bin | uuencode uu.bin > uu.uu
	uudecode -o uu2.bin uu.uu
	./bin/bindiff uu.bin uu2.bin

testsplit:
	@-echo "-- testing binsplit/binjoin ..."
	./bin/bingen  -n 100024  -c  -o split.bin
	./bin/binsplit -n 8192 -i split.bin -r split.out
	./bin/binjoin -r split.out -o split2.bin
	./bin/bindiff split.bin split2.bin

# ========================================================================

#------------------------------------------------------------------------
# Make distribution file
#------------------------------------------------------------------------

TAR_HOME = $(DIST)
TAR_NAME = $(DIST)-$(VERSION)

TAR_FILES = 	\
	$(TAR_HOME)/COPYING.txt		\
	$(TAR_HOME)/README.txt		\
	$(TAR_HOME)/REVISION.txt	\
	$(TAR_HOME)/Makefile		\
	$(TAR_HOME)/bin				\
	$(TAR_HOME)/man/*			\
	$(TAR_HOME)/src/*

tar: distclean
	cd .. ; \
	$(TAR) -cvf $(TAR_NAME).tar $(TAR_FILES) ; \
	$(GZIP) $(TAR_NAME).tar ; \
	$(MV) $(TAR_NAME).tar.gz $(TAR_HOME)

# ========================================================================
# end of bintools makefile
