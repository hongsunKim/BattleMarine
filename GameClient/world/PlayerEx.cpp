/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "PlayerEx.h"
#include "../CommonHeader.h"

extern Color *Red_Color;

extern Bitmap* g_pkCollisionMap;

CPlayerEx::CPlayerEx() : m_eState(STATE_IDLE), m_eZombieState(ZOMBIE_STATE_IDLE), m_tkStopTick(0), m_pkAnimator(NULL), m_bFire(false), g_Color(NULL),
						bCheck(false), m_wType(WEAPON_RIFLE), Lazor_count(5), m_attCheck(false), m_pkInventory(NULL) {

	m_tTarget = { 0,0 };
	ck_Position = SPosition();
	if(false == isptr(m_pkRoomHandler)) {
		m_pkRoomHandler = new CRoomHandler(*this);
	}

	if(false == isptr(m_pkAnimator)) {
		m_pkAnimator = new CAnimator(*this);
		m_pkAnimator->Initialize();
	}

	if (false == isptr(g_Color))
	{
		g_Color = new Color;
	}

	if (false == isptr(m_pkInventory)) {
		m_pkInventory = new CInventory();
	}

}

CPlayerEx::~CPlayerEx() {
	if(isptr(m_pkRoomHandler)) {
		SAFE_DELETE(m_pkRoomHandler);
	}

	if(isptr(m_pkAnimator)) {
		SAFE_DELETE_RELEASE(m_pkAnimator);
	}

	if (isptr(g_Color)) {
		SAFE_DELETE(g_Color);
	}

	if (isptr(m_pkInventory)) {
		SAFE_DELETE(m_pkInventory);
	}
}

//void
//CPlayerEx::Create() {
//
//}

void
CPlayerEx::Clear() {
	CPlayer::Clear();
}

void
CPlayerEx::Move() {
	SetState(STATE_MOVE);
	ck_Position = m_tPosition;
	if (m_bSteamPack)
	{
		if (DIRECTION_UP == GetDirection()) {
			ck_Position.y += iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_RIGHT_UP == GetDirection()) {
			ck_Position.x -= iPLAYER_MOVE_DISTANCE * 2;
			ck_Position.y += iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_RIGHT == GetDirection()) {
			ck_Position.x -= iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_RIGHT_DOWN == GetDirection()) {
			ck_Position.x -= iPLAYER_MOVE_DISTANCE * 2;
			ck_Position.y -= iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_DOWN == GetDirection()) {
			ck_Position.y -= iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_LEFT_DOWN == GetDirection()) {
			ck_Position.x += iPLAYER_MOVE_DISTANCE * 2;
			ck_Position.y -= iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_LEFT == GetDirection()) {
			ck_Position.x += iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
		else if (DIRECTION_LEFT_UP == GetDirection()) {
			ck_Position.x += iPLAYER_MOVE_DISTANCE * 2;
			ck_Position.y += iPLAYER_MOVE_DISTANCE * 2;
			//bCheck = true;
		}
	}
	else
	{
		if (DIRECTION_UP == GetDirection()) {
			ck_Position.y += iPLAYER_MOVE_DISTANCE;
			//bCheck = true;
		}
		else if (DIRECTION_RIGHT_UP == GetDirection()) {
			ck_Position.x -= iPLAYER_MOVE_DISTANCE;
			ck_Position.y += iPLAYER_MOVE_DISTANCE;
			//bCheck = true;
		}
		else if (DIRECTION_RIGHT == GetDirection()) {
			ck_Position.x -= iPLAYER_MOVE_DISTANCE;
			//bCheck = true;
		}
		else if (DIRECTION_RIGHT_DOWN == GetDirection()) {
			ck_Position.x -= iPLAYER_MOVE_DISTANCE;
			ck_Position.y -= iPLAYER_MOVE_DISTANCE;
			//bCheck = true;
		}
		else if (DIRECTION_DOWN == GetDirection()) {
			ck_Position.y -= iPLAYER_MOVE_DISTANCE;
			//bCheck = true;
		}
		else if (DIRECTION_LEFT_DOWN == GetDirection()) {
			ck_Position.x += iPLAYER_MOVE_DISTANCE;
			ck_Position.y -= iPLAYER_MOVE_DISTANCE;
			//bCheck = true;
		}
		else if (DIRECTION_LEFT == GetDirection()) {
			ck_Position.x += iPLAYER_MOVE_DISTANCE;

		}
		else if (DIRECTION_LEFT_UP == GetDirection()) {
			ck_Position.x += iPLAYER_MOVE_DISTANCE;
			ck_Position.y += iPLAYER_MOVE_DISTANCE;

		}
	}

	if (ck_Position.x != m_tPosition.x || ck_Position.y != m_tPosition.y)
	{
		g_pkCollisionMap->GetPixel(-ck_Position.x, -ck_Position.y, g_Color);
		if (g_Color->GetValue() == Red_Color->GetValue())
		{
			m_tPosition = ck_Position;
			SetPosition(m_tPosition.x, m_tPosition.y);
			bCheck = true;
		}
	}


	if (bCheck) {
		CCommand kCommand;
		kCommand.SetOrder(USER_MOVE);
		kCommand.SetExtra(START);

		SUserMoveClToGs& rtSData = (SUserMoveClToGs&)kCommand.GetData();
		rtSData.pos.x = GetPosX();
		rtSData.pos.y = GetPosY();
		rtSData.dir = GetDirection();

		Send(kCommand, sizeof(SUserMoveClToGs));
		bCheck = false;
	}
}

void
CPlayerEx::Stop() {
	m_tkStopTick = g_kTick.GetTick();
	m_attCheck = false;
	Lazor_count = 5;
}

void
CPlayerEx::Attack() {
	SetState(STATE_ATTACK);

	CCommand kCommand;
	kCommand.SetOrder(USER_ATTACK);
	kCommand.SetExtra(NONE);

	SUserAttackClToGs& rtSData = (SUserAttackClToGs&)kCommand.GetData();
	rtSData.target = NULL;

	if (STATUS_DYING == GetStatus()) {
		return;
	}

	switch (m_wType)
	{
	case WEAPON_RIFLE:
		switch (GetDirection())
		{
		case DIRECTION_DOWN:
			rtSData.mapIdx.x = GetMapIdxX();
			rtSData.mapIdx.y = GetMapIdxY() + 5;
			break;
		case DIRECTION_LEFT:
			rtSData.mapIdx.x = GetMapIdxX() - 5;
			rtSData.mapIdx.y = GetMapIdxY();
			break;
		case DIRECTION_LEFT_DOWN:
			rtSData.mapIdx.x = GetMapIdxX() - 5;
			rtSData.mapIdx.y = GetMapIdxY() + 5;
			break;
		case DIRECTION_LEFT_UP:
			rtSData.mapIdx.x = GetMapIdxX() - 5;
			rtSData.mapIdx.y = GetMapIdxY() - 5;
			break;
		case DIRECTION_RIGHT:
			rtSData.mapIdx.x = GetMapIdxX() + 5;
			rtSData.mapIdx.y = GetMapIdxY();
			break;
		case DIRECTION_RIGHT_DOWN:
			rtSData.mapIdx.x = GetMapIdxX() + 5;
			rtSData.mapIdx.y = GetMapIdxY() + 5;
			break;
		case DIRECTION_RIGHT_UP:
			rtSData.mapIdx.x = GetMapIdxX() + 5;
			rtSData.mapIdx.y = GetMapIdxY() - 5;
			break;
		case DIRECTION_UP:
			rtSData.mapIdx.x = GetMapIdxX();
			rtSData.mapIdx.y = GetMapIdxY() - 5;
			break;
		}
		break;
	case WEAPON_LAZOR:
		switch (GetDirection())
		{
		case DIRECTION_DOWN:
			rtSData.mapIdx.x = GetMapIdxX();
			rtSData.mapIdx.y = GetMapIdxY() + (Lazor_count);
			break;
		case DIRECTION_LEFT:
			rtSData.mapIdx.x = GetMapIdxX() - (Lazor_count);
			rtSData.mapIdx.y = GetMapIdxY();
			break;
		case DIRECTION_LEFT_DOWN:
			rtSData.mapIdx.x = GetMapIdxX() - (Lazor_count);
			rtSData.mapIdx.y = GetMapIdxY() + (Lazor_count);
			break;
		case DIRECTION_LEFT_UP:
			rtSData.mapIdx.x = GetMapIdxX() - (Lazor_count);
			rtSData.mapIdx.y = GetMapIdxY() - (Lazor_count);
			break;
		case DIRECTION_RIGHT:
			rtSData.mapIdx.x = GetMapIdxX() + (Lazor_count);
			rtSData.mapIdx.y = GetMapIdxY();
			break;
		case DIRECTION_RIGHT_DOWN:
			rtSData.mapIdx.x = GetMapIdxX() + (Lazor_count);
			rtSData.mapIdx.y = GetMapIdxY() + (Lazor_count);
			break;
		case DIRECTION_RIGHT_UP:
			rtSData.mapIdx.x = GetMapIdxX() + (Lazor_count);
			rtSData.mapIdx.y = GetMapIdxY() - (Lazor_count);
			break;
		case DIRECTION_UP:
			rtSData.mapIdx.x = GetMapIdxX();
			rtSData.mapIdx.y = GetMapIdxY() - (Lazor_count);
			break;
		}
		break;
	}

	size_t size = g_kMainRoom.GetTopCount();
	for (size_t i = 0; i < size; ++i) {
		CPlayerEx* kPlayer = (CPlayerEx*)g_kMainRoom.GetMember(i);
		if (isptr(kPlayer))
		{
			if (kPlayer->GetKey() == this->GetKey()) {
				continue;
			}
			if (STATUS_DYING == kPlayer->GetStatus()) {
				continue;
			}
			if (m_wType == WEAPON_RIFLE)
			{
				switch (GetDirection())
				{
				case DIRECTION_DOWN:
					if (GetMapIdxX() == kPlayer->GetMapIdxX()) {
						if (GetMapIdxY() <= kPlayer->GetMapIdxY() && kPlayer->GetMapIdxY() <= GetMapIdxY() + 5) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.y > kPlayer->GetMapIdxY()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_LEFT:
					if (GetMapIdxY() == kPlayer->GetMapIdxY()) {
						if (GetMapIdxX() - 5 <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_LEFT_DOWN:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == -(GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() - 5 <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_LEFT_UP:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == (GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() - 5 <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_RIGHT:
					if (GetMapIdxY() == kPlayer->GetMapIdxY()) {
						if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + 5) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_RIGHT_DOWN:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == (GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + 5) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_RIGHT_UP:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == -(GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + 5) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_UP:
					if (GetMapIdxX() == kPlayer->GetMapIdxX()) {
						if (GetMapIdxY() - 5 <= kPlayer->GetMapIdxY() && kPlayer->GetMapIdxY() <= GetMapIdxY()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.y < kPlayer->GetMapIdxY()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				}
			}
			else
			{
				switch (GetDirection())
				{
				case DIRECTION_DOWN:
					if (GetMapIdxX() == kPlayer->GetMapIdxX()) {
						if (GetMapIdxY() <= kPlayer->GetMapIdxY() && kPlayer->GetMapIdxY() <= GetMapIdxY() + (Lazor_count)) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.y > kPlayer->GetMapIdxY()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_LEFT:
					if (GetMapIdxY() == kPlayer->GetMapIdxY()) {
						if (GetMapIdxX() - (Lazor_count) <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_LEFT_DOWN:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == (GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() - (Lazor_count) <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_LEFT_UP:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == -(GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() - (Lazor_count) <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_RIGHT:
					if (GetMapIdxY() == kPlayer->GetMapIdxY()) {
						if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + (Lazor_count)) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_RIGHT_DOWN:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == -(GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + (Lazor_count)) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_RIGHT_UP:
					if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == (GetMapIdxX() - kPlayer->GetMapIdxX())) {
						if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + (Lazor_count)) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				case DIRECTION_UP:
					if (GetMapIdxX() == kPlayer->GetMapIdxX()) {
						if (GetMapIdxY() - (Lazor_count) <= kPlayer->GetMapIdxY() && kPlayer->GetMapIdxY() <= GetMapIdxY()) {
							if (GetTeamType() != TEAM_NONE && GetTeamType() == kPlayer->GetTeamType())
								continue;
							if (rtSData.target) {
								if (rtSData.mapIdx.y < kPlayer->GetMapIdxY()) {
									rtSData.target = kPlayer->GetKey();
									rtSData.mapIdx.x = kPlayer->GetMapIdxX();
									rtSData.mapIdx.y = kPlayer->GetMapIdxY();
								}
							}
							else {
								rtSData.target = kPlayer->GetKey();
								rtSData.mapIdx.x = kPlayer->GetMapIdxX();
								rtSData.mapIdx.y = kPlayer->GetMapIdxY();
							}
						}
					}
					break;
				}
			}
			/*switch (GetDirection())
			{
			case DIRECTION_DOWN:
			if (GetMapIdxX() == kPlayer->GetMapIdxX()) {
			if (GetMapIdxY() <= kPlayer->GetMapIdxY() && kPlayer->GetMapIdxY() <= GetMapIdxY() + 5) {
			if (rtSData.target) {
			if (rtSData.mapIdx.y > kPlayer->GetMapIdxY()) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_LEFT:
			if (GetMapIdxY() == kPlayer->GetMapIdxY()) {
			if (GetMapIdxX() - 5 <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
			if (rtSData.target) {
			if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_LEFT_DOWN:
			if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == (GetMapIdxX() - kPlayer->GetMapIdxX())) {
			if (GetMapIdxX() - 5 <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
			if (rtSData.target) {
			if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_LEFT_UP:
			if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == -(GetMapIdxX() - kPlayer->GetMapIdxX())) {
			if (GetMapIdxX() - 5 <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX()) {
			if (rtSData.target) {
			if (rtSData.mapIdx.x < kPlayer->GetMapIdxX()) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_RIGHT:
			if (GetMapIdxY() == kPlayer->GetMapIdxY()) {
			if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + 5) {
			if (rtSData.target) {
			if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_RIGHT_DOWN:
			if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == -(GetMapIdxX() - kPlayer->GetMapIdxX())) {
			if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + 5) {
			if (rtSData.target) {
			if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_RIGHT_UP:
			if ((GetMapIdxY() - kPlayer->GetMapIdxY()) == (GetMapIdxX() - kPlayer->GetMapIdxX())) {
			if (GetMapIdxX() <= kPlayer->GetMapIdxX() && kPlayer->GetMapIdxX() <= GetMapIdxX() + 5) {
			if (rtSData.target) {
			if (kPlayer->GetMapIdxX() < rtSData.mapIdx.x) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			case DIRECTION_UP:
			if (GetMapIdxX() == kPlayer->GetMapIdxX()) {
			if (GetMapIdxY() - 5 <= kPlayer->GetMapIdxY() && kPlayer->GetMapIdxY() <= GetMapIdxY()) {
			if (rtSData.target) {
			if (rtSData.mapIdx.y < kPlayer->GetMapIdxY()) {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			else {
			rtSData.target = kPlayer->GetKey();
			rtSData.mapIdx.x = kPlayer->GetMapIdxX();
			rtSData.mapIdx.y = kPlayer->GetMapIdxY();
			}
			}
			}
			break;
			}*/
		}
	}


	m_bFire = true;
	m_tTarget.x = rtSData.mapIdx.x;
	m_tTarget.y = rtSData.mapIdx.y;

	Send(kCommand, sizeof(SUserAttackClToGs));
}

//장미경
bool
CPlayerEx::CollideWithItem(SPosition CItemPos_) {
	if((m_tPosition.x - 4 <= CItemPos_.x && m_tPosition.x + 4 >= CItemPos_.x)
		&& (m_tPosition.y - 4 <= CItemPos_.y && m_tPosition.y + 4 >= CItemPos_.y)) {
		return true;
	}
	return false;
}


//장현우, 이주봉 스팀팩 구현
void
CPlayerEx::SteamPakc() {
	CCommand kCommand;
	kCommand.SetOrder(USER_STEAMPACK);
	kCommand.SetExtra(START);
	
	SUserSteamPackClToGs& rtSData = (SUserSteamPackClToGs&)kCommand.GetData();
	rtSData.SteamPackTime = m_ulSteamPackTiem;

	if (this->GetCurLife() != 1)
		Send(kCommand, sizeof(SUserSteamPackClToGs));
}

void CPlayerEx::PlusLazorCount()
{
	Lazor_count++;
	if (Lazor_count > 15)
		Lazor_count = 15;
}

void CPlayerEx::ZombieInfest()
{
	//SetState(STATE_INFESTED);
	//if(STATE_INFESTED != GetState()) SetState(STATE_INFESTED);

	//if (STATUS_DYING == GetStatus()) return;

	//bool isTouched0 = 0; //isInfested0 = 0;

	size_t userCount0 = g_kMainRoom.GetTopCount();

	for (size_t i = 0; i < userCount0; ++i)
	{
		CPlayerEx* player0 = (CPlayerEx*)g_kMainRoom.GetMember(i);

		if (player0)
		{
			if (player0->GetKey() == this->GetKey()) continue;

			if (STATE_INFESTED != player0->GetState())
			{
				if ((GetMapIdxX() - 1 <= player0->GetMapIdxX() && player0->GetMapIdxX() <= GetMapIdxX() + 1)
					&& (GetMapIdxY() - 1 <= player0->GetMapIdxY() && player0->GetMapIdxY() <= GetMapIdxY() + 1))
				{
					//isTouched0 = 1;
					SetZombieState(ZOMBIE_STATE_INFEST);

					CCommand command0;

					command0.SetOrder(USER_ZOMBIE_INFEST);
					command0.SetExtra(NONE);

					SUserInfestClToGs& sendingDatum0 = (SUserInfestClToGs&)command0.GetData();

					sendingDatum0.target = player0->GetKey();
					sendingDatum0.mapIdx = player0->GetMapIdx();

					Send(command0, sizeof(SUserInfestClToGs));
				}
			}
		}
	}
}

void CPlayerEx::ZombieMove()
{
	//SetState(STATE_INFESTED);
	//if(STATE_INFESTED != GetState()) SetState(STATE_INFESTED);
	SetZombieState(ZOMBIE_STATE_MOVE);
	
	bool isChecked0 = 1;
	SPosition currentPosition0 = m_tPosition;
	
	switch (GetDirection())
	{
	case DIRECTION_UP:
		currentPosition0.y += iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_RIGHT_UP:
		currentPosition0.x -= iPLAYER_MOVE_DISTANCE;
		currentPosition0.y += iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_RIGHT:
		currentPosition0.x -= iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_RIGHT_DOWN:
		currentPosition0.x -= iPLAYER_MOVE_DISTANCE;
		currentPosition0.y -= iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_DOWN:
		currentPosition0.y -= iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_LEFT_DOWN:
		currentPosition0.x += iPLAYER_MOVE_DISTANCE;
		currentPosition0.y -= iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_LEFT:
		currentPosition0.x += iPLAYER_MOVE_DISTANCE;
		break;
	case DIRECTION_LEFT_UP:
		currentPosition0.x += iPLAYER_MOVE_DISTANCE;
		currentPosition0.y += iPLAYER_MOVE_DISTANCE;
		break;
	}

	if (currentPosition0.x != m_tPosition.x || currentPosition0.y != m_tPosition.y)
	{
		Color pixelColor0;

		g_pkCollisionMap->GetPixel(-currentPosition0.x, -currentPosition0.y, &pixelColor0);

		if (pixelColor0.GetValue() == 0xffff0000)
		{
			m_tPosition = currentPosition0;
			SetPosition(m_tPosition.x, m_tPosition.y);
			isChecked0 = 1;
		}
	}
	
	if (isChecked0)
	{
		CCommand command0;
		
		command0.SetOrder(USER_ZOMBIE_MOVE);
		command0.SetExtra(START);

		SUserMoveClToGs& sendingDatum0 = (SUserMoveClToGs&)command0.GetData();
		
		sendingDatum0.pos.x = GetPosX();
		sendingDatum0.pos.y = GetPosY();
		sendingDatum0.dir = GetDirection();

		Send(command0, sizeof(SUserMoveClToGs));
	}
}

void
CPlayerEx::Update() {
	if(STATUS_DYING == GetStatus()) {
		if (MOD_TDM == g_kMainRoom.GetModType()) {
			if (ROOM_STATE_READY != g_kMainRoom.GetRoomState()) {
				return;
			}
		}

		if(GetDeathStartTick() + 300 < g_kTick.GetTick()) {
			SetCurLife(GetMaxLife());
			SetStatus(STATUS_NORMAL);

			CCommand kCommand;
			kCommand.SetOrder(USER_RESPAWN);

			Send(kCommand);

			/*if (isptr(m_pkRoomHandler)) {
			CRoomEx* kRoom = (CRoomEx*)m_pkRoomHandler->GetRoom();
			if (isptr(kRoom)) {

			CCommand kCommand;
			kCommand.SetOrder(OTHER_RESPAWN);
			kCommand.SetExtra(OK);

			((CRoomEx*)kRoom)->Broadcast(kCommand, 0, this);
			}
			}*/
		}
	}

	if(0 < m_tkStopTick) {
		if(g_kTick.GetTick() >= (m_tkStopTick + 30)) {

			CCommand kCommand;

			if (STATE_INFESTED == GetState())
			{
				SetZombieState(ZOMBIE_STATE_IDLE);

				kCommand.SetOrder(USER_ZOMBIE_MOVE);
			}
			else
			{
				SetState(STATE_IDLE);

				kCommand.SetOrder(USER_MOVE);
			}

			kCommand.SetExtra(STOP);

			Send(kCommand);

			m_tkStopTick = 0;
		}
	}
	
	if (MOD_TDM == g_kMainRoom.GetModType() && ROOM_STATE_END != g_kMainRoom.GetRoomState()) {
		if (g_kMainRoom.GetTimeOut() <= 0) {
			if (g_kMainPlayer->GetKey() == g_kMainRoom.GetLeader()->GetKey()) {
				CCommand kCommand;
				kCommand.SetOrder(ROOM_END_PLAYING);
				SRoomEndPlaying& rtSData = (SRoomEndPlaying&)kCommand.GetData();
				if (g_kMainRoom.GetTeamPoint(TEAM_RED) == g_kMainRoom.GetTeamPoint(TEAM_BLUE)) {
					rtSData.draw = true;
				}
				else if (g_kMainRoom.GetTeamPoint(TEAM_RED) > g_kMainRoom.GetTeamPoint(TEAM_BLUE)) {
					rtSData.winTeam = TEAM_RED;
				}
				else {
					rtSData.winTeam = TEAM_BLUE;
				}
				g_kMainPlayer->Send(kCommand, sizeof(SRoomEndPlaying));
				g_kMainRoom.SetRoomState(ROOM_STATE_END);
			}
		}
	}
}
