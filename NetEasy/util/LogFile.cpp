/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

CLogFile* g_kFileLog = NULL;

bool
CLogFile::Initialize(const char* szFilePath_) {
	if (szFilePath_ != NULL) {
		memset(m_szLogFilePath, 0, sizeof(m_szLogFilePath));
		strncpy(m_szLogFilePath, szFilePath_, iFILE_PATH_LEN);
		m_szLogFilePath[iFILE_PATH_LEN] = '\0';
	}

	std::cout << "path: " << m_szLogFilePath << std::endl;
	return true;
}

void
CLogFile::Output(const char* szFormat_, ...) {
	if (szFormat_ != NULL) {
		if (m_iOffset < iLOG_BUFFER_LEN) {
			va_list va;
			va_start(va, szFormat_);

			//if(isptr(va)) {
			char* szBuffer = m_szLogBuffer + m_iOffset;
			vsnprintf(szBuffer, iLOG_BUFFER_LEN - m_iOffset - 1, szFormat_, va);
			va_end(va);

			if ('\n' == szBuffer[0]) {
				if (m_iOffset < iLOG_BUFFER_LEN) {
					if (',' == m_szLogBuffer[m_iOffset - 1]) {
						m_szLogBuffer[m_iOffset - 1] = '\0';
					} else {
						m_szLogBuffer[m_iOffset] = '\0';
					}
				} else {
					if (',' == m_szLogBuffer[iLOG_BUFFER_LEN - 1]) {
						m_szLogBuffer[iLOG_BUFFER_LEN - 1] = '\0';
					} else {
						m_szLogBuffer[iLOG_BUFFER_LEN] = '\0';
					}
				}

				Write(m_szLogBuffer);
				memset(m_szLogBuffer, 0, iLOG_BUFFER_LEN);
				m_iOffset = 0;
				return;
			}

			std::cout << "[" << m_szLogBuffer << "] : [" << szBuffer << "] : " << iLOG_BUFFER_LEN - m_iOffset-1 << " : " << szFormat_ << std::endl;

			m_iOffset = strlen(m_szLogBuffer);
			if ((m_iOffset + 1) < iLOG_BUFFER_LEN) {
				m_szLogBuffer[m_iOffset] = ',';
				++m_iOffset;
			} else {
				m_szLogBuffer[iLOG_BUFFER_LEN] = '\0';
				m_iOffset = iLOG_BUFFER_LEN;
			}
			return;
			//}
		}

		std::cout << "[" << time(0) << "] critical error: log string is too long: " << m_iOffset << std::endl;
		m_szLogBuffer[iLOG_BUFFER_LEN] = '\0';

		Write(m_szLogBuffer);
		memset(m_szLogBuffer, 0, iLOG_BUFFER_LEN);
		m_iOffset = 0;
	}
	else {
		std::cout << "[" << time(0) << "] critical error: log string is null: " << std::endl;
	}
}

bool
CLogFile::Write(const char* szLog_) {
	if (szLog_ != NULL) {
		char szFilePath[iFILE_PATH_LEN + 1] = { 0, };
		char szLog[iLOG_BUFFER_LEN + 64 + 1] = { 0, };

		time_t tmCurrentTime = time(0);
		struct tm* tCurrentTime = localtime(&tmCurrentTime);

		sprintf(szFilePath, "%s-%d%02d%02d%02d%02d.log", m_szLogFilePath, tCurrentTime->tm_year + 1900, tCurrentTime->tm_mon + 1, tCurrentTime->tm_mday, tCurrentTime->tm_hour, (tCurrentTime->tm_min / m_iIntervalMin) * m_iIntervalMin);

		FILE* fp = fopen(szFilePath, "a+");

		if (fp != NULL) {
			sprintf(szLog, "%s\n", szLog_);
			std::cout << "log: " << szLog << std::endl;

			fwrite(szLog, 1, strlen(szLog), fp);
			fclose(fp);

			return true;
		} else {
			std::cout << "[" << time(0) << "] log file was not found: " << szFilePath << std::endl;
		}
	}
	else {
		std::cout << "[" << time(0) << "] critical error: log string is null: " << std::endl;
	}
	return false;
}
