#!/bin/sh

ip="$(ip a | grep tap-easytether | grep inet | awk '{print$2}')"
indicat="$(ip a | grep tap-easytether | grep inet | awk '{print$2}' | wc -l )"
check () {
	if [ $indicat == 1 ]; then
		echo "  Online"
	else
		echo "  Offline"
	fi
}

check_ip () {
	if [ $indicat == 1 ]; then
		echo $ip
	else
		echo "Unknown"
	fi
}

case $BUTTON in
	1) notify-send --icon=Network-info "  Network" " -----------------
 Ip Address:   $(check_ip)
 Status    : $(check)" ;;
	3) st -e tether ;;
esac


