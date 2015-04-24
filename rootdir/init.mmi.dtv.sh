#!/system/bin/sh

# check for presence of DTV device and start jellyservice if found
# if not found leave jellyservice disabled to avoid system tombstones

if [ -e /dev/isdbt ]
then
	setprop dtv.hw.status ok
	echo "Starting DTV service"
	start dtv-jelly
else
	setprop dtv.hw.status unavailable
	echo "No DTV device found"
fi
