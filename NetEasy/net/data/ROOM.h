/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../../ReTypedefined.h"
#include "../../GlobalVariable.h"

#pragma pack(4)

// ROOM_CREATE
struct SRoomCreateClToGs {
	SRoomCreateClToGs() { memset(this, 0, sizeof(SRoomCreateClToGs)); }

	const char*	GetName()				{ return name; }
	void		SetName(const char* o)	{ memcpy(name, o, iROOM_NAME_LEN); name[iROOM_NAME_LEN] = '\0'; }

	UINT32	padding1: 1;
	UINT32	max: 6;
	UINT32	mod: 4;
	UINT32	padding2: 21;

	char	name[iROOM_NAME_LEN + 1];

};

struct SRoomCreateGsToCl {
	SRoomCreateGsToCl() { memset(this, 0, sizeof(SRoomCreateGsToCl)); }

	const char*	GetName()				{ return name; }
	void		SetName(const char* o)	{ memcpy(name, o, iROOM_NAME_LEN); name[iROOM_NAME_LEN] = '\0'; }

	UINT32	id;

	UINT32	offset: 1;
	UINT32	max: 6;
	UINT32	mod: 4;
	UINT32	padding: 21;

	char	name[iROOM_NAME_LEN + 1];
};

// ROOM_JOIN
struct SRoomJoinClToGs {
	UINT32	id;
};

struct SRoomJoinGsToCl {
	SRoomJoinGsToCl() { memset(this, 0, sizeof(SRoomJoinGsToCl)); }

	const char*	GetName()				{ return name; }
	void		SetName(const char* o)	{ memcpy(name, o, iROOM_NAME_LEN); name[iROOM_NAME_LEN] = '\0'; }

	UINT32	id;

	UINT32	offset: 1;
	UINT32	max: 6;
	UINT32	mod: 4;
	UINT32	team : 4;
	UINT32	isPlaying : 1;
	UINT32	padding: 16;

	FLOAT	timeOut;

	char	name[iROOM_NAME_LEN + 1];
};

// ROOM MATCH
struct SRoomMatchClToGs {
	const char*	GetName()				{ return name; }
	void		SetName(const char* o)	{ memcpy(name, o, iROOM_NAME_LEN); name[iROOM_NAME_LEN] = '\0'; }

	UINT32	padding1: 1;
	UINT32	max: 6;
	UINT32	mod: 4;
	UINT32	padding2: 21;

	char	name[iROOM_NAME_LEN + 1];
};

// ROOM_INFO
struct SRoomInfo {
	SRoomInfo() { memset(this, 0, sizeof(SRoomInfo)); }

	const char*	GetName()				{ return name; }
	void		SetName(const char* o)	{ memcpy(name, o, iROOM_NAME_LEN); name[iROOM_NAME_LEN] = '\0'; }

	UINT		GetMax()				{ return max; }

	UINT32	id;

	UINT32	offset: 1;
	UINT32	max: 6;
	UINT32	mod: 4;
	UINT32	state : 3;
	UINT32	padding : 18;

	char	name[iROOM_NAME_LEN + 1];
};

// ROOM_LIST
const INT iMAX_PACKET_ROOM_LIST = (iCOMMAND_DATA_SIZE) / sizeof(SRoomInfo);

struct SRoomListGsToCl {
	SRoomInfo	list[iMAX_PACKET_ROOM_LIST];
};

struct SRoomMember {
	SRoomMember()					{ memset(this, 0, sizeof(SRoomMember)); }

	const char*	GetName()			{ return name; }
	void	SetName(const char* o)	{ memcpy(name, o, iPLAYER_NAME_LEN); name[iPLAYER_NAME_LEN] = '\0'; }

	UINT32		actor;

	UINT32		status: 4;
	UINT32		team: 4;
	UINT32		padding: 24;

	SPosition	pos;
	SColor		color;

	char		name[iPLAYER_NAME_LEN + 1];
};

const INT iMAX_PACKET_ROOM_MEMBER_LIST = (iCOMMAND_DATA_SIZE) / sizeof(SRoomMember);

struct SRoomMemberListGsToCl {
	SRoomMember	list[iMAX_PACKET_ROOM_MEMBER_LIST];
};

struct SRoomMemberLeaderGsToCl {
	UINT32	leader;
};

// ROOM_JOIN_OTHER
struct SRoomJoinOtherGsToCl {
	SRoomJoinOtherGsToCl()			{ memset(this, 0, sizeof(SRoomJoinOtherGsToCl)); }

	const char*	GetName()			{ return name; }
	void	SetName(const char* o)	{ memcpy(name, o, iPLAYER_NAME_LEN); name[iPLAYER_NAME_LEN] = '\0'; }

	UINT32	actor;

	char	name[iPLAYER_NAME_LEN + 1];
};

// ROOM_LEAVE_OTHER
struct SRoomLeaveOtherGsToCl {
	UINT32	actor;
	UINT32	leader;
};

// ROOM_START_OTHER
struct SRoomStartOtherGsToCl {
	UINT32	actor;
};

// ROOM_STOP_OTHER
struct SRoomStopOtherGsToCl {
	UINT32	leader;
};

typedef struct SRoomSyncGsToCl{
	SRoomSyncGsToCl() { memset(this, 0, sizeof(SRoomSyncGsToCl)); }

	UINT32		actor;
} SRoomSyncClToGs;

// ROOM_START_PLAYING
struct SRoomStartPlayingClToGs {
	SRoomStartPlayingClToGs() { memset(this, 0, sizeof(SRoomStartPlayingClToGs)); }

	UINT32	actor;
};

// ROOM_START_INFO
struct SRoomStartInfoGsToCl {
	SRoomStartInfoGsToCl() { memset(this, 0, sizeof(SRoomStartInfoGsToCl)); }

	UINT32	room;
};

struct SRoomEndPlaying {
	SRoomEndPlaying() { memset(this, 0, sizeof(SRoomEndPlaying)); }
	
	UINT32	winTeam : 3;
	UINT32	draw : 1;
	UINT32	padding : 28;

};

// ROOM_END_INFO
struct SRoomEndInfoGsToCl {
	SRoomEndInfoGsToCl() { memset(this, 0, sizeof(SRoomEndInfoGsToCl)); }

	UINT32	room;
};

#pragma pack()
