/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <synchapi.h>

#define LOCKING(o)		CLocking locking(o)

class CLocker {
public:
	CLocker()			{ InitializeCriticalSection(&m_cs); }
	~CLocker()			{ DeleteCriticalSection(&m_cs); }

	void	Lock()		{ EnterCriticalSection(&m_cs); }
	void	Unlock()	{ LeaveCriticalSection(&m_cs); }

	CRITICAL_SECTION	m_cs;
};

class CLocking {
public:
	CLocking(CLocker& o) : m_rLocker(o) {
		EnterCriticalSection(&m_rLocker.m_cs);
	}

	~CLocking() {
		LeaveCriticalSection(&m_rLocker.m_cs);
	}

private:
	CLocker&	m_rLocker;
};
