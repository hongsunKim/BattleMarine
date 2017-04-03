/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */
 //#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

//장미경
bool
CMD_ITEM_DROP(CCommand& rkCommand_) {
	SItemDropGsToCl& rtRData = (SItemDropGsToCl&)rkCommand_.GetData();

	CItemEx* pkItem = new CItemEx();
	const SDropInfo* dropinfo = g_kDropInfoList.Find(rtRData.drop_id);
	UINT itemId = dropinfo->GetItemId();

	pkItem->SetId(itemId);
	pkItem->SetSerial(rtRData.serial);
	pkItem->SetPos(rtRData.pos);
	pkItem->SetOwner(rtRData.owner);

	g_kDropItemMgr.InsertDropItem(&(*pkItem));
	CONSOLE("CMD_ITEM_DROP: owner: " << pkItem->GetOwner());

	return true;
}

bool
CMD_ITEM_USE(CCommand& rkCommand_) {
	return true;
}

bool
CMD_ITEM_PICK(CCommand& rkCommand_) {
	if (OK == rkCommand_.GetExtra()) {
		SItemPickGsToCl& rtRData = (SItemPickGsToCl&)rkCommand_.GetData();

		g_kDropItemMgr.DeleteDropItem(rtRData.serial);
		CONSOLE("CMD_ITEM_PICK: picker: " << rtRData.picker << ", serial: " << rtRData.serial);


		REFRESH_INVENTORY_LIST();
	}

	return true;
}

bool
CMD_ITEM_ENTER(CCommand& rkCommand_) {
	return true;
}

bool
CMD_ITEM_LEAVE(CCommand& rkCommand_) {
	return true;
}


void
InitializeItemCommand() {
	SET_COMMAND(ITEM_DROP);
	SET_COMMAND(ITEM_USE);
	SET_COMMAND(ITEM_PICK);
	SET_COMMAND(ITEM_ENTER);
	SET_COMMAND(ITEM_LEAVE);
}
