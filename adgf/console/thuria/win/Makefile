# makefile for Dungeons of Thuria -- a game of interactive fiction
#
# type 'make' to build windows package
#
#

REV  = 1.0


default: 
	@echo "Making ... Dungeons of Thuria"
	$(MAKE) package
	$(MAKE) remove
	
package: copy tar 

	
#
# make windows distribution file
#

DUNGEON_HOME = dungeon-thuria
DUNGEON_NAME = thuria-$(REV)


copy: remove
	mkdir $(DUNGEON_HOME)
	cp readme.txt          $(DUNGEON_HOME)
	cp copying.txt         $(DUNGEON_HOME)
	cp revision.txt        $(DUNGEON_HOME)
	cp thuria.exe          $(DUNGEON_HOME)
	cp ../cheats/map.pdf   $(DUNGEON_HOME)
	cp ../cheats/walk.txt  $(DUNGEON_HOME)

remove:
	rm -rf $(DUNGEON_HOME)

tar:
	tar -cvf $(DUNGEON_NAME).tar $(DUNGEON_HOME)/* ; \
	gzip $(DUNGEON_NAME).tar ; \
	mv $(DUNGEON_NAME).tar.gz $(DUNGEON_NAME).tgz

