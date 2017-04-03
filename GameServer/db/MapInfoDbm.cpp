/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "MapInfoDbm.h"

#include "../CommonHeader.h"

#define DB_MAPINFO_TABLE "`mapinfo`"

#define SQL_MAPINFO_STRUCTURE "mi_id,mi_max_user,mi_mod_ffa-1,mi_mod_tdm-1,mi_mod_zombie-1"
#define SQL_MAPINFO_SELECT "SELECT "SQL_MAPINFO_STRUCTURE" FROM "DB_MAPINFO_TABLE" ORDER BY mi_id ASC"

enum DB_MAPINFO_INFO {
	DB_MAPINFO_ID = 0,
	DB_MAPINFO_MAX_USER,
	DB_MAPINFO_MOD_FFA,
	DB_MAPINFO_MOD_TDM,
	DB_MAPINFO_MOD_ZOMBIE,
	DB_MAPINFO_MAX
};

INT
CMapInfoDbm::Query() {
	char** ppRow;
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_MAPINFO_SELECT);
	if(RealQuery()) {
		void* pvResult = StoreResult();
		if (isptr(pvResult)) {
			INT iOffset = 0;
			INT iPrevId = 0;

			SMapInfo tInfo;
			g_kMapInfoList.Clear();

			while(NULL != (ppRow = FetchRow(pvResult))) {
				memset(&tInfo, 0, sizeof(tInfo));
				if(ConvDB2Data(ppRow, tInfo)) {
					if(iPrevId < INT(tInfo.GetId())) {
						iPrevId = tInfo.GetId();
						if(g_kMapInfoList.Insert(tInfo)) {
							++iOffset;
						} else {
							g_kMapInfoList.Clear();
							FreeResult(pvResult);
							OUTPUT("mapinfo table: error: list insert failed: " << iOffset + 1);
							return 0;
						}
					} else {
						g_kMapInfoList.Clear();
						FreeResult(pvResult);
						OUTPUT("mapinfo table: error: " << iOffset + 1);
						return 0;
					}
				} else {
					g_kMapInfoList.Clear();
					FreeResult(pvResult);
					OUTPUT("mapinfo table: error: " << iOffset + 1);
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
CMapInfoDbm::ConvDB2Data(char** row, SMapInfo& rtData_) {
	bool bRet = true;

	rtData_.id = RTOQ(DB_MAPINFO_ID);
	rtData_.max_user = RTOQ(DB_MAPINFO_MAX_USER);
	rtData_.mod_ffa = bool(RTOI(DB_MAPINFO_MOD_FFA));
	rtData_.mod_tdm = bool(RTOI(DB_MAPINFO_MOD_TDM));
	rtData_.mod_zombie = bool(RTOI(DB_MAPINFO_MOD_ZOMBIE));

	//OUTPUT("mapinfo: id: " << rtData_.id << ", max user: " << rtData_.max_user
	//<< ", ffa: " << rtData_.mod_ffa << ", tdm: " << rtData_.mod_tdm
	//<< ", zombie: " << rtData_.mod_zombie);

	return bRet;
}
