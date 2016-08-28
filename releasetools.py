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
  RestoreApnList(info)

def IncrementalOTA_InstallEnd(info):
  ReplaceApnList(info)

def FullOTA_InstallEnd(info):
  ReplaceApnList(info)
  ExtractFirmwares(info)

def ExtractFirmwares(info):
  info.script.Mount("/system")
  info.script.Mount("/firmware")
  info.script.AppendExtra('ui_print("Extracting modem firmware");')
  info.script.AppendExtra('run_program("/sbin/sh", "/tmp/install/bin/extract_firmware.sh");')
  info.script.AppendExtra('ui_print("Firmware extracted");')
  info.script.Unmount("/firmware")
  info.script.Unmount("/system")

def ReplaceApnList(info):
  info.script.AppendExtra('if getprop("ro.boot.hardware.sku") == "XT1548" then')
  info.script.Mount("/system")
  info.script.AppendExtra('run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf.xml /system/etc/apns-conf.xml.bak");')
  info.script.AppendExtra('ifelse(getprop("ro.boot.carrier") == "sprint", ' +
                          'run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf-vmob.xml /system/etc/apns-conf.xml"), ' +
                          'run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf-usc.xml /system/etc/apns-conf.xml"));')
  info.script.Unmount("/system")
  info.script.AppendExtra('endif;')

def RestoreApnList(info):
  info.script.AppendExtra('if getprop("ro.boot.hardware.sku") == "XT1548" then')
  info.script.Mount("/system")
  info.script.AppendExtra('delete("/system/etc/apns-conf.xml");')
  info.script.AppendExtra('run_program("/sbin/sh", "-c", "mv /system/etc/apns-conf.xml.bak /system/etc/apns-conf.xml");')
  info.script.Unmount("/system")
  info.script.AppendExtra('endif;')
