/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../../CommonHeader.h"

#pragma pack(4)

typedef struct SOtherMoveStartGsToCl {
	SOtherMoveStartGsToCl()		{ memset(this, 0, sizeof(SOtherMoveStartGsToCl)); }

	UINT32		actor;

	SPosition	pos;
	UINT32		dir;
} SCheatWarpGsToCl;

struct SOtherMoveStopGsToCl {
	SOtherMoveStopGsToCl()		{ memset(this, 0, sizeof(SOtherMoveStopGsToCl)); }

	UINT32		actor;
};

struct SOtherRespawnGsToCl {
	SOtherRespawnGsToCl()		{ memset(this, 0, sizeof(SOtherRespawnGsToCl)); }

	UINT32		actor;

	SPosition	pos;
	SColor		color;
	TEAM_TYPE	team;
};

struct SOtherAttackGsToCl {
	SOtherAttackGsToCl()		{ memset(this, 0, sizeof(SOtherAttackGsToCl)); }

	UINT32		actor;
	UINT32		target;
	SPosition	mapIdx;
};

typedef SOtherAttackGsToCl SOtherInfestGsToCl;

//struct SOtherInfestGsToCl {
//	SOtherInfestGsToCl() { memset(this, 0, sizeof(SOtherInfestGsToCl)); }
//
//	UINT32		actor;
//	UINT32		target;
//	SPosition	mapIdx;
//};

struct SOtherSteamPackGsToCl {
	SOtherSteamPackGsToCl() { memset(this, 0, sizeof(SOtherSteamPackGsToCl)); }

	UINT32		actor;
};

#pragma pack()
