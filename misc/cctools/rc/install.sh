#!/bin/sh
#
# install.sh - installs .smmrc files and sets up link for specified site
#
# Usage:
#	install.sh <site> 
#
#	<site>	- site abbreviation {ie, mw, ne, sd}
#
# Notes:
#	- script must be executed from $PROJHOME/cctools/rc
#	- script assumes $CCHOME is defined
#
# Revisions:
#	06/29/98 BSL 	originated
#



if [ $# -lt "1" ]
then
  echo "Usage: install.sh [ie|mw|ne|sd]"
  echo "(i.e.  install.sh ne)"
  exit 1
fi


#
# if site specific file exists, install and create link
#
if [ -f $1.smmrc ]
then
  rm -f $CCHOME/.smmrc

  cp $1.smmrc $CCHOME/$1.smmrc

  ln -s $CCHOME/$1.smmrc .smmrc

  echo "Done."
else
  echo "Unknown site specified - $1"
  exit 1
fi


exit 0
