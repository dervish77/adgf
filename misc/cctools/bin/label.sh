#!/bin/sh
#
# label.sh - label view wrapper script for smm_labelview.sh
#
#	Note, intended for use inside of a cron job, at job, or to be
#	executed from a web server engine.
#
# Usage:
#	label.sh <viewname> <label>
#
#	<viewname>	- must be real view name
#
#	<label>		- must be real label type
#
# Revisions:
#	03/09/99 BSL	adapted for Millennium project
#	06/26/98 BSL	modified to use PROJHOME variable
#	06/01/98 BSL 	originated
#


VIEWNAME=$1
LABEL=$2


#
# define necessary tool/file paths
#
CTL="/usr/atria/bin/cleartool"
LSCRIPT="$PROJHOME/bin/smm_labelview.sh"


#
# define smm_labelview.sh invocation
#
DOIT="$LSCRIPT $VIEWNAME $LABEL"


#
# run smm_labelview.sh inside a view
#
$CTL setview -exec "$DOIT" ${USER}_${PROJECT}_${VIEWNAME}


exit 0
