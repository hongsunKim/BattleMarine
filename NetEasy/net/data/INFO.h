/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../../CommonHeader.h"

#pragma pack(4)
struct SInfoServerGsToCl {
	SInfoServerGsToCl()	{ memset(this, 0, sizeof(SInfoServerGsToCl)); }

	tick_t	tick;
};

struct SInfoUserListGsToCl {
	SInfoUserListGsToCl()	{ memset(this, 0, sizeof(SInfoUserListGsToCl)); }

	const char*
	GetName() {
		return name;
	}
	
	void
	SetName(const char* o) {
		memcpy(name, o, iPLAYER_NAME_LEN);
		name[iPLAYER_NAME_LEN] = '\0';
	}
	
	UINT32	actor;
	UINT32	target;
	char	name[iPLAYER_NAME_LEN+1];
};

struct SInfoUserInGsToCl {
	SInfoUserInGsToCl() { memset(this, 0, sizeof(SInfoUserInGsToCl)); }

	const char*
		GetName() {
		return name;
	}

	void
		SetName(const char* o) {
		memcpy(name, o, iPLAYER_NAME_LEN);
		name[iPLAYER_NAME_LEN] = '\0';
	}

	UINT	target;
	char	name[iPLAYER_NAME_LEN + 1];
};

struct SInfoUserOutGsToCl {
	UINT	target;
};

#pragma pack()
