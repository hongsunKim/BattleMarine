/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Tick.h"

#include "../CommonHeader.h"

CTick::CTick() : m_uliTick(0), m_tmTime(time(0)), m_iDeltaTick(0), m_uliServerTick(0), m_tmStartedTime(0) {
	m_uliTick = 0;
	m_uliServerTick = 0;

	QueryPerformanceFrequency(&m_Freq);
	QueryPerformanceCounter(&m_Start);

	m_tmStartedTime = (time(0));
	srand((UINT)m_tmTime);
}

CTick::~CTick() {

}

tick_t
CTick::GetTick() {
	return tick_t(m_uliTick / 10);
}

UINT
CTick::GetCSec() {
	return UINT(m_uliTick / 10);
}

UINT64
CTick::GetMSec() {
	return m_uliTick;
}

time_t
CTick::GetTime() {
	return m_tmTime;
}

UINT64
CTick::GetServerTick() {
	return m_uliServerTick;
}

void
CTick::Reset(UINT64 o) {
	QueryPerformanceFrequency(&m_Freq);
	QueryPerformanceCounter(&m_Start);

	m_uliServerTick = o;
	m_uliTick = o;
	m_tmTime = time(0);
	m_tmStartedTime = m_tmTime;
}

INT
CTick::GetDeltaMSec() {
	return m_iDeltaTick;
}

bool
CTick::IsUpdate() {
	return (0 != m_iDeltaTick);
}

INT
CTick::Update() {
	UINT64 uliOldTick = m_uliTick;

	m_tmTime = time(0);
	LARGE_INTEGER stTime;
	QueryPerformanceCounter(&stTime);
	
	m_uliTick = UINT64((stTime.QuadPart - m_Start.QuadPart) * 1000) / m_Freq.QuadPart + m_uliServerTick;

	m_iDeltaTick = tick_t(m_uliTick - uliOldTick);
	return m_iDeltaTick;
}
