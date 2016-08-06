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

int is2GB()
{
    int ram_size;
    FILE *fp;

    fp = fopen("/sys/ram/size", "r");
    fscanf(fp, "%d", &ram_size);
    pclose(fp);

    return ram_size > 1024;
}

void vendor_load_properties()
{
    bool MSIM;
    char gb[PROP_VALUE_MAX];
    char carrier[PROP_VALUE_MAX];
    char customerid[PROP_VALUE_MAX];
    char description[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char ds[PROP_VALUE_MAX];
    char fingerprint[PROP_VALUE_MAX];
    char platform[PROP_VALUE_MAX];
    char radio[PROP_VALUE_MAX];
    char sku[PROP_VALUE_MAX];
    char tv[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    // Warning-less way of sprintf(var, "");
    ds[0] = 0;
    tv[0] = 0;
    MSIM = false;
    property_get("ro.boot.radio", radio);
    property_get("ro.boot.hardware.sku", sku);
    property_get("ro.boot.carrier", carrier);

    if (is2GB()) {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "512m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "512k");
        property_set("dalvik.vm.heapmaxfree", "8m");
        sprintf(gb, "_2gb");
    } else {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "96m");
        property_set("dalvik.vm.heapsize", "256m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "2m");
        property_set("dalvik.vm.heapmaxfree", "8m");
        gb[0] = 0;
    }

    property_set("ro.telephony.default_network", "9");
    property_set("ro.gsm.data_retry_config", "default_randomization=2000,max_retries=infinite,1000,1000,80000,125000,485000,905000");

    if (ISMATCH(sku, "XT1540")) {
        /* XT1540 */
        sprintf(device, is2GB() ? "osprey_u2" : "osprey_umts");
        sprintf(customerid, "retus");
        property_set("ro.gsm.data_retry_config", "");
    } else if (ISMATCH(sku, "XT1541")) {
        /* XT1541 */
        sprintf(device, is2GB() ? "osprey_u2" : "osprey_umts");
        sprintf(customerid, "reteu");
        property_set("ro.fsg-id", "emea");
        property_set("persist.radio.process_sups_ind", "0");
    } else if (ISMATCH(sku, "XT1542")) {
        /* XT1542 */
        sprintf(device, is2GB() ? "osprey_u2" : "osprey_umts");
        sprintf(customerid, "retla");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (ISMATCH(sku, "XT1543") || ISMATCH(radio, "0x6")) {
        /* XT1543 */
        MSIM = true;
        sprintf(device, is2GB() ? "osprey_ud2" : "osprey_uds");
        sprintf(customerid, "retla");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (ISMATCH(sku, "XT1544")) {
        /* XT1544 */
        MSIM = true;
        sprintf(device, "osprey_udstv");
        sprintf(customerid, "retbr");
        sprintf(tv, "tv");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (ISMATCH(sku, "XT1548")) {
        /* XT1548 */
        if (ISMATCH(carrier, "sprint")) {
            sprintf(customerid, "sprint");
            property_set("ro.cdma.home.operator.alpha", "Virgin Mobile US");
            property_set("ro.cdma.home.operator.numeric", "311490");
            property_set("ro.fsg-id", "sprint");
        } else /*if (ISMATCH(carrier, "usc"))*/ {
            sprintf(customerid, "usc");
            property_set("ro.cdma.home.operator.alpha", "U.S. Cellular");
            property_set("ro.cdma.home.operator.numeric", "311580");
            property_set("ro.fsg-id", "usc");
        }
        sprintf(device, "osprey_cdma");
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
        MSIM = true;
        sprintf(device, is2GB() ? "osprey_ud2" : "osprey_uds");
        sprintf(customerid, "retasia");
        property_set("ro.fsg-id", "apac");
        property_set("persist.radio.process_sups_ind", "0");
    }

    if (MSIM) {
        property_set("persist.radio.force_get_pref", "1");
        property_set("persist.radio.multisim.config", "dsds");
        property_set("ro.telephony.ril.config", "simactivation");
        sprintf(ds, "_ds");
    }

    sprintf(description, "osprey_%s%s%s%s-user 6.0.1 MPI24.107-55 33 release-keys", customerid, ds, tv, gb);
    sprintf(fingerprint, "motorola/osprey_%s%s%s%s/%s:6.0.1/MPI24.107-55/33:user/release-keys", customerid, ds, tv, gb, device);

    property_set("ro.product.device", device);
    property_set("ro.build.product", device);
    property_set("ro.build.description", description);
    property_set("ro.build.fingerprint", fingerprint);
    property_set("ro.mot.build.customerid", customerid);

    INFO("Found sku id: %s setting build properties for %s device\n", sku, device);
}
