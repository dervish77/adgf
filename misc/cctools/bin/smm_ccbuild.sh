#!/bin/sh
#
# ccbuild - Build script for use with ClearCase.  
#
#           Produces a 'make log' and an 'error log' in the root
#           VOBS directory "/mvobs/smm_root" with the names "make_log" 
#           and "error_log".  The error log is mailed to 
#           the user.  Note that the user must have set the view
#           before calling this script.
#
# Usage:
#	ccbuild <viewname> [<target> <level>] [nomail]
#
# Options:
#	<viewname>	- name of a ClearCase view {verified to exist}
#
#	<target>	- make target (ALL, DV, SMM, TEST)
#			  {default SMM}
#
#	<level>		- directory level (root, proj)
#			  {default root}
#
#	[nomail]	- if 'nomail', will suppress sending mail to user
#
# Revisions:
#	05/07/99 BSL	added DV, SMM, TEST targets
#	03/09/99 BSL	adapted for Millennium project
#	11/09/98 BSL 	originated
#


#
# verify arguments
#
if [ $# -lt 1 ]
then
  echo "Usage: ccbuild <viewname> [<target> <level>] [nomail]"
  echo " "
  echo "  <viewname>	- name of a ClearCase view {verified to exist}"
  echo " "
  echo "  <target>	- make target (ALL, TEST, SMM, DV)"
  echo "		  {default SMM}"
  echo " "
  echo "  <level>	- directory level (root, proj)"
  echo "		  {default root}"
  echo " "
  echo "  [nomail]	- if 'nomail', will suppress sending mail to user"
  echo " "
  echo "  {creates error_log, make_log and time_log in $SMMROOT"
  exit 1
else
  VIEWNAME=$1
fi

if [ $# -eq 4 ]
then
  TARGET=$2
  LEVEL=$3
  NOMAIL=$4
else
  if [ $# -eq 3 ]
  then
    TARGET=$2
    LEVEL=$3
    NOMAIL=mail
  else
    TARGET=SMM
    LEVEL=root
    NOMAIL=mail
  fi
fi

LOGPATH="$SMMROOT"

MAKELOG=$LOGPATH/make_log
ERRORLOG=$LOGPATH/error_log
TIMELOG=$LOGPATH/time_log

CTL="/usr/atria/bin/cleartool"


#
# verify ClearCase view
#
VIEWTAG=${USER}_${PROJECT}_${VIEWNAME}

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


if [ $CURRENT_VIEW -eq $VIEWTAG ]
then
  # remove old log files
  rm -rf $MAKELOG
  rm -rf $ERRORLOG
  rm -rf $TIMELOG

  # echo date and header to log files
  echo "Built on `/usr/bin/date`" > $MAKELOG 
  echo "Using ClearCase view $VIEWTAG ..........."
  echo "Using ClearCase view $VIEWTAG ..........." >> $MAKELOG
else
  echo "Error - Current view does not match specified view"
  echo "      - Current view   = $CURRENT_VIEW"
  echo "      - Specified view = $VIEWTAG"
  exit 1
fi


#
# determine build directory based on level
#
case $LEVEL in
  root)
	BUILD_DIR=/millenniumvobs/smm_root
	;;
  proj)
	BUILD_DIR=/millenniumvobs/smm_root/reva/proj
	;;
  *)
	echo "Error - Unknown level specified - $LEVEL"
	exit 1
	;;
esac

echo "Using build level of $BUILD_DIR ..........."
echo "Using build level of $BUILD_DIR ..........." >> $MAKELOG


#
# build image specified by target
#
case $TARGET in
  ALL)
	echo "Making ALL ..........."
	echo "Making ALL ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building ALL" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL ALL >> $MAKELOG 2>&1
	;;

  BOOT)
	echo "Making BOOT ..........."
	echo "Making BOOT ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building BOOT" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL BOOT >> $MAKELOG 2>&1
	;;

  DV)
	echo "Making DV ..........."
	echo "Making DV ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building DV" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL DV >> $MAKELOG 2>&1
	;;

  FADS)
	echo "Making FADS ..........."
	echo "Making FADS ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building FADS" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL FADS >> $MAKELOG 2>&1
	;;

  REVA)
	echo "Making REVA ..........."
	echo "Making REVA ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building REVA" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL REVA >> $MAKELOG 2>&1
	;;

  SMM)
	echo "Making SMM ..........."
	echo "Making SMM ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building SMM" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL SMM >> $MAKELOG 2>&1
	;;

  TEST)
	echo "Making TEST ..........."
	echo "Making TEST ..........." >> $MAKELOG
        echo "timelog `/usr/bin/date` -- building TEST" >> $MAKELOG
        cd $BUILD_DIR
	$MAKETOOL TEST >> $MAKELOG 2>&1
	;;

  *)
	echo "Error - Unknown target specified - $TARGET"
	exit 1
	;;
esac

echo "Checking for errors ..........."
echo "timelog `/usr/bin/date` -- checking for errors" >> $MAKELOG

#
# generate error log
#
echo "Error log for ClearCase view $VIEWTAG" > $ERRORLOG
/usr/bin/date >> $ERRORLOG 
echo " " >> $ERRORLOG
echo "Number of errors" >> $ERRORLOG
grep -cw Error $MAKELOG >> $ERRORLOG
echo "Number of warnings" >> $ERRORLOG
grep -c warning $MAKELOG >> $ERRORLOG

echo "timelog `/usr/bin/date` -- done" >> $MAKELOG

#
# generate time log
#
echo "Generating timing log ..........."
echo "Timing log for ClearCase view $VIEWTAG" > $TIMELOG
/usr/bin/date >> $TIMELOG 
echo " " >> $TIMELOG
grep timelog $MAKELOG >> $TIMELOG


if [ $NOMAIL -eq "mail" ]
then
  /usr/ucb/mail $USER < $ERRORLOG
else
  echo "Review error_log at $ERRORLOG"
fi

echo "Done"
echo "Done" >> $MAKELOG

exit 0
