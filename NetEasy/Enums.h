﻿/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

enum PROTOCOL {
	PROTOCOL_NULL = 0,

	PROTOCOL_COMMON_BEGIN = 100,
	ID_AUTHORIZE,
	ID_CREATE,
	ID_PING,
	ID_PONG,
	ID_QUIT,

	INFO_USER_LIST,
	INFO_SERVER,
	//INFO_OTHER,

	ROOM_CREATE,
	ROOM_JOIN,
	ROOM_LEAVE,
	ROOM_INFO,
	ROOM_LIST,
	ROOM_MATCH,
	ROOM_SYNC,
	ROOM_START_PLAYING,
	ROOM_START_INFO,
	ROOM_END_PLAYING,
	ROOM_END_INFO,

	ROOM_JOIN_OTHER,
	ROOM_LEAVE_OTHER,

	USER_STATUS,
	USER_CHAT,
	USER_ATTACK,
	USER_MOVE,
	USER_RESPAWN,
	USER_STEAMPACK,
	USER_INFESTED,
	USER_ZOMBIE_INFEST,
	USER_ZOMBIE_MOVE,

	OTHER_STATUS,
	OTHER_CHAT,
	OTHER_ATTACK,
	OTHER_MOVE,
	OTHER_RESPAWN,
	OTHER_STEAMPACK,
	OTHER_INFESTED,
	OTHER_ZOMBIE_INFEST,
	OTHER_ZOMBIE_MOVE,

	ITEM_DROP,
	ITEM_USE,
	ITEM_PICK,
	ITEM_ENTER,
	ITEM_LEAVE,

	CHEAT_CODE_WARP,
	CHEAT_CODE_KILL,

	PROTOCOL_COMMON_END,

	PROTOCOL_MAX
};

enum EXTRA {
	// Default
	NONE = 0,
	OK,
	FAIL,

	// Fail
	BUSY,
	EMPTY,
	FULL,
	BLOCK,
	TIMEOUT,
	DATA_ERROR,
	CANT_DO,
	CANT_DO_ANYTHING,
	DONT_EXIST,
	NOT_FOUND,
	NOT_ENOUGH,
	NO_PERMISSION,
	OUT_OF_BOUND,
	OUT_OF_CONDITION,

	// Pair
	OPEN,
	CLOSE,

	REQUEST,
	RESPONSE,

	AGREE,
	DISAGREE,

	ACCEPT,
	CANCEL,

	ALLOW,
	DENY,

	START,
	STOP,

	BEGIN,
	END,

	LOCK,
	UNLOCK,

	IN_,
	OUT_,

	ADD,
	DEL,

	CONNECT,

	AUTOMATCH,
	WEB,

	// Etc
	MODIFY,
	DONE,
	CHECK,
	CHANGE,
	NEW,
	APPEND,
	ATTACH,
	ROOM,
	LOBBY,

	// CheatCode
	WARP,
	ALL,

	MAX_EXTRA
};

enum STATUS_TYPE {
	STATUS_EXIT = 0,
	STATUS_NORMAL,
	STATUS_DYING,
};

enum DIRECTION_TYPE {
	DIRECTION_UP = 0,
	DIRECTION_RIGHT_UP,
	DIRECTION_RIGHT,
	DIRECTION_RIGHT_DOWN,
	DIRECTION_DOWN,
	DIRECTION_LEFT_DOWN,
	DIRECTION_LEFT,
	DIRECTION_LEFT_UP,
	DIRECTION_COUNT
};

enum MOD_TYPE {
	MOD_NONE = 0,
	MOD_FFA = MOD_NONE,
	MOD_TDM,
	MOD_ZOMBIE,
	MOD_MAX = MOD_ZOMBIE,
};

enum DROP_TYPE {
	DROP_NONE = 0,
	DROP_FIELD = DROP_NONE,
	DROP_RESPAWN,
	DROP_MAX = DROP_RESPAWN
};

enum TEAM_TYPE {
	TEAM_NONE = 0,
	TEAM_RED,
	TEAM_BLUE,
	TEAM_GREEN,
	TEAM_MAX
};

//ENUM('POINT', 'PASSIVE', 'ACTIVE', 'NONE')
enum ITEM_TYPE {
	ITEM_POINT = 0,
	ITEM_PASSIVE,
	ITEM_ACTIVE,
	ITEM_NONE,
	ITEM_MAX = ITEM_NONE
};

enum REWARD_TYPE {
	REWARD_NORMAL = 0,
	REWARD_RARE,
	REWARD_NONE,
	REWARD_MAX = REWARD_NONE
};

enum ROOM_STATE {
	ROOM_STATE_READY = 0,
	ROOM_STATE_PLAYING,
	ROOM_STATE_END
};

enum GAME_RESULT {
	GAME_RESULT_NONE = 0,
	GAME_RESULT_WIN,
	GAME_RESULT_LOSE,
	GAME_RESULT_DRAW
};