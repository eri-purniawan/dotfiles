#!/usr/bin/bash

# Volume notification: Pulseaudio and dunst
# inspired by gist.github.com/sebastiencs/5d7227f388d93374cebdf72e783fbd6a


icon_path=/usr/share/icons/flattrcolor/status/22/
notify_id=506
sink_nr=1   # use `pacmd list-sinks` to find out sink_nr


function get_volume {
    pacmd list-sinks | awk '/\tvolume:/ { print $5 }' | tail -n+$((sink_nr+1)) | head -n1 | cut -d '%' -f 1
}

function get_volume_icon {
    if [ "$1" -lt 34 ]
    then
        echo -n "audio-volume-low.svg"
    elif [ "$1" -lt 67 ]
    then
        echo -n "audio-volume-medium.svg"
    elif [ "$1" -le 100 ]
    then
        echo -n "audio-volume-medium.svg"
    else
        echo -n "xfce4-mixer-volume-very-high.svg"
    fi
}

function volume_notification { 
    volume=`get_volume`
    vol_icon=`get_volume_icon $volume`
    bar=$(seq -s "" $(($volume / 5)) | sed 's/[0-9]//g')
    dunstify -r $notify_id -u low -i $icon_path$vol_icon $bar
}

function mute_notification {
    muted=$(pacmd list-sinks | awk '/muted/ { print $2 }' | tail -n+$((sink_nr+1)) | head -n1)
    if [ $muted == 'yes' ]
    then
        dunstify -r $notify_id -u low -i ${icon_path}audio-volume-muted.svg Mute
    else
        dunstify -r $notify_id -u low -i ${icon_path}`get_volume_icon $(get_volume)` Unmute
    fi
}

case $BUTTON$1 in
    4)
        pactl set-sink-volume $sink_nr +5%
        volume_notification
        ;;
    5)
        pactl set-sink-volume $sink_nr -5%
        volume_notification
	    ;;
    1)
        pactl set-sink-mute $sink_nr toggle
        mute_notification
        ;;
    3)	pavucontrol ;;
    *)
        echo "Usage: $0 up | down | mute"
        ;;
esac

: 'case $BUTTON in
	1) pamixer -t ;;
	3) pavucontrol ;;
	4) pamixer -i 5 ;;
	5) pamixer -d 5 ;;
esac '

