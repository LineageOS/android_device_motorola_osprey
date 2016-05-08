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

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#define ISMATCH(a,b)    (!strncmp(a,b,PROP_VALUE_MAX))

void setMsim()
{
    property_set("persist.radio.force_get_pref", "1");
    property_set("persist.radio.multisim.config", "dsds");
    property_set("ro.telephony.ril.config", "simactivation");
}

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char radio[PROP_VALUE_MAX];
    char sku[PROP_VALUE_MAX];
    char carrier[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.boot.radio", radio);
    property_get("ro.boot.hardware.sku", sku);
    property_get("ro.boot.carrier", carrier);

    property_set("ro.telephony.default_network", "9");
    property_set("ro.gsm.data_retry_config", "default_randomization=2000,max_retries=infinite,1000,1000,80000,125000,485000,905000");

    if (ISMATCH(sku, "XT1540")) {
        /* XT1540 */
        property_set("ro.product.device", "osprey_umts");
        property_set("ro.build.description", "osprey_retus-user 6.0.1 MPI24.107-55 33 release-keys");
        property_set("ro.build.fingerprint", "motorola/osprey_retus/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
        property_set("ro.build.product", "osprey_umts");
        property_set("ro.mot.build.customerid", "retus");
        property_set("ro.gsm.data_retry_config", "");
    } else if (ISMATCH(sku, "XT1541")) {
        /* XT1541 */
        property_set("ro.product.device", "osprey_umts");
        property_set("ro.build.description", "osprey_reteu-user 6.0.1 MPI24.107-55 33 release-keys");
        property_set("ro.build.fingerprint", "motorola/osprey_reteu/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
        property_set("ro.build.product", "osprey_umts");
        property_set("ro.mot.build.customerid", "reteu");
        property_set("ro.fsg-id", "emea");
        property_set("persist.radio.mot_ecc_custid", "emea");
        property_set("persist.radio.process_sups_ind", "0");
    } else if (ISMATCH(sku, "XT1542")) {
        /* XT1542 */
        property_set("ro.product.device", "osprey_umts");
        property_set("ro.build.description", "osprey_retla-user 6.0.1 MPI24.107-55 33 release-keys");
        property_set("ro.build.fingerprint", "motorola/osprey_retla/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
        property_set("ro.build.product", "osprey_umts");
        property_set("ro.mot.build.customerid", "retla");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (ISMATCH(sku, "XT1543") || ISMATCH(radio, "0x6")) {
        /* XT1543 */
        setMsim();
        property_set("ro.product.device", "osprey_uds");
        property_set("ro.build.description", "osprey_retla_ds-user 6.0.1 MPI24.107-55 33 release-keys");
        property_set("ro.build.fingerprint", "motorola/osprey_retla_ds/osprey_uds:6.0.1/MPI24.107-55/33:user/release-keys");
        property_set("ro.build.product", "osprey_uds");
        property_set("ro.mot.build.customerid", "retla");
        property_set("ro.fsg-id", "dstv");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (ISMATCH(sku, "XT1544")) {
        /* XT1544 */
        setMsim();
        property_set("ro.product.device", "osprey_udstv");
        property_set("ro.build.description", "osprey_retbr_dstv-user 6.0.1 MPI24.107-55 33 release-keys");
        property_set("ro.build.fingerprint", "motorola/osprey_retbr_dstv/osprey_udstv:6.0.1/MPI24.107-55/33:user/release-keys");
        property_set("ro.build.product", "osprey_udstv");
        property_set("ro.mot.build.customerid", "retbr");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (ISMATCH(sku, "XT1548")) {
        /* XT1548 */
        if (ISMATCH(carrier, "sprint")) {
            property_set("ro.build.description", "osprey_sprint-user 6.0.1 MPI24.107-55 33 release-keys");
            property_set("ro.build.fingerprint", "motorola/osprey_sprint/osprey_cdma:6.0.1/MPI24.107-55/33:user/release-keys");
            property_set("ro.mot.build.customerid", "sprint");
            property_set("ro.cdma.home.operator.alpha", "Virgin Mobile US");
            property_set("ro.cdma.home.operator.numeric", "311490");
            property_set("ro.fsg-id", "sprint");
        } else /*if (ISMATCH(carrier, "usc"))*/ {
            property_set("ro.build.description", "osprey_usc-user 6.0.1 MPI24.107-55 33 release-keys");
            property_set("ro.build.fingerprint", "motorola/osprey_usc/osprey_cdma:6.0.1/MPI24.107-55/33:user/release-keys");
            property_set("ro.mot.build.customerid", "usc");
            property_set("ro.cdma.home.operator.alpha", "U.S. Cellular");
            property_set("ro.cdma.home.operator.numeric", "311580");
            property_set("ro.fsg-id", "usc");
        }
        property_set("ro.product.device", "osprey_cdma");
        property_set("ro.build.product", "osprey_cdma");
        property_set("ro.cdma.data_retry_config", "max_retries=infinite,0,0,10000,10000,100000,10000,10000,10000,10000,140000,540000,960000");
        property_set("ro.product.locale.region", "US");
        property_set("gsm.sim.operator.iso-country", "US");
        property_set("gsm.operator.iso-country", "US");
        property_set("ril.subscription.types", "NV,RUIM");
        property_set("ro.ril.force_eri_from_xml", "true");
        property_set("ro.telephony.default_cdma_sub", "0");
        property_set("ro.telephony.default_network", "10");
        property_set("ro.telephony.get_imsi_from_sim", "true");
        property_set("telephony.lteOnCdmaDevice", "1");
    } else if (ISMATCH(sku, "XT1550")) {
        /* XT1550 */
        setMsim();
        property_set("ro.product.device", "osprey_uds");
        property_set("ro.build.description", "osprey_retasia_ds-user 6.0.1 MPI24.107-55 35 release-keys");
        property_set("ro.build.fingerprint", "motorola/osprey_retasia_ds/osprey_uds:6.0.1/MPI24.107-55/35:user/release-keys");
        property_set("ro.build.product", "osprey_uds");
        property_set("ro.mot.build.customerid", "retasia");
        property_set("ro.fsg-id", "apac");
        property_set("persist.radio.mot_ecc_custid", "emea");
        property_set("persist.radio.process_sups_ind", "0");
    }

    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    INFO("Found sku id: %s setting build properties for %s device\n", sku, devicename);
}
