/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "ItemInfoDbm.h"

#include "../CommonHeader.h"

bool
CItemInfoDbm::Load() {
	std::string szPath = "..\\Data\\iteminfo.csv";

	if(false == CDBM::Load(szPath.c_str())) {
		CONSOLE("file not found: " << szPath.c_str());
		return false;
	}

	g_kItemInfoList.Clear();

	INT iIdOffset = GetField("ii_id")->GetOffset();
	INT iNameOffset = GetField("ii_name")->GetOffset();
	INT iTypeOffset = GetField("ii_type")->GetOffset();
	INT iUsableOffset = GetField("ii_usable")->GetOffset();
	INT iStocksOffset = GetField("ii_stocks")->GetOffset();
	INT iBuyPointOffset = GetField("ii_buy_point")->GetOffset();
	INT iSellPointOffset = GetField("ii_sell_point")->GetOffset();
	INT iDescOffset = GetField("ii_desc")->GetOffset();

	INT iIdSize = GetField("ii_id")->GetSize();
	INT iNameSize = GetField("ii_name")->GetSize();
	INT iTypeSize = GetField("ii_type")->GetSize();
	INT iUsableSize = GetField("ii_usable")->GetSize();
	INT iStocksSize = GetField("ii_stocks")->GetSize();
	INT iBuyPointSize = GetField("ii_buy_point")->GetSize();
	INT iSellPointSize = GetField("ii_sell_point")->GetSize();
	INT iDescSize = GetField("ii_desc")->GetSize();

	for(INT i = 0; i < GetDataCount(); ++i) {
		std::string szId(GetData(i, iIdOffset), iIdSize);
		std::string szName(GetData(i, iNameOffset), iNameSize);
		std::string szType(GetData(i, iTypeOffset), iTypeSize);
		std::string szUsable(GetData(i, iUsableOffset), iUsableSize);
		std::string szStocks(GetData(i, iStocksOffset), iStocksSize);
		std::string szBuyPoint(GetData(i, iBuyPointOffset), iBuyPointSize);
		std::string szSellPoint(GetData(i, iSellPointOffset), iSellPointSize);
		std::string szDesc(GetData(i, iDescOffset), iDescSize);

		UINT uiId = atoll(szId.c_str());

		ITEM_TYPE eType = ITEM_NONE;
		if(0 == strcmp(szType.c_str(), "POINT")) {
			eType = ITEM_POINT;
		} else if (0 == strcmp(szType.c_str(), "PASSIVE")) {
			eType = ITEM_PASSIVE;
		} else if (0 == strcmp(szType.c_str(), "ACTIVE")) {
			eType = ITEM_ACTIVE;
		}
		
		bool bUsable = false;
		if(0 == strcmp(szUsable.c_str(), "TRUE")) {
			bUsable = true;
		}
		
		UINT uiStocks = atoll(szStocks.c_str());
		UINT uiBuyPoint = atoll(szBuyPoint.c_str());
		UINT uiSellPoint = atoll(szSellPoint.c_str());

		SItemInfo tInfo;
		tInfo.id = uiId;
		tInfo.SetName(szName.c_str());
		tInfo.item_type = eType;
		tInfo.usable = bUsable;
		tInfo.stocks = uiStocks;
		tInfo.buy_point = uiBuyPoint;
		tInfo.sell_point = uiSellPoint;
		tInfo.SetDesc(szDesc.c_str());

		//CONSOLE("iteminfo: id: " << tInfo.GetId() << ", name: " << tInfo.GetName() << ", type: " << tInfo.GetItemType());
		//CONSOLE("iteminfo: usable: " << tInfo.IsUsable() << ", stocks: " << tInfo.GetStocks() << ", sell point: " << tInfo.GetSellPoint() << ", buy point: " << tInfo.GetBuyPoint());
		//CONSOLE("iteminfo: desc: " << tInfo.GetDesc());

		g_kItemInfoList.Insert(tInfo);
	}

	Clear();
	return true;
}
