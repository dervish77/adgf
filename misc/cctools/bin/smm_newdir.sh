#!/bin/sh
#
# newdir
#
#	Creates a new directory within the SMM ClearCase repository.   The 
#	new directory is created as "<dirname>@@/main/0" if view is set to a 
#	/main/LATEST view.
#
# Usage:
#	newdir <vob_path> <dirname>
#
# Options:
#	<vob_path>	- path to directory within VOB or "."
#
#	<dirname>	- new directory's name
#
# Notes:
#
#	Note that the script verifies that a view is currently set.
#
#	Note that if the specified vob path does not exist, the 
#	script will fail.
#
#	Note that if the new directory name already exists, the 
#	script will fail.
#
#	Note that now directories can be branched, which will complicate
#	branch merges, typically requiring a two-pass merge.
#
# Caution:
#	
#	Care must be taken when using  "." as the VOB path argument 
#	if the current working directory is set to something other 
#	than inside the VOB.  The script should fail, but unpredictable 
#	results may occur.
#
# Revisions:
#	04/20/99 BSL	modified to allow new directory in any view
#	03/11/99 BSL	added "ctl protect -chmod"
#	03/09/99 BSL	adapted for Millennium project
#	11/09/98 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 2 ]
then
  echo "Usage: newdir <vob_path> <dirname>"
  echo "(i.e.  newdir /millenniumvobs/smm_sw newmod)"
  echo "(i.e.  newdir . newmod)"
  exit 1
else
  VOBPATH=$1
  DIRNAME=$2
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
# if current view matches specified view, add new directory to VOB
#
# notused! if [ $CURRENT_VIEW -eq $VIEWTAG ]
# notused! then
  echo "Adding new directory $DIRNAME to path $VOBPATH"

  if [ -d $VOBPATH ]
  then
    if [ ! -d $VOBPATH/$DIRNAME ]
    then

      cd $VOBPATH
      $CTL checkout -res -nc .
      $CTL mkdir -nco -c "new directory" $DIRNAME
      $CTL protect -chmod 775 $DIRNAME
      $CTL protect -chgrp ccusers $DIRNAME
      $CTL protect -chown swtadmin $DIRNAME
      $CTL checkin -c "added new directory" .

    else
      echo "Error - directory $VOBPATH/$DIRNAME already exists!"
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
