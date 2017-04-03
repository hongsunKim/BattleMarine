/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_CHEAT_CODE_WARP(CCommand& rkCommand_)
{
	SCheatWarpGsToCl& rtRDate = (SCheatWarpGsToCl&)rkCommand_.GetData();

	if (rkCommand_.GetExtra() == WARP)
	{
		CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRDate.actor);
		if (isptr(pkPlayer))
		{
			pkPlayer->SetPosition(rtRDate.pos);
		}
		else
		{
			CONSOLE("null Player: ", rtRDate.actor);
		}
	}

	return true;
}

bool
CMD_CHEAT_CODE_KILL(CCommand& rkCommand_)
{
	SuserKillGsToCl& rtRDate = (SuserKillGsToCl&)rkCommand_.GetData();
	CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRDate.GetActor());

	if (rkCommand_.GetExtra() == ALL)
	{
		int size = pkPlayer->GetRoomHandler()->GetRoom()->GetTopCount();

		for (int i = 0; i < size; i++)
		{
			if (g_kPlayerMgr.Seek(i)->GetKey() == rtRDate.GetActor())
			{
				continue;
			}
			else
			{
				g_kPlayerMgr.Seek(i)->Damaged(g_kPlayerMgr.Seek(i)->GetCurLife());
				g_kPlayerMgr.Seek(i)->SetStatus(STATUS_DYING);
				g_kPlayerMgr.Seek(i)->SetDeathStartTick(g_kTick.GetTick());
			}
		}
	}
	else if (rkCommand_.GetExtra() == OK)
	{
		pkPlayer->Damaged(pkPlayer->GetCurLife());
		pkPlayer->SetStatus(STATUS_DYING);
		pkPlayer->SetDeathStartTick(g_kTick.GetTick());
	}

	return true;
}

void
InitializeCheatCommand()
{
	SET_COMMAND(CHEAT_CODE_WARP);
	SET_COMMAND(CHEAT_CODE_KILL);
}