# makefile for adgf directory tree
#
# simply type 'make' to make everything
#
#
#

VERSION = 0.1.7

DATE = `date +%D-%T`

DIRS = anim audio bindump bintools breakout bumpdemo chat \
	   dev8085 dirtest drawdemo drawsdl drawsdl-alt drawsdl-save dsp \
	   echo emboss emu85 game geturl hwsim icon image lang libgfs libvm life \
	   modeler modeler2 mos msgdemo mymail othello \
	   particle polyscan pong-libsx ppm_test \
       render render2 rpg sicdacloe soundex starfire \
	   story survival thuria


#
# make all programs
#

default: all

all:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make ; cd ..;     \
	done;


# remove all *.o and backup files

clean:
	for dir in $(DIRS);  do               \
	   cd $$dir ; make clean ; cd ..;     \
	done;


# remove all *.o, executables, and library files

realclean: clean
	for dir in $(DIRS);  do               \
	   cd $$dir ; make realclean ; cd ..; \
	done;
	rm -f *~

distclean: realclean


#
# make distribution file
#

ADGF_HOME = adgf
ADGF_NAME = adgf-$(VERSION)

tar: newversion
	cp /dev/null ../$(ADGF_NAME).txt
	cd .. ; \
	tar -cvf $(ADGF_NAME).tar $(ADGF_HOME) ; \
	gzip $(ADGF_NAME).tar ; \
	mv $(ADGF_NAME).tar.gz $(ADGF_NAME).tgz
	-@echo "Distribution is ../$(ADGF_NAME).tgz (also see ../$(ADGF_NAME).txt)"
	-@echo "Distribution is ../$(ADGF_NAME).tgz" >> ../$(ADGF_NAME).txt
	-@echo "-----------------------------------" >> ../$(ADGF_NAME).txt
	-@cat Version >> ../$(ADGF_NAME).txt
	-@echo "-----------------------------------" >> ../$(ADGF_NAME).txt

newversion:
	cp /dev/null Version
	-@echo "VERSION = $(VERSION)" >> Version
	-@echo "DATE    = $(DATE)" >> Version


