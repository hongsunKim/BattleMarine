/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"
#include "CheatCode.h"

bool
CMD_USER_STATUS(CPlayer& rkActor_, CCommand& rkCommand_) {
	OUTPUT("CMD_USER_STATUS: actor: " << rkActor_.GetKey());

	return true;
}

//장현우
bool
CMD_USER_CHAT(CPlayer& rkActor_, CCommand& rkCommand_) {
	CCommand kCommand;
	kCommand.SetOrder(USER_CHAT);
	kCommand.SetExtra(rkCommand_.GetExtra());
	
	SUserChatClToGs& Actor_Chat = (SUserChatClToGs&)rkCommand_.GetData();
	SUserChatGsToCl& rtData = (SUserChatGsToCl&)kCommand.GetData();
	
	rtData = Actor_Chat;

	if (rtData.chat[0] == '/')
	{
		char* temp;
		strtok_s(rtData.chat, " ", &temp);

		if (strcmp(rtData.chat, "/Warp") == 0)
		{
			if (temp[0] == 'p')
			{
				char* Player_temp;

				strtok_s(temp, " ", &Player_temp);
				strtok_s(Player_temp, " ", &temp);

				CPlayer& Actor_ = *g_kPlayerMgr.Find(atoi(Player_temp));
				char* x = temp;
				char* y;
				strtok_s(x, ",", &y);

				CCheatCode::Warp(Actor_, atoi(x), atoi(y));
				return true;
			}
			char* x = temp;
			char* y;
			strtok_s(x, ",", &y);

			CCheatCode::Warp(rkActor_, atoi(x), atoi(y));
		}
		else if (strcmp(rtData.chat, "/Kill") == 0)
		{
			CCheatCode::Kill(rkActor_, temp);
		}

		return true;
	}
			
	rkActor_.Send(kCommand, sizeof(SUserChatGsToCl));

	kCommand.SetOrder(OTHER_CHAT);
	
	if (kCommand.GetExtra() == LOBBY)
	{
		g_kChannelMgr.Broadcast(&rkActor_, kCommand, sizeof(SUserChatGsToCl));
	}
	else if (kCommand.GetExtra() == ROOM)
	{
		CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
		if (isptr(pkRoomHandler)) {
			CRoom* pkRoom = pkRoomHandler->GetRoom();
			if (isptr(pkRoom)) {
				if (kCommand.GetExtra() == ROOM)
				{
					pkRoom->Broadcast(kCommand, sizeof(SUserChatGsToCl), &rkActor_);
				}
			}
		}
	}

	OUTPUT("CMD_USER_CHAT: " << Actor_Chat.chat<< ", actor: " << rkActor_.GetKey());
	return true;
}

bool
CMD_USER_ATTACK(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_USER_ATTACK: actor: " << rkActor_.GetKey());

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if(isptr(pkRoomHandler)) {
		CRoom* pkRoom = pkRoomHandler->GetRoom();
		if(isptr(pkRoom)) {
			if(NONE == rkCommand_.GetExtra()) {
				SUserAttackClToGs& rtRData = (SUserAttackClToGs&)rkCommand_.GetData();

				CCommand kCommand;
				kCommand.SetOrder(USER_ATTACK);
				kCommand.SetExtra(OK);

				SUserAttackGsToCl& rtSDataActor = (SUserAttackGsToCl&)kCommand.GetData();
				rtSDataActor.target = rtRData.target;
				rtSDataActor.mapIdx = rtRData.mapIdx;

				rkActor_.Send(kCommand, sizeof(SUserAttackGsToCl));

				kCommand.SetOrder(OTHER_ATTACK);
				kCommand.SetExtra(OK);

				SOtherAttackGsToCl& rtSData = (SOtherAttackGsToCl&)kCommand.GetData();
				rtSData.actor = rkActor_.GetKey();
				rtSData.target = rtRData.target;
				rtSData.mapIdx = rtRData.mapIdx;

				pkRoom->Broadcast(kCommand, sizeof(SOtherAttackGsToCl), &rkActor_);

				OUTPUT("CMD_USER_ATTACK: actor: " << rkActor_.GetKey() << ", pos: (" << rtSData.mapIdx.x << ":" << rtSData.mapIdx.y << ")");
				return true;
			}
		}
	}
	return true;
}

bool
CMD_USER_MOVE(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_USER_MOVE: actor: " << rkActor_.GetKey());

	CRoomHandler* pkRoomHandler = rkActor_.GetRoomHandler();
	if(isptr(pkRoomHandler)) {
		CRoom* pkRoom = pkRoomHandler->GetRoom();
		if(isptr(pkRoom)) {
			if(START == rkCommand_.GetExtra()) {
				SUserMoveClToGs& rtRData = (SUserMoveClToGs&)rkCommand_.GetData();
				rkActor_.SetPosition(rtRData.pos);
				rkActor_.SetDirection((DIRECTION_TYPE)rtRData.dir);

				CCommand kCommand;
				kCommand.SetOrder(OTHER_MOVE);
				kCommand.SetExtra(START);

				SOtherMoveStartGsToCl& rtSData = (SOtherMoveStartGsToCl&)kCommand.GetData();
				rtSData.actor = rkActor_.GetKey();
				rtSData.pos.x = rkActor_.GetPosition().x;
				rtSData.pos.y = rkActor_.GetPosition().y;
				rtSData.dir = rkActor_.GetDirection();

				pkRoom->Broadcast(kCommand, sizeof(SOtherMoveStartGsToCl), &rkActor_);

				OUTPUT("CMD_USER_MOVE: START: actor: " << rkActor_.GetKey() << ", pos: (" << rkActor_.GetPosition().x << ":" << rkActor_.GetPosition().y << "), dir: " << rkActor_.GetDirection());
				return true;
			} else if(STOP == rkCommand_.GetExtra()) {
				CCommand kCommand;
				kCommand.SetOrder(OTHER_MOVE);
				kCommand.SetExtra(STOP);

				SOtherMoveStopGsToCl& rtSData = (SOtherMoveStopGsToCl&)kCommand.GetData();
				rtSData.actor = rkActor_.GetKey();

				pkRoom->Broadcast(kCommand, sizeof(SOtherMoveStopGsToCl), &rkActor_);

				OUTPUT("CMD_USER_MOVE: STOP: actor: " << rkActor_.GetKey());
				return true;
			}
		}
	}
	return true;
}

bool
CMD_USER_RESPAWN(CPlayer& rkActor_, CCommand& rkCommand_) {
	//rkActor_.SetMaxLife(iPLAYER_MAX_LIFE);
	//rkActor_.SetCurLife(iPLAYER_MAX_LIFE);

	CCommand kCommand;
	kCommand.SetOrder(OTHER_RESPAWN);
	kCommand.SetExtra(OK);
	SOtherRespawnGsToCl& rtSData = (SOtherRespawnGsToCl&)kCommand.GetData();
	rtSData.actor = rkActor_.GetKey();
	rtSData.color.A = rkActor_.GetColor().A;
	rtSData.color.R = rkActor_.GetColor().R;
	rtSData.color.G = rkActor_.GetColor().G;
	rtSData.color.B = rkActor_.GetColor().B;
	rtSData.pos.x = rkActor_.GetPosition().x;
	rtSData.pos.y = rkActor_.GetPosition().y;
	rtSData.team = rkActor_.GetTeamType();

	CRoomHandler* kRoomHandler = rkActor_.GetRoomHandler();

	if (isptr(kRoomHandler)) {
		CRoomEx* kRoom = (CRoomEx*)kRoomHandler->GetRoom();
		if (isptr(kRoom)) {
			kRoom->Broadcast(kCommand, sizeof(SOtherRespawnGsToCl), &rkActor_);
		}
	}

	return true;
}

//장현우, 이주봉 스팀팩 구현
bool
CMD_USER_STEAMPACK(CPlayer& rkActor_, CCommand& rkCommand_) {
	CRoomHandler* kRoomHandler = rkActor_.GetRoomHandler();
	if (isptr(kRoomHandler)) {
		CRoomEx* kRoom = (CRoomEx*)kRoomHandler->GetRoom();
		if (isptr(kRoom)) {
			CCommand kCommand;
			if (rkCommand_.GetExtra() == START)
			{
				SOtherSteamPackGsToCl& rtSData = (SOtherSteamPackGsToCl&)kCommand.GetData();
				rtSData.actor = rkActor_.GetKey();

				kCommand.SetOrder(USER_STEAMPACK);
				kCommand.SetExtra(START);
				
				rkActor_.Damaged(iPLAYER_STEAMPACK_POWER);
				if (rkActor_.GetCurLife() <= 0)
				{
					rkActor_.SetCurLife(1);
				}
				rkActor_.SetISSteamPackTime(10000);
				rkActor_.SetISSteamPack(true);
				rkActor_.Send(kCommand, sizeof(SUserSteamPackGsToCl));

				kCommand.SetOrder(OTHER_STEAMPACK);
				kCommand.SetExtra(NONE);
				kRoom->Broadcast(kCommand, sizeof(SOtherSteamPackGsToCl), &rkActor_);
			}
		}
	}
	return true;
}

bool
CMD_USER_INFESTED(CPlayer& rkActor_, CCommand& rkCommand_) {
	return 1;
}

bool
CMD_USER_ZOMBIE_INFEST(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_USER_ZOMBIE_INFEST: actor: " << rkActor_.GetKey());

	CRoomHandler* roomHandler0 = rkActor_.GetRoomHandler();
	
	if (roomHandler0)
	{
		CRoom* room0 = roomHandler0->GetRoom();
		
		if (room0)
		{
			if (NONE == rkCommand_.GetExtra())
			{
				SUserInfestClToGs& receivedDatum0 = (SUserInfestClToGs&)rkCommand_.GetData();

				CCommand command0;
				command0.SetOrder(USER_ZOMBIE_INFEST);
				command0.SetExtra(OK);

				SUserInfestGsToCl& sendingDatumActor0 = (SUserInfestGsToCl&)command0.GetData();

				sendingDatumActor0.target = receivedDatum0.target;
				sendingDatumActor0.mapIdx = receivedDatum0.mapIdx;

				rkActor_.Send(command0, sizeof(SUserInfestGsToCl));

				command0.SetOrder(OTHER_ZOMBIE_INFEST);
				command0.SetExtra(OK);

				SOtherInfestGsToCl& sendingDatum0 = (SOtherInfestGsToCl&)command0.GetData();

				sendingDatum0.actor = rkActor_.GetKey();
				sendingDatum0.target = receivedDatum0.target;
				sendingDatum0.mapIdx = receivedDatum0.mapIdx;

				room0->Broadcast(command0, sizeof(SOtherInfestGsToCl), &rkActor_);

				OUTPUT("CMD_USER_ZOMBIE_INFEST: actor: " << rkActor_.GetKey() << ", pos: (" << sendingDatum0.mapIdx.x << ":" << sendingDatum0.mapIdx.y << ")");
				
				return 1;
			}
		}
	}

	return 1;
}

bool
CMD_USER_ZOMBIE_MOVE(CPlayer& rkActor_, CCommand& rkCommand_) {
	//OUTPUT("CMD_USER_ZOMBIE_MOVE: actor: " << rkActor_.GetKey());

	CRoomHandler* roomHandler0 = rkActor_.GetRoomHandler();
	
	if (roomHandler0)
	{
		CRoom* room0 = roomHandler0->GetRoom();
		
		if (room0)
		{
			if (START == rkCommand_.GetExtra())
			{
				SUserMoveClToGs& receivedDatum0 = (SUserMoveClToGs&)rkCommand_.GetData();
				rkActor_.SetPosition(receivedDatum0.pos);
				rkActor_.SetDirection((DIRECTION_TYPE)receivedDatum0.dir);

				CCommand command0;

				command0.SetOrder(OTHER_ZOMBIE_MOVE);
				command0.SetExtra(START);

				SOtherMoveStartGsToCl& sendingDatum0 = (SOtherMoveStartGsToCl&)command0.GetData();

				sendingDatum0.actor = rkActor_.GetKey();
				sendingDatum0.pos = rkActor_.GetPosition();
				sendingDatum0.dir = rkActor_.GetDirection();
				room0->Broadcast(command0, sizeof(SOtherMoveStartGsToCl), &rkActor_);

				OUTPUT("CMD_USER_ZOMBIE_MOVE: START: actor: " << rkActor_.GetKey() << ", pos: (" << rkActor_.GetPosition().x << ":" << rkActor_.GetPosition().y << "), dir: " << rkActor_.GetDirection());
				
				return 1;
			}
			else if (STOP == rkCommand_.GetExtra())
			{
				CCommand command0;

				command0.SetOrder(OTHER_ZOMBIE_MOVE);
				command0.SetExtra(STOP);

				SOtherMoveStopGsToCl& sendingDatum0 = (SOtherMoveStopGsToCl&)command0.GetData();

				sendingDatum0.actor = rkActor_.GetKey();
				room0->Broadcast(command0, sizeof(SOtherMoveStopGsToCl), &rkActor_);

				OUTPUT("CMD_USER_ZOMBIE_MOVE: STOP: actor: " << rkActor_.GetKey());
				
				return 1;
			}
		}
	}
	
	return 1;
}

void
InitializeUserCommand() {
	SET_COMMAND(USER_STATUS);
	SET_COMMAND(USER_CHAT);
	SET_COMMAND(USER_ATTACK);
	SET_COMMAND(USER_MOVE);
	SET_COMMAND(USER_RESPAWN);
	SET_COMMAND(USER_STEAMPACK);
	SET_COMMAND(USER_INFESTED);
	SET_COMMAND(USER_ZOMBIE_INFEST);
	SET_COMMAND(USER_ZOMBIE_MOVE);
}
