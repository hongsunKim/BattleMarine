/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "ItemInfoDbm.h"

#include "../CommonHeader.h"

#define DB_ITEMINFO_TABLE "`iteminfo`"

#define SQL_ITEMINFO_STRUCTURE "ii_id,ii_type-1,ii_usable-1,ii_stocks,ii_buy_point,ii_sell_point"
#define SQL_ITEMINFO_SELECT "SELECT "SQL_ITEMINFO_STRUCTURE" FROM "DB_ITEMINFO_TABLE" ORDER BY ii_id ASC"

enum DB_ITEMINFO_INFO {
	DB_ITEMINFO_ID = 0,
	DB_ITEMINFO_TYPE,
	DB_ITEMINFO_USABLE,
	DB_ITEMINFO_STOCKS,
	DB_ITEMINFO_BUY_POINT,
	DB_ITEMINFO_SELL_POINT,
	DB_ITEMINFO_MAX
};

INT
CItemInfoDbm::Query() {
	char** ppRow;
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ITEMINFO_SELECT);
	if(RealQuery()) {
		void* pvResult = StoreResult();
		if (isptr(pvResult)) {
			INT iOffset = 0;
			INT iPrevId = 0;

			SItemInfo tInfo;
			g_kItemInfoList.Clear();

			while(NULL != (ppRow = FetchRow(pvResult))) {
				memset(&tInfo, 0, sizeof(tInfo));
				if(ConvDB2Data(ppRow, tInfo)) {
					if(iPrevId < INT(tInfo.GetId())) {
						iPrevId = tInfo.GetId();
						if (g_kItemInfoList.Insert(tInfo)) {
							++iOffset;
						} else {
							g_kItemInfoList.Clear();
							FreeResult(pvResult);
							OUTPUT("iteminfo table: error: list insert failed: " << iOffset + 1);
							return 0;
						}
					} else {
						g_kItemInfoList.Clear();
						FreeResult(pvResult);
						OUTPUT("iteminfo table: error: " << iOffset + 1);
						return 0;
					}
				} else {
					g_kItemInfoList.Clear();
					FreeResult(pvResult);
					OUTPUT("iteminfo table: error: " << iOffset + 1);
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
CItemInfoDbm::ConvDB2Data(char** row, SItemInfo& rtData_) {
	bool bRet = true;

	rtData_.id = RTOQ(DB_ITEMINFO_ID);
	rtData_.item_type = ITEM_TYPE(RTOI(DB_ITEMINFO_TYPE));
	rtData_.stocks = RTOQ(DB_ITEMINFO_STOCKS);
	rtData_.usable = bool(RTOI(DB_ITEMINFO_USABLE));
	rtData_.buy_point = RTOQ(DB_ITEMINFO_BUY_POINT);
	rtData_.sell_point = RTOQ(DB_ITEMINFO_SELL_POINT);

	//OUTPUT("iteminfo: id: " << rtData_.id << ", item type: " << rtData_.item_type
	//<< ", stocks: " << rtData_.stocks << ", usable: " << rtData_.usable
	//<< ", buy point: " << rtData_.buy_point << ", sell point: " << rtData_.sell_point);

	return bRet;
}
