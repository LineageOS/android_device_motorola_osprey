/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

void gsm_properties();
void cdma_properties(char cdma_sub[]);


void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char radio[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.boot.radio", radio);

    if (ISMATCH(radio, "0x7")) {
        /* XT1521 */
	gsm_properties();
        property_set("ro.product.name", "surnia_retasia_ds");
	property_set("ro.product.model", "XT1521");
        property_set("ro.product.device", "surnia_uds");
        property_set("ro.build.product", "surnia_uds");
        property_set("ro.build.description", "surnia_reteu-user 5.0.2 LXI22.50-53.1 1 release-keys");
        property_set("ro.build.fingerprint", "motorola/surnia_reteu/surnia_umts:5.0.2/LXI22.50-53.1/1:user/release-keys");
        property_set("ro.mot.build.customerid", "retasiaall");
        property_set("persist.radio.multisim.config", "dsds");
        
    } else if (ISMATCH(radio, "0x4")) {
        /* XT1524 */
	gsm_properties();
        property_set("ro.product.name", "surnia_reteu");
	property_set("ro.product.model", "XT1524");
        property_set("ro.product.device", "surnia_umts");
        property_set("ro.build.product", "surnia_umts");
        property_set("ro.build.description", "surnia_reteu-user 5.0.2 LXI22.50-24.1 2 release-keys");
        property_set("ro.build.fingerprint", "motorola/surnia_reteu/surnia_umts:5.0.2/LXI22.50-24.1/2:user/release-keys");
        property_set("ro.mot.build.customerid", "reteuall");
        property_set("persist.radio.multisim.config", "");
    } else if (ISMATCH(radio, "0x1")) {
        /* XT1527 */
	gsm_properties();
        property_set("ro.product.name", "surnia_retus");
	property_set("ro.product.model", "XT1527");
        property_set("ro.product.device", "surnia_umts");
        property_set("ro.build.product", "surnia_umts");
        property_set("ro.build.description", "surnia_retus-user 5.0.2 LXI22.50-24.1 1 release-keys");
        property_set("ro.build.fingerprint", "motorola/surnia_retus/surnia_umts:5.0.2/LXI22.50-24.1/1:user/release-keys");
        property_set("ro.mot.build.customerid", "retus");
        property_set("persist.radio.multisim.config", "");
    } else if (ISMATCH(radio, "0x6")){
        /* XT1523 */
        gsm_properties();
        property_set("ro.product.name", "surnia_retbr_dstv");
	property_set("ro.product.model", "XT1523");
        property_set("ro.product.device", "surnia_udstv");
        property_set("ro.build.product", "surnia_udstv");
        property_set("ro.build.description", "surnia_retbr_dstv-user 5.0.2 LXI22.50-24.1 3 release-keys");
        property_set("ro.build.fingerprint", "motorola/surnia_retbr_dstv/surnia_udstv:5.0.2/LXI22.50-24.1/3:user/release-keys");
        property_set("ro.mot.build.customerid", "retbr");
        property_set("persist.radio.multisim.config", "");
        property_set("persist.radio.multisim.config", "dsds");
    } else if (ISMATCH(radio, "0x3")){
	/* XT1526 */
	cdma_properties("0");
        property_set("ro.product.name", "surnia_boost");
        property_set("ro.product.model", "XT1526");
        property_set("ro.build.description", "surnia_boost-user 5.0.2 LXI22.50-14.8 30 release-keys");
        property_set("ro.build.fingerprint", "motorola/surnia_boost/surnia_cdma:5.0.2/LXI22.50-14.8/30:user/release-keys");
        property_set("persist.radio.multisim.config", "");
        property_set("ro.mot.build.customerid ","sprint");
        property_set("ro.com.android.dataroaming","false");
        property_set("persist.radio.0x9e_not_callname","1");
        property_set("ro.fsg-id", "sprint");
        property_set("ro.diag.enumeration", "diag,serial,rmnet");
        property_set("ro.cdma.subscription", "0");
        property_set("ro.cdma.international.eri", "2,74,124,125,126,157,158,159,193,194,195,196,197,198,228,229,230,231,232,233,234,235");
        property_set("persist.radio.lifecalls", "0");
        property_set("persist.radio.lifetimer", "0");
        property_set("ro.com.google.clientidbase.am", "android-boost-us");
        property_set("ro.com.google.clientidbase.gmm", "android-motorola");
        property_set("ro.com.google.clientidbase.ms", "android-boost-us");
        property_set("ro.com.google.clientidbase.yt", "android-boost-us");
        property_set("ro.com.google.clientidbase", "android-motorola");
        property_set("ro.cdma.home.operator.alpha", "Boost Mobile");
        property_set("ro.cdma.home.operator.numeric", "311870");
        property_set("ro.carrier", "Boost Mobile");
        property_set("gsm.operator.alpha", "Boost Mobile");
        property_set("gsm.operator.numeric", "311870");
        property_set("ro.cdma.default_alpha", "Boost Mobile");
        property_set("ro.cdma.default_numeric", "311870");
    }

    property_get("ro.product.device", device);
    property_set("ro.product.display", "Moto E");
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found radio id: %s setting build properties for %s device\n", radio, devicename);
}
void cdma_properties(char cdma_sub[])
{
    property_set("ril.subscription.types","NV,RUIM");
    property_set("DEVICE_PROVISIONED","1");
    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.telephony.default_network", "8");
}
void gsm_properties()
{
    property_set("telephony.lteOnGsmDevice", "1");
    property_set("ro.telephony.default_network", "9");
}
