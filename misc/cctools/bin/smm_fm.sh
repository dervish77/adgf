#!/usr/bin/ksh
#
# fm -- Use findmerge command to list files for branch merge or actually
#       perform merge of specified source branch into current view.
#
#
# NOTES:
#	You must set your view to the destination branch.  
#
#	Assumes that source branch exists.
#
#	Suppresses checkout comments.
#
#	Suppresses findmerge log output (in -print mode).
#
#	Performs reserved checkouts.
#
#
# Usage:
#	fm <ALL|vob> <src_branch> [print|merge|grmerge|qualify]
#
# Options:
#	<ALL|vob>		- ALL checks all vobs, else specify vob
#
#	<src_branch>		- source branch name
#
#	[print|merge|		- print, yields list of files (default action)
#	 grmerge|qualify]         merge, performs merge
#			          grmerge, performs merge, with graphical
#				  qualify, merges with no automatic decisions
#
#
# Revisions:
#	05/12/99 BSL	added qualify mode, to avoid automatic merges
#	03/09/99 BSL	adapted for Millennium project
#	05/14/98 BSL	switched to use -avobs in ALL case
#	03/12/98 BSL	switched to reserved checkouts
# 	03/10/98 BSL	originated
#


#
# verify arguments
#
if [ $# -lt "2" ]
then
  echo "Usage: fm <ALL|vob> <src_branch>              [print|merge|grmerge|qualify]"
  echo "(i.e.  fm ALL       int_ne_smm_prod_01.03.00)"
  echo "(i.e.  fm smm_sc    int_ne_smm_beta           print)"
  echo "(i.e.  fm smm_sw    dev_ne_feature            merge)"
  echo "(i.e.  fm lynx      dev_ne_feature            grmerge)"
  echo "(i.e.  fm 3party    dev_ne_import             qualify)"
  exit 1
fi

VOB=$1
SRCBR=$2
TYPE="print"

if [ $# -eq "3" ]
then
  TYPE=$3
fi


#
# command aliases
#
CTL="/usr/atria/bin/cleartool"

CMD="$CTL findmerge"

SRCPATH="-fversion .../$SRCBR/LATEST"

PROPTIONS="-log /dev/null -print"

MGOPTIONS="-nc -merge"

GRMGOPTIONS="-nc -merge -graphical"

QALOPTIONS="-nc -merge -graphical -qal"


#
# pick merge type options
#
case $TYPE in
  print)
	OPTS=$PROPTIONS
	;;
  merge)
	OPTS=$MGOPTIONS
	;;
  grmerge)
	OPTS=$GRMGOPTIONS
	;;
  qualify)
	OPTS=$QALOPTIONS
	;;
  *)
	echo "Error - unknown merge type - $TYPE"
	exit 1
	;;
esac


#
# verify ClearCase view
#
NO_VIEW=`$CTL pwv | grep "Set view" | awk '{print $4}'`
CURRENT_VIEW=`$CTL pwv | grep "Set view" | awk '{print $3}'`

case $NO_VIEW in
  NONE)
	echo "Error - no view is currently set!"
	exit 1
	;;
  *)
	echo "Current view is $CURRENT_VIEW"
	echo "Merging from $SRCBR branch"
	echo " "
	;;
esac

#
# switch on <vob>
# 
case $VOB in
  ALL)
        echo "Merging all vobs"
	$CMD -avobs          $SRCPATH $OPTS
	;;
  smm_root)
        echo "Merging /millenniumvobs/smm_root only"
	$CMD /millenniumvobs/smm_root $SRCPATH $OPTS
	;;
  smm_sc)
        echo "Merging /millenniumvobs/smm_sc only"
	$CMD /millenniumvobs/smm_sc   $SRCPATH $OPTS
	;;
  smm_sw)
        echo "Merging /millenniumvobs/smm_sw only"
	$CMD /millenniumvobs/smm_sw   $SRCPATH $OPTS
	;;
  lynx)
        echo "Merging /millenniumvobs/lynx only"
	$CMD /millenniumvobs/lynx     $SRCPATH $OPTS
	;;
  3party)
        echo "Merging /millenniumvobs/3party only"
	$CMD /millenniumvobs/3party   $SRCPATH $OPTS
	;;
  *)
	echo "Error - unknown vob specified - $VOB"
	exit 1
esac

exit 0
