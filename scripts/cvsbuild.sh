#!/bin/bash
#
# cvsbuild - Build script for use with Program Source CVS Repository  
#
#           Produces a 'make log' and an 'error log' in the user's
#           HOME directory with the names "make_log" and "error_log".  
#           The error log is mailed to the user. 
#
#           Requires environment variable PROJHOME set to user's CVS
#           workspace.
#
# Usage:
#	cvsbuild <target> [<level>] [nomail]
#
# Options:
#
#	<target>	- make target (ALL, PROD, DEV, CLEAN, REALCLEAN)
#			  {default ALL}
#
#	<level>		- directory level (TOP, BSP, LEC, 3PARTY, HU, UTILS)
#			  {default TOP}
#
#	[nomail]	- if 'nomail', will suppress sending mail to user
#
# Revisions:
#       01/27/2006 BSL  modified for use with latest top level makefile
#	01/13/2006 BSL 	originated
#

LOGPATH="$HOME/var"

#
# verify arguments
#
if [ $# -lt 1 ]
then
  echo "Usage: cvsbuild <target> [<level>] [nomail]"
  echo " "
  echo "  <target>	- make target (ALL, PROD, DEV, CLEAN, REALCLEAN)"
  echo " "
  echo "  <level>	- directory level (TOP, BSP, LEC, 3PARTY, HU, UTILS)"
  echo "		  {default TOP}"
  echo " "
  echo "  [nomail]	- if 'nomail', will suppress sending mail to user"
  echo " "
  echo "  {creates error_log, make_log and time_log in $LOGPATH"
  exit 1
else
  TARGET=$1
fi

if [ $# -eq 3 ]
then
  LEVEL=$2
  NOMAIL=$3
else
  if [ $# -eq 2 ]
  then
    LEVEL=$2
    NOMAIL=mail
  else
    LEVEL=TOP
    NOMAIL=mail
  fi
fi

MAKELOG=$LOGPATH/make_log_$TARGET-$LEVEL
ERRORLOG=$LOGPATH/error_log_$TARGET-$LEVEL
TIMELOG=$LOGPATH/time_log_$TARGET-$LEVEL

MAKETOOL=/usr/bin/make

        
#
# echo date and header to log files
#

echo "Built on `/usr/bin/date`" 
echo "Built on `/usr/bin/date`" > $MAKELOG 

echo "Target is $TARGET - Level is $LEVEL"
echo "Target is $TARGET - Level is $LEVEL" >> $MAKELOG

#
# build image specified by target
#
case $TARGET in
  ALL)
        case $LEVEL in
          TOP)
	        BUILD_DIR=$PROJHOME
                TRG=all
	        ;;
          BSP)
        	BUILD_DIR=$PROJHOME
                TRG=bspprod
        	;;
          LEC)
        	BUILD_DIR=$PROJHOME
                TRG=lec
        	;;
          3PARTY)
        	BUILD_DIR=$PROJHOME
                TRG=3party
        	;;
          HU)
        	BUILD_DIR=$PROJHOME
                TRG=hu
        	;;
          UTILS)
        	BUILD_DIR=$PROJHOME
                TRG=utils
        	;;
          *)
        	echo "Error - Unknown level specified - $LEVEL"
        	exit 1
        	;;
        esac
	;;

  DEV)
        case $LEVEL in
          TOP)
	        BUILD_DIR=$PROJHOME
                TRG=dev
	        ;;
          BSP)
        	BUILD_DIR=$PROJHOME
                TRG=bspdev
        	;;
          LEC)
        	BUILD_DIR=$PROJHOME
                TRG=lec
        	;;
          3PARTY)
        	BUILD_DIR=$PROJHOME
                TRG=3party
        	;;
          HU)
        	BUILD_DIR=$PROJHOME
                TRG=hu
        	;;
          UTILS)
        	BUILD_DIR=$PROJHOME
                TRG=utils
        	;;
          *)
        	echo "Error - Unknown level specified - $LEVEL"
        	exit 1
        	;;
        esac
	;;

  PROD)
        case $LEVEL in
          TOP)
	        BUILD_DIR=$PROJHOME
                TRG=all
	        ;;
          BSP)
        	BUILD_DIR=$PROJHOME
                TRG=bspprod
        	;;
          LEC)
        	BUILD_DIR=$PROJHOME
                TRG=lec
        	;;
          3PARTY)
        	BUILD_DIR=$PROJHOME
                TRG=3party
        	;;
          HU)
        	BUILD_DIR=$PROJHOME
                TRG=hu
        	;;
          UTILS)
        	BUILD_DIR=$PROJHOME
                TRG=utils
        	;;
          *)
        	echo "Error - Unknown level specified - $LEVEL"
        	exit 1
        	;;
        esac
	;;

  CLEAN)
        case $LEVEL in
          TOP)
	        BUILD_DIR=$PROJHOME
                TRG=clean
	        ;;
          *)
        	echo "Error - Invalid level specified - $LEVEL"
        	exit 1
        	;;
        esac
	;;

  REALCLEAN)
        case $LEVEL in
          TOP)
	        BUILD_DIR=$PROJHOME
                TRG=clean
	        ;;
          *)
        	echo "Error - Invalid level specified - $LEVEL"
        	exit 1
        	;;
        esac
	;;
        
  *)
	echo "Error - Unknown target specified - $TARGET"
	exit 1
	;;
esac

echo "Build directory - $BUILD_DIR ..........."
echo "Build directory - $BUILD_DIR ..........." >> $MAKELOG

#
# build image specified by target
#

echo "Making - $TRG ..........."
echo "Making - $TRG ..........." >> $MAKELOG
echo "timelog `/usr/bin/date` -- building - $TRG" >> $MAKELOG
cd $BUILD_DIR
$MAKETOOL $TRG >> $MAKELOG 2>&1



#
# generate error log
#
echo "Checking for errors ..........."
echo "timelog `/usr/bin/date` -- checking for errors" >> $MAKELOG


echo "Error log for CVS workarea $BUILD_DIR" > $ERRORLOG
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
echo "Timing log for CVS workarea $BUILD_DIR" > $TIMELOG
/usr/bin/date >> $TIMELOG 
echo " " >> $TIMELOG
grep timelog $MAKELOG >> $TIMELOG


#
# send error log via mail
#

#if [ $NOMAIL -eq "mail" ]
#then
#  echo "Review error_log at $ERRORLOG"
#  /usr/ucb/mail $USER < $ERRORLOG
#else
#  echo "Review error_log at $ERRORLOG"
#fi

#
# we're done!!
#

echo "Done at `/usr/bin/date`"
echo "Done at `/usr/bin/date`" >> $MAKELOG

exit 0
