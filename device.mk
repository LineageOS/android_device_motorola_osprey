#
# Copyright (C) 2015 The Android Open-Source Project
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
#


LOCAL_PATH := device/motorola/surnia

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

$(call inherit-product-if-exists, vendor/motorola/surnia/surnia-vendor.mk)

# Ramdisk
 PRODUCT_COPY_FILES += \
     $(call find-copy-subdir-files,*,${LOCAL_PATH}/rootdir,root)

# Prebuilt
PRODUCT_COPY_FILES += \
     $(call find-copy-subdir-files,*,${LOCAL_PATH}/prebuilt/system,system)

PRODUCT_AAPT_CONFIG := normal hdpi xhdpi
PRODUCT_AAPT_PREF_CONFIG := hdpi

DEVICE_PACKAGE_OVERLAYS := \
    $(LOCAL_PATH)/overlay

PRODUCT_PACKAGES += \
    gralloc.msm8916 \
    copybit.msm8916 \
    hwcomposer.msm8916 \
    memtrack.msm8916 \
    power.msm8916

PRODUCT_PACKAGES += \
    audio.msm8916 \
    audio_policy.msm8916

PRODUCT_PACKAGES += \
    audiod \
    audio.primary.msm8916 \
    audio.a2dp.default \
    audio.usb.default \
    audio.r_submix.default \
    libaudio-resampler \
    tinymix \
    libqcomvisualizer \
    libqcomvoiceprocessing

# ANT+
PRODUCT_PACKAGES += \
    AntHalService \
    com.dsi.ant.antradio_library \
    libantradio

# Camera
PRODUCT_PACKAGES += \
    camera.msm8916 \
    libmm-qcamera

# Filesystem
PRODUCT_PACKAGES += \
    setup_fs

# Qcom SoftAP & wifi
PRODUCT_PACKAGES += \
    libQWiFiSoftApCfg

# Motorola
PRODUCT_PACKAGES += \
    charge_only_mode

# Misc
PRODUCT_PACKAGES += \
    libxml2

# OMX
PRODUCT_PACKAGES += \
    libdashplayer \
    libOmxCore \
    libOmxVdec \
    libOmxVdecHevc \
    libOmxVenc \
    libstagefrighthw 

PRODUCT_PACKAGES += \
    wlan_module_symlink \
    wlan_persist_symlink \
    wcnss_service

PRODUCT_PACKAGES += \
    librs_jni \
    com.android.future.usb.accessory

# Ebtables
PRODUCT_PACKAGES += \
    ebtables \
    ethertypes \
    libebtc

# FM
PRODUCT_PACKAGES += \
    FM2 \
    FMRecord \
    libqcomfm_jni \
    qcom.fmradio

# Keystore
PRODUCT_PACKAGES += \
    keystore.msm8916

# Lights
PRODUCT_PACKAGES += \
    lights.msm8916

# GPS
PRODUCT_PACKAGES += \
    gps.msm8916

# CRDA
PRODUCT_PACKAGES += \
    crda \
    linville.key.pub.pem \
    regdbdump \
    regulatory.bin

# Misc
PRODUCT_PACKAGES += \
    curl \
    libbson \
    libcurl \
    tcpdump

# Wifi
PRODUCT_PACKAGES += \
    p2p_supplicant_overlay.conf \
    wpa_supplicant_overlay.conf

# Wifi
PRODUCT_PACKAGES += \
    hostapd.accept \
    hostapd_default.conf \
    hostapd.deny \
    hostapd \
    wpa_supplicant \
    wpa_supplicant.conf \
    dhcpcd.conf

PRODUCT_PACKAGES += \
    WCNSS_qcom_wlan_factory_nv.bin

# Inhert dalvik heap values from aosp
$(call inherit-product, frameworks/native/build/phone-xhdpi-1024-dalvik-heap.mk)

$(call inherit-product-if-exists, hardware/qcom/msm8x74/msm8x74.mk)
