#!/bin/sh
#
# lockbranch
#
#	Locks specified branch in all VOBs within current view.  
#
# Usage:
#	lockbranch <viewname> <branch> [<user_list>]
#
# Options:
#	<viewname>	- name of a ClearCase view {verified to exist}
#
#	<label>		- label to lock {verified to exist}
#
#	[<user_list>]	- comma separated username list (no whitespace)
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
  echo "Usage: lockbranch <viewname> <branch> [<user_list>]"
  echo "(i.e.  lockbranch main dev_ne_atmsig joe,fred)"
  echo "(i.e.  lockbranch main int_ne_beta_01.00.00)"
  exit 1
else
  VIEWNAME=$1
  BRANCH=$2
fi

if [ $# -eq "3" ]
then
  USERLIST=$3
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
# if current view matches specified view, lock branch in each VOB
#
if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  echo "Locking branch $BRANCH in view $VIEWTAG"

  #
  # lock branch in each VOB in VOBLIST
  #
  for VOB in $VOBLIST
  do
    cd $VOB
    TESTLABEL=`$CTL lstype -short -kind brtype | grep $BRANCH | awk '{print $1}`
    if [ $TESTLABEL -eq $BRANCH ]
    then
      if [ $# -eq "3" ]
      then
        echo "Locking branch $BRANCH in $VOB except for $USERLIST ..."
        $CTL lock -nusers $USERLIST brtype:$BRANCH
      else
        echo "Locking branch $BRANCH in $VOB ..."
        $CTL lock brtype:$BRANCH
      fi
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
