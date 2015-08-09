#!/system/bin/sh

PATH=/system/bin

function advance_system_time()
{
	min_utc=$1
	current_utc=`date +%s`

	# Is current date less then minumun acceptable date
	if [ $current_utc -lt $min_utc ]
	then
		day_s=$(( 24 * 60 * 60 ))
		# Average duration of month in seconds
		month_s=$(( $day_s * 30 + $day_s * 4375 / 10000 ))
		year_s=$(( $month_s * 12 ))

		# Convert UTC time to format accepted by date
		year=$(( $min_utc / $year_s + 1970 ))
		yr=$(( $min_utc % $year_s ))
		month=$(( $yr / $month_s + 1))
		mr=$(( $yr % $month_s ))
		if [ $month -le 9 ]
		then
			month="0$month"
		fi
		day=$(( $mr / $day_s + 1))
		if [ $day -le 9 ]
		then
			day="0$day"
		fi

		echo "set system time to $year$month$day.0"
		date -s "$year$month$day.0"
	fi
}

# Advance system time to SW build date as early as possible
# in the script to avoid race condition with time daemon
build_date_utc=`getprop ro.build.date.utc`
if [ ! -z $build_date_utc ]; then
        advance_system_time $build_date_utc
fi
