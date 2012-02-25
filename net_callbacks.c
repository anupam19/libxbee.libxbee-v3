/*
	libxbee - a C library to aid the use of Digi's XBee wireless modules
	          running in API mode (AP=2).

	Copyright (C) 2009	Attie Grande (attie@attie.co.uk)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.	If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "internal.h"
#include "xbee_int.h"
#include "net.h"
#include "net_callbacks.h"
#include "mode.h"
#include "conn.h"
#include "log.h"

/* ######################################################################### */

void xbee_net_start(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	int i, o;
	int callbackCount;
	struct xbee_buf *iBuf;
	size_t bufLen;
	size_t memSize;
	
	
	client = *data;

	if (strncasecmp((char *)(*pkt)->data, libxbee_commit, (*pkt)->dataLen)) {
#ifndef XBEE_NO_NET_STRICT_VERSIONS
		unsigned char buf[2];
		buf[0] = (*pkt)->frameId;
		buf[1] = 0x02;
		xbee_connTx(con, NULL, buf, 2);
		client->die = 1;
		return;
#else
		xbee_log(-1, "*** client with mismatched version connected... this may cause instability ***");
#endif
	}

	memSize = 0;
	for (i = 1; xbee_netServerCallbacks[i].callback; i++) {
		memSize += strlen(xbee_netServerCallbacks[i].name) + 1;
	}
	callbackCount = i;
	
	memSize += 1; /* for an 8 bit 'count' */
	memSize += 2; /* for the frameId, and return value */
	bufLen = memSize;
	
	memSize += sizeof(*iBuf);
	
	if ((iBuf = malloc(memSize)) == NULL) {
		/* out of memory */
		unsigned char buf[2];
		buf[0] = (*pkt)->frameId;
		buf[1] = 0x01; /* <-- this means intenal error */
		xbee_connTx(con, NULL, buf, 2);
		return;
	}
	
	iBuf->len = bufLen;
	iBuf->data[0] = (*pkt)->frameId;
	iBuf->data[1] = 0x00; /* <-- success */
	iBuf->data[2] = callbackCount - 1; /* -1 cos we started at 1, not 0 */
	for (i = 1, o = 3; i < callbackCount; i++) {
		o += snprintf((char *)&(iBuf->data[o]), iBuf->len - o, "%s", xbee_netServerCallbacks[i].name) + 1;
	}
	
	xbee_connTx(con, NULL, iBuf->data, iBuf->len);
	
	free(iBuf);

	client->started = 1;
}

void xbee_net_echo(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	xbee_connTx(con, NULL, (*pkt)->data, (*pkt)->dataLen);
}

/* ######################################################################### */

void xbee_net_conNew(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

void xbee_net_conValidate(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

/* ######################################################################### */

void xbee_net_connTx(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

void xbee_net_conRx(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

/* ######################################################################### */

void xbee_net_conSleep(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

/* ######################################################################### */

void xbee_net_conInfoGet(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

/* ######################################################################### */

void xbee_net_conSettings(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

/* ######################################################################### */

void xbee_net_conEnd(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	client = *data;
	if (!client->started) return;
	
}

/* ######################################################################### */

void xbee_net_conGetTypes(struct xbee *xbee, struct xbee_con *con, struct xbee_pkt **pkt, void **data) {
	struct xbee_netClientInfo *client;
	int typeCount;
	struct xbee_buf *iBuf;
	int i, o;
	size_t bufLen;
	size_t memSize;
	struct xbee_modeConType *conType;
	
	client = *data;
	
	if (!client->started) return;
	
	memSize = 0;
	for (i = 0; xbee->iface.conTypes[i].name; i++) {
		memSize += strlen(xbee->iface.conTypes[i].name) + 2; /* 1 for '\0', 1 for flags */
	}
	typeCount = i;
	
	memSize += 1; /* for an 8 bit 'count' */
	memSize += 2; /* for the frameId and return value */
	bufLen = memSize;
	
	memSize += sizeof(*iBuf);
	
	if ((iBuf = malloc(memSize)) == NULL) goto err;
	
	iBuf->len = bufLen;
	iBuf->data[0] = (*pkt)->frameId;
	iBuf->data[1] = 0x00; /* <-- success */
	iBuf->data[2] = typeCount;
	for (i = 0, o = 3; i < typeCount; i++) {
		conType = &(xbee->iface.conTypes[i]);
		iBuf->data[o] = 0;
		if (conType->allowFrameId) iBuf->data[o] |= 0x01;
		if (conType->rxHandler)    iBuf->data[o] |= 0x02;
		if (conType->txHandler)    iBuf->data[o] |= 0x04;
		o++;
		o += snprintf((char *)&(iBuf->data[o]), iBuf->len - o, "%s", conType->name) + 1;
	}
	
	xbee_connTx(con, NULL, iBuf->data, iBuf->len);
	
	free(iBuf);
	
	return;
err:
	{
		unsigned char buf[2];
		buf[0] = (*pkt)->frameId;
		buf[1] = 0x01; /* <-- this means intenal error */
		xbee_connTx(con, NULL, buf, 2);
	}
}

/* ######################################################################### */

#define ADD_NETSERVERCALLBACK(cb) { .name = #cb, .callback = xbee_net_##cb },
const struct xbee_netCallback xbee_netServerCallbacks[] = {
	/* backchannel (0x00), endpoint 0 (0x00) is ALWAYS the 'start' function */
	ADD_NETSERVERCALLBACK(start) /* this MUST BE FIRST */
	/* the rest may be ordered for efficiency...
	   e.g: tx is probrably going to be the most commonly called */
	ADD_NETSERVERCALLBACK(connTx)
	ADD_NETSERVERCALLBACK(conRx)
	ADD_NETSERVERCALLBACK(conValidate)
	ADD_NETSERVERCALLBACK(conSleep)
	ADD_NETSERVERCALLBACK(conInfoGet)
	ADD_NETSERVERCALLBACK(conSettings)
	ADD_NETSERVERCALLBACK(conNew)
	ADD_NETSERVERCALLBACK(conEnd)
	ADD_NETSERVERCALLBACK(conGetTypes)
	/* these are 'system' functions */
	ADD_NETSERVERCALLBACK(echo)
	/* terminate */
	{ NULL, NULL },
};