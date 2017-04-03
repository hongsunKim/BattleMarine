/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_USER_STATUS(CCommand& rkCommand_) {
	CONSOLE("CMD_USER_STATUS: actor: " << g_kMainPlayer->GetKey());

	return true;
}

bool
CMD_USER_CHAT(CCommand& rkCommand_) {
	//장현우
	SUserChatGsToCl& rtRData = (SUserChatGsToCl&)rkCommand_.GetData();
	USER_CHAT_OUT(rtRData, rkCommand_.GetExtra());
	CONSOLE("CMD_USER_CHAT: " << ", actor: " << g_kMainPlayer->GetKey());
	return true;
}

bool
CMD_USER_ATTACK(CCommand& rkCommand_) {
	CONSOLE("CMD_USER_ATTACK: actor: " << g_kMainPlayer->GetKey());

	if (OK == rkCommand_.GetExtra()) {
		SUserAttackGsToCl& rtRData = (SUserAttackGsToCl&)rkCommand_.GetData();
		if (NULL != rtRData.target) {
			CPlayerEx* pkTarget = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.target);
			pkTarget->Damaged(g_kMainPlayer->GetPower());
			if (0 >= pkTarget->GetCurLife()) {
				if (STATUS_NORMAL == pkTarget->GetStatus()) {
					g_kMainRoom.IncreaseTeamPoint(g_kMainPlayer->GetTeamType());
				}
				pkTarget->SetStatus(STATUS_DYING);
			}
		}
	}
	return true;
}

//장현우, 이주봉 스팀팩 구현
bool
CMD_USER_STEAMPACK(CCommand& rkCommand_) {
	CONSOLE("CMD_USER_STEAMPACK: actor: " << g_kMainPlayer->GetKey());

	SUserSteamPackGsToCl& rtRData = (SUserSteamPackGsToCl&)rkCommand_.GetData();

	if (rkCommand_.GetExtra() == END)
	{
		g_kMainPlayer->SetISSteamPack(rtRData.IsSteamPack);
		g_kMainPlayer->SetISSteamPackTime(rtRData.SteamPackTime);
	}
	else if (rkCommand_.GetExtra() == START)
	{
		g_kMainPlayer->SetISSteamPackTime(10000);
		g_kMainPlayer->SetISSteamPack(true);

		g_kMainPlayer->Damaged(iPLAYER_STEAMPACK_POWER);
		if (g_kMainPlayer->GetCurLife() == 0)
		{
			g_kMainPlayer->SetCurLife(1);
		}
	}
	return true;
}

bool
CMD_USER_INFESTED(CCommand& rkCommand_)
{
	return 1;
}

bool
CMD_USER_ZOMBIE_INFEST(CCommand& rkCommand_)
{
	CONSOLE("CMD_USER_ZOMBIE_INFEST: actor: " << g_kMainPlayer->GetKey());

	if (OK == rkCommand_.GetExtra())
	{
		SUserInfestGsToCl& receivedDatum0 = (SUserInfestGsToCl&)rkCommand_.GetData();
		
		if (receivedDatum0.target)
		{
			CPlayerEx* pkTarget = (CPlayerEx*)g_kPlayerMgr.GetPlayer(receivedDatum0.target);

			pkTarget->SetState(STATE_INFESTED);
			pkTarget->SetTeamType(TEAM_GREEN);
		}
	}

	return 1;
}

//bool
//CMD_USER_ZOMBIE_MOVE(CCommand& rkCommand_)
//{
//
//}

void
InitializeUserCommand() {
	SET_COMMAND(USER_STATUS);
	SET_COMMAND(USER_CHAT);
	SET_COMMAND(USER_ATTACK);
	SET_COMMAND(USER_STEAMPACK);
	SET_COMMAND(USER_INFESTED);
	SET_COMMAND(USER_ZOMBIE_INFEST);
	//SET_COMMAND(USER_ZOMBIE_MOVE);
}
