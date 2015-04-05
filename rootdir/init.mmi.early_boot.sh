#!/system/bin/sh

PATH=/system/bin

function advance_system_time()
{
        min_utc=$1
        systime=`date +%s`

        # Is current date less then minumun acceptable date
        if [ $systime -lt $min_utc ]
        then
                echo "set system time to $min_utc"
                date $min_utc
        fi
}

# Advance system time to SW build date as early as possible
# in the script to avoid race condition with time daemon
build_date_utc=`getprop ro.build.date.utc`
if [ ! -z $build_date_utc ]; then
        advance_system_time $build_date_utc
fi
