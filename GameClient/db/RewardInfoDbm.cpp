/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "RewardInfoDbm.h"

#include "../CommonHeader.h"

bool
CRewardInfoDbm::Load() {
	std::string szPath = "..\\Data\\rewardinfo.csv";

	if (false == CDBM::Load(szPath.c_str())) {
		CONSOLE("file not found: " << szPath.c_str());
		return false;
	}

	g_kRewardInfoList.Clear();

	INT iIdOffset = GetField("ri_id")->GetOffset();
	INT iTypeOffset = GetField("ri_type")->GetOffset();
	INT iGroupOffset = GetField("ri_group")->GetOffset();
	INT iProbOffset = GetField("ri_prob")->GetOffset();
	INT iItemIdOffset = GetField("ri_item_id")->GetOffset();

	INT iIdSize = GetField("ri_id")->GetSize();
	INT iTypeSize = GetField("ri_type")->GetSize();
	INT iGroupSize = GetField("ri_group")->GetSize();
	INT iProbSize = GetField("ri_prob")->GetSize();
	INT iItemIdSize = GetField("ri_item_id")->GetSize();

	for (INT i = 0; i < GetDataCount(); ++i) {
		std::string szId(GetData(i, iIdOffset), iIdSize);
		std::string szType(GetData(i, iTypeOffset), iTypeSize);
		std::string szGroup(GetData(i, iGroupOffset), iGroupSize);
		std::string szProb(GetData(i, iProbOffset), iProbSize);
		std::string szItemId(GetData(i, iItemIdOffset), iItemIdSize);

		UINT uiId = atoll(szId.c_str());

		REWARD_TYPE eType = REWARD_NONE;
		if (0 == strcmp(szType.c_str(), "NORMAL")) {
			eType = REWARD_NORMAL;
		} else if(0 == strcmp(szType.c_str(), "RARE")) {
			eType = REWARD_RARE;
		}

		UINT uiGroup = atoll(szGroup.c_str());
		UINT uiProb = atoll(szProb.c_str());
		UINT uiItemId = atoll(szItemId.c_str());

		SRewardInfo tInfo;
		tInfo.id = uiId;
		tInfo.type = eType;
		tInfo.group = uiGroup;
		tInfo.prob = uiProb;
		tInfo.item_id = uiItemId;

		//CONSOLE("rewardinfo: id: " << tInfo.GetId() << ", type: " << tInfo.GetType() << ", group: " << tInfo.GetGroup() << ", prob: " << tInfo.GetProb() << ", item id: " << tInfo.GetItemId());

		g_kRewardInfoList.Insert(tInfo);
	}

	Clear();
	return true;
}
