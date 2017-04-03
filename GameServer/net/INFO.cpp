/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_INFO_USER_LIST(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_INFO_USER_LIST: actor: " << rkActor_.GetKey());
	return true;
}

bool
CMD_INFO_SERVER(CPlayer& rkActor_, CCommand& rkCommand_) {
	CCommand kCommand;
	kCommand.SetOrder(INFO_SERVER);
	SInfoServerGsToCl& rtSData = (SInfoServerGsToCl&)kCommand.GetData();
	rtSData.tick = g_kTick.GetTick();

	rkActor_.Send(kCommand, sizeof(SInfoServerGsToCl));

	OUTPUT("CMD_INFO_SERVER: actor: " << rkActor_.GetKey() << ", tick: " << rtSData.tick);

	g_kChannelMgr.InUser(rkActor_);
	g_kChannelMgr.GetUserList(rkActor_);
	return true;
}

void
InitializeInfoCommand() {
	SET_COMMAND(INFO_USER_LIST);
	SET_COMMAND(INFO_SERVER);
}
