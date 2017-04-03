/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_ROOM_CREATE(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_ROOM_CREATE: actor: " << rkActor_.GetKey());

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		CRoom* pkRoom = pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			CCommand kCommand;
			kCommand.SetOrder(ROOM_LEAVE);
			kCommand.SetExtra(NONE);

			rkActor_.Send(kCommand);
		}

		pkRoom = g_kChannelMgr.NewRoom();
		if (isptr(pkRoom)) {
			SRoomCreateClToGs& rtRData = (SRoomCreateClToGs&)rkCommand_.GetData();
			pkRoom->SetName(rtRData.GetName());
			pkRoom->SetMaxUser(rtRData.max);
			pkRoom->SetModType((MOD_TYPE)rtRData.mod);

			//OUTPUT("CMD_ROOM_CREATE: actor : " << rkActor_.GetKey() << ", name: " << rtRData.GetName() << ", max: " << rtRData.max);

			if (pkRoom->Create(rkActor_)) {
				pkRoom->SetDoing(true);

				rkCommand_.SetExtra(OK);
				SRoomCreateGsToCl& rtSData = (SRoomCreateGsToCl&)rkCommand_.GetData();
				rtSData.id = pkRoom->GetId();
				rtSData.SetName(pkRoom->GetName());
				rtSData.max = pkRoom->GetMaxUser();
				rtSData.mod = pkRoom->GetModType();

				switch (rtSData.mod)
				{
				case MOD_FFA:
					pkRoom->SetRoomState(ROOM_STATE_PLAYING);
					rkActor_.SetTeamType(TEAM_NONE);
					break;
				case MOD_TDM:
					pkRoom->SetTimeOut(50);
					rkActor_.SetTeamType(TEAM_RED);
					break;
				case MOD_ZOMBIE:
					pkRoom->SetRoomState(ROOM_STATE_PLAYING);
					break;
				}

				rkActor_.Send(rkCommand_, sizeof(SRoomCreateGsToCl));

				OUTPUT("OK: key: " << rkActor_.GetKey() << ", name: " << rkActor_.GetName() << ", room id: " << pkRoom->GetId() << ", room max user: " << pkRoom->GetMaxUser() << ", room mod type: " << pkRoom->GetModType() << ", room name: " << pkRoom->GetName());

				SRespawnPosition* ptPosition = ((CRoomEx*)pkRoom)->GetRespawnPosition(rkActor_);
				if(isptr(ptPosition)) {
					rkActor_.SetPosition(*ptPosition);
				}

				SRespawnColor* ptColor = ((CRoomEx*)pkRoom)->GetRespawnColor(rkActor_);
				if(isptr(ptColor)) {
					rkActor_.SetColor(*ptColor);
				}

				CCommand kCommand;
				kCommand.SetOrder(OTHER_RESPAWN);
				kCommand.SetExtra(OK);

				SOtherRespawnGsToCl& rtSData2 = (SOtherRespawnGsToCl&)kCommand.GetData();
				rtSData2.actor = rkActor_.GetKey();
				rtSData2.pos.x = rkActor_.GetPosition().x;
				rtSData2.pos.y = rkActor_.GetPosition().y;

				rtSData2.color.A = rkActor_.GetColor().A;
				rtSData2.color.R = rkActor_.GetColor().R;
				rtSData2.color.G = rkActor_.GetColor().G;
				rtSData2.color.B = rkActor_.GetColor().B;
				rtSData2.team = rkActor_.GetTeamType();

				pkRoom->Broadcast(kCommand, sizeof(SOtherRespawnGsToCl));

				rkActor_.SetStatus(STATUS_NORMAL);
				//rkActor_.SetCurLife(rkActor_.GetMaxLife());
				OUTPUT("RESPAWN: actor: " << rkActor_.GetKey() << ", pos: (" << rkActor_.GetPosition().x << ":" << rkActor_.GetPosition().y << ", color: (" << rkActor_.GetColor().A << ":" << rkActor_.GetColor().R << ":" << rkActor_.GetColor().G << ":" << rkActor_.GetColor().B << ")");
				return true;
			} else {
				OUTPUT("[" << rkActor_.GetKey() << "] room create failed: ");
			}
			rkCommand_.SetExtra(DENY);
			g_kChannelMgr.DeleteRoom(pkRoom->GetId());
		} else {
			rkCommand_.SetExtra(NOT_ENOUGH);
			rkActor_.Send(rkCommand_);
			return true;
		}
	} else {
		OUTPUT("[" << rkActor_.GetKey() << "] room handler is null: ");
	}

	rkActor_.Send(rkCommand_);
	rkActor_.Disconnect();
	return true;
}

bool
CMD_ROOM_JOIN(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_ROOM_JOIN: actor: " << rkActor_.GetKey());

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		CRoom* pkRoom = pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			CCommand kCommand;
			kCommand.SetOrder(ROOM_LEAVE);
			kCommand.SetExtra(NONE);

			rkActor_.Send(kCommand);
		}

		SRoomJoinClToGs& rtRData = (SRoomJoinClToGs&)rkCommand_.GetData();

		pkRoom = g_kChannelMgr.FindRoom(rtRData.id);
		if (isptr(pkRoom)) {
			if (pkRoom->Join(rkActor_)) {

				pkRoom->SetDoing(true);
				OUTPUT("OK: key: " + rkActor_.GetKey() << ", room id: " << rtRData.id);

				SRespawnPosition* ptPosition = ((CRoomEx*)pkRoom)->GetRespawnPosition(rkActor_);
				if(isptr(ptPosition)) {
					rkActor_.SetPosition(*ptPosition);
				}

				SRespawnColor* ptColor = ((CRoomEx*)pkRoom)->GetRespawnColor(rkActor_);
				if(isptr(ptColor)) {
					rkActor_.SetColor(*ptColor);
				}

				CCommand kCommand;
				kCommand.SetOrder(OTHER_RESPAWN);
				kCommand.SetExtra(OK);

				SOtherRespawnGsToCl& rtSData = (SOtherRespawnGsToCl&)kCommand.GetData();
				rtSData.actor = rkActor_.GetKey();
				rtSData.pos.x = rkActor_.GetPosition().x;
				rtSData.pos.y = rkActor_.GetPosition().y;

				rtSData.color.A = rkActor_.GetColor().A;
				rtSData.color.R = rkActor_.GetColor().R;
				rtSData.color.G = rkActor_.GetColor().G;
				rtSData.color.B = rkActor_.GetColor().B;
				rtSData.team = rkActor_.GetTeamType();

				pkRoom->Broadcast(kCommand, sizeof(SOtherRespawnGsToCl));

				rkActor_.SetStatus(STATUS_NORMAL);
				//rkActor_.SetCurLife(rkActor_.GetMaxLife());
				OUTPUT("RESPAWN: actor: " << rkActor_.GetKey() << ", pos: (" << rkActor_.GetPosition().x << ":" << rkActor_.GetPosition().y << ", color: (" << rkActor_.GetColor().A << ":" << rkActor_.GetColor().R << ":" << rkActor_.GetColor().G << ":" << rkActor_.GetColor().B << ")");
			} else {
				if (1 == pkRoom->GetTopCount()) {
					if (isptr(pkRoom->GetLeader())) {
						if (pkRoom != pkRoom->GetLeader()->GetRoomHandler()->GetRoom()) {
							OUTPUT("critical error: unit is not in this room: ");
							g_kChannelMgr.DeleteRoom(pkRoom->GetId());
						}
					}
				}
				OUTPUT("error: join failed: " << rtRData.id);
			}
			return true;
		} else {
			OUTPUT("error: join failed: EMPTY");
			rkCommand_.SetExtra(EMPTY);
			rkActor_.Send(rkCommand_);
			return true;
		}
	} else {
		OUTPUT("[" << rkActor_.GetKey() << "] room handler is null: ");
		rkCommand_.SetExtra(FAIL);
	}
	rkActor_.Send(rkCommand_);
	rkActor_.Disconnect();
	return true;
}

bool
CMD_ROOM_MATCH(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_ROOM_MATCH: actor: " << rkActor_.GetKey());

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		CRoom* pkRoom = pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			CCommand kCommand;
			kCommand.SetOrder(ROOM_LEAVE);
			kCommand.SetExtra(DONE);

			rkActor_.Send(rkCommand_);
		}

		pkRoom = g_kChannelMgr.FindMatchRoom();
		if (isptr(pkRoom)) {
			if (pkRoom->Join(rkActor_)) {
				pkRoom->SetDoing(true);
				OUTPUT("OK: key: " << rkActor_.GetKey() << ", room id: " << pkRoom->GetId());

				SRespawnPosition* ptPosition = ((CRoomEx*)pkRoom)->GetRespawnPosition(rkActor_);
				if(isptr(ptPosition)) {
					rkActor_.SetPosition(*ptPosition);
				}

				SRespawnColor* ptColor = ((CRoomEx*)pkRoom)->GetRespawnColor(rkActor_);
				if(isptr(ptColor)) {
					rkActor_.SetColor(*ptColor);
				}

				CCommand kCommand;
				kCommand.SetOrder(OTHER_RESPAWN);
				kCommand.SetExtra(OK);

				SOtherRespawnGsToCl& rtSData = (SOtherRespawnGsToCl&)kCommand.GetData();
				rtSData.actor = rkActor_.GetKey();
				rtSData.pos.x = rkActor_.GetPosition().x;
				rtSData.pos.y = rkActor_.GetPosition().y;

				rtSData.color.A = rkActor_.GetColor().A;
				rtSData.color.R = rkActor_.GetColor().R;
				rtSData.color.G = rkActor_.GetColor().G;
				rtSData.color.B = rkActor_.GetColor().B;

				pkRoom->Broadcast(kCommand, sizeof(SOtherRespawnGsToCl));

				rkActor_.SetStatus(STATUS_NORMAL);
				//CChannelMgr::PlayerInRoom(rkActor_);
				//rkActor_.SetCurLife(rkActor_.GetMaxLife());
				OUTPUT("RESPAWN: actor: " << rkActor_.GetKey() << ", pos: (" << rkActor_.GetPosition().x << ":" << rkActor_.GetPosition().y << ", color: (" << rkActor_.GetColor().A << ":" << rkActor_.GetColor().R << ":" << rkActor_.GetColor().G << ":" << rkActor_.GetColor().B << ")");
			} else {
				if (1 == pkRoom->GetTopCount()) {
					if (isptr(pkRoom->GetLeader())) {
						if (pkRoom != pkRoom->GetLeader()->GetRoomHandler()->GetRoom()) {
							OUTPUT("critical error: player is not in this room: ");
							g_kChannelMgr.DeleteRoom(pkRoom->GetId());
						}
					}
				}
				OUTPUT("error: join failed: " << pkRoom->GetId());
			}
			return true;
		} else {
			pkRoom = g_kChannelMgr.NewRoom();
			if (isptr(pkRoom)) {
				SRoomMatchClToGs& rtRData = (SRoomMatchClToGs&)rkCommand_.GetData();
				pkRoom->SetName(rtRData.GetName());
				pkRoom->SetMaxUser(rtRData.max);
				pkRoom->SetModType((MOD_TYPE)rtRData.mod);

				if (pkRoom->Create(rkActor_)) {
					pkRoom->SetDoing(true);
					
					rkCommand_.SetOrder(ROOM_CREATE);
					rkCommand_.SetExtra(OK);
					SRoomCreateGsToCl& rtSData = (SRoomCreateGsToCl&)rkCommand_.GetData();
					rtSData.id = pkRoom->GetId();
					rtSData.SetName(pkRoom->GetName());
					rtSData.max = pkRoom->GetMaxUser();
					rtSData.mod = pkRoom->GetModType();

					rkActor_.Send(rkCommand_, sizeof(SRoomCreateGsToCl));

					OUTPUT("OK: key: " << rkActor_.GetKey() << ", name: " << rkActor_.GetName() << ", room id: " << pkRoom->GetId() << ", room max user: " << pkRoom->GetMaxUser() << ", room mod type: " << pkRoom->GetModType() << ", room name: " << pkRoom->GetName());

					SRespawnPosition* ptPosition = ((CRoomEx*)pkRoom)->GetRespawnPosition(rkActor_);
					if(isptr(ptPosition)) {
						rkActor_.SetPosition(*ptPosition);
					}

					SRespawnColor* ptColor = ((CRoomEx*)pkRoom)->GetRespawnColor(rkActor_);
					if(isptr(ptColor)) {
						rkActor_.SetColor(*ptColor);
					}

					CCommand kCommand;
					kCommand.SetOrder(OTHER_RESPAWN);
					kCommand.SetExtra(OK);

					SOtherRespawnGsToCl& rtSData2 = (SOtherRespawnGsToCl&)kCommand.GetData();
					rtSData2.actor = rkActor_.GetKey();
					rtSData2.pos.x = rkActor_.GetPosition().x;
					rtSData2.pos.y = rkActor_.GetPosition().y;

					rtSData2.color.A = rkActor_.GetColor().A;
					rtSData2.color.R = rkActor_.GetColor().R;
					rtSData2.color.G = rkActor_.GetColor().G;
					rtSData2.color.B = rkActor_.GetColor().B;

					pkRoom->Broadcast(kCommand, sizeof(SOtherRespawnGsToCl));

					rkActor_.SetStatus(STATUS_NORMAL);
					//rkActor_.SetCurLife(rkActor_.GetMaxLife());
					OUTPUT("RESPAWN: actor: " << rkActor_.GetKey() << ", pos: (" << rkActor_.GetPosition().x << ":" << rkActor_.GetPosition().y << ", color: (" << rkActor_.GetColor().A << ":" << rkActor_.GetColor().R << ":" << rkActor_.GetColor().G << ":" << rkActor_.GetColor().B << ")");
					return true;
				} else {
					OUTPUT("[" << rkActor_.GetKey() << "] room create failed: ");
				}

				rkCommand_.SetOrder(ROOM_CREATE);
				rkCommand_.SetExtra(DENY);
				g_kChannelMgr.DeleteRoom(pkRoom->GetId());
			} else {
				rkCommand_.SetOrder(ROOM_CREATE);
				rkCommand_.SetExtra(NOT_ENOUGH);
				rkActor_.Send(rkCommand_);
				return true;
			}
		}
	} else {
		OUTPUT("[" << rkActor_.GetKey() << "] room handler is null: ");
		rkCommand_.SetExtra(FAIL);
	}

	rkActor_.Send(rkCommand_);
	rkActor_.Disconnect();
	return true;
}

bool
CMD_ROOM_LEAVE(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ROOM_LEAVE: actor: " << rkActor_.GetKey());
	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		CRoom* pkRoom = pkRoomHandler->GetRoom();
		if (isptr(pkRoom)) {
			if (pkRoomHandler->InRoom()) {
				pkRoom->Leave(rkActor_);
			}

			rkCommand_.SetExtra(OK);
			rkActor_.Send(rkCommand_);

			CCommand kCommand;
			kCommand.SetOrder(ROOM_LEAVE_OTHER);
			kCommand.SetExtra(OK);

			SRoomLeaveOtherGsToCl& rtSData = (SRoomLeaveOtherGsToCl&)kCommand.GetData();
			rtSData.actor = rkActor_.GetKey();
			g_kChannelMgr.Broadcast(&rkActor_, kCommand, sizeof(SRoomLeaveOtherGsToCl));

			return true;
		} else {
			OUTPUT("[" << rkActor_.GetKey() << "] room is null: ");
			rkCommand_.SetExtra(FAIL);
		}
	} else {
		OUTPUT("[" << rkActor_.GetKey() << "] room handler is null: ");
		rkCommand_.SetExtra(FAIL);
	}

	rkActor_.Send(rkCommand_);
	rkActor_.Disconnect();
	return true;
}

bool
CMD_ROOM_LIST(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ROOM_LIST: actor: " << rkActor_.GetKey());

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		if (1 == rkCommand_.GetMission()) {
			// MEMBER LIST
			g_kChannelMgr.GetRoomMemberList(rkActor_);
			OUTPUT("OK: ROOM LIST: NONE: member: key: " << rkActor_.GetKey());
		} else {
			g_kChannelMgr.GetRoomList(rkActor_);
			OUTPUT("OK: ROOM LIST: NONE: key: " << rkActor_.GetKey());
		}
		return true;
	} else {
		OUTPUT("[" << rkActor_.GetKey() << "] room handler is null: ");
		rkCommand_.SetExtra(FAIL);
	}

	rkActor_.Send(rkCommand_);
	rkActor_.Disconnect();
	return true;
}

//장현우 구현
bool
CMD_ROOM_SYNC(CPlayer& rkActor_, CCommand& rkCommand_){
	OUTPUT("CMD_ROOM_SYNC: actor: " << rkActor_.GetKey());

	g_kChannelMgr.RoomSync(rkActor_, rkCommand_);

	return true;
}

bool
CMD_ROOM_START_PLAYING(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_ROOM_START_PLAYING: actor: " << rkActor_.GetKey());
	SRoomStartPlayingClToGs& rtRData =  (SRoomStartPlayingClToGs&)rkCommand_.GetData();
	CRoom* room;
	if (rkActor_.GetKey() == rtRData.actor) {
		room = rkActor_.GetRoomHandler()->GetRoom();
		room->SetRoomState(ROOM_STATE_PLAYING);
		rkCommand_.SetExtra(OK);
		room->Broadcast(rkCommand_, sizeof(SRoomStartPlayingClToGs));
		OUTPUT("OK: CMD_ROOM_START_PLAYING: actor: " << rkActor_.GetKey());
		CCommand kCommand;
		kCommand.SetOrder(ROOM_START_INFO);
		SRoomStartInfoGsToCl& rtSData = (SRoomStartInfoGsToCl&)kCommand.GetData();
		rtSData.room = room->GetId();
		g_kChannelMgr.Broadcast(&rkActor_, kCommand, sizeof(SRoomStartInfoGsToCl));
	} else {
		rkCommand_.SetExtra(FAIL);
		room->Broadcast(rkCommand_, sizeof(SRoomStartPlayingClToGs));
		OUTPUT("FAIL: CMD_ROOM_START_PLAYING: actor: " << rkActor_.GetKey());
	}
	return true;
}

bool
CMD_ROOM_END_PLAYING(CPlayer& rkActor_, CCommand& rkCommand_) {
	CRoomHandler* roomHandler = rkActor_.GetRoomHandler();
	if (isptr(roomHandler)) {
		CRoomEx* room = (CRoomEx*)roomHandler->GetRoom();
		if (isptr(room)) {
			g_kChannelMgr.FindRoom(room->GetId())->SetRoomState(ROOM_STATE_END);
			room->SetRoomState(ROOM_STATE_END);
			room->Broadcast(rkCommand_, sizeof(SRoomEndPlaying));
			OUTPUT("OK: CMD_END_PLAYING: actor: " << rkActor_.GetKey());
			CCommand kCommand;
			kCommand.SetOrder(ROOM_END_INFO);
			SRoomEndInfoGsToCl& rtSData = (SRoomEndInfoGsToCl&)kCommand.GetData();
			rtSData.room = room->GetId();
			g_kChannelMgr.Broadcast(&rkActor_, kCommand, sizeof(SRoomEndInfoGsToCl));
		}
	}
	return true;
}

void
InitializeRoomCommand() {
	SET_COMMAND(ROOM_CREATE);
	SET_COMMAND(ROOM_JOIN);
	SET_COMMAND(ROOM_MATCH);
	SET_COMMAND(ROOM_LEAVE);
	SET_COMMAND(ROOM_LIST);
	SET_COMMAND(ROOM_SYNC);
	SET_COMMAND(ROOM_START_PLAYING);
	SET_COMMAND(ROOM_END_PLAYING);
}
