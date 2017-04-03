/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

//장현우
bool
CMD_ID_AUTHORIZE(CCommand& rkCommand_) {
	CONSOLE("CMD_ID_AUTHORIZE: actor: " << g_kMainPlayer->GetKey());
	SIdAuthorizeGsToCl& rtRData = (SIdAuthorizeGsToCl&)rkCommand_.GetData();

	if(rkCommand_.GetExtra() == OK) {
		CONSOLE("로그인 성공!");
		g_kMainPlayer->SetAid(rtRData.GetAid());
		g_kMainPlayer->SetName(rtRData.GetName());
		g_kMainPlayer->SetLoginTime(rtRData.GetLoginTime());
		g_kMainPlayer->SetLogoutTime(rtRData.GetLogoutTime());
		g_kMainPlayer->SetPoint(rtRData.GetPoint());
	} else if (rkCommand_.GetExtra() == FAIL) {
		CONSOLE("로그인 실패!");
	}

	return true;
}

bool
CMD_ID_CREATE(CCommand& rkCommand_) {
	//CONSOLE("CMD_ID_CREATE: actor: " << g_kMainPlayer->GetKey());
	if (OK == rkCommand_.GetExtra()) {
		CONSOLE("CMD_ID_CREATE: actor: " << g_kMainPlayer->GetKey() << ", extra: OK");
	} else if (CANT_DO == rkCommand_.GetExtra()) {
		CONSOLE("CMD_ID_CREATE: actor: " << g_kMainPlayer->GetKey() << ", extra: CANT_DO");
	} else if (FAIL == rkCommand_.GetExtra()) {
		CONSOLE("CMD_ID_CREATE: actor: " << g_kMainPlayer->GetKey() << ", extra: FAIL");
	}
	return true;
}

bool
CMD_ID_PONG(CCommand& rkCommand_) {
	//CONSOLE("CMD_ID_PONG: actor: " << g_kMainPlayer->GetKey());

	if (true == g_kMainRoom.IsAvailable()) {
		SIdPingGsToCl& rtRData = (SIdPingGsToCl&)rkCommand_.GetData();
		g_kTick.Reset(rtRData.tick * 10);
		g_kMainRoom.SetTimeOut(rtRData.timeOut);
	}

	/*if(false == g_kMainRoom.IsAvailable()) {
		SIdPingGsToCl& rtRData = (SIdPingGsToCl&)rkCommand_.GetData();
		g_kTick.Reset(rtRData.tick * 10);
		g_kMainRoom.SetTimeOut(rtRData.timeOut);
	}*/

	//CONSOLE("key: " << g_kMainPlayer->GetKey() << ", name: " << g_kMainPlayer->GetName() << ", recv tick: " << rtRData.tick);
	return true;
}

bool
CMD_ID_QUIT(CCommand& rkCommand_) {
	CONSOLE("CMD_ID_QUIT: actor: " << g_kMainPlayer->GetKey());
	return true;
}

void
InitializeIdCommand() {
	SET_COMMAND(ID_AUTHORIZE);
	SET_COMMAND(ID_CREATE);
	SET_COMMAND(ID_PONG);
	SET_COMMAND(ID_QUIT);
}
