/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "ItemInfoDbm.h"

#include "../CommonHeader.h"

//장미경
bool
CDropInfoDbm::Load() {
	std::string szPath = "..\\Data\\dropinfo.csv";

	if (false == CDBM::Load(szPath.c_str())) {
		CONSOLE("file not found: " << szPath.c_str());
		return false;
	}

	g_kDropInfoList.Clear();

	INT iIdOffset = GetField("di_id")->GetOffset();
	INT iModOffset = GetField("di_mod")->GetOffset();
	INT iTypeOffset = GetField("di_type")->GetOffset();
	INT iTeamOffset = GetField("di_team")->GetOffset();
	INT iItemIdOffset = GetField("di_item_id")->GetOffset();
	INT iMapIdOffset = GetField("di_map_id")->GetOffset();
	INT iXOffset = GetField("di_x")->GetOffset();
	INT iYOffset = GetField("di_y")->GetOffset();
	INT iProbOffset = GetField("di_prob")->GetOffset();
	INT iGroupOffset = GetField("di_group")->GetOffset();
	INT iRemovalTimeOffset = GetField("di_removal_time")->GetOffset();
	INT iRespawnTimeOffset = GetField("di_respawn_time")->GetOffset();
	INT iLeftOverTimeOffset = GetField("di_left_over_time")->GetOffset();

	INT iIdSize = GetField("di_id")->GetSize();
	INT iModSize = GetField("di_mod")->GetSize();
	INT iTypeSize = GetField("di_type")->GetSize();
	INT iTeamSize = GetField("di_team")->GetSize();
	INT iItemIdSize = GetField("di_item_id")->GetSize();
	INT iMapIdSize = GetField("di_map_id")->GetSize();
	INT iXSize = GetField("di_x")->GetSize();
	INT iYSize = GetField("di_y")->GetSize();
	INT iProbSize = GetField("di_prob")->GetSize();
	INT iGroupSize = GetField("di_group")->GetSize();
	INT iRemovalTimeSize = GetField("di_removal_time")->GetSize();
	INT iRespawnTimeSize = GetField("di_respawn_time")->GetSize();
	INT iLeftOverTimeSize = GetField("di_left_over_time")->GetSize();


	for (INT i = 0; i < GetDataCount(); ++i) {
		std::string szId(GetData(i, iIdOffset), iIdSize);
		std::string szMod(GetData(i, iModOffset), iModSize);
		std::string szType(GetData(i, iTypeOffset), iTypeSize);
		std::string szTeam(GetData(i, iTeamOffset), iTeamSize);
		std::string szItemId(GetData(i, iItemIdOffset), iItemIdSize);
		std::string szMapId(GetData(i, iMapIdOffset), iMapIdSize);
		std::string szX(GetData(i, iXOffset), iXSize);
		std::string szY(GetData(i, iYOffset), iYSize);
		std::string szProb(GetData(i, iProbOffset), iProbSize);
		std::string szGroup(GetData(i, iGroupOffset), iGroupSize);
		std::string szRemovalTime(GetData(i, iRemovalTimeOffset), iRemovalTimeSize);
		std::string szRespawnTime(GetData(i, iRespawnTimeOffset), iRespawnTimeSize);
		std::string szLeftOverTime(GetData(i, iLeftOverTimeOffset), iLeftOverTimeSize);

		UINT uiId = atoll(szId.c_str());

		MOD_TYPE eModType = MOD_NONE;
		if (0 == strcmp(szType.c_str(), "FFA")) {
			eModType = MOD_FFA;
		}
		else if (0 == strcmp(szType.c_str(), "TDM")) {
			eModType = MOD_TDM;
		}
		else if (0 == strcmp(szType.c_str(), "ZOMBIE")) {
			eModType = MOD_ZOMBIE;
		}

		DROP_TYPE eDropType = DROP_NONE;
		if (0 == strcmp(szType.c_str(), "FIELD")) {
			eDropType = DROP_FIELD;
		}
		else if (0 == strcmp(szType.c_str(), "RESPAWN")) {
			eDropType = DROP_RESPAWN;
		}

		TEAM_TYPE eTeamType = TEAM_NONE;
		if (0 == strcmp(szType.c_str(), "RED")) {
			eTeamType = TEAM_RED;
		}
		else if (0 == strcmp(szType.c_str(), "BLUE")) {
			eTeamType = TEAM_BLUE;
		}
		else if (0 == strcmp(szType.c_str(), "GREEN")) {
			eTeamType = TEAM_GREEN;
		}

		UINT uiItemId = atoll(szItemId.c_str());
		UINT uiMapId = atoll(szMapId.c_str());
		FLOAT uiX = atof(szX.c_str());
		FLOAT uiY = atof(szY.c_str());
		UINT uiProb = atoll(szProb.c_str());
		UINT uiGroup = atoll(szGroup.c_str());
		UINT uiRemovalTime = atoll(szRemovalTime.c_str());
		UINT uiRespawnTime = atoll(szRespawnTime.c_str());
		UINT uiLeftOverTime = atoll(szLeftOverTime.c_str());

		SDropInfo tInfo;
		tInfo.id = uiId;
		tInfo.mod_type = eModType;
		tInfo.drop_type = eDropType;
		tInfo.team_type = eTeamType;
		tInfo.item_id = uiItemId;
		tInfo.map_id = uiMapId;
		tInfo.x = uiX;
		tInfo.y = uiY;
		tInfo.prob = uiProb;
		tInfo.group = uiGroup;
		tInfo.removal_time = uiRemovalTime;
		tInfo.respawn_time = uiRespawnTime;
		tInfo.left_over_time = uiLeftOverTime;
		
		CONSOLE("dropinfo: id: " << tInfo.GetId() 
			<< ", droptype: " << tInfo.GetDropType()
			<< ", x: " << tInfo.GetPosX()
			<< ", y: " << tInfo.GetPosY()

		);
		

		g_kDropInfoList.Insert(tInfo);
	}

	Clear();
	return true;
}
