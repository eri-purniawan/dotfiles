#!/bin/sh

proces="$(ps axch -o cmd,%cpu --sort=-%cpu | head)"
cpu_usage="$(top -b -n1 | grep "Cpu(s)" | awk '{print $2 + $4}')%"
cpu_temp="$(paste <(cat /sys/class/thermal/thermal_zone*/type) <(cat /sys/class/thermal/thermal_zone*/temp) | column -s $'\t' -t | sed 's/\(.\)..$/.\1°C/' | tail -n1 | awk '{print$2}')"
mem_usage_used="$(free -h | grep Mem | awk '{print$3}')"
mem_usage_total="$(free -h | grep Mem | awk '{print$2}')"
mem_usage="$mem_usage_used / $mem_usage_total"
swap_usage_used="$(free -h | grep Swap | awk '{print$3}')"
swap_usage_total="$(free -h | grep Swap | awk '{print$2}')"
swap_usage="$swap_usage_used / $swap_usage_total"

case $BUTTON in
	1) notify-send --icon=Resources-Info "  Resources" " ---------------------
   Cpu Usage : $cpu_usage
   Cpu Temp  : $cpu_temp
 ---------------------- 
 ﬙  Mem Usage : $mem_usage
 易  Swap Usage: $swap_usage" ;;
	3) st -e gotop ;;
esac

