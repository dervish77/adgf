#!/bin/sh
#
# nite.sh - nitely merge/build wrapper script for ccnightly.pl
#
#	Note, intended for use inside of smm_crontab.sh.  This script
#	first removes existing view then creates a new one for the 
#	specified build or merge action.
#
# Usage:
#	nite.sh <action> <viewname> <src_br_listpath>
#
#	<action> 		- must be BUILD, MERGE or BOTH
#
#	<viewname>		- must be real view name
#
#	<src_br_listpath>	- must be present if action is MERGE or BOTH
#
# Revisions:
#	07/24/98 BSL	temporarily removed rv and mkv operations
#	06/26/98 BSL	modified to use PROJHOME and CCHOME variables
#	05/27/98 BSL 	added usage comments
#	05/19/98 BSL 	originated
#


ACTION=$1
VIEWNAME=$2
LISTPATH=$3


#
# define necessary tool/file paths
#
CTL="/usr/atria/bin/cleartool"
CCTOOLPATH="$CCHOME/bin"
NSCRIPT="$PROJHOME/bin/ccnightly.pl"


#
# define ccnightly.pl invocation
#
NIGHTLY="$NSCRIPT $ACTION $VIEWNAME $LISTPATH"


#
# remove view, make a new view, then run ccnightly.pl
#
# $CCTOOLPATH/rmview.pl $VIEWNAME
# $CCTOOLPATH/mkv.pl $VIEWNAME
$CTL setview -exec "$NIGHTLY" ${USER}_${PROJECT}_${VIEWNAME}


exit 0
