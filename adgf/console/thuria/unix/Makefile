# makefile for Dungeons of Thuria -- a game of interactive fiction
#
# simply type 'make' to make everything
#
#
#
# Note:  You may want to edit "thuria.mk" before making the package.
#

REV  = 1.0

INSTALL_BIN_PATH     = $(HOME)/bin
INSTALL_MAN_PATH     = $(HOME)/man/man1


#
# make binaries
#

default: 
	@echo "Making ... Dungeons of Thuria"
	(cd src ; $(MAKE) )

all: default
#all: default install realclean

# remove all *.o and backup files

clean:
	(cd src; $(MAKE) clean)
	(rm -f *% *~)


# remove all *.o and executables files

realclean:
	@echo "Cleaning up build ..."
	(cd src; $(MAKE) realclean)
	(rm -f *% *~)
	(cd man; rm -f *% *~)
	(cd ../win; rm -f *% *~)
	(cd ../cheats; rm -f *% *~)


#
# install binaries
#

install: default
	@echo "Installing ... Dungeons of Thuria"
	(cp man/thuria.man $(INSTALL_MAN_PATH)/thuria.1)
	(cp src/thuria $(INSTALL_BIN_PATH)/.)

uninstall:
	@echo "Uninstalling ... Dungeons of Thuria"
	(rm -f $(INSTALL_BIN_PATH)/thuria)
	(rm -f $(INSTALL_MAN_PATH)/thuria.1)

#
# make distribution file
#

DUNGEON_HOME = thuria
DUNGEON_NAME = thuria-$(REV)

TAR_FILES = 	\
	$(DUNGEON_HOME)/README.unx		\
	$(DUNGEON_HOME)/READWIN.txt		\
	$(DUNGEON_HOME)/Makefile		\
	$(DUNGEON_HOME)/cheats/map.ppt		\
	$(DUNGEON_HOME)/cheats/walk.txt		\
	$(DUNGEON_HOME)/win/readme.txt		\
	$(DUNGEON_HOME)/win/copying.txt		\
	$(DUNGEON_HOME)/win/revision.txt	\
	$(DUNGEON_HOME)/win/thuria.exe		\
	$(DUNGEON_HOME)/win/install.bat		\
	$(DUNGEON_HOME)/win/uninstall.bat	\
	$(DUNGEON_HOME)/win/Dungeons_of_Thuria.lnk	\
	$(DUNGEON_HOME)/win/Readme.lnk		\
	$(DUNGEON_HOME)/unix/README		\
	$(DUNGEON_HOME)/unix/COPYING		\
	$(DUNGEON_HOME)/unix/REVISION		\
	$(DUNGEON_HOME)/unix/Makefile		\
	$(DUNGEON_HOME)/unix/thuria.mk		\
	$(DUNGEON_HOME)/unix/man/thuria.man	\
	$(DUNGEON_HOME)/unix/src/*.c		\
	$(DUNGEON_HOME)/unix/src/*.h		\
	$(DUNGEON_HOME)/unix/src/makefile	

tar:
	cd ../.. ; \
	tar -cvf $(DUNGEON_NAME).tar $(TAR_FILES) ; \
	gzip $(DUNGEON_NAME).tar ; \
	mv $(DUNGEON_NAME).tar.gz thuria.tgz

