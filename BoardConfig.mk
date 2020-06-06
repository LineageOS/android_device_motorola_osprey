#
# Copyright (C) 2015-2016 The CyanogenMod Project
# Copyright (C) 2017-2018 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include device/motorola/msm8916-common/BoardConfigCommon.mk

-include vendor/motorola/osprey/BoardConfigVendor.mk

DEVICE_PATH := device/motorola/osprey

# Asserts
TARGET_OTA_ASSERT_DEVICE := osprey,osprey_umts,osprey_u2,osprey_ud2,osprey_uds,osprey_cdma,osprey_sprint,osprey_udstv

# Camera
BOARD_GLOBAL_CFLAGS += -DCONFIG_MSM_USES_M_STACK
TARGET_HAS_LEGACY_CAMERA_HAL1 := true
TARGET_PROCESS_SDK_VERSION_OVERRIDE := \
    /system/bin/cameraserver=23 \
    /system/bin/mediaserver=23 \
    /system/bin/mm-qcamera-daemon=23

# Kernel
TARGET_KERNEL_CONFIG := osprey_defconfig

# Partitions
BOARD_BOOTIMAGE_PARTITION_SIZE := 16777216     # 16384 * 1024 mmcblk0p31
BOARD_CACHEIMAGE_PARTITION_SIZE := 268435456   # 262144 * 1024 mmcblk0p40
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 16879616 # 16484 * 1024 mmcblk0p32
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2432696320 # 2375680 * 1024 mmcblk0p41
BOARD_PERSISTIMAGE_PARTITION_SIZE := 8388608   # 8192 * 1024 mmcblk0p29
BOARD_USERDATAIMAGE_PARTITION_SIZE := 4865261568 # 4751232 * 1024 mmcblk0p42

# Sensors
BOARD_USES_STML0XX_SENSOR_HUB := true
