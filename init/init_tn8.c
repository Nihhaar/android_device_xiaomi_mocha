/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
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
#include <errno.h>

#include "init.h"
#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"
#include <stdio.h>
#include <string.h>


void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char model[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    /* Wi-Fi Only */
    property_set("ro.build.fingerprint", "nvidia/wx_na_wf/shieldtablet:5.1.1/LMY48C/36442_589.1541:user/release-keys");
    property_set("ro.build.description", "wx_na_wf-user 5.1.1 LMY48C 36442_589.1541 release-keys");
    property_set("ro.product.model", "mocha");
    property_set("ro.radio.noril", "true");

    property_set("ro.product.device", "mocha");
    property_get("ro.product.model", model);
    ERROR("Setting build properties for %s model\n", model);
}

int vendor_handle_control_message(const char *msg, const char *arg)
{
    struct service *sf_svc = NULL;
    struct service *zg_svc = NULL;

    if (!strcmp(msg,"restart") && !strcmp(arg,"consolemode")) {
        sf_svc = service_find_by_name("surfaceflinger");
        zg_svc = service_find_by_name("zygote");

        if (sf_svc && zg_svc) {
            service_stop(zg_svc);
            service_stop(sf_svc);
            service_start(sf_svc, NULL);
            service_start(zg_svc, NULL);
        } else {
            ERROR("Required services not found to toggle console mode");
        }

        return 0;
    }

    return -EINVAL;
}
