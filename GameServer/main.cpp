/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "CommonHeader.h"

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

int main()
{
	g_kConnectorFactory.Register(CConnectorEx::New);
	g_kRoomFactory.Register(CRoomEx::New);
	g_kPlayerFactory.Register(CPlayerEx::New);

	const char* szServerPort = NULL;
	const char* szDatabaseHost = NULL;
	const char* szDatabaseName = NULL;
	const char* szDatabaseUser = NULL;
	const char* szDatabasePasswd = NULL;

	TiXmlDocument kXmlPreference;
	if(kXmlPreference.LoadFile("..\\Data\\config.xml")) {
		TiXmlNode* pkRoot = kXmlPreference.FirstChild("configs");
		if(isptr(pkRoot)) {
			TiXmlNode* pkPreference = pkRoot->FirstChild("preference");
			if(isptr(pkPreference)) {
				TiXmlNode* pkServer = pkPreference->FirstChild("server");
				if (isptr(pkServer)) {
					if (isptr(pkServer->ToElement())) {
						szServerPort = pkServer->ToElement()->Attribute("port");
					}
				}

				TiXmlNode* pkDb = pkPreference->FirstChild("db");
				if (isptr(pkDb)) {
					if (isptr(pkDb->ToElement())) {
						szDatabaseHost = pkDb->ToElement()->Attribute("host");
						szDatabaseName = pkDb->ToElement()->Attribute("name");
						szDatabaseUser = pkDb->ToElement()->Attribute("user");
						szDatabasePasswd = pkDb->ToElement()->Attribute("passwd");
					}
				}
			}
		}
	}

	INT iServerPort = 0;
	if(isptr(szServerPort)) {
		iServerPort = atoi(szServerPort);
	} else {
		iServerPort = REMOTE_PORT;
	}

	if(isptr(szDatabaseHost)) {
		g_kDbMgr.SetGameHost(szDatabaseHost);
	} else {
		g_kDbMgr.SetGameHost(DATABASE_HOST);
	}
	
	if(isptr(szDatabaseName)) {
		g_kDbMgr.SetGameDB(szDatabaseName);
	} else {
		g_kDbMgr.SetGameDB(DATABASE_NAME);
	}

	if(isptr(szDatabaseUser)) {
		g_kDbMgr.SetGameUser(szDatabaseUser);
	} else {
		g_kDbMgr.SetGameUser(DATABASE_USER);
	}

	if(isptr(szDatabasePasswd)) {
		g_kDbMgr.SetGamePassword(szDatabasePasswd);
	} else {
		g_kDbMgr.SetGamePassword(DATABASE_PASSWD);
	}

	g_kDbMgr.Initialize();
	g_kPlayerMgr.Initialize();
	g_kChannelMgr.Initialize();

	g_kItemMgr.Initialize(1);

	InitializeCommand();

	WSAData wsaData;

	// WinSock2 설정
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return 1;
	}

	CEventSelectSensor* pkSensor = new CEventSelectSensor();
	if (isptr(pkSensor)) {
		pkSensor->Initialize(WSA_MAXIMUM_WAIT_EVENTS);

		CListener* pkListener = new CListener();
		if (isptr(pkListener)) {
			pkSensor->SetListener(pkListener);
			pkListener->SetSensor(pkSensor);
			pkListener->Listen("0.0.0.0", iServerPort);
		}

		while (true) {
			g_kTick.Update();
			g_kChannelMgr.Update();

			pkSensor->WaitEvent(0);
			Sleep(100);
		}

		pkSensor->Release();
	}

	g_kItemMgr.Release();
	g_kChannelMgr.Release();
	g_kPlayerMgr.Release();
	g_kDbMgr.Release();

    return 0;
}
