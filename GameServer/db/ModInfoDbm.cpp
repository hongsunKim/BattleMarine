/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "ModInfoDbm.h"

#include "../CommonHeader.h"

#define DB_MODINFO_TABLE "`modinfo`"

#define SQL_MODINFO_STRUCTURE "mi_mod-1,mi_map,mi_rule,mi_time,mi_itemdrop-1"
#define SQL_MODINFO_SELECT "SELECT "SQL_MODINFO_STRUCTURE" FROM "DB_MODINFO_TABLE" ORDER BY mi_mod ASC"

enum DB_MODINFO_INFO {
	DB_MODINFO_MOD = 0,
	DB_MODINFO_MAP,
	DB_MODINFO_RULE,
	DB_MODINFO_TIME,
	DB_MODINFO_ITEMDROP,
	DB_MODINFO_MAX
};

INT
CModInfoDbm::Query() {
	char** ppRow;
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_MODINFO_SELECT);
	if(RealQuery()) {
		void* pvResult = StoreResult();
		if (isptr(pvResult)) {
			INT iOffset = 0;

			SModInfo tInfo;
			g_kModInfoList.Clear();

			while(NULL != (ppRow = FetchRow(pvResult))) {
				memset(&tInfo, 0, sizeof(tInfo));
				if(ConvDB2Data(ppRow, tInfo)) {
					if(g_kModInfoList.Insert(tInfo)) {
						++iOffset;
					} else {
						g_kModInfoList.Clear();
						FreeResult(pvResult);
						OUTPUT("modinfo table: error: list insert failed: " << iOffset + 1);
						return 0;
					}
				} else {
					g_kModInfoList.Clear();
					FreeResult(pvResult);
					OUTPUT("modinfo table: error: " << iOffset + 1);
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
CModInfoDbm::ConvDB2Data(char** row, SModInfo& rtData_) {
	bool bRet = true;

	rtData_.type = MOD_TYPE(RTOI(DB_MODINFO_MOD));
	rtData_.map_id = RTOQ(DB_MODINFO_MAP);
	rtData_.rule = RTOQ(DB_MODINFO_RULE);
	rtData_.time = RTOQ(DB_MODINFO_TIME);
	rtData_.item_drop = bool(RTOI(DB_MODINFO_ITEMDROP));

	//OUTPUT("modinfo: type: " << rtData_.type << ", map id: " << rtData_.map_id
	//<< ", rule: " << rtData_.rule << ", time: " << rtData_.time
	//<< ", item drop: " << rtData_.item_drop);

	return bRet;
}
