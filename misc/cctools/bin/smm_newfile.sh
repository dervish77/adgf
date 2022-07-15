#!/bin/sh
#
# newfile
#
#	Creates a new file within the ClearCase repository.   The new 
#	file is created as "<filename>@@/main/1" if view is set to a 
#	/main/LATEST view.
#
# Usage:
#	newfile <vob_path> <filename>
#
# Options:
#	<vob_path>	- path to directory within VOB or "."
#
#	<filename>	- new file's name
#
# Notes:
#
#	Note that the script verifies that a view is currently set.
#
#	If file exists as <filename.new>, that version is copied.
#
#	Otherwise the file is created as an empty file (i.e. the file
#	size is 0).  The developer must check out the file to their 
#	working branch and replace with the desired contents.  
#
#	Note that if the directory path does not exist, the script fails.
#
# Caution:
#	
#	Care must be taken when using  "." as the VOB path argument 
#	if the current working directory is set to something other 
#	than inside the VOB.  The script should fail, but unpredictable 
#	results may occur.
#
# Revisions:
#	04/20/99 BSL	modified to allow new file in any view
#	03/08/99 BSL	adapted for Millennium
#	11/09/98 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 2 ]
then
  echo "Usage: newfile <vob_path> <filename>"
  echo "(i.e.  newfile /millenniumvobs/smm_sw/dv common.c)"
  echo "(i.e.  newfile . common.c)"
  exit 1
else
  VOBPATH=$1
  FILENAME=$2
fi


VIEWNAME="main"

CURRENT_DIR_PATH="."


#
# verify ClearCase view
#
VIEWTAG=${USER}_${PROJECT}_${VIEWNAME}

CTL="/usr/atria/bin/cleartool"

NO_VIEW=`$CTL pwv | grep "Set view" | awk '{print $4}'`
CURRENT_VIEW=`$CTL pwv | grep "Set view" | awk '{print $3}'`

case $NO_VIEW in
  NONE)
	echo "Error - no view is currently set!"
	exit 1
	;;
  *)
	echo "Current view is $CURRENT_VIEW"
	;;
esac


#
# Handle <vob_path> of "." (i.e. current working directory)
#
if [ $VOBPATH -eq $CURRENT_DIR_PATH ]
then
  echo "Setting VOBPATH to `pwd`"
  VOBPATH=`pwd`
fi


#
# if current view matches specified view, add new file to VOB
#
# notused! if [ $CURRENT_VIEW -eq $VIEWTAG ]
# notused! then
  echo "Adding new file $FILENAME to path $VOBPATH"

  if [ -d $VOBPATH ]
  then
    #
    # verify file is not already in VOB
    #
    if [ ! -f $VOBPATH/$FILENAME ]
    then

      #
      # if not found as $FILENAME.new, then create empty version
      #
      cd $VOBPATH
      $CTL checkout -res -nc .

      if [ -f ./$FILENAME.new ]
      then
        echo "Found $VOBPATH/$FILENAME.new, copying to $FILENAME"
	cp $FILENAME.new $FILENAME
      else
	echo "Creating empty file as $FILENAME"
        touch $FILENAME
      fi

      $CTL mkelem -nc $FILENAME
      $CTL checkin -ide -c "initial revision" $FILENAME
      $CTL protect -chown swtadmin $FILENAME
      $CTL checkin -c "added new file" .

    else
      echo "Error - file $VOBPATH/$FILENAME already exists!"
      exit 1
    fi
  else
    echo "Error - directory $VOBPATH does not exist!"
    exit 1
  fi
# notused! else
# notused!   echo "Error - Current view does not match specified view"
# notused!   echo "      - Current view   = $CURRENT_VIEW"
# notused!   echo "      - Specified view = $VIEWTAG"
# notused!   exit 1
# notused! fi

echo "Done"

exit 0
