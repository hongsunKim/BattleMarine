/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "../GlobalVariable.h"

#define CONSOLE(x)	do { (*g_kConsole) << x << "\n"; } while(0)

class CConsole {
public:
	CConsole() : m_hWnd(NULL), m_iOffset(0) {
		memset(m_szConsoleBuffer, 0, sizeof(m_szConsoleBuffer));
	}

	virtual ~CConsole() {}

	void	SetHandler(HWND o)		{ m_hWnd = o; }
	HWND	GetHandler()			{ return m_hWnd; }

	void	Output(const char*, ...);

	CConsole&	operator << (bool arg) { Output("%d", (int)arg); return *this; }

	CConsole&	operator << (signed short arg) { Output("%d", arg); return *this; }
	CConsole&	operator << (unsigned short arg) { Output("%u", arg); return *this; }

	CConsole&	operator << (signed int arg) { Output("%ld", arg); return *this; }
	CConsole&	operator << (unsigned int arg) { Output("%lu", arg); return *this; }

	CConsole&	operator << (signed long arg) { Output("%ld", arg); return *this; }
	CConsole&	operator << (unsigned long arg) { Output("%lu", arg); return *this; }

	CConsole&	operator << (long long arg) { Output("%lld", arg); return *this; }
	CConsole&	operator << (unsigned long long arg) { Output("%llu", arg); return *this; }

	CConsole&	operator << (float arg) { Output("%f", arg); return *this; }
	CConsole&	operator << (double arg) { Output("%lf", arg); return *this; }

	CConsole&	operator << (signed char arg) { Output("%d", (int)arg); return *this; }
	CConsole&	operator << (unsigned char arg) { Output("%u", (int)arg); return *this; }

	CConsole&	operator << (char* arg) { Output("%s", arg); return *this; }
	CConsole&	operator << (const char* arg) { Output("%s", arg); return *this; }

	CConsole&	operator << (void* arg) { Output("%p", arg); return *this; }

private:
	bool	Write(const char*);

	HWND	m_hWnd;
	INT		m_iOffset;

	char	m_szConsoleBuffer[iCONSOLE_BUFFER_LEN + 1];

};

extern CConsole* g_kConsole;
