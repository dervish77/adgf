#!/bin/sh
#
# importfile
#
#	Imports the specified file to the specified VOB location 
#	within the current view. 
#
# Usage:
#	importfile <viewname> <src_file> <dest_file>
#
# Options:
#	<viewname>	- name of a ClearCase view {verified to exist}
#
#	<src_file>	- label to apply to all elements {verified to exist}
#
#	<dest_file>	- label to apply to all elements {verified to exist}
#
# Notes:
#	- if the destination file exists in the VOB, it is overwritten 
#	with the contents of the source file.
#
#	- if the destination file does not exist in the VOB, the script fails.
#
#	- source and destination paths may be relative paths assuming that
#	current working directory is appropriate.
#
# Revisions:
#	05/17/99 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 3 ]
then
  echo "Usage: importfile <viewname> <src_file> <dest_file>"
  echo "(i.e.  importfile main ~joeuser/file.c /millenniumvobs/3party/file.c)"
  exit 1
else
  VIEWNAME=$1
  SRC=$2
  DEST=$3
fi



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
# if current view matches specified view, import specified file
#
if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  echo "Importing $SRC as $DEST"

  #
  # verify destination file is already in VOB, then copy
  #
  if [ ! -f $DEST ]
  then

    #
    # verify that the source file exists
    #
    if [ ! -f $SRC ]
    then
      $CTL checkout -res -nc $DEST
      cp $SRC $DEST
#      $CTL checkin -c "imported from $SRC" $DEST
    else
      echo "Error - file $SRC cannot be found!"
      exit 1
    fi

  else
    echo "Error - file $DEST is missing from VOB!"
    exit 1
  fi

else
  echo "Error - Current view does not match specified view"
  echo "      - Current view   = $CURRENT_VIEW"
  echo "      - Specified view = $VIEWTAG"
  exit 1
fi

echo "Done"

exit 0
