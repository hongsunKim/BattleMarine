/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "RoomEx.h"
#include "../CommonHeader.h"

bool
CRoomEx::Initialize() {
	if(CRoom::Initialize()) {
		// Respawn 좌표
		m_tRespawnPosition[0].x = -6 * iSECTION_DISTANCE;
		m_tRespawnPosition[0].y = -8 * iSECTION_DISTANCE;

		m_tRespawnPosition[1].x = -4 * iSECTION_DISTANCE;
		m_tRespawnPosition[1].y = -13 * iSECTION_DISTANCE;

		m_tRespawnPosition[2].x = -22 * iSECTION_DISTANCE;
		m_tRespawnPosition[2].y = -13 * iSECTION_DISTANCE;

		m_tRespawnPosition[3].x = -15 * iSECTION_DISTANCE;
		m_tRespawnPosition[3].y = -24 * iSECTION_DISTANCE;

		m_tRespawnPosition[4].x = -35 * iSECTION_DISTANCE;
		m_tRespawnPosition[4].y = -8 * iSECTION_DISTANCE;

		m_tRespawnPosition[5].x = -51 * iSECTION_DISTANCE;
		m_tRespawnPosition[5].y = -11 * iSECTION_DISTANCE;

		m_tRespawnPosition[6].x = -45 * iSECTION_DISTANCE;
		m_tRespawnPosition[6].y = -19 * iSECTION_DISTANCE;

		m_tRespawnPosition[7].x = -35 * iSECTION_DISTANCE;
		m_tRespawnPosition[7].y = -23 * iSECTION_DISTANCE;

		m_tRespawnPosition[8].x = -8 * iSECTION_DISTANCE;
		m_tRespawnPosition[8].y = -48 * iSECTION_DISTANCE;

		m_tRespawnPosition[9].x = -24 * iSECTION_DISTANCE;
		m_tRespawnPosition[9].y = -52 * iSECTION_DISTANCE;

		m_tRespawnPosition[10].x = -35 * iSECTION_DISTANCE;
		m_tRespawnPosition[10].y = -38 * iSECTION_DISTANCE;

		m_tRespawnPosition[11].x = -12 * iSECTION_DISTANCE;
		m_tRespawnPosition[11].y = -35 * iSECTION_DISTANCE;

		m_tRespawnPosition[12].x = -38 * iSECTION_DISTANCE;
		m_tRespawnPosition[12].y = -34 * iSECTION_DISTANCE;

		m_tRespawnPosition[13].x = -40 * iSECTION_DISTANCE;
		m_tRespawnPosition[13].y = -48 * iSECTION_DISTANCE;

		m_tRespawnPosition[14].x = -55 * iSECTION_DISTANCE;
		m_tRespawnPosition[14].y = -35 * iSECTION_DISTANCE;

		m_tRespawnPosition[15].x = -48 * iSECTION_DISTANCE;
		m_tRespawnPosition[15].y = -54 * iSECTION_DISTANCE;

		// Respawn 색상
		m_tRespawnColor[0].A = 255;
		m_tRespawnColor[0].R = 153;
		m_tRespawnColor[0].G = 153;
		m_tRespawnColor[0].B = 000;

		m_tRespawnColor[1].A = 255;
		m_tRespawnColor[1].R = 204;
		m_tRespawnColor[1].G = 204;
		m_tRespawnColor[1].B = 000;

		m_tRespawnColor[2].A = 255;
		m_tRespawnColor[2].R = 255;
		m_tRespawnColor[2].G = 255;
		m_tRespawnColor[2].B = 000;

		m_tRespawnColor[3].A = 255;
		m_tRespawnColor[3].R = 153;
		m_tRespawnColor[3].G = 153;
		m_tRespawnColor[3].B = 102;

		m_tRespawnColor[4].A = 255;
		m_tRespawnColor[4].R = 204;
		m_tRespawnColor[4].G = 255;
		m_tRespawnColor[4].B = 204;

		m_tRespawnColor[5].A = 255;
		m_tRespawnColor[5].R = 153;
		m_tRespawnColor[5].G = 204;
		m_tRespawnColor[5].B = 153;

		m_tRespawnColor[6].A = 255;
		m_tRespawnColor[6].R = 051;
		m_tRespawnColor[6].G = 102;
		m_tRespawnColor[6].B = 051;

		m_tRespawnColor[7].A = 255;
		m_tRespawnColor[7].R = 051;
		m_tRespawnColor[7].G = 153;
		m_tRespawnColor[7].B = 051;

		m_tRespawnColor[8].A = 255;
		m_tRespawnColor[8].R = 000;
		m_tRespawnColor[8].G = 102;
		m_tRespawnColor[8].B = 000;

		m_tRespawnColor[9].A = 255;
		m_tRespawnColor[9].R = 051;
		m_tRespawnColor[9].G = 000;
		m_tRespawnColor[9].B = 102;

		m_tRespawnColor[10].A = 255;
		m_tRespawnColor[10].R = 153;
		m_tRespawnColor[10].G = 102;
		m_tRespawnColor[10].B = 204;

		m_tRespawnColor[11].A = 255;
		m_tRespawnColor[11].R = 204;
		m_tRespawnColor[11].G = 153;
		m_tRespawnColor[11].B = 255;

		m_tRespawnColor[12].A = 255;
		m_tRespawnColor[12].R = 255;
		m_tRespawnColor[12].G = 204;
		m_tRespawnColor[12].B = 000;

		m_tRespawnColor[13].A = 255;
		m_tRespawnColor[13].R = 204;
		m_tRespawnColor[13].G = 153;
		m_tRespawnColor[13].B = 000;

		m_tRespawnColor[14].A = 255;
		m_tRespawnColor[14].R = 255;
		m_tRespawnColor[14].G = 204;
		m_tRespawnColor[14].B = 102;

		m_tRespawnColor[15].A = 255;
		m_tRespawnColor[15].R = 255;
		m_tRespawnColor[15].G = 204;
		m_tRespawnColor[15].B = 153;

		return true;
	}
	return false;
}

bool
CRoomEx::Release() {
	if (CRoom::Release()) {
		return true;
	}
	return false;
}

void
CRoomEx::Clear() {
	CCommand kCommand;
	kCommand.SetOrder(ROOM_LEAVE);
	kCommand.SetExtra(CLOSE);

	for (UINT i = 0; i < GetTopCount(); ++i) {
		CPlayer* pkPlayer = m_pkMembers[i];
		if (isptr(pkPlayer)) {
			pkPlayer->Send(kCommand);
		}
	}

	CRoom::Clear();
}

bool
CRoomEx::Update() {
	//장현우, 이주봉 스팀팩 구현
	for (UINT i = 0; i < GetTopCount(); ++i) {
		CPlayer* pkPlayer = m_pkMembers[i];
		if (isptr(pkPlayer)) {
			if (isptr(pkPlayer->GetIsSteamPack())) {
				pkPlayer->SetISSteamPackTime(pkPlayer->GetIsSteamPackTime() - g_kTick.GetDeltaMSec());

				if (pkPlayer->GetIsSteamPackTime() <= g_kTick.GetDeltaMSec() + 100)
				{
					CCommand kCommand;
					kCommand.SetOrder(USER_STEAMPACK);
					kCommand.SetExtra(END);
					SUserSteamPackGsToCl& rtSData = (SUserSteamPackGsToCl&)kCommand.GetData();
					rtSData.SteamPackTime = 0;
					rtSData.IsSteamPack = false;

					pkPlayer->Send(kCommand, sizeof(SUserSteamPackGsToCl));
				}
			}
		}
	}

	if (ROOM_STATE_PLAYING == GetRoomState()) {
		TimeUpdate(FLOAT(g_kTick.GetDeltaMSec()) / FLOAT(1000));
	}

	CheckWin();

	return true;
}

bool
CRoomEx::Create(CPlayer& rkPlayer_) {
	((CPlayerEx&)rkPlayer_).SetRespawnIndex(GetTopCount());

	if(CRoom::Create(rkPlayer_)) {
		CCommand kCommand;
		kCommand.SetOrder(ROOM_INFO);
		kCommand.SetExtra(IN_);

		SRoomInfo& rtSData = (SRoomInfo&)kCommand.GetData();
		rtSData.id = GetId();
		rtSData.max = GetMaxUser();
		rtSData.mod = GetModType();
		if(IsDoing()) {
			rtSData.offset = 1;
		} else {
			rtSData.offset = 0;
		}
		rtSData.SetName(GetName());

		// ChannelMgr을 통한 Broadcast
		g_kChannelMgr.Broadcast(&rkPlayer_, kCommand, sizeof(SRoomInfo));
		return true;
	}
	return false;
}

bool
CRoomEx::Join(CPlayer& rkPlayer_) {
	CCommand kCommand;
	kCommand.SetOrder(ROOM_JOIN);

	if(0 < GetTopCount() && (GetTopCount() < GetMaxUser())) {
		CRoomHandler* pkRoomHandler = rkPlayer_.GetRoomHandler();
		if(isptr(pkRoomHandler)) {
			if(false == isptr(pkRoomHandler->GetRoom())) {
				((CPlayerEx&)rkPlayer_).SetRespawnIndex(GetTopCount());

				if(CRoom::Join(rkPlayer_)) {
					kCommand.SetExtra(OK);
					SRoomJoinGsToCl& rtSData = (SRoomJoinGsToCl&)kCommand.GetData();
					rtSData.id = GetId();

					rtSData.max = GetMaxUser();
					rtSData.mod = GetModType();
					rtSData.isPlaying = GetRoomState();

					switch (GetModType()) {
					case MOD_FFA:
						rtSData.team = TEAM_NONE;
						break;
					case MOD_TDM:
						UINT size;
						size = GetTopCount();
						UINT red, blue;
						red = 0; blue = 0;
						for (UINT i = 0; i < size; ++i) {
							switch (GetMember(i)->GetTeamType())
							{
							case TEAM_RED:
								++red;
								break;
							case TEAM_BLUE:
								++blue;
								break;
							}
						}
						rtSData.team = (red > blue) ? TEAM_BLUE : TEAM_RED;
						rkPlayer_.SetTeamType((TEAM_TYPE)rtSData.team);
						break;
					case MOD_ZOMBIE:
						break;
					}

					if (IsDoing()) {
						rtSData.offset = 1;
					} else {
						rtSData.offset = 0;
					}

					rtSData.SetName(GetName());

					rtSData.timeOut = GetTimeOut();

					rkPlayer_.Send(kCommand, sizeof(SRoomJoinGsToCl));

					return true;
				} else {
					kCommand.SetExtra(DENY);
					OUTPUT("critical error: in room");
				}
			} else {
				kCommand.SetExtra(DENY);
				OUTPUT("critical error: in room");
			}
		} else {
			OUTPUT("critical error: roomHandler is null: ");
			kCommand.SetExtra(FAIL);
		}
	} else {
		OUTPUT("error: room is full or empty: " << GetTopCount() << "[" << iMAX_ROOM_MEMBERS << "] " << rkPlayer_.GetKey());
		kCommand.SetExtra(FULL);
	}
	rkPlayer_.Send(kCommand);
	return false;
}

bool
CRoomEx::Leave(CPlayer& rkPlayer_) {
	if(CRoom::Leave(rkPlayer_)) {
		((CPlayerEx&)rkPlayer_).SetRespawnIndex(0);

		if(0 >= GetTopCount()) {
			 g_kChannelMgr.DeleteRoom(GetId());

			CCommand kCommand;
			kCommand.SetOrder(ROOM_INFO);
			kCommand.SetExtra(OUT_);

			SRoomInfo& rtOtherData = (SRoomInfo&)kCommand.GetData();
			rtOtherData.id = GetId();

			g_kChannelMgr.Broadcast(&rkPlayer_, kCommand, sizeof(UINT32));
		}
		return true;
	}
	return false;
}

bool
CRoomEx::Broadcast(CCommand& rkCommand_, INT iSize_, CPlayer* pkActor_, CPlayer* pkTarget_) {
	if (0 < GetTopCount()) {
		CPlayer* pkPlayer = NULL;
		for (UINT i = 0; i < GetTopCount(); ++i) {
			pkPlayer = m_pkMembers[i];
			if (isptr(pkPlayer)) {
				if ((pkPlayer != pkActor_) && (pkPlayer != pkTarget_)) {
					pkPlayer->Send(rkCommand_, iSize_);
				}
			}
			else {
				OUTPUT("critical error: player[" << i << "] is null: " << GetTopCount());
			}
		}
		return true;
	}
	else {
		OUTPUT("room is empty");
	}
	return false;
}

SRespawnPosition*
CRoomEx::GetRespawnPosition(CPlayer& rkPlayer_) {
	if((0 <= ((CPlayerEx&)rkPlayer_).GetRespawnIndex()) && (iMAX_ROOM_MEMBERS > ((CPlayerEx&)rkPlayer_).GetRespawnIndex())) {
		return &m_tRespawnPosition[((CPlayerEx&)rkPlayer_).GetRespawnIndex()];
	}
	return NULL;
}

SRespawnColor*
CRoomEx::GetRespawnColor(CPlayer& rkPlayer_) {
	if((0 <= ((CPlayerEx&)rkPlayer_).GetRespawnIndex()) && (iMAX_ROOM_MEMBERS > ((CPlayerEx&)rkPlayer_).GetRespawnIndex())) {
		return &m_tRespawnColor[((CPlayerEx&)rkPlayer_).GetRespawnIndex()];
	}
	return NULL;
}

bool CRoomEx::CheckWin(CPlayer* player)
{
	int zombieCount0 = 0;
	int deadZombieCount0 = 0;

	for (UINT i = 0; i < GetTopCount(); ++i)
	{
		CPlayer* player0 = m_pkMembers[i];

		if (player0)
		{
			if (TEAM_GREEN == player0->GetTeamType())
			{
				++zombieCount0;

				if (STATUS_DYING == player0->GetStatus()) ++deadZombieCount0;
			}
		}
	}

	if (zombieCount0 == deadZombieCount0) return 1; //인간 승리
	else if (zombieCount0 == GetTopCount()) return 0; //좀비 승리

	return 0;
}
