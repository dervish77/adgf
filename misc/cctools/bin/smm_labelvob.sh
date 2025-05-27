#!/bin/sh
#
# labelvob
#
#	Applies specified label to all elements of the specified VOB
#	within current view.  
#
# Usage:
#	labelvob <vobname> <viewname> <label>
#
# Options:
#	<vobname>	- name of a Millennium VOB {verified to exist}
#
#	<viewname>	- name of a ClearCase view {verified to exist}
#
#	<label>		- label to apply to all elements {verified to exist}
#
# Notes:
#	- since 'ctl mklabel -recurse' does not traverse symbolic 
#	links must 'cd' into each VOB separately
#
# Revisions:
#	05/11/99 BSL	copied and modified from smm_labelview.sh
#


#
# verify arguments
#
if [ $# -lt 3 ]
then
  echo "Usage: labelvob <vobname> <viewname> <label>"
  echo "(i.e.  labelvob 3party main REL_SMM_PROD_01.03.03)"
  exit 1
else
  VOBNAME=$1
  VIEWNAME=$2
  LABEL=$3
fi


VOB=/millenniumvobs/$VOBNAME


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
# if current view matches specified view, apply label to specified VOB
#
if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  echo "Labeling ClearCase view $VIEWTAG as $LABEL"

  #
  # apply label to specified VOB only if the VOB exists
  #
  cd $VOB

  CURRENT_VOB=`pwd`
  if [ $CURRENT_VOB -eq $VOB ]
  then
    TESTLABEL=`$CTL lstype -short -kind lbtype | grep $LABEL | awk '{print $1}'`
    if [ $TESTLABEL -eq $LABEL ]
    then
      echo "Labeling $VOB ..."
      $CTL mklabel -recurse $LABEL .
    else
      echo "Error - label $LABEL missing from $VOB"
      exit 1
    fi
  else
    echo "Error - specified VOB $VOB does not exist"
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
