indicat="$(ip a | grep tap-easytether | grep inet | awk '{print$2}' | wc -l )"
check () {
	if [ $indicat == 1 ]; then
		echo "說"
	else
		echo "ﲁ"
	fi
}

check
