/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../GlobalVariable.h"

#pragma pack(4)

struct SItemData {
	SItemData() : id(0), stocks(0), serial(0) {}
	SItemData(const SItemData& o) : id(o.id), stocks(o.stocks), serial(o.serial) {}

	void	operator =(const SItemData& rval_) {
				id = rval_.id;
				stocks = rval_.stocks;
				serial = rval_.serial;
			}

	bool	operator ==(SItemData& rval_) {
				if(serial == rval_.serial) {
					return true;
				}
				return false;
			}

	bool	operator !=(SItemData& rval_)	{
				if(serial != rval_.serial) {
					return true;
				}
				return false;
			}

	void	Clear()	{ memset(this, 0, sizeof(SItemData)); }

	UINT32	id:23;
	UINT32	stocks:9;
	UINT64	serial;
};

#pragma pack()
