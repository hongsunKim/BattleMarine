/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "Console.h"

#include "../CommonHeader.h"

CConsole* g_kConsole = NULL;

void
CConsole::Output(const char* szFormat_, ...) {
	if (szFormat_ != NULL) {
		if (m_iOffset < iCONSOLE_BUFFER_LEN) {
			va_list va;
			va_start(va, szFormat_);

			//if(isptr(va)) {
			char* szBuffer = m_szConsoleBuffer + m_iOffset;
			vsnprintf(szBuffer, iCONSOLE_BUFFER_LEN - m_iOffset - 1, szFormat_, va);
			va_end(va);

			if ('\n' == szBuffer[0]) {
				if (m_iOffset < iCONSOLE_BUFFER_LEN) {
					m_szConsoleBuffer[m_iOffset] = '\0';
				} else {
					m_szConsoleBuffer[iCONSOLE_BUFFER_LEN] = '\0';
				}

				Write(m_szConsoleBuffer);
				memset(m_szConsoleBuffer, 0, iCONSOLE_BUFFER_LEN);
				m_iOffset = 0;
				return;
			}

			std::cout << "[" << m_szConsoleBuffer << "] : [" << szBuffer << "] : " << iCONSOLE_BUFFER_LEN - m_iOffset - 1 << " : " << szFormat_ << std::endl;

			m_iOffset = strlen(m_szConsoleBuffer);
			if(m_iOffset >= iCONSOLE_BUFFER_LEN) {
				m_szConsoleBuffer[iCONSOLE_BUFFER_LEN] = '\0';
				m_iOffset = iCONSOLE_BUFFER_LEN;
			}
			return;
			//}
		}

		std::cout << "[" << time(0) << "] critical error: log string is too long: " << m_iOffset << std::endl;
		m_szConsoleBuffer[iCONSOLE_BUFFER_LEN] = '\0';

		Write(m_szConsoleBuffer);
		memset(m_szConsoleBuffer, 0, iCONSOLE_BUFFER_LEN);
		m_iOffset = 0;
	} else {
		std::cout << "[" << time(0) << "] critical error: log string is null: " << std::endl;
	}
}

bool
CConsole::Write(const char* szBuffer_) {
	if(szBuffer_ != NULL) {
		if(isptr(m_hWnd)) {
			char szOldMessage[iCONSOLE_BUFFER_LEN * iCONSOLE_MESSAGE_LINE] = { 0, };
			GetDlgItemText(m_hWnd, IDC_CONSOLE_MESSAGE, szOldMessage, iCONSOLE_BUFFER_LEN * iCONSOLE_MESSAGE_LINE);

			char szNewMessage[iCONSOLE_BUFFER_LEN * iCONSOLE_MESSAGE_LINE] = { 0, };
			sprintf(szNewMessage, "%s\r\n%s\r\n", szBuffer_, szOldMessage);

			SetDlgItemText(m_hWnd, IDC_CONSOLE_MESSAGE, szNewMessage);

			return true;
		}
	} else {
		std::cout << "[" << time(0) << "] critical error: log string is null: " << std::endl;
	}
	return false;
}
