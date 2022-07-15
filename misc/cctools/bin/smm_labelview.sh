#!/bin/sh
#
# labelview
#
#	Applies specified label to all elements within current view.  
#
# Usage:
#	labelview <viewname> <label>
#
# Options:
#	<viewname>	- name of a ClearCase view {verified to exist}
#
#	<label>		- label to apply to all elements {verified to exist}
#
# Notes:
#	- since 'ctl mklabel -recurse' does not traverse symbolic 
#	links must 'cd' into each VOB separately
#
# Revisions:
#	03/09/99 BSL	adapted for Millennium project
#	06/01/98 BSL	added label verification
#	05/29/98 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 2 ]
then
  echo "Usage: labelview <viewname> <label>"
  echo "(i.e.  labelview main REL_SMM_PROD_01.03.03)"
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
# if current view matches specified view, apply label to each VOB
#
if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  echo "Labeling ClearCase view $VIEWTAG as $LABEL"

  #
  # apply label to each VOB in VOBLIST
  #
  for VOB in $VOBLIST
  do
    cd $VOB
    TESTLABEL=`$CTL lstype -short -kind lbtype | grep $LABEL`
    if [ $TESTLABEL -eq $LABEL ]
    then
      echo "Labeling $VOB ..."
      $CTL mklabel -recurse $LABEL .
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
