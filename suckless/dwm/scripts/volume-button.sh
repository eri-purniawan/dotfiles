#!/bin/sh

case $BUTTON in
	1) pamixer -t ;;
	3) pavucontrol ;;
	4) pamixer -i 5 ;;
	5) pamixer -d 5 ;;
esac

