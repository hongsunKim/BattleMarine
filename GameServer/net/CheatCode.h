/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

// 장현우
class CCheatCode
{
public:
	CCheatCode() {}
	virtual ~CCheatCode() {}

	static bool Warp(CPlayer& rkActor_, int x_, int y_)
	{
		CPlayer* pkPlayer = g_kPlayerMgr.Find(rkActor_.GetKey());
		CCommand kCommand;
		SPosition position;
		SCheatWarpGsToCl& rtSData = (SCheatWarpGsToCl&)kCommand.GetData();

		kCommand.SetOrder(CHEAT_CODE_WARP);
		kCommand.SetExtra(WARP);

		position.x = x_;
		position.y = y_;

		rtSData.actor = rkActor_.GetKey();
		rtSData.pos = position;
		rtSData.dir = DIRECTION_DOWN;

		if (isptr(pkPlayer))
		{
			pkPlayer->SetPosition(position);
		}
		else
		{
			OUTPUT("CMD_CHEAT_CODE_WARP: NULL Player: ", rkActor_.GetKey());
		}

		CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
		if (isptr(pkRoomHandler))
		{
			CRoom* pkRoom = pkRoomHandler->GetRoom();
			if (isptr(pkRoom))
			{
				pkRoom->Broadcast(kCommand, sizeof(SCheatWarpGsToCl));
			}
			else
			{
				OUTPUT("CMD_CHEAT_CODE_WARP: Room is NULL error");
			}
		}
		else
		{
			OUTPUT("CMD_CHEAT_CODE_WARP: RoomHandelr is NULL error");
		}

		return true;
	}
	static bool Kill(CPlayer& rkAcror_, char* KillPlayer)
	{
		CPlayer* pkPlayer = g_kPlayerMgr.Find(rkAcror_.GetKey());
		CPlayer* pkKillPlayer_ = g_kPlayerMgr.Find(atoi(KillPlayer));

		CCommand kCommand;
		kCommand.SetOrder(CHEAT_CODE_KILL);

		SuserKillGsToCl& rtSDate = (SuserKillGsToCl&)kCommand.GetData();

		if (strcmp(KillPlayer, "ALL") == 0)
		{
			kCommand.SetExtra(ALL);
			rtSDate.SetActor(pkPlayer->GetKey());

			CRoomHandler* pkRoomHandler = pkPlayer->GetRoomHandler();
			if (isptr(pkRoomHandler))
			{
				CRoom* pkRoom = pkRoomHandler->GetRoom();
				if (isptr(pkRoom))
				{
					pkRoom->Broadcast(kCommand, sizeof(SuserKillGsToCl));
					return true;
				}
				else
				{
					OUTPUT("CHEAT_CODE_KILL: Room is NULL error");
				}
			}
			else
			{
				OUTPUT("CHEAT_CODE_KILL: RoomHandelr is NULL error");
			}
		}
		else if (isptr(pkKillPlayer_))
		{
			kCommand.SetExtra(OK);
			rtSDate.SetActor(pkKillPlayer_->GetKey());

			CRoomHandler* pkRoomHandler = pkPlayer->GetRoomHandler();
			if (isptr(pkRoomHandler))
			{
				CRoom* pkRoom = pkRoomHandler->GetRoom();
				if (isptr(pkRoom))
				{
					pkRoom->Broadcast(kCommand, sizeof(SuserKillGsToCl));
					return true;
				}
				else
				{
					OUTPUT("CHEAT_CODE_KILL: Room is NULL error");
				}
			}
			else
			{
				OUTPUT("CHEAT_CODE_KILL: RoomHandelr is NULL error");
			}
		}

		return false;
	}

private:

};