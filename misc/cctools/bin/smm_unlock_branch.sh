#!/bin/sh
#
# unlockbranch
#
#	Unlocks specified branch in all VOBs within current view.  
#
# Usage:
#	unlockbranch <viewname> <branch>
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
  echo "Usage: unlockbranch <viewname> <branch>"
  echo "(i.e.  unlockbranch main int_ne_beta_01.00.00)"
  exit 1
else
  VIEWNAME=$1
  BRANCH=$2
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
# if current view matches specified view, unlock branch in each VOB
#
if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  echo "Unlocking branch $BRANCH in view $VIEWTAG"

  #
  # unlock branch in each VOB in VOBLIST
  #
  for VOB in $VOBLIST
  do
    cd $VOB
    TESTLABEL=`$CTL lstype -short -kind brtype | grep $BRANCH | awk '{print $1}`
    if [ $TESTLABEL -eq $BRANCH ]
    then
      echo "Unlocking branch $BRANCH in $VOB ..."
      $CTL unlock brtype:$BRANCH
    else
      echo "Error - branch $BRANCH missing from $VOB"
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
