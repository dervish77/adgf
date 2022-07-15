#!/bin/bash
#
# color.sh -- control Philips Hue light via IFTTT Maker channel
#

# Maker channel key
key=pzswrJ5uI8W8XJZhqW0A1

if [ $# -lt "1" ]
then
	echo "Usage: color.sh <color> "
	echo "i.e.:  color.sh purple"
	exit
fi

color=$1

if [ $color == "red" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"red"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "green" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"green"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "blue" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"blue"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "yellow" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"yellow"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "orange" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"orange"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "purple" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"purple"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "white" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"#FFFFFF"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

if [ $color == "custom" ]
then
    curl -X POST -H "Content-Type: application/json" -d '{"value1":"#652143"}' https://maker.ifttt.com/trigger/BSL_set_hue_color/with/key/$key
fi 

exit

