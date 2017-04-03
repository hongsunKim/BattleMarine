/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "../GlobalVariable.h"
#include "../world/PlayerEx.h"

using namespace Gdiplus;

class CAnimator {
public:
	CAnimator(CPlayerEx& o) : m_rkBody(o), m_iOffset(0), m_tkDelayTick(0) {}
	virtual ~CAnimator() {}

	bool			Initialize();
	bool			Release();

	void			Load();
	void			LoadZombieMotions();
	void			Update(HDC);

	bool			
		
	ChangeColor(Bitmap*);

	CPlayerEx&		GetBody()			{ return m_rkBody; }

private:
	CPlayerEx&		m_rkBody;

	INT				m_iOffset;
	tick_t			m_tkDelayTick;

private:
	// IDLE
	Bitmap*			m_pkIdleUp[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleRightUp[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleRight[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleRightDown[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleDown[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleLeftDown[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleLeft[iANIMATOR_IDLE_LEN];
	Bitmap*			m_pkIdleLeftUp[iANIMATOR_IDLE_LEN];
	
	// ATTACK
	Bitmap*			m_pkAttackUp[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackRightUp[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackRight[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackRightDown[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackDown[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackLeftDown[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackLeft[iANIMATOR_ATTACK_LEN];
	Bitmap*			m_pkAttackLeftUp[iANIMATOR_ATTACK_LEN];

	// MOVE
	Bitmap*			m_pkMoveUp[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveRightUp[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveRight[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveRightDown[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveDown[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveLeftDown[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveLeft[iANIMATOR_MOVE_LEN];
	Bitmap*			m_pkMoveLeftUp[iANIMATOR_MOVE_LEN];

	// DIED
	Bitmap*			m_pkDied[iANIMATOR_DIED_LEN];

	// Zombie Motions
	Bitmap****		m_ppppkZombie;
	//Bitmap***		m_pkZombie[ZOMBIE_STATE_COUNT];
	//Bitmap*			m_pkZombieIdle[DIRECTION_COUNT][iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//Bitmap*			m_pkZombieInfest[DIRECTION_COUNT][iANIMATOR_ZOMBIE_INFEST_LENGTH];
	//Bitmap*			m_pkZombieMove[DIRECTION_COUNT][iANIMATOR_ZOMBIE_MOVE_LENGTH];
	//Bitmap*			m_pkZombieDie[iANIMATOR_ZOMBIE_DIE_LENGTH];
	
};
