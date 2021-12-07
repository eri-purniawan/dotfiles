#!/bin/bash

sc="$(scrot '/home/eri/Screenshot/%b%d_%H:%M:%S.png')"

if $sc ; then
	notify-send -t 4000 " Success!"
fi

