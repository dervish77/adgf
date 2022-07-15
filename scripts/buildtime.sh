#!/bin/bash
#
# buildtime.sh - Build script for use with Program Source CVS Repository  
#
#           Generates overall build time log for testing build times.
#
#           Produces a 'make log' and an 'time log' in the user's
#           HOME directory with the names "make_log" and "time_log".  
#
#           Requires environment variable PROJHOME set to user's CVS
#           workspace.
#
# Usage:
#	buildtime.sh <target>
#
#
# Revisions:
#       01/27/2006 BSL  modified for use with latest top level makefile
#	01/13/2006 BSL 	originated
#

LOGPATH="./"
LOGPATH2="$HOME/var"

MAKELOG=$LOGPATH/make_log
ERRORLOG=$LOGPATH/error_log
TIMELOG=$LOGPATH/time_log

BUILDSCRIPT=$HOME/bin/cvsbuild.sh


#
# verify arguments
#
if [ $# -lt 1 ]
then
  echo "Usage: buildtime.sh <target>"
  echo " "
  echo "  <target>	- make target (ALL, PROD, DEV, CLEAN, REALCLEAN)"
  echo " "
  echo "  {creates error_log, make_log and time_log in $LOGPATH"
  exit 1
else
  TARGET=$1
fi


#
# delete old log files
#

rm -f $MAKELOG
rm -f $ERRORLOG
rm -f $TIMELOG

rm -f $LOGPATH2/make_log_*
rm -f $LOGPATH2/error_log_*
rm -f $LOGPATH2/time_log_*


#
# echo date and header to log files
#

echo "Begin on `/usr/bin/date`" 
echo "Begin on `/usr/bin/date`" > $MAKELOG 

#
# build image specified by target
#

$BUILDSCRIPT $TARGET BSP
$BUILDSCRIPT $TARGET LEC
$BUILDSCRIPT $TARGET 3PARTY
$BUILDSCRIPT $TARGET HU
$BUILDSCRIPT $TARGET UTILS


#
# generate time log
#
echo "Generating overall timing log ..........."
echo "Overall Timing Log - BEGIN" > $TIMELOG
echo " " >> $TIMELOG
cat $LOGPATH2/time_log_$TARGET-BSP >> $TIMELOG
cat $LOGPATH2/time_log_$TARGET-LEC >> $TIMELOG
cat $LOGPATH2/time_log_$TARGET-3PARTY >> $TIMELOG
cat $LOGPATH2/time_log_$TARGET-HU >> $TIMELOG
cat $LOGPATH2/time_log_$TARGET-UTILS >> $TIMELOG
echo " " >> $TIMELOG
echo "Overall Timing Log - END" >> $TIMELOG


#
# we're done!!
#

echo "Done at `/usr/bin/date`"
echo "Done at `/usr/bin/date`" >> $MAKELOG

exit 0
