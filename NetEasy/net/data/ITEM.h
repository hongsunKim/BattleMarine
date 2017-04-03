/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */
#pragma once
#include "../../CommonHeader.h"

#pragma pack(4)

struct SItemDropClToGs {
	SItemDropClToGs() { memset(this, 0, sizeof(SItemDropClToGs)); }

	UINT32	owner;
	UINT32  victim;

};

struct SItemDropGsToCl {
	SItemDropGsToCl() { memset(this, 0, sizeof(SItemDropGsToCl)); }

	UINT32		owner;
	UINT32		victim;
	UINT32		drop_id;
	UINT64		serial;
	SPosition	pos;
};

struct SItemUseClToGs {
	SItemUseClToGs() { memset(this, 0, sizeof(SItemUseClToGs)); }

	UINT32 user;
	UINT64 serial;
};

struct SItemUseGsToCl {
	SItemUseGsToCl() { memset(this, 0, sizeof(SItemUseGsToCl)); }

	UINT32 user;
	UINT64 serial;
};

struct SItemPickClToGs {
	SItemPickClToGs() { memset(this, 0, sizeof(SItemPickClToGs)); }

	UINT32  picker;
	UINT64	serial;
};

struct SItemPickGsToCl {
	SItemPickGsToCl() { memset(this, 0, sizeof(SItemPickGsToCl)); }

	UINT32  picker;
	UINT64	serial;
};

struct SItemEnterClToGs {
	SItemEnterClToGs() { memset(this, 0, sizeof(SItemEnterClToGs)); }
};

struct SItemEnterGsToCl {
	SItemEnterGsToCl() { memset(this, 0, sizeof(SItemEnterGsToCl)); }

	UINT32	drop_id;
	//	UINT64	serial;
	FLOAT	x;
	FLOAT	y;
};

struct SItemLeaveClToGs {
	SItemLeaveClToGs() { memset(this, 0, sizeof(SItemLeaveClToGs)); }

};

struct SItemLeaveGsToCl {
	SItemLeaveGsToCl() { memset(this, 0, sizeof(SItemLeaveGsToCl)); }

	//	UINT32	drop_id;
	UINT64  serial;
};

#pragma pack()