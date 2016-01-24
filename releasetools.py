# Copyright (C) 2016 The CyanogenMod Project
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

def IncrementalOTA_VerifyBegin(info):
  # Workaround for apn list changes
  info.script.Mount("/system")
  RestoreApn(info)
  info.script.Unmount("/system")

def IncrementalOTA_InstallEnd(info):
  info.script.Mount("/system")
  BakupApn(info)
  VirginApn(info)
  USCApn(info)
  info.script.Unmount("/system")

def FullOTA_InstallEnd(info):
  info.script.Mount("/system")
  BakupApn(info)
  VirginApn(info)
  USCApn(info)
  info.script.Unmount("/system")

def BakupApn(info):
  info.script.AppendExtra('ifelse(getprop("ro.boot.hardware.sku") == "XT1548", run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf.xml /system/etc/apns-conf.xml.bak"));')

def RestoreApn(info):
  info.script.AppendExtra('ifelse(getprop("ro.boot.hardware.sku") == "XT1548", run_program("/sbin/sh", "-c", "rm /system/etc/apns-conf.xml && mv /system/etc/apns-conf.xml.bak /system/etc/apns-conf.xml"));')

def VirginApn(info):
  info.script.AppendExtra('ifelse(getprop("ro.boot.carrier") == "sprint", run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf-vmob.xml /system/etc/apns-conf.xml"));')

def USCApn(info):
  info.script.AppendExtra('ifelse(getprop("ro.boot.carrier") == "usc", run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf-usc.xml /system/etc/apns-conf.xml"));')
