#!/vendor/bin/sh

# Copyright (c) 2018 Alberto97
#
# Device configuration for osprey variants
#
PATH=/sbin:/vendor/sbin:/vendor/bin:/vendor/xbin
export PATH

radio=`getprop ro.boot.radio`
sku=`getprop ro.boot.hardware.sku`
ram=`cat /sys/ram/size`

set_config_props ()
{
    case $sku in
        # Single SIM Devices
        XT154[0-2] )
            setprop ro.device.dualsim false
        ;;
        # Dual SIM Devices
        XT154[3-4]|XT1550 )
            setprop ro.device.dualsim true
        ;;
    esac

    case $radio in
        # ro.boot.hardware.sku is not populated on some XT1543 devices
        0x6 )
            setprop ro.device.dualsim true
        ;;
    esac
}

set_dalvik_props ()
{
    case $ram in
        # 1GB
        1024 )
            setprop dalvik.vm.heapstartsize "8m"
            setprop dalvik.vm.heapgrowthlimit "96m"
            setprop dalvik.vm.heapsize "256m"
            setprop dalvik.vm.heaptargetutilization "0.75"
            setprop dalvik.vm.heapminfree "2m"
            setprop dalvik.vm.heapmaxfree "8m"
        ;;
        # 2GB
        * )
            setprop dalvik.vm.heapstartsize "8m"
            setprop dalvik.vm.heapgrowthlimit "192m"
            setprop dalvik.vm.heapsize "512m"
            setprop dalvik.vm.heaptargetutilization "0.75"
            setprop dalvik.vm.heapminfree "512k"
            setprop dalvik.vm.heapmaxfree "8m"
        ;;
    esac
}

# Main
set_dalvik_props
set_config_props

return 0
