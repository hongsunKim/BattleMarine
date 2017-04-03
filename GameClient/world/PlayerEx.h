/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "../Enums.h"
#include "../item/Inventory.h"

using namespace Gdiplus;
class CAnimator;
class CInventory;

class CPlayerEx : public CPlayer {
public:
	CPlayerEx();
	virtual ~CPlayerEx();

	//void			Create();
	//void			Terminate();

	virtual void	Clear();
	virtual void	Update();

	CAnimator*		GetAnimator()					{ return m_pkAnimator; }

	STATE_TYPE		GetState()						{ return m_eState; }
	void			SetState(STATE_TYPE o)			{ m_eState = o; }

	void			Move();
	void			Stop();
	void			Attack();
	void			SteamPakc();
	bool			CollideWithItem(SPosition);

	///////////////
	WEAPON_TYPE			GetWeaponType() { return m_wType; }
	void			SwitchWeapon(WEAPON_TYPE o) { m_wType = o; }
	int				GetLazorCount() { return Lazor_count; }
	void			SetLazorCount(int o) { Lazor_count = o; }

	bool			GetAttCheck() { return m_attCheck; }
	void			SetAttCheck(bool o) { m_attCheck = o; }


	void			PlusLazorCount();
	///////////////

	void			ZombieInfest();
	void			ZombieMove();

	static void*	New()							{ return new CPlayerEx; }

	POINT			GetTargetMapIdx()				{ return m_tTarget; }
	void			SetTargetMapIdx(POINT o)		{ m_tTarget = o; }

	bool			IsFire()						{ return m_bFire; }
	void			SetFire(bool o)					{ m_bFire = o; }

	CInventory*		GetInventory()					{ return m_pkInventory;  }

	ZOMBIE_STATE_TYPE	GetZombieState()					{ return m_eZombieState; }
	void				SetZombieState(ZOMBIE_STATE_TYPE o)	{ m_eZombieState = o; }

private:
	STATE_TYPE		m_eState;
	tick_t			m_tkStopTick;

	CAnimator*		m_pkAnimator;

	POINT			m_tTarget;
	bool			m_bFire;

	bool			bCheck;

	SPosition		ck_Position;

	CInventory*		m_pkInventory;

	ZOMBIE_STATE_TYPE m_eZombieState;
	Color*			g_Color;

	//////////
	WEAPON_TYPE		m_wType;
	bool			m_attCheck;

	int				Lazor_count;
	//////////
};
