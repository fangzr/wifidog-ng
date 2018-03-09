/*
 * Copyright (C) 2017 Jianhui Zhao <jianhuizhao329@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <libubox/ulog.h>
#include <uhttpd/uhttpd.h>

#include "version.h"
#include "ubus.h"
#include "auth.h"
#include "utils.h"
#include "resolv.h"
#include "config.h"
#include "termianl.h"
#include "check_internet.h"

int main(int argc, char **argv)
{
    ULOG_INFO("wifidog-ng version %s\n", WIFIDOG_NG_VERSION_STRING);

    if (parse_config())
        return -1;
    
    uloop_init();

    resolv_init();

    if (auth_init() < 0)
        goto EXIT;
    
    termianl_init();
    wifidog_ubus_init();
    start_check_internet();

    uloop_run();

EXIT:
    resolv_shutdown();
    uloop_done();
    ULOG_INFO("wifidog-ng exit.\n");
    
    return 0;
}
