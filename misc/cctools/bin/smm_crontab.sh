#!/bin/sh
#
# crontab.sh - cron job test script for nightly merge/build
#
#
# example of merge and build
# $NITESCRIPT BOTH ne_smm_piglatin $LISTPATH/smm_piglatin.lst
#
# example of merge only
# $NITESCRIPT MERGE ne_smm_piglatin $LISTPATH/smm_piglatin.lst
#
# example of build only
# $NITESCRIPT BUILD ne_smm_piglatin $LISTPATH/smm_piglatin.lst
#
#
# Revisions:
#	11/09/98 BSL 	originated
#




#
# define necessary tool/file paths
#
# {NOTE:  When run from crontab, $PROJHOME is not defined!!!}

NITESCRIPT="$PROJHOME/bin/nite.sh"

LISTPATH="$PROJHOME/srclist"




#
# invoke nite script for each merge/build
# comment out lines which shouldn't be run
#


$NITESCRIPT BUILD main $LISTPATH/main.lst


exit 0
