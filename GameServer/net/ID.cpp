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
CMD_ID_AUTHORIZE(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ID_AUTHORIZE: actor: " << rkActor_.GetKey());
	if (rkCommand_.GetExtra() == NONE)
	{
		SIdAuthorizeClToGs& rtRData = (SIdAuthorizeClToGs&)rkCommand_.GetData();
		if (true == g_kAccountDB.QueryCheck(rtRData.GetLoginId())) {
			if (g_kAccountDB.QueryLogin(rtRData.GetLoginId(), rtRData.GetLoginPasswd(), rkActor_) == true) {
				CCommand kCommand;
				kCommand.SetOrder(ID_AUTHORIZE);
				kCommand.SetExtra(OK);

				SIdAuthorizeGsToCl& rtSData = (SIdAuthorizeGsToCl&)kCommand.GetData();
				rtSData.SetAid(rkActor_.GetAid());
				rtSData.SetName(rkActor_.GetName());
				rtSData.SetLoginTime(rkActor_.GetLoginTime());
				rtSData.SetLogoutTime(rkActor_.GetLogoutTime());
				rtSData.SetPoint(rkActor_.GetPoint());

				g_kAccountDB.UpdateLoginTime(rkActor_);


				rkActor_.Send(kCommand, sizeof(SIdAuthorizeGsToCl));
			}
			else {
				CCommand kCommand;
				kCommand.SetOrder(ID_AUTHORIZE);
				kCommand.SetExtra(FAIL);

				rkActor_.Send(kCommand);
			}
		}
	}
	else if (rkCommand_.GetExtra() == WEB)
	{
		SIdAuthorizeWepClToGs& rtRData = (SIdAuthorizeWepClToGs&)rkCommand_.GetData();
		if (true == g_kAccountDB.QueryCheck(rtRData.GetAid()))
		{
			if (g_kAccountDB.QueryLogin(rtRData.GetAid(), rkActor_) == true)
			{
				OUTPUT("CMD_ID_AUTHORIZE_WEB: actor: " << rkActor_.GetKey());
				return true;
			}
			else
			{
				OUTPUT("Fail Find Key: actor: " << rkActor_.GetKey());
				CCommand kCommand;
				kCommand.SetOrder(ID_AUTHORIZE);
				kCommand.SetExtra(FAIL);

				rkActor_.Send(kCommand);
				return false;
			}

		}
		else
		{
			OUTPUT("Fail Find Aid" << rtRData.GetAid());
			CCommand kCommand;
			kCommand.SetOrder(ID_AUTHORIZE);
			kCommand.SetExtra(FAIL);

			rkActor_.Send(kCommand);
			return false;
		}
	}

	OUTPUT("잘못된 커맨드 엑스트라: Extra:" << rkCommand_.GetExtra());
	return false;
}

bool
CMD_ID_CREATE(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ID_CREATE: actor: " << rkActor_.GetKey());

	SIdCreateClToGs& rtRData = (SIdCreateClToGs&)rkCommand_.GetData();
	if(false == g_kAccountDB.QueryCheck(rtRData.GetLoginId())) {
		if (g_kAccountDB.Insert(rtRData.GetLoginId(), rtRData.GetLoginPasswd(), rtRData.GetName())) {
			// 성공.
			rkCommand_.SetExtra(OK);

			rkActor_.Send(rkCommand_);
			return true;
		} else {
			// 실패1.
			rkCommand_.SetExtra(CANT_DO);
			rkActor_.Send(rkCommand_);
		}
	} else {
		// 실패2.
		rkCommand_.SetExtra(FAIL);
		rkActor_.Send(rkCommand_);
	}

	return true;
}

bool
CMD_ID_PING(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ID_PING: actor: " << rkActor_.GetKey());

	SIdPingClToGs& rtRData = (SIdPingClToGs&)rkCommand_.GetData();
	OUTPUT("key: " << rkActor_.GetKey() << ", name: " << rkActor_.GetName() << "recv tick: " << rtRData.tick);

	CCommand kCommand;
	kCommand.SetOrder(ID_PONG);
	SIdPingGsToCl& rtSData = (SIdPingGsToCl&)kCommand.GetData();
	rtSData.tick = g_kTick.GetTick();
	rtSData.timeOut = 0;
	if (NULL != rkActor_.GetRoomHandler()) {
		if (NULL != rkActor_.GetRoomHandler()->GetRoom()) {
			switch (rkActor_.GetRoomHandler()->GetRoom()->GetModType())
			{
			case MOD_FFA:
				break;
			case MOD_TDM:
				rtSData.timeOut = rkActor_.GetRoomHandler()->GetRoom()->GetTimeOut();
				break;
			case MOD_ZOMBIE:
				break;
			default:
				break;
			}
		}
	}

	OUTPUT("send tick: " << rtSData.tick);

	rkActor_.Send(kCommand, sizeof(SIdPingGsToCl));
	return true;
}

bool
CMD_ID_QUIT(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ID_QUIT: actor: " << rkActor_.GetKey());
	return true;
}

void
InitializeIdCommand() {
	SET_COMMAND(ID_AUTHORIZE);
	SET_COMMAND(ID_CREATE);
	SET_COMMAND(ID_PING);
	SET_COMMAND(ID_QUIT);
}
