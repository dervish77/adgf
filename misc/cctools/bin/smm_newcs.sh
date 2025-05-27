#!/bin/sh
#
# newcs
#
#	Creates a new config spec in the directory 
#	/millenniumvobs/hdm_root/cctools/config.spec.  The new file 
#	is created as "<filename>@@/main/1".
#
# Usage:
#	newcs <filename>
#
# Options:
#	<filename>	- new config spec's filename
#
# Notes:
#
#	Assumes that desired config spec has already been generated using
#	"csgen" in the user's home directory $HOME.
#
#	Note that the script verifies that the current view is 
#	on /main/LATEST.
#
#	Note that if the directory path does not exist, the script fails.
#
# Revisions:
#	03/09/99 BSL	adapted for Millennium project
#	11/09/98 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 1 ]
then
  echo "Usage: newcs <filename>"
  echo "(i.e.  newcs smm_ne_smm_feature.cs)"
  exit 1
else
  FILENAME=$1
fi


VIEWNAME="main"

VOBPATH="/millenniumvobs/smm_root/cctools/config.spec"

SRCPATH="$HOME"


#
# verify config spec template exists in $SRCPATH
#
if [ -f ${SRCPATH}/${FILENAME} ]
then

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
  # if current view matches specified view, add new file to VOB
  #
  if [ $CURRENT_VIEW -eq $VIEWTAG ]
  then
    echo "Adding new file $FILENAME to path $VOBPATH from $SRCPATH"

    if [ -d $VOBPATH ]
    then

      #
      # verify template is not already in VOB
      #
      if [ ! -f $VOBPATH/$FILENAME ]
      then

        #
        # create version on /main/1
        #
        cd $VOBPATH
        $CTL checkout -res -nc .
        cp ${SRCPATH}/${FILENAME} $FILENAME 
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
  else
    echo "Error - Current view does not match specified view"
    echo "      - Current view   = $CURRENT_VIEW"
    echo "      - Specified view = $VIEWTAG"
    exit 1
  fi
else
  echo "Error - template $FILENAME not found at $SRCPATH!"
  exit 1
fi

echo "Done"

exit 0
