vol="$(pamixer --get-volume)"
vol_mute="$(pamixer --get-mute)"

if [ $vol -eq 0 ] || [ $vol_mute == true ]; then
	echo "婢"
elif [ $vol -gt 0 ] && [ $vol -le 65 ]; then
	echo " $vol %"
else
	echo " $vol %"
fi
