/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "InventoryDbm.h"

#include "../CommonHeader.h"

#define DB_INVENTORY_TABLE "'inventory'"

#define SQL_INVENTORY_STRUCTURE "in_aid, in_offset, in_itemid, in_serial, in_count"
#define SQL_INVENTORY_SELECT "SELECT "SQL_INVENTORY_STRUCTURE" FROM "DB_INVENTORY_TABLE" ORDER BY in_aid ASC"

enum DB_INVENTORY_INFO {
	DB_INVENTORY_ID = 0,
	DB_INVENTORY_OFFSET,
	DB_INVENTORY_ITEMID,
	DB_INVENTORY_SERIAL,
	DB_INVENTORY_COUNT,
	DB_INVENTORY_MAX
};

bool
CInventoryDbm::Query(UINT uiAid_, CPlayer& rkPlayer_) {
	
	if (0 < uiAid_) {
		char** ppRow;
		sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_INVENTORY_SELECT);

		if (RealQuery()) {
			void* pvResult = StoreResult();
			if (isptr(pvResult)) {

				SItemInfo tInfo;



			}
			FreeResult(pvResult);
		}
		else {
			ErrMsg();
		}

	}
	else {

	}

	return false;
}

bool
CInventoryDbm::ConvDB2Data(char** row, CPlayer& rkPlayer_) {
	
	
	return false;
}
