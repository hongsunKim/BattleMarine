/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#define g_kTick		CTick::GetInstance()

class CTick : public CSingleton < CTick > {
public:
	CTick();
	virtual ~CTick();

	INT				Update();
	void			Reset(UINT64);

	UINT64			GetServerTick();
	tick_t			GetTick();
	INT				GetDeltaMSec();

	bool			IsUpdate();

	UINT			GetCSec();
	UINT64			GetMSec();
	time_t			GetTime();

protected:
	UINT64			m_uliTick;
	time_t			m_tmTime;
	INT				m_iDeltaTick;

	LARGE_INTEGER	m_Start;
	LARGE_INTEGER	m_Freq;

	UINT64			m_uliServerTick;

	time_t			m_tmStartedTime;

};

