#ifndef __XBEE_TX_H
#define __XBEE_TX_H

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

struct xbee_txInfo {
	struct ll_head *bufList;
	xsys_sem sem;
};

xbee_err xbee_txAlloc(struct xbee_txInfo **nInfo);
xbee_err xbee_txFree(struct xbee_txInfo *info);

xbee_err xbee_tx(struct xbee *xbee, int *restart, void *arg);

#endif /* __XBEE_TX_H */