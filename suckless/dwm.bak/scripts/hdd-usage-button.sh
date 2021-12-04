#!/bin/sh

size="$(df -h / | grep /dev/sdb3 | awk '{print$2'})"
used="$(df -h / | grep /dev/sdb3 | awk '{print$3}')"
usedperc="$(df -h / | grep /dev/sdb3 | awk '{print$5}')"
avail="$(df -h / | grep /dev/sdb3 | awk '{print$4}')"

case $BUTTON in
	1) notify-send --icon=Disk-Info " Disk" " ----------------------
 Size : $size 
 Used : $used - $usedperc 
 Available : $avail";;
	3) st -e ranger ;;
esac

