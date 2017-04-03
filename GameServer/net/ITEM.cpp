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
CMD_ITEM_DROP(CPlayer& rkActor_, CCommand& rkCommand_) {
	SItemDropClToGs& rtRData = (SItemDropClToGs&)rkCommand_.GetData();

	CCommand kCommand;
	kCommand.SetOrder(ITEM_DROP);
	kCommand.SetExtra(rkCommand_.GetExtra());
	OUTPUT("CMD_ITEM_DROP: owner: " << rtRData.owner << ", victim: " << rtRData.victim);

	SItemDropGsToCl& rtSData = (SItemDropGsToCl&)kCommand.GetData();
	rtSData.owner = rtRData.owner;
	rtSData.victim = rtRData.victim;
	rtSData.drop_id = 2; //test
	rtSData.serial = g_kItemMgr.NewSerial();
	rtSData.pos = rkActor_.GetPosition();

	rkActor_.Send(kCommand, sizeof(SItemDropGsToCl));

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();

	if (isptr(pkRoomHandler)) {
		CRoomEx* pkRoom = (CRoomEx*)pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			pkRoom->Broadcast(kCommand, sizeof(SItemDropGsToCl), &rkActor_);
			return true;
		}
	}
	return true;
}

bool
CMD_ITEM_USE(CPlayer& rkActor_, CCommand& rkCommand_) {
	SItemUseClToGs& rtRData = (SItemUseClToGs&)rkCommand_.GetData();

	CCommand kCommand;
	kCommand.SetOrder(ITEM_USE);
	kCommand.SetExtra(rkCommand_.GetExtra());
	OUTPUT("CMD_ITEM_DROP: user: " << rtRData.user << ", serial: " << rtRData.serial);

	SItemUseGsToCl& rtSData = (SItemUseGsToCl&)kCommand.GetData();
	rtSData.user = rtRData.user;
	rtSData.serial = rtRData.serial;

	rkActor_.Send(kCommand, sizeof(SItemUseGsToCl));

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();

	if (isptr(pkRoomHandler)) {
		CRoomEx* pkRoom = (CRoomEx*)pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			pkRoom->Broadcast(kCommand, sizeof(SItemUseGsToCl), &rkActor_);
			return true;
		}
	}

	return true;
}

bool
CMD_ITEM_PICK(CPlayer& rkActor_, CCommand& rkCommand_) {
	SItemPickClToGs& rtRData = (SItemPickClToGs&)rkCommand_.GetData();

	CCommand kCommand;
	kCommand.SetOrder(ITEM_PICK);
	kCommand.SetExtra(rkCommand_.GetExtra());
	OUTPUT("CMD_ITEM_DROP: user: " << rtRData.picker << ", serial: " << rtRData.serial);

	SItemPickGsToCl& rtSData = (SItemPickGsToCl&)kCommand.GetData();
	rtSData.picker = rtRData.picker;
	rtSData.serial = rtRData.serial;

	rkActor_.Send(kCommand, sizeof(SItemUseGsToCl));

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();

	if (isptr(pkRoomHandler)) {
		CRoomEx* pkRoom = (CRoomEx*)pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			pkRoom->Broadcast(kCommand, sizeof(SItemUseGsToCl), &rkActor_);
			return true;
		}
	}

	return true;

}

bool
CMD_ITEM_ENTER(CPlayer& rkActor_, CCommand& rkCommand_) {
	return true;
}

bool
CMD_ITEM_LEAVE(CPlayer& rkActor_, CCommand& rkCommand_) {
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
