/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../../CommonHeader.h"

#pragma pack(4)

struct SUserMoveClToGs {
	SUserMoveClToGs()		{ memset(this, 0, sizeof(SUserMoveClToGs)); }

	SPosition	pos;
	UINT32		dir;
};

struct SUserAttackClToGs {
	SUserAttackClToGs()		{ memset(this, 0, sizeof(SUserAttackClToGs)); }

	UINT		target;
	SPosition	mapIdx;

};

typedef SUserAttackClToGs SUserInfestClToGs;

//struct SUserInfestClToGs {
//	SUserInfestClToGs() { memset(this, 0, sizeof(SUserInfestClToGs)); }
//
//	UINT		target;
//	SPosition	mapIdx;
//
//};

struct SUserAttackGsToCl {
	SUserAttackGsToCl() { memset(this, 0, sizeof(SUserAttackGsToCl)); }

	UINT		target;
	SPosition	mapIdx;
};

typedef SUserAttackGsToCl SUserInfestGsToCl;

//struct SUserInfestGsToCl {
//	SUserInfestGsToCl() { memset(this, 0, sizeof(SUserInfestGsToCl)); }
//
//	UINT		target;
//	SPosition	mapIdx;
//};

typedef struct SUserSteamPackClToGs{
	SUserSteamPackClToGs() { memset(this, 0, sizeof(SUserSteamPackClToGs)); }

	BOOL		IsSteamPack;
	FLOAT		SteamPackTime;
}SUserSteamPackGsToCl;

//장현우
typedef struct SUserChatClToGs{
	SUserChatClToGs() { memset(this, 0, sizeof(SUserChatClToGs)); }

	void Setchar(const char* o) {
		memcpy(chat, o, iPLAYER_CHAT_LEN);
		chat[iPLAYER_CHAT_LEN] = '\0';
	}

	void Setname(const char* o) {
		memcpy(name, o, iPLAYER_NAME_LEN);
		name[iPLAYER_NAME_LEN] = '\0';
	}

	char	name[iPLAYER_NAME_LEN + 1];
	char	chat[iPLAYER_CHAT_LEN + 1];
} SUserChatGsToCl;

struct SuserKillGsToCl
{
	SuserKillGsToCl() { memset(this, 0, sizeof(SuserKillGsToCl)); }

	void SetActor(const UINT o)
	{
		actor = o;
	}

	UINT GetActor()
	{
		return actor;
	}

private:
	UINT actor;
};

#pragma pack()