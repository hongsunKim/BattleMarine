/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

CEventSelectSensor::CEventSelectSensor()
: m_uiMaxConnection(0) {
	memset(m_skSockets, INVALID_SOCKET, WSA_MAXIMUM_WAIT_EVENTS);
	memset(m_kEvents, 0, sizeof(WSAEVENT) * WSA_MAXIMUM_WAIT_EVENTS);
}

CEventSelectSensor::~CEventSelectSensor() {
	Release();
}

bool
CEventSelectSensor::Initialize(UINT uiMaxConnection_) {
	if(uiMaxConnection_ <= WSA_MAXIMUM_WAIT_EVENTS) {
		m_uiMaxConnection = uiMaxConnection_;
		return true;
	} else {
		OUTPUT("critical error: max connection overflow: [" << uiMaxConnection_ << ":" << WSA_MAXIMUM_WAIT_EVENTS);
	}
	return false;
}

void
CEventSelectSensor::Release() {
	Clear();
}

void
CEventSelectSensor::Clear() {
	if(0 < m_uiMaxConnection) {
		for (SOCKET i = 0; i < GetCount(); ++i) {
			if(INVALID_SOCKET != m_skSockets[i]) {
				WSACloseEvent(m_kEvents[i]);
			}
		}

		m_uiMaxConnection = 0;
		memset(m_skSockets, INVALID_SOCKET, WSA_MAXIMUM_WAIT_EVENTS);
		memset(m_kEvents, 0, sizeof(WSAEVENT) * WSA_MAXIMUM_WAIT_EVENTS);
	}
	ISensor::Clear();
}

INT
CEventSelectSensor::WaitEvent(INT iTimeout_) {
	if(0 < GetCount()) {
		WSANETWORKEVENTS wsaNetworkEvents;
		DWORD iRet = WSAWaitForMultipleEvents((DWORD)GetCount(), &m_kEvents[0], false, iTimeout_, false);
		iRet = iRet - WSA_WAIT_EVENT_0;

		for(DWORD i = iRet; i < (DWORD)GetCount(); ++i) {
			iRet = WSAWaitForMultipleEvents(1, &m_kEvents[i], false, 0, false);
			if((WSA_WAIT_FAILED == iRet) || (WSA_WAIT_TIMEOUT == iRet)) {
				continue;
			} else {
				iRet = i;
				WSAEnumNetworkEvents(m_skSockets[iRet], m_kEvents[iRet], &wsaNetworkEvents);

				CPlayer* pkPlayer = g_kPlayerMgr.Find((UINT)m_skSockets[iRet]);
				if(isptr(pkPlayer)) {
					CConnector* pkConnector = pkPlayer->GetConnector();
					if(isptr(pkConnector)) {
						if(IsCLOSE(wsaNetworkEvents.lNetworkEvents)) {
							pkConnector->Read();
							pkConnector->Disconnect(m_skSockets[iRet]);

							g_kPlayerMgr.Delete((UINT)m_skSockets[iRet]);
							SAFE_DELETE(pkPlayer);
						} else {
							pkConnector->Read();
						}
					} else {
						OUTPUT("connector is null: " << m_skSockets[iRet]);
					}
				} else {
					//OUTPUT("player is null: " << m_skSockets[iRet]);
					if (isptr(m_pkListener)) {
						if (IsCLOSE(wsaNetworkEvents.lNetworkEvents)) {
							m_pkListener->Read();
							m_pkListener->Disconnect(m_skSockets[iRet]);
						} else {
							m_pkListener->Read();
						}
					} else {
						OUTPUT("listener is null: " << m_skSockets[iRet]);
					}
				}
			}
		}
	} else {
		return -2;
	}
	return 0;
}

bool
CEventSelectSensor::Register(const SOCKET skSocket_) {
	if(INVALID_SOCKET != skSocket_) {
		if(InRange(GetCount())) {
			m_skSockets[GetCount()] = skSocket_;
			m_kEvents[GetCount()] = WSACreateEvent();

			WSAEventSelect(skSocket_, m_kEvents[GetCount()], FD_ACCEPT | FD_READ | FD_CLOSE);
			IncreasedCount();

			return true;
		} else {
			OUTPUT("Register: overflow connection: [" << skSocket_ << "]");
		}
	} else {
		OUTPUT("Register: error: [" << skSocket_ << "] " << GetMaxConnection());
	}
	return false;
}

bool
CEventSelectSensor::Unregister(const SOCKET skSocket_) {
	if(INVALID_SOCKET != skSocket_) {
		for(UINT i = 0; i < GetCount(); ++i) {
			if(m_skSockets[i] == skSocket_) {
				WSACloseEvent(m_kEvents[i]);
				DecreasedCount();

				m_skSockets[GetCount()] = INVALID_SOCKET;
				return true;
			}
		}
	}
	return false;
}
