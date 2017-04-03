/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_ROOM_CREATE(CCommand& rkCommand_) {
	//CONSOLE("CMD_ROOM_CREATE: actor: " << rkActor_.GetKey());

	// rtActor_는 컨넥터에 따라 다른 플레이어를 지정함.
	// 클라이언트는 되도록 MainPlayer 사용을 권장.

	if (OK == rkCommand_.GetExtra()) {
		SRoomCreateGsToCl& rtRData = (SRoomCreateGsToCl&)rkCommand_.GetData();
		
		g_kMainRoom.SetId(rtRData.id);
		g_kMainRoom.SetName(rtRData.GetName());
		g_kMainRoom.SetMaxUser(rtRData.max);
		g_kMainRoom.SetModType((MOD_TYPE)rtRData.mod);
		g_kMainRoom.Create(*g_kMainPlayer);
		g_kMainRoom.SetDoing(true);

		switch (g_kMainRoom.GetModType())
		{
		case MOD_FFA:
			g_kMainPlayer->SetTeamType(TEAM_NONE);
			g_kMainRoom.SetRoomState(ROOM_STATE_PLAYING);
			break;
		case MOD_TDM:
			g_kMainPlayer->SetTeamType(TEAM_RED);
			//데이터베이스
			//모드에 따른 시간 설정해줘야함
			//g_kModInfoDB
			g_kMainRoom.SetTimeOut(50);
			break;
		case MOD_ZOMBIE:
			g_kMainPlayer->SetTeamType(TEAM_GREEN);
			g_kMainRoom.SetRoomState(ROOM_STATE_PLAYING);
			break;
		}

		g_kMainPlayer->SetIsRoom(true);
		g_kMainPlayer->SetStatus(STATUS_DYING);
		//g_kMainPlayer->SetCurLife(g_kMainPlayer->GetMaxLife());

		SRoomInfo tRoomInfo;
		tRoomInfo.id = g_kMainRoom.GetId();
		tRoomInfo.max = g_kMainRoom.GetMaxUser();
		tRoomInfo.offset = 1;
		tRoomInfo.mod = g_kMainRoom.GetModType();
		tRoomInfo.SetName(g_kMainRoom.GetName());
		tRoomInfo.state = g_kMainRoom.GetRoomState();

		g_kMainRoom.InsertRoomList(tRoomInfo);
		
		CCommand kCommand;
		kCommand.SetOrder(ROOM_SYNC);
		kCommand.SetExtra(NONE);
		g_kMainPlayer->Send(kCommand);
		
		CONSOLE("CMD_ROOM_CREATE: OK: room id: " << rtRData.id << ", room id: " << g_kMainRoom.GetId());

		REFRESH_ROOM_LIST();
		REFRESH_ROOM_MEMBER_LIST();
		REFRESH_USER_LIST();
	} else if (DENY == rkCommand_.GetExtra()) {
		CONSOLE("CMD_ROOM_CREATE: DENY: ");
	} else if (NOT_ENOUGH == rkCommand_.GetExtra()) {
		CONSOLE("CMD_ROOM_CREATE: NOT_ENOUGH: ");
	} else if (FAIL == rkCommand_.GetExtra()) {
		CONSOLE("CMD_ROOM_CREATE: FAIL: ");
	}
	return true;
}

bool
CMD_ROOM_JOIN(CCommand& rkCommand_) {
	//CONSOLE("CMD_ROOM_JOIN: actor: " << rkActor_.GetKey());

	if (OK == rkCommand_.GetExtra()) {
		SRoomJoinGsToCl& rtRData = (SRoomJoinGsToCl&)rkCommand_.GetData();

		g_kMainRoom.SetId(rtRData.id);
		g_kMainRoom.SetName(rtRData.GetName());
		g_kMainRoom.SetMaxUser(rtRData.max);
		g_kMainRoom.SetModType((MOD_TYPE)rtRData.mod);
		g_kMainRoom.SetDoing(true);
		g_kMainRoom.Join(*g_kMainPlayer);
		g_kMainRoom.SetTimeOut(rtRData.timeOut);
		g_kMainRoom.SetRoomState((ROOM_STATE)rtRData.isPlaying);

		g_kMainPlayer->SetIsRoom(true);
		g_kMainPlayer->SetStatus(STATUS_DYING);
		g_kMainPlayer->SetTeamType((TEAM_TYPE)rtRData.team);

		CCommand kCommand;
		kCommand.SetOrder(ROOM_SYNC);
		kCommand.SetExtra(NONE);
		g_kMainPlayer->Send(kCommand);

		CONSOLE("CMD_ROOM_JOIN: OK: room id: " << rtRData.id << ", room name: " << rtRData.GetName());

		REFRESH_ROOM_LIST();
		REFRESH_ROOM_MEMBER_LIST();
	} else if(FULL == rkCommand_.GetExtra()) {
		// 더이상 못들어감.
		CONSOLE("CMD_ROOM_JOIN: FULL: ");
	} else if (DENY == rkCommand_.GetExtra()) {
		// 이미 다른방에 있음.
		CONSOLE("CMD_ROOM_JOIN: DENY: ");
	} else if (EMPTY == rkCommand_.GetExtra()) {
		// 방이 없음.
		CONSOLE("CMD_ROOM_JOIN: EMPTY: ");
	} else if (FAIL == rkCommand_.GetExtra()) {
		// 서버 오류.
		CONSOLE("CMD_ROOM_JOIN: FAIL: ");
	}
	return true;
}

bool
CMD_ROOM_LEAVE(CCommand& rkCommand_) {
	CONSOLE("CMD_ROOM_LEAVE: actor: " << g_kMainPlayer->GetKey());
	if (OK == rkCommand_.GetExtra()) {
		UINT uiRoomId = g_kMainRoom.GetId();
		g_kMainRoom.Leave(*g_kMainPlayer);
		g_kMainPlayer->SetIsRoom(false);

		CCommand kCommand;
		kCommand.SetOrder(ROOM_SYNC);
		kCommand.SetExtra(OUT_);
		g_kMainPlayer->Send(kCommand);

		// kill/death 등 Player 정보 생성시 Clear() 함수 구현 필요.
		//g_kMainPlayer->Clear();

		if(false == g_kMainRoom.IsAvailable()) {
			g_kMainRoom.DeleteRoomList(uiRoomId);
		}

		g_kMainRoom.Clear();

		REFRESH_ROOM_LIST();
		REFRESH_ROOM_MEMBER_LIST();
	} else if (FAIL == rkCommand_.GetExtra()) {
		// 서버 오류.
		CONSOLE("CMD_ROOM_LEAVE: FAIL: ");
	}
	return true;
}

bool
CMD_ROOM_MATCH(CCommand& rkCommand_) {
	CONSOLE("CMD_ROOM_MATCH: actor: " << g_kMainPlayer->GetKey() << ", extra: " << rkCommand_.GetExtra() << ", option: " << rkCommand_.GetOption() << ", mission: " << rkCommand_.GetMission());

	return true;
}

bool
CMD_ROOM_INFO(CCommand& rkCommand_) {
	//CONSOLE("CMD_ROOM_INFO: actor: " << g_kMainPlayer->GetKey());

	if(IN_ == rkCommand_.GetExtra()) {
		SRoomInfo& rtRData = (SRoomInfo&)rkCommand_.GetData();
		
		CONSOLE("CMD_ROOM_INFO: IN_: id: " << rtRData.id + ", offset: " << rtRData.offset << ", max: " << rtRData.GetMax() << ", mod: " << rtRData.mod << ", name: " << rtRData.GetName());

		g_kMainRoom.InsertRoomList(rtRData);

		REFRESH_ROOM_LIST();
	} else if (OUT_ == rkCommand_.GetExtra()) {
		SRoomInfo& rtRData = (SRoomInfo&)rkCommand_.GetData();

		CONSOLE("CMD_ROOM_INFO: OUT_: id: " << rtRData.id);

		g_kMainRoom.DeleteRoomList(rtRData.id);

		REFRESH_ROOM_LIST();
	}

	return true;
}

bool
CMD_ROOM_LIST(CCommand& rkCommand_) {
	//CONSOLE("CMD_ROOM_LIST: actor: " << g_kMainPlayer->GetKey());
	if (0 == rkCommand_.GetMission()) {
		if (NEW == rkCommand_.GetExtra()) {
			// 방목록 정보 도착.
			g_kMainRoom.ClearRoomList();

			SRoomListGsToCl& rtRData = (SRoomListGsToCl&)rkCommand_.GetData();
			for (UINT i = 0; i < rkCommand_.GetOption(); ++i) {
				SRoomInfo tRoomInfo;
				tRoomInfo.id = rtRData.list[i].id;
				tRoomInfo.max = rtRData.list[i].max;
				tRoomInfo.mod = rtRData.list[i].mod;
				tRoomInfo.offset = rtRData.list[i].offset;
				tRoomInfo.SetName(rtRData.list[i].GetName());
				tRoomInfo.state = rtRData.list[i].state;

				CONSOLE("CMD_ROOM_LIST: NEW: id: " << tRoomInfo.id + ", offset: " << tRoomInfo.offset << ", max: " << tRoomInfo.GetMax() << ", mod: " << tRoomInfo.mod << ", name: " << tRoomInfo.GetName());

				g_kMainRoom.InsertRoomList(tRoomInfo);
			}
			CONSOLE("CMD_ROOM_LIST: NEW: count: " << rkCommand_.GetOption());
		} else if (CHANGE == rkCommand_.GetExtra()) {
			// 방목록 끊어서 받음.
			SRoomListGsToCl& rtRData = (SRoomListGsToCl&)rkCommand_.GetData();
			for (UINT i = 0; i < rkCommand_.GetOption(); ++i) {
				SRoomInfo tRoomInfo;
				tRoomInfo.id = rtRData.list[i].id;
				tRoomInfo.max = rtRData.list[i].max;
				tRoomInfo.mod = rtRData.list[i].mod;
				tRoomInfo.offset = rtRData.list[i].offset;
				tRoomInfo.SetName(rtRData.list[i].GetName());
				tRoomInfo.state = rtRData.list[i].state;

				CONSOLE("CMD_ROOM_LIST: CHANGE: id: " << tRoomInfo.id + ", offset: " << tRoomInfo.offset << ", max: " << tRoomInfo.GetMax() << ", mod: " << tRoomInfo.mod << ", name: " << tRoomInfo.GetName());

				g_kMainRoom.InsertRoomList(tRoomInfo);
			}
			CONSOLE("CMD_ROOM_LIST: CHANGE: count: " << rkCommand_.GetOption());
		} else if (DONE == rkCommand_.GetExtra()) {
			// 방목록 전송 완료.

			REFRESH_ROOM_LIST();
			CONSOLE("CMD_ROOM_LIST: DONE: ");
		} else if (EMPTY == rkCommand_.GetExtra()) {
			// 방목록 없음.
			CONSOLE("CMD_ROOM_LIST: EMPTY: ");
		} else if (FAIL == rkCommand_.GetExtra()) {
			// 서버 오류.
			CONSOLE("CMD_ROOM_LIST: FAIL: ");
		}
	} else if (1 == rkCommand_.GetMission()) {
		if (NEW == rkCommand_.GetExtra()) {
			// 맴버 목록 정보 도착.

			SRoomMemberListGsToCl& rtRData = (SRoomMemberListGsToCl&)rkCommand_.GetData();
			for (UINT i = 0; i < rkCommand_.GetOption(); ++i) {
				CPlayer* pkPlayer = g_kPlayerMgr.GetPlayer(rtRData.list[i].actor);
				if (isptr(pkPlayer)) {
					pkPlayer->SetName(rtRData.list[i].GetName());

					g_kMainRoom.Join(*pkPlayer);

					pkPlayer->SetStatus((STATUS_TYPE)rtRData.list[i].status);
					pkPlayer->SetTeamType((TEAM_TYPE)rtRData.list[i].team);
					pkPlayer->SetPosition(rtRData.list[i].pos);
					pkPlayer->SetColor(rtRData.list[i].color);

					CONSOLE("CMD_ROOM_LIST: MEMBER: NEW: key: " << pkPlayer->GetKey() << ", name: " << pkPlayer->GetName() << ", team: " << pkPlayer->GetTeamType() << ", pos: (" << pkPlayer->GetPosition().x << ":" << pkPlayer->GetPosition().y << "), color: (" << pkPlayer->GetColor().A << ":" << pkPlayer->GetColor().R << ":" << pkPlayer->GetColor().G << ":" << pkPlayer->GetColor().B << ")");
				}
			}
			CONSOLE("CMD_ROOM_LIST: MEMBER: NEW: count: " << rkCommand_.GetOption());
		} else if (CHANGE == rkCommand_.GetExtra()) {
			// 맴버 목록 끊어서 받음.
			SRoomMemberListGsToCl& rtRData = (SRoomMemberListGsToCl&)rkCommand_.GetData();
			for (UINT i = 0; i < rkCommand_.GetOption(); ++i) {
				CPlayer* pkPlayer = g_kPlayerMgr.GetPlayer(rtRData.list[i].actor);
				if (isptr(pkPlayer)) {
					pkPlayer->SetName(rtRData.list[i].GetName());

					g_kMainRoom.Join(*pkPlayer);

					pkPlayer->SetStatus((STATUS_TYPE)rtRData.list[i].status);
					pkPlayer->SetTeamType((TEAM_TYPE)rtRData.list[i].team);
					pkPlayer->SetPosition(rtRData.list[i].pos);
					pkPlayer->SetColor(rtRData.list[i].color);

					CONSOLE("CMD_ROOM_LIST: MEMBER: CHANGE: key: " << pkPlayer->GetKey() << ", name: " << pkPlayer->GetName() << ", team: " << pkPlayer->GetTeamType() << ", pos: (" << pkPlayer->GetPosition().x << ":" << pkPlayer->GetPosition().y << "), color: (" << pkPlayer->GetColor().A << ":" << pkPlayer->GetColor().R << ":" << pkPlayer->GetColor().G << ":" << pkPlayer->GetColor().B << ")");
				}
			}
			CONSOLE("CMD_ROOM_LIST: MEMBER: CHANGE: count: " << rkCommand_.GetOption());
		} else if (DONE == rkCommand_.GetExtra()) {
			// 맴버 목록 전송 완료.

			REFRESH_ROOM_MEMBER_LIST();
			CONSOLE("CMD_ROOM_LIST: MEMBER: DONE: ");
		} else if (EMPTY == rkCommand_.GetExtra()) {
			// 맴버 목록 없음.
			CONSOLE("CMD_ROOM_LIST: MEMBER: EMPTY: ");
		} else if (FAIL == rkCommand_.GetExtra()) {
			// 서버 오류.
			CONSOLE("CMD_ROOM_LIST: MEMBER: FAIL: ");
		}
	}

	return true;
}

bool
CMD_ROOM_JOIN_OTHER(CCommand& rkCommand_) {
	CONSOLE("CMD_ROOM_JOIN_OTHER: actor: " << g_kMainPlayer->GetKey());

	if (OK == rkCommand_.GetExtra()) {
		if (g_kMainRoom.IsAvailable()) {
			SRoomJoinOtherGsToCl& rtRData = (SRoomJoinOtherGsToCl&)rkCommand_.GetData();

			CPlayer* pkPlayer = g_kPlayerMgr.GetPlayer(rtRData.actor);
			if (isptr(pkPlayer)) {
				g_kMainRoom.Join(*pkPlayer);

				REFRESH_ROOM_MEMBER_LIST();
				CONSOLE("CMD_ROOM_JOIN_OTHER: OK: key: " << pkPlayer->GetKey() << ", name: " << pkPlayer->GetName());
			}
		}
	}

	return true;
}

bool
CMD_ROOM_LEAVE_OTHER(CCommand& rkCommand_) {
	CONSOLE("CMD_ROOM_LEAVE_OTHER: actor: " << g_kMainPlayer->GetKey());

	if (g_kMainRoom.IsAvailable()) {
		if (OK == rkCommand_.GetExtra()) {
			SRoomLeaveOtherGsToCl& rtRData = (SRoomLeaveOtherGsToCl&)rkCommand_.GetData();

			CPlayer* pkPlayer = g_kPlayerMgr.GetPlayer(rtRData.actor);
			if (isptr(pkPlayer)) {
				g_kMainRoom.Leave(*pkPlayer);

				CONSOLE("CMD_ROOM_LEAVE_OTHER: OK: actor: " << rtRData.actor);
			} else {
				CONSOLE("CMD_ROOM_LEAVE_OTHER: OK: player is null: actor: " << rtRData.actor);
			}
		} else if (CHECK == rkCommand_.GetExtra()) {
			// 리더 변경정보 포함.
			SRoomLeaveOtherGsToCl& rtRData = (SRoomLeaveOtherGsToCl&)rkCommand_.GetData();

			CPlayer* pkPlayer = g_kPlayerMgr.GetPlayer(rtRData.actor);
			if (isptr(pkPlayer)) {
				g_kMainRoom.Leave(*pkPlayer);

				CPlayer* pkLeader = g_kMainRoom.GetLeader();
				if (isptr(pkLeader)) {
					if (pkLeader->GetKey() == rtRData.leader) {
						CONSOLE("CMD_ROOM_LEAVE_OTHER: CHECK: actor: " << rtRData.actor << ", leader: " << rtRData.leader);
					} else {
						CONSOLE("CMD_ROOM_LEAVE_OTHER: CHECK: leader was not found: actor: " << rtRData.actor << ", leader: [" << rtRData.leader << ":" << pkLeader->GetKey() << "]");
					}
				} else {
					CONSOLE("CMD_ROOM_LEAVE_OTHER: CHECK: leader is null: actor: " << rtRData.actor << ", leader: [" << rtRData.leader << ":0]");
				}
			} else {
				CONSOLE("CMD_ROOM_LEAVE_OTHER: CHECK: player is null: actor: " << rtRData.actor << ", leader: " << rtRData.leader);
			}
		}
		REFRESH_ROOM_MEMBER_LIST();
		if (MOD_TDM == g_kMainRoom.GetModType() && ROOM_STATE_PLAYING == g_kMainRoom.GetRoomState()) {
			if (g_kMainPlayer->GetKey() == g_kMainRoom.GetLeader()->GetKey()) {
				if (0 == g_kMainRoom.GetTeamCount(TEAM_RED) || 0 == g_kMainRoom.GetTeamCount(TEAM_BLUE)) {
					//방장팀이 이겼다.
					CCommand kCommand;
					kCommand.SetOrder(ROOM_END_PLAYING);
					SRoomEndPlaying& rtSData = (SRoomEndPlaying&)kCommand.GetData();
					rtSData.winTeam = g_kMainPlayer->GetTeamType();
					g_kMainPlayer->Send(kCommand, sizeof(SRoomEndPlaying));
				}
			}
		}
	}
	return true;
}

//장현우 구현
bool
CMD_ROOM_SYNC(CCommand& rkCommand_) {
	SRoomSyncGsToCl& rtRData = (SRoomSyncGsToCl&)rkCommand_.GetData();

	CONSOLE("CMD_ROOM_SYNC: actor: " << g_kMainPlayer->GetKey() << "is: " << g_kPlayerMgr.Find(rtRData.actor)->GetKey());

	if (rkCommand_.GetExtra() == CONNECT || rkCommand_.GetExtra() == NONE)
	{
		g_kPlayerMgr.Find(rtRData.actor)->SetIsRoom(true);
	}
	else if (rkCommand_.GetExtra() == OUT_)
	{
		g_kPlayerMgr.Find(rtRData.actor)->SetIsRoom(false);
	}


	return true;
}

bool
CMD_ROOM_START_PLAYING(CCommand& rkCommand_) {
	if (OK == rkCommand_.GetExtra()) {
		g_kMainRoom.SetRoomState(ROOM_STATE_PLAYING);
		CONSOLE("CMD_ROOM_START_PLAYING: OK");
	} else if (FAIL == rkCommand_.GetExtra()){
		
	}
	return true;
}

bool
CMD_ROOM_START_INFO(CCommand& rkCommand_) {
	SRoomStartInfoGsToCl& rtRData = (SRoomStartInfoGsToCl&)rkCommand_.GetData();
	SRoomInfo* roomInfo = g_kMainRoom.FindRoomList(rtRData.room);
	if (NULL != roomInfo) {
		roomInfo->state = ROOM_STATE_PLAYING;
		REFRESH_ROOM_LIST();
		REFRESH_USER_LIST();
		CONSOLE("CMD_ROOM_START_INFO: room: " << roomInfo->id);
	}
	return true;
}

bool
CMD_ROOM_END_PLAYING(CCommand& rkCommand_) {
	SRoomEndPlaying& rtRData = (SRoomEndPlaying&)rkCommand_.GetData();
	if (rtRData.draw) {
		g_kMainPlayer->SetResult(GAME_RESULT_DRAW);
	}
	else {
		if (g_kMainPlayer->GetTeamType() == rtRData.winTeam) {
			g_kMainPlayer->SetResult(GAME_RESULT_WIN);
		}
		else {
			g_kMainPlayer->SetResult(GAME_RESULT_LOSE);
		}
	}
	g_kMainRoom.SetRoomState(ROOM_STATE_END);
	g_kMainRoom.FindRoomList(g_kMainRoom.GetId())->state = ROOM_STATE_END;
	REFRESH_ROOM_LIST();
	REFRESH_USER_LIST();
	CONSOLE("CMD_ROOM_END_PLAYING: OK");
	return true;
}

bool
CMD_ROOM_END_INFO(CCommand& rkCommand_) {
	SRoomEndInfoGsToCl& rtRData = (SRoomEndInfoGsToCl&)rkCommand_.GetData();
	SRoomInfo* roomInfo = g_kMainRoom.FindRoomList(rtRData.room);
	if (NULL != roomInfo) {
		roomInfo->state = ROOM_STATE_END;
		REFRESH_ROOM_LIST();
		REFRESH_USER_LIST();
		CONSOLE("CMD_ROOM_END_INFO: room: " << roomInfo->id);
	}
	return true;
}

void
InitializeRoomCommand() {
	SET_COMMAND(ROOM_CREATE);
	SET_COMMAND(ROOM_JOIN);
	SET_COMMAND(ROOM_LEAVE);
	SET_COMMAND(ROOM_MATCH);
	SET_COMMAND(ROOM_INFO);
	SET_COMMAND(ROOM_LIST);
	SET_COMMAND(ROOM_JOIN_OTHER);
	SET_COMMAND(ROOM_LEAVE_OTHER);
	SET_COMMAND(ROOM_SYNC);
	SET_COMMAND(ROOM_START_PLAYING);
	SET_COMMAND(ROOM_START_INFO);
	SET_COMMAND(ROOM_END_PLAYING);
	SET_COMMAND(ROOM_END_INFO);
}
