#!/bin/bash
#
# colorloop.sh -- control Philips Hue light in a loop
#

ontime=5
offtime=5

if [ $# -lt "1" ]
then
	echo "Usage: colorloop.sh <count>"
	echo "i.e.:  colorloop.sh 10"
	exit
fi

loopcount=$1

current=1

echo " "
echo "COLORLOOP TEST - starting ..."
echo "COLORLOOP TEST - ............ loopcount $loopcount ..."
echo " "

while [[ $current -le $loopcount ]] 
do
	echo " "
	echo "COLORLOOP TEST - loop $current start"
	echo " "

    color.sh red 
    sleep $ontime

    color.sh green
    sleep $ontime

    color.sh blue
    sleep $ontime

    color.sh orange
    sleep $ontime

    color.sh purple
    sleep $ontime

    color.sh yellow
    sleep $ontime

    color.sh white
    sleep $ontime

	echo " "
	echo "COLORLOOP TEST - loop $current end"
	echo " "
	sleep $offtime

	let current=$current+1
done

echo " "
echo "COLORLOOP TEST - done."
echo " "

exit

