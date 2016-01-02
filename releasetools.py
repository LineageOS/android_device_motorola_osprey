# Copyright (C) 2015 The CyanogenMod Project
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

def FullOTA_Assertions(info):
  AddSkuAssertion(info, info.input_zip)


def IncrementalOTA_Assertions(info):
  AddSkuAssertion(info, info.input_zip)


def AddSkuAssertion(info, input_zip):
  info.script.AppendExtra("assert(" +'getprop("ro.boot.hardware.sku") != "XT1548" || abort("CDMA devices are not supported");' + ");")
