/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_OTHER_STATUS(CCommand& rkCommand_) {
	CONSOLE("CMD_OTHER_STATUS: actor: " << g_kMainPlayer->GetKey());

	return true;
}

bool
CMD_OTHER_CHAT(CCommand& rkCommand_) {
	//장현우
	SUserChatGsToCl& rtRData = (SUserChatGsToCl&)rkCommand_.GetData();
	USER_CHAT_OUT(rtRData, rkCommand_.GetExtra());
	CONSOLE("CMD_OTHER_CHAT: actor: " << g_kMainPlayer->GetKey());
	return true;
}

bool
CMD_OTHER_ATTACK(CCommand& rkCommand_) {
	//CONSOLE("CMD_OTHER_ATTACK: actor: " << g_kMainPlayer->GetKey());

	if(OK == rkCommand_.GetExtra()) {
		SOtherAttackGsToCl& rtRData = (SOtherAttackGsToCl&)rkCommand_.GetData();
		CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.actor);
		if(isptr(pkPlayer)) {
			pkPlayer->SetState(STATE_ATTACK);
			if (NULL != rtRData.target) {
				if (rtRData.target == g_kMainPlayer->GetKey()) {
					g_kMainPlayer->Damaged(pkPlayer->GetPower());
					pkPlayer->SetFire(true);
					POINT point;
					point.x = g_kMainPlayer->GetMapIdx().x;
					point.y = g_kMainPlayer->GetMapIdx().y;
					pkPlayer->SetTargetMapIdx(point);
					if (0 >= g_kMainPlayer->GetCurLife()) {
						if (STATUS_NORMAL == g_kMainPlayer->GetStatus()) {
							g_kMainRoom.IncreaseTeamPoint(pkPlayer->GetTeamType());
						}
						g_kMainPlayer->SetStatus(STATUS_DYING);
						g_kMainPlayer->SetDeathStartTick(g_kTick.GetTick());

						//장미경
						CCommand kCommand;
						kCommand.SetOrder(ITEM_DROP);

						SItemDropClToGs& rtSData = (SItemDropClToGs&)kCommand.GetData();
						rtSData.owner = rtRData.actor;
						rtSData.victim = rtRData.target;
						g_kMainPlayer->Send(kCommand, sizeof(SItemDropClToGs));

						CONSOLE("CMD_ITEM_DROP: owner: " << rtRData.actor);
					}
				} else {
					CPlayerEx* pkTarget = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.target);
					if (isptr(pkTarget)) {
						pkTarget->Damaged(pkPlayer->GetPower());
						pkPlayer->SetFire(true);
						POINT point;
						point.x = pkTarget->GetMapIdx().x;
						point.y = pkTarget->GetMapIdx().y;
						pkPlayer->SetTargetMapIdx(point);
						if (0 >= pkTarget->GetCurLife()) {
							if (STATUS_NORMAL == pkTarget->GetStatus()) {
								g_kMainRoom.IncreaseTeamPoint(pkPlayer->GetTeamType());
							}
							pkTarget->SetStatus(STATUS_DYING);
						}
					}
				}
			}
			else {
				pkPlayer->SetFire(true);
				POINT point;
				point.x = rtRData.mapIdx.x;
				point.y = rtRData.mapIdx.y;
				pkPlayer->SetTargetMapIdx(point);
			}
			//rtRData.pos.x;
			//rtRData.pos.y;

			CONSOLE("CMD_OTHER_ATTACK: actor: " << g_kMainPlayer->GetKey() << ", pos: (" << rtRData.mapIdx.x << ":" << rtRData.mapIdx.y << ")");
		}
	}
	return true;
}

bool
CMD_OTHER_MOVE(CCommand& rkCommand_) {
	//CONSOLE("CMD_OTHER_MOVE: actor: " << g_kMainPlayer->GetKey());

	if(START == rkCommand_.GetExtra()) {
		SOtherMoveStartGsToCl& rtRData = (SOtherMoveStartGsToCl&)rkCommand_.GetData();
		CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.actor);
		if(isptr(pkPlayer)) {
			pkPlayer->SetPosition(rtRData.pos);
			pkPlayer->SetDirection((DIRECTION_TYPE)rtRData.dir);
			
			//if (STATE_INFESTED == pkPlayer->GetState()) pkPlayer->SetZombieState(ZOMBIE_STATE_MOVE);
			//else pkPlayer->SetState(STATE_MOVE);

			pkPlayer->SetState(STATE_MOVE);

			CONSOLE("CMD_OTHER_MOVE: START: actor: " << g_kMainPlayer->GetKey() << ", pos: (" << pkPlayer->GetPosition().x << ":" << pkPlayer->GetPosition().y << "), dir: " << pkPlayer->GetDirection());
		}
	} else if(STOP == rkCommand_.GetExtra()) {
		SOtherMoveStopGsToCl& rtRData = (SOtherMoveStopGsToCl&)rkCommand_.GetData();
		CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.actor);
		if(isptr(pkPlayer)) {

			//if (STATE_INFESTED == pkPlayer->GetState()) pkPlayer->SetZombieState(ZOMBIE_STATE_IDLE);
			//else pkPlayer->SetState(STATE_IDLE);

			pkPlayer->SetState(STATE_IDLE);

			CONSOLE("CMD_OTHER_MOVE: STOP: actor: " << g_kMainPlayer->GetKey());
		}
	}
	return true;
}

bool
CMD_OTHER_RESPAWN(CCommand& rkCommand_) {
	//CONSOLE("CMD_OTHER_RESPAWN: actor: " << g_kMainPlayer->GetKey());

	if(OK == rkCommand_.GetExtra()) {
		SOtherRespawnGsToCl& rtRData = (SOtherRespawnGsToCl&)rkCommand_.GetData();
		CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.actor);
		if(isptr(pkPlayer)) {
			pkPlayer->SetPosition(rtRData.pos);
			pkPlayer->SetColor(rtRData.color);
			pkPlayer->SetStatus(STATUS_NORMAL);
			pkPlayer->SetState(STATE_IDLE);		///< 동기화 필요시 서버에 저장 하도록 추가 (이후 전송)
			pkPlayer->SetTeamType(rtRData.team);

			pkPlayer->SetCurLife(pkPlayer->GetMaxLife());

			CONSOLE("CMD_OTHER_RESPAWN: actor: " << g_kMainPlayer->GetKey() << ", pos: (" << pkPlayer->GetPosX() << ":" << pkPlayer->GetPosY() << "), color: (" << pkPlayer->GetColor().A << ":" << pkPlayer->GetColor().R << ":" << pkPlayer->GetColor().G << ":" << pkPlayer->GetColor().B << ")");
		}
	}
	return true;
}

//장현우, 이주봉 스팀팩 구현
bool
CMD_OTHER_STEAMPACK(CCommand& rkCommand_) {

	SOtherSteamPackGsToCl& rtRData = (SOtherSteamPackGsToCl&)rkCommand_.GetData();
	CPlayerEx* pkPlayer = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.actor);
	if (isptr(pkPlayer))
	{
		pkPlayer->Damaged(iPLAYER_STEAMPACK_POWER);
		if (pkPlayer->GetCurLife() == 0)
		{
			pkPlayer->SetCurLife(1);
		}
	}
	return true;
}

bool
CMD_OTHER_INFESTED(CCommand& rkCommand_)
{
	return 1;
}

bool
CMD_OTHER_ZOMBIE_INFEST(CCommand& rkCommand_)
{
	//CONSOLE("CMD_OTHER_ZOMBIE_INFEST: actor: " << g_kMainPlayer->GetKey());

	if (OK == rkCommand_.GetExtra())
	{
		SOtherInfestGsToCl& receivedDatum0 = (SOtherInfestGsToCl&)rkCommand_.GetData();
		CPlayerEx* playerEx0 = (CPlayerEx*)g_kPlayerMgr.GetPlayer(receivedDatum0.actor);

		if (playerEx0)
		{
			playerEx0->SetZombieState(ZOMBIE_STATE_INFEST);
			
			if (receivedDatum0.target)
			{
				if (receivedDatum0.target == g_kMainPlayer->GetKey())
				{
					g_kMainPlayer->SetTeamType(TEAM_GREEN);
					((CPlayerEx*)g_kMainPlayer)->SetState(STATE_INFESTED);
				}
				else {
					CPlayerEx* target0 = (CPlayerEx*)g_kPlayerMgr.GetPlayer(receivedDatum0.target);
					
					if (target0)
					{
						target0->SetTeamType(TEAM_GREEN);
						target0->SetState(STATE_INFESTED);
					}
				}
			}

			CONSOLE("CMD_OTHER_INFEST: actor: " << g_kMainPlayer->GetKey() << ", pos: (" << receivedDatum0.mapIdx.x << ":" << receivedDatum0.mapIdx.y << ")");
		}
	}

	return 1;
}

bool
CMD_OTHER_ZOMBIE_MOVE(CCommand& rkCommand_)
{
	if (START == rkCommand_.GetExtra())
	{
		SOtherMoveStartGsToCl& receivedDatum0 = (SOtherMoveStartGsToCl&)rkCommand_.GetData();
		CPlayerEx* player0 = (CPlayerEx*)g_kPlayerMgr.GetPlayer(receivedDatum0.actor);
		
		if (player0)
		{
			player0->SetPosition(receivedDatum0.pos);
			player0->SetDirection((DIRECTION_TYPE)receivedDatum0.dir);
			
			if(STATE_INFESTED != player0->GetState()) player0->SetState(STATE_INFESTED);
			
			player0->SetZombieState(ZOMBIE_STATE_MOVE);

			CONSOLE("CMD_OTHER_ZOMBIE_MOVE: START: actor: " << g_kMainPlayer->GetKey() << ", pos: (" << player0->GetPosition().x << ":" << player0->GetPosition().y << "), dir: " << player0->GetDirection());
		}
	}
	else if (STOP == rkCommand_.GetExtra())
	{
		SOtherMoveStopGsToCl& receivedDatum0 = (SOtherMoveStopGsToCl&)rkCommand_.GetData();
		CPlayerEx* player0 = (CPlayerEx*)g_kPlayerMgr.GetPlayer(receivedDatum0.actor);
		
		if (player0)
		{
			if (STATE_INFESTED != player0->GetState()) player0->SetState(STATE_INFESTED);
				
			player0->SetZombieState(ZOMBIE_STATE_IDLE);

			CONSOLE("CMD_OTHER_ZOMBIE_MOVE: STOP: actor: " << g_kMainPlayer->GetKey());
		}
	}

	return 1;
}

void
InitializeOtherCommand() {
	SET_COMMAND(OTHER_STATUS);
	SET_COMMAND(OTHER_CHAT);
	SET_COMMAND(OTHER_ATTACK);
	SET_COMMAND(OTHER_MOVE);
	SET_COMMAND(OTHER_RESPAWN);
	SET_COMMAND(OTHER_STEAMPACK);
	SET_COMMAND(OTHER_INFESTED);
	SET_COMMAND(OTHER_ZOMBIE_INFEST);
	SET_COMMAND(OTHER_ZOMBIE_MOVE);
}
