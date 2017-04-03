/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "../GlobalVariable.h"

#define FILELOG(x)	do { (*g_kFileLog) << x << "\n"; } while(0)

class CLogFile {
public:
	CLogFile(const char* szFilePath_, int iIntervalMin_ = 10) : m_iIntervalMin(iIntervalMin_), m_iOffset(0) {
		memset(m_szLogBuffer, 0, sizeof(m_szLogBuffer));
		memset(m_szLogFilePath, 0, sizeof(m_szLogFilePath));

		Initialize(szFilePath_);
	}

	virtual ~CLogFile() {}

	bool	Initialize(const char*);

	void	Output(const char*, ...);

	CLogFile&	operator << (bool arg) { Output("%d", (int)arg); return *this; }

	CLogFile&	operator << (signed short arg) { Output("%d", arg); return *this; }
	CLogFile&	operator << (unsigned short arg) { Output("%u", arg); return *this; }

	CLogFile&	operator << (signed int arg) { Output("%ld", arg); return *this; }
	CLogFile&	operator << (unsigned int arg) { Output("%lu", arg); return *this; }

	CLogFile&	operator << (signed long arg) { Output("%ld", arg); return *this; }
	CLogFile&	operator << (unsigned long arg) { Output("%lu", arg); return *this; }

	CLogFile&	operator << (long long arg) { Output("%lld", arg); return *this; }
	CLogFile&	operator << (unsigned long long arg) { Output("%llu", arg); return *this; }

	CLogFile&	operator << (float arg) { Output("%f", arg); return *this; }
	CLogFile&	operator << (double arg) { Output("%lf", arg); return *this; }

	CLogFile&	operator << (signed char arg) { Output("%d", (int)arg); return *this; }
	CLogFile&	operator << (unsigned char arg) { Output("%u", (int)arg); return *this; }

	CLogFile&	operator << (char* arg) { Output("%s", arg); return *this; }
	CLogFile&	operator << (const char* arg) { Output("%s", arg); return *this; }

	CLogFile&	operator << (void* arg) { Output("%p", arg); return *this; }

private:
	bool	Write(const char*);

	int		m_iIntervalMin;

	int		m_iOffset;

	char	m_szLogBuffer[iLOG_BUFFER_LEN + 1];
	char	m_szLogFilePath[iFILE_PATH_LEN + 1];

};

extern CLogFile* g_kFileLog;
