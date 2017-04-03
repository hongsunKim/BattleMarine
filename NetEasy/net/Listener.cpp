/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

INT
CListener::Listen(const char* szAddr_, INT iPort_) {
	if(isptr(m_pkSensor)) {
		SOCKET skSocket = GetTcpSocket()->Listen(szAddr_, iPort_);
		if (INVALID_SOCKET != skSocket) {
			if (m_pkSensor->Register(skSocket)) {
				SetLocalAddress(szAddr_, iPort_);

				return 1;
			} else {
				OUTPUT("register failed: ");
			}
		} else {
			OUTPUT("listen failed: ");
		}
	} else {
		OUTPUT("sensor is null: ");
	}
	return -1;
}

bool
CListener::Read() {
	if(isptr(m_pkSensor)) {
		SOCKET skSocket = GetTcpSocket()->Accept();
		if(INVALID_SOCKET != skSocket) {
			CPlayer* pkPlayer = (CPlayer*)g_kPlayerFactory.Create();
			pkPlayer->SetIndex((UINT)skSocket);
			pkPlayer->SetKey((UINT)skSocket);

			char szName[iPLAYER_NAME_LEN] = { 0, };
			sprintf(szName, "Player%d", pkPlayer->GetIndex());
			pkPlayer->SetName(szName);

			CConnector* pkConnector = (CConnector*)g_kConnectorFactory.Create();
			if (isptr(pkConnector)) {
				pkPlayer->SetConnector(pkConnector);
				pkConnector->SetBody(pkPlayer);

				if (m_pkSensor->Register(skSocket)) {
					SetRegister(true);

					pkConnector->SetSocket(skSocket);
					pkConnector->SetConnected();
					pkConnector->SetRemoteAddress(m_pkSocket->GetRemoteAddressIn());
				} else {
					OUTPUT("critical error: don't register in sensor: ");
				}
			} else {
				OUTPUT("critical error: connector is null: ");
			}

			g_kPlayerMgr.Insert(*pkPlayer);
		} else {
			//TRACE("accept failed: ");
			return true;
		}
	}
	return true;
}
