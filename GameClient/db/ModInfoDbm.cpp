/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "ModInfoDbm.h"

#include "../CommonHeader.h"

bool
CModInfoDbm::Load() {
	std::string szPath = "..\\Data\\modinfo.csv";

	if (false == CDBM::Load(szPath.c_str())) {
		CONSOLE("file not found: " << szPath.c_str());
		return false;
	}

	g_kModInfoList.Clear();

	INT iModOffset = GetField("mi_mod")->GetOffset();
	INT iMapOffset = GetField("mi_map")->GetOffset();
	INT iRuleOffset = GetField("mi_rule")->GetOffset();
	INT iTimeOffset = GetField("mi_time")->GetOffset();
	INT iItemDropOffset = GetField("mi_itemdrop")->GetOffset();

	INT iModSize = GetField("mi_mod")->GetSize();
	INT iMapSize = GetField("mi_map")->GetSize();
	INT iRuleSize = GetField("mi_rule")->GetSize();
	INT iTimeSize = GetField("mi_time")->GetSize();
	INT iItemDropSize = GetField("mi_itemdrop")->GetSize();

	for (INT i = 0; i < GetDataCount(); ++i) {
		std::string szMod(GetData(i, iModOffset), iModSize);
		std::string szMap(GetData(i, iMapOffset), iMapSize);
		std::string szRule(GetData(i, iRuleOffset), iRuleSize);
		std::string szTime(GetData(i, iTimeOffset), iTimeSize);
		std::string szItemDrop(GetData(i, iItemDropOffset), iItemDropSize);

		MOD_TYPE eType = MOD_NONE;
		if(0 == strcmp(szMod.c_str(), "FFA")) {
			eType = MOD_FFA;
		} else if(0 == strcmp(szMod.c_str(), "TDM")) {
			eType = MOD_TDM;
		} else if(0 == strcmp(szMod.c_str(), "ZOMBIE")) {
			eType = MOD_ZOMBIE;
		}

		UINT uiMap = atoll(szMap.c_str());
		UINT uiRule = atoll(szRule.c_str());
		UINT uiTime = atoll(szTime.c_str());

		bool bItemDrop = false;
		if(0 == strcmp(szItemDrop.c_str(), "TRUE")) {
			bItemDrop = true;
		}

		SModInfo tInfo;
		tInfo.type = eType;
		tInfo.map_id = uiMap;
		tInfo.rule = uiRule;
		tInfo.time = uiTime;
		tInfo.item_drop = bItemDrop;

		//CONSOLE("modinfo: type: " << tInfo.GetType() << ", map id: " << tInfo.GetMapId() << ", rule: " << tInfo.GetRule() << ", time: " << tInfo.GetTime() << ", item drop: " << tInfo.IsItemDrop());

		g_kModInfoList.Insert(tInfo);
	}

	Clear();
	return true;
}
