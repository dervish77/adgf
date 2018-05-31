#!/bin/bash
#
# toggle.sh -- unmounts filesystems, then toggles vbatt
#


~/bin/unmount-main-exp 192.168.0.10

~/bin/unmount-vow-exp 192.168.0.20

~/bin/power-ctl 0

sleep 10

~/bin/power-ctl 1

exit

