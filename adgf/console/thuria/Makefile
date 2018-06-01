# makefile for Dungeons Thuria -- a game of interactive fiction
#
# simply type 'make' to make everything
#
#
#
# Note:  You may want to edit "unix/thuria.mk" before making the package.
#

#
# make targets
#

default: 
	(cd unix ; $(MAKE) )

clean:
	(cd unix; $(MAKE) clean)
	(rm -f *~ *%)

realclean:
	(cd unix; $(MAKE) realclean)
	(rm -f *~ *%)

install: default
	(cd unix; $(MAKE) install)

uninstall:
	(cd unix; $(MAKE) uninstall)

tar:
	(cd unix; $(MAKE) tar)

