/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "DropInfoDbm.h"

#include "../CommonHeader.h"

#define DB_DROPINFO_TABLE "`dropinfo`"

#define SQL_DROPINFO_STRUCTURE "di_id,di_mod,di_type,di_team,di_item_id,di_map_id,di_x,di_y,di_prob,di_group,di_removal_time,di_respawn_time,di_left_over_time"
#define SQL_DROPINFO_SELECT "SELECT "SQL_DROPINFO_STRUCTURE" FROM "DB_DROPINFO_TABLE" ORDER BY di_id ASC"

enum DB_DROPINFO_INFO {
	DB_DROPINFO_ID = 0,
	DB_DROPINFO_MOD,
	DB_DROPINFO_TYPE,
	DB_DROPINFO_TEAM,
	DB_DROPINFO_ITEMID,
	DB_DROPINFO_MAPID,
	DB_DROPINFO_X,
	DB_DROPINFO_Y,
	DB_DROPINFO_PROB,
	DB_DROPINFO_GROUP,
	DB_DROPINFO_REMOVAL_TIME,
	DB_DROPINFO_RESPAWN_TIME,
	DB_DROPINFO_LEFTOVER_TIME,
	DB_DROPINFO_MAX
};


INT
CDropInfoDbm::Query() {
	char** ppRow;
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_DROPINFO_SELECT);
	if (RealQuery()) {
		void* pvResult = StoreResult();
		if (isptr(pvResult)) {
			INT iOffset = 0;
			INT iPrevId = 0;

			SDropInfo tInfo;
			g_kItemInfoList.Clear();

			while (NULL != (ppRow = FetchRow(pvResult))) {
				memset(&tInfo, 0, sizeof(tInfo));
				if (ConvDB2Data(ppRow, tInfo)) {
					if (iPrevId < INT(tInfo.GetId())) {
						iPrevId = tInfo.GetId();
						if (g_kDropInfoList.Insert(tInfo)) {
							++iOffset;
						}
						else {
							g_kDropInfoList.Clear();
							FreeResult(pvResult);
							OUTPUT("dropinfo table: error: list insert failed: " << iOffset + 1);
							return 0;
						}
					}
					else {
						g_kDropInfoList.Clear();
						FreeResult(pvResult);
						OUTPUT("dropinfo table: error: " << iOffset + 1);
						return 0;
					}
				}
				else {
					g_kDropInfoList.Clear();
					FreeResult(pvResult);
					OUTPUT("dropinfo table: error: " << iOffset + 1);
				}
			}
			FreeResult(pvResult);
			return iOffset;
		}
		else {
			TRACE("query result is failed: ");
		}
	}
	else {
		ErrMsg();
	}

	return -1;
}


bool
CDropInfoDbm::ConvDB2Data(char** row, SDropInfo& rtData_) {
	bool bRet = true;

	rtData_.id = RTOQ(DB_DROPINFO_ID);
	rtData_.mod_type = MOD_TYPE(RTOI(DB_DROPINFO_MOD));
	rtData_.drop_type = DROP_TYPE(RTOI(DB_DROPINFO_TYPE));
	rtData_.team_type = TEAM_TYPE(RTOI(DB_DROPINFO_TEAM));
	rtData_.item_id = RTOQ(DB_DROPINFO_ITEMID);
	rtData_.map_id = RTOQ(DB_DROPINFO_MAPID);
	rtData_.x = RTOF(DB_DROPINFO_X);
	rtData_.y = RTOF(DB_DROPINFO_Y);
	rtData_.prob = RTOQ(DB_DROPINFO_PROB);
	rtData_.group = RTOQ(DB_DROPINFO_GROUP);
	rtData_.removal_time = RTOQ(DB_DROPINFO_REMOVAL_TIME);
	rtData_.respawn_time = RTOQ(DB_DROPINFO_RESPAWN_TIME);
	rtData_.left_over_time = RTOQ(DB_DROPINFO_LEFTOVER_TIME);

	//OUTPUT("dropinfo: id: " << rtData_.id << ", mod type: " << rtData_.mod_type
	//<< ", drop type: " << rtData_.drop_type << ", team type: " << rtData_.team_type
	//<< ", item id: " << rtData_.item_id << ", map id: " << rtData_.map_id << ", x: " << rtData_.x << ", y: " << rtData_.y
	//<< ", prob: " << rtData_.prob << ", group: " << rtData_.group << ", removal time: " << rtData_.removal_time
	//<< ", respawn time: " << rtData_.respawn_time << ", left over time: " << rtData_.left_over_time);

	return bRet;
}
