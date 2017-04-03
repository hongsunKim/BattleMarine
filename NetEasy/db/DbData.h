/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../GlobalVariable.h"
#include "../Enums.h"

struct SItemInfo {
	SItemInfo() { memset(this, 0, sizeof(SItemInfo)); }

	const UINT			GetId() const { return id; }

	const ITEM_TYPE		GetItemType() const { return item_type; }

	const UINT			GetStocks() const { return stocks; }

	const bool			IsStockable() const { return (0 < stocks); }
	const bool			IsUsable() const { return usable; }

	const UINT			GetBuyPoint() const { return buy_point; }
	const UINT			GetSellPoint() const { return sell_point; }

	const char*			GetName() { return name; }
	void				SetName(const char* o) { memcpy(name, o, iITEM_NAME_LEN); name[iITEM_NAME_LEN] = '\0'; }

	const char*			GetDesc() { return desc; }
	void				SetDesc(const char* o) { memcpy(desc, o, iITEM_DESC_LEN); desc[iITEM_DESC_LEN] = '\0'; }

	UINT				id;
	ITEM_TYPE			item_type;
	UINT				stocks;
	bool				usable;

	UINT				buy_point;
	UINT				sell_point;

	char				name[iITEM_NAME_LEN + 1];
	char				desc[iITEM_DESC_LEN + 1];
};

//장미경
struct SDropInfo {
	SDropInfo() { memset(this, 0, sizeof(SDropInfo)); }

	const UINT			GetId() const { return id; }

	const MOD_TYPE		GetModType() const { return mod_type; }
	const DROP_TYPE		GetDropType() const { return drop_type; }
	const TEAM_TYPE		GetTeamType() const { return team_type; }

	const UINT			GetItemId() const { return item_id; }
	const UINT			GetMapId() const { return map_id; }
	const FLOAT			GetPosX() const { return x; }
	const FLOAT			GetPosY() const { return y; }

	const UINT			GetProb() const { return prob; }
	const UINT			GetGroup() const { return group; }

	const UINT			GetRemovalTime() const { return removal_time; }
	const UINT			GetRespawnTime() const { return respawn_time; }
	const UINT			GetLeftOverTime() const { return left_over_time; }

	UINT				id;

	MOD_TYPE			mod_type;
	DROP_TYPE			drop_type;
	TEAM_TYPE			team_type;

	UINT				item_id;
	UINT				map_id;
	FLOAT				x;
	FLOAT				y;

	UINT				prob;
	UINT				group;

	UINT				removal_time;
	UINT				respawn_time;
	UINT				left_over_time;

};

struct SRewardInfo {
	SRewardInfo() { memset(this, 0, sizeof(SRewardInfo)); }

	const UINT			GetId() const { return id; }
	const REWARD_TYPE	GetType() const { return type; }
	const UINT			GetProb() const { return prob; }
	const UINT			GetGroup() const { return group; }
	const UINT			GetItemId() const { return item_id; }

	UINT				id;

	REWARD_TYPE			type;
	UINT				prob;
	UINT				group;
	UINT				item_id;
};

struct SModInfo {
	SModInfo() { memset(this, 0, sizeof(SModInfo)); }

	const MOD_TYPE		GetType() const { return type; }
	const UINT			GetMapId() const { return map_id; }
	const UINT			GetRule() const { return rule; }
	const UINT			GetTime() const { return time; }

	const bool			IsItemDrop() const { return item_drop; }

	MOD_TYPE			type;
	UINT				map_id;
	UINT				rule;
	UINT				time;

	bool				item_drop;
};

struct SMapInfo {
	SMapInfo() { memset(this, 0, sizeof(SMapInfo)); }

	const UINT			GetId() const { return id; }
	const UINT			GetMaxUser() const { return max_user; }

	const bool			IsModFFA() const { return mod_ffa; }
	const bool			IsModTDM() const { return mod_tdm; }
	const bool			IsModZOMBIE() const { return mod_zombie; }

	const char*			GetName() { return name; }
	void				SetName(const char* o) { memcpy(name, o, iMAP_NAME_LEN); name[iMAP_NAME_LEN] = '\0'; }

	const char*			GetDesc() { return desc; }
	void				SetDesc(const char* o) { memcpy(desc, o, iMAP_DESC_LEN); desc[iMAP_DESC_LEN] = '\0'; }

	UINT				id;
	UINT				max_user;

	bool				mod_ffa;
	bool				mod_tdm;
	bool				mod_zombie;

	char				name[iMAP_NAME_LEN + 1];
	char				desc[iMAP_DESC_LEN + 1];
};
