# Copyright (C) 2015-2016 The CyanogenMod Project
#               2017-2018 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

$(call inherit-product, device/motorola/osprey/full_osprey.mk)

# Boot animation
TARGET_SCREEN_WIDTH := 720
TARGET_SCREEN_HEIGHT := 1280

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := osprey
PRODUCT_NAME := lineage_osprey
PRODUCT_MODEL := MotoG3
PRODUCT_BRAND := Motorola
PRODUCT_MANUFACTURER := Motorola
PRODUCT_RELEASE_NAME := osprey

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="osprey_reteu-user 6.0.1 MPIS24.107-55-2-12 9 release-keys"

BUILD_FINGERPRINT := "motorola/osprey_retus/osprey_umts:6.0/MPI24.65-25.1/1:user/release-keys"
