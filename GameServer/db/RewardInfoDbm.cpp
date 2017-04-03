/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "RewardInfoDbm.h"

#include "../CommonHeader.h"

#define DB_REWARDINFO_TABLE "`rewardinfo`"

#define SQL_REWARDINFO_STRUCTURE "ri_id,ri_type-1,ri_group,ri_prob,ri_item_id"
#define SQL_REWARDINFO_SELECT "SELECT "SQL_REWARDINFO_STRUCTURE" FROM "DB_REWARDINFO_TABLE" ORDER BY ri_id ASC"

enum DB_REWARDINFO_INFO {
	DB_REWARDINFO_ID = 0,
	DB_REWARDINFO_TYPE,
	DB_REWARDINFO_GROUP,
	DB_REWARDINFO_PROB,
	DB_REWARDINFO_ITEM_ID,
	DB_REWARDINFO_MAX
};

INT
CRewardInfoDbm::Query() {
	char** ppRow;
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_REWARDINFO_SELECT);
	if(RealQuery()) {
		void* pvResult = StoreResult();
		if (isptr(pvResult)) {
			INT iOffset = 0;

			SRewardInfo tInfo;
			g_kRewardInfoList.Clear();

			while(NULL != (ppRow = FetchRow(pvResult))) {
				memset(&tInfo, 0, sizeof(tInfo));
				if(ConvDB2Data(ppRow, tInfo)) {
					if(g_kRewardInfoList.Insert(tInfo)) {
						++iOffset;
					} else {
						g_kRewardInfoList.Clear();
						FreeResult(pvResult);
						OUTPUT("rewardinfo table: error: list insert failed: " << iOffset + 1);
						return 0;
					}
				} else {
					g_kRewardInfoList.Clear();
					FreeResult(pvResult);
					OUTPUT("rewardinfo table: error: " << iOffset + 1);
				}
			}
			FreeResult(pvResult);
			return iOffset;
		} else {
			TRACE("query result is failed: ");
		}
	} else {
		ErrMsg();
	}

	return -1;
}

bool
CRewardInfoDbm::ConvDB2Data(char** row, SRewardInfo& rtData_) {
	bool bRet = true;

	rtData_.id = RTOQ(DB_REWARDINFO_ID);
	rtData_.type = REWARD_TYPE(RTOI(DB_REWARDINFO_TYPE));
	rtData_.group = RTOQ(DB_REWARDINFO_GROUP);
	rtData_.prob = RTOQ(DB_REWARDINFO_PROB);
	rtData_.item_id = RTOQ(DB_REWARDINFO_ITEM_ID);

	//OUTPUT("rewardinfo: id: " << rtData_.id << ", type: " << rtData_.type
	//<< ", group: " << rtData_.group << ", prob: " << rtData_.prob
	//<< ", item id: " << rtData_.item_id);

	return bRet;
}
