#!/system/bin/sh
system=`stml0xx getversion | cut -d"=" -f2 | cut -d"[" -f1`
hardware=`stml0xx getversion | cut -d"=" -f3 | cut -d"[" -f1`
TAG="scritch007"

if [ "$system" -ge "$hardware" ]; then
	log -t$TAG "Version update or the same $system vs $hardware"
else
	log -t$TAG "Downgrading version"
	#Flush current version
	stml0xx tboot
fi
#Install file system version
stml0xx boot

