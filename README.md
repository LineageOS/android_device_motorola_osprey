#CM12.1 tree for Moto E LTE (2015)
* Based off https://github.com/Motorola-CyanogenMod/android_device_motorola_surnia
* Most credit should go to the updstream developers (scritch007 and company)
* This fork just uses my "Squid" kernel instead of the stock kernel

##Dependencies:
(you probably don't need most of these)
````
sudo apt-get install bison build-essential curl flex git gnupg gperf libesd0-dev liblz4-tool libncurses5-dev libsdl1.2-dev libwxgtk2.8-dev libxml2 libxml2-utils lzop openjdk-6-jdk openjdk-6-jre pngcrush schedtool squashfs-tools xsltproc zip zlib1g-dev
sudo apt-get install g++-multilib gcc-multilib lib32ncurses5-dev lib32readline-gplv2-dev lib32z1-dev
````
You also need the repo tool for cloning Android source trees.

##Set up and get the repo:
````
mkdir ~/cm12.1-tree
cd ~/cm12.1-tree
repo init -u git://github.com/CyanogenMod/android.git -b cm-12.1
mkdir -p .repo/local_manifests
````

Create a file .repo/local_manifests/styx.xml and paste this in:
````
<?xml version="1.0" encoding="UTF-8"?>
<manifest>
    <project name="sultanqasim/android_device_motorola_surnia" path="device/motorola/surnia" remote="github" revision="cm-12.1" />
    <project name="Motorola-CyanogenMod/android_vendor_motorola_surnia" path="vendor/motorola/surnia" remote="github" revision="cm-12.1" />
    <project name="sultanqasim/android_kernel_surnia" path="kernel/motorola/msm8916" remote="github" revision="squid_cm12" />
    <project name="CyanogenMod/android_hardware_qcom_display-caf-new" path="hardware/qcom/display-caf-new" remote="github" revision="cm-11.0" />
    <project name="CyanogenMod/android_hardware_qcom_fm" path="hardware/qcom/fm" remote="github" />
    <project name="CyanogenMod/android_hardware_qcom_media-caf-new" path="hardware/qcom/media-caf-new" remote="github" revision="cm-11.0" />
    <project name="CyanogenMod/android_frameworks_opt_connectivity" path="frameworks/opt/connectivity" remote="github" revision="cm-11.0" />
    <project name="CyanogenMod/android_device_qcom_common" path="device/qcom/common" remote="github" />
</manifest>
````

Then fetch the repositories
````
repo sync
````

##Building:
````
source build/envsetup.sh
breakfast surnia
make clean
brunch surnia
````
