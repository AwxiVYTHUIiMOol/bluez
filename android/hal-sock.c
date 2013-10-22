/*
 * Copyright (C) 2013 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdlib.h>

#include "hal-log.h"
#include "hal.h"

static bt_status_t sock_listen_rfcomm(const char *service_name,
					const uint8_t *uuid, int chan,
					int *sock, int flags)
{
	DBG("");

	return BT_STATUS_UNSUPPORTED;
}

static bt_status_t sock_listen(btsock_type_t type, const char *service_name,
					const uint8_t *uuid, int chan,
					int *sock, int flags)
{
	if ((!uuid && chan <= 0) || !sock) {
		error("%s: invalid params: uuid %p, chan %d, sock %p",
						__func__, uuid, chan, sock);
		return BT_STATUS_PARM_INVALID;
	}

	DBG("uuid %p chan %d sock %p type %d service_name %s",
					uuid, chan, sock, type, service_name);

	switch (type) {
	case BTSOCK_RFCOMM:
		return sock_listen_rfcomm(service_name, uuid, chan, sock,
									flags);
	default:
		error("%s: Socket type %d not supported", __func__, type);
		break;
	}

	return BT_STATUS_UNSUPPORTED;
}

static bt_status_t sock_connect(const bt_bdaddr_t *bdaddr, btsock_type_t type,
					const uint8_t *uuid, int chan,
					int *sock, int flags)
{
	if ((!uuid && chan <= 0) || !bdaddr || !sock) {
		error("invalid params: bd_addr %p, uuid %p, chan %d, sock %p",
					bdaddr, uuid, chan, sock);
		return BT_STATUS_PARM_INVALID;
	}

	DBG("uuid %p chan %d sock %p type %d", uuid, chan, sock, type);

	return BT_STATUS_UNSUPPORTED;
}

static btsock_interface_t sock_if = {
	sizeof(sock_if),
	sock_listen,
	sock_connect
};

btsock_interface_t *bt_get_sock_interface(void)
{
	return &sock_if;
}
