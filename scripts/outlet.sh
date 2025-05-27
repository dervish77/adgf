#!/bin/bash
#
# outlet.sh -- control SmartThings outlet via IFTTT Maker channel
#

# Maker channel key
key=pzswrJ5uI8W8XJZhqW0A1

if [ $# -lt "1" ]
then
	echo "Usage: outlet.sh <state> "
	echo "i.e.:  outlet.sh 1"
	exit
fi

state=$1

if [ $state -eq "1" ]
then
    curl -X POST https://maker.ifttt.com/trigger/BSL_outlet_on/with/key/$key
fi

if [ $state -eq "0" ]
then
    curl -X POST https://maker.ifttt.com/trigger/BSL_outlet_off/with/key/$key
fi

exit

