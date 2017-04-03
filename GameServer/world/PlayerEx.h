/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "../Enums.h"

class CPlayerEx : public CPlayer {
public:
	CPlayerEx();
	virtual ~CPlayerEx();

	virtual void	Clear();

	GRADE_TYPE		GetGradeType()				{ return m_eGradeType; }
	void			SetGradeType(GRADE_TYPE o)	{ m_eGradeType = o; }

	INT				GetRespawnIndex()			{ return m_iRespawnIndex; }
	void			SetRespawnIndex(INT o)		{ m_iRespawnIndex = o; }

	FLOAT			GetSteamPackTime()			{ return m_fSteamPackTime; }
	void			SetSteamPackTime(FLOAT o)	{ m_fSteamPackTime = o; }

	static void*	New()						{ return new CPlayerEx; }

private:
	GRADE_TYPE		m_eGradeType;

	INT				m_iRespawnIndex;
	FLOAT			m_fSteamPackTime;

};
