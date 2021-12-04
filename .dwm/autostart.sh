#!/bin/sh

nitrogen --restore &
picom &
dunst &
killall /usr/lib/xfce-polkit/xfce-polkit &
/usr/lib/xfce-polkit/xfce-polkit &
#xinput --set-prop "Logitech Wireless Mouse PID:4022" "Coordinate Transformation Matrix" 0.9 0 0 0 0.9 0 0 0 1 &

killall slstatus
slstatus &
#killall dwmblocks
#dwmblocks &
