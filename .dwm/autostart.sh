#!/bin/sh

nitrogen --restore &
picom &
dunst &
killall /usr/lib/xfce-polkit/xfce-polkit
/usr/lib/xfce-polkit/xfce-polkit &

killall slstatus
slstatus &

xset s off
xset -dpms
