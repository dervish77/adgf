#!/bin/sh
#
# locklabel
#
#	Locks specified label in all VOBs within current view.  
#
# Usage:
#	locklabel <viewname> <label>
#
# Options:
#	<viewname>	- name of a ClearCase view {verified to exist}
#
#	<label>		- label to lock {verified to exist}
#
# Notes:
#	- verifies <viewname> is current view
#	- verifies <label> exists in VOB before locking it
#
# Revisions:
#	03/19/99 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 2 ]
then
  echo "Usage: locklabel <viewname> <label>"
  echo "(i.e.  locklabel main REL_SMM_PROD_01.03.03)"
  exit 1
else
  VIEWNAME=$1
  LABEL=$2
fi


VOBLIST="/millenniumvobs/smm_root /millenniumvobs/smm_sc /millenniumvobs/smm_sw /millenniumvobs/lynx /millenniumvobs/3party"


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
# if current view matches specified view, lock label in each VOB
#
if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  echo "Locking label $LABEL in view $VIEWTAG"

  #
  # lock label in each VOB in VOBLIST
  #
  for VOB in $VOBLIST
  do
    cd $VOB
    TESTLABEL=`$CTL lstype -short -kind lbtype | grep $LABEL | awk '{print $1}`
    if [ $TESTLABEL -eq $LABEL ]
    then
      echo "Locking label $LABEL in $VOB ..."
      $CTL lock lbtype:$LABEL
    else
      echo "Error - label $LABEL missing from $VOB"
      exit 1
    fi
  done

else
  echo "Error - Current view does not match specified view"
  echo "      - Current view   = $CURRENT_VIEW"
  echo "      - Specified view = $VIEWTAG"
  exit 1
fi

echo "Done"

exit 0
