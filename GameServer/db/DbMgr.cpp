/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "DbMgr.h"
#include "../CommonHeader.h"

CDbMgr::CDbMgr() : m_bInitialized(true), m_bSecureAuth(false) {
	memset(m_szCharacterSet, 0, iDATABASE_CHARACTER_SET_LEN);
}

CDbMgr::~CDbMgr() {
	Release();
}

bool
CDbMgr::Initialize() {
	m_bInitialized = true;

	SetSecureAuth(true);

	LoadInfo();
	Open();

	return m_bInitialized;
}

bool
CDbMgr::Release() {
	Close();
	return true;
}

bool
CDbMgr::LoadInfo() {
	if(false == LoadMapInfo()) {
		OUTPUT("Loading mapinfo table: [FAIL]");
		m_bInitialized = false;
	} else {
		OUTPUT("Loading mapinfo table: [OK]");
	}

	if(false == LoadModInfo()) {
		OUTPUT("Loading modinfo table: [FAIL]");
		m_bInitialized = false;
	} else {
		OUTPUT("Loading modinfo table: [OK]");
	}

	if(false == LoadItemInfo()) {
		OUTPUT("Loading iteminfo table: [FAIL]");
		m_bInitialized = false;
	} else {
		OUTPUT("Loading iteminfo table: [OK]");
	}

	if(false == LoadDropInfo()) {
		OUTPUT("Loading dropinfo table: [FAIL]");
		m_bInitialized = false;
	} else {
		OUTPUT("Loading dropinfo table: [OK]");
	}

	if(false == LoadRewardInfo()) {
		OUTPUT("Loading rewardinfo table: [FAIL]");
		m_bInitialized = false;
	} else {
		OUTPUT("Loading rewardinfo table: [OK]");
	}

	return m_bInitialized;
}

bool
CDbMgr::Open() {
	if(false == g_kAccountDB.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		OUTPUT("Opening account table: [FAIL]");
		OUTPUT("host: " << &GetGameHost() << " : " << &GetGameDB() << " : " << &GetGameUser() << " : " << &GetGamePassword());
		m_bInitialized = false;
	} else {
		OUTPUT("Opening account table: [OK]");
	}

	if(false == g_kInventoryDB.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		OUTPUT("Opening inventory table: [FAIL]");
		OUTPUT("host: " << &GetGameHost() << " : " << &GetGameDB() << " : " << &GetGameUser() << " : " << &GetGamePassword());
		m_bInitialized = false;
	} else {
		OUTPUT("Opening inventory table: [OK]");
	}

	return m_bInitialized;
}

void
CDbMgr::Close() {
	if(false == g_kAccountDB.Release()) {
		OUTPUT("Closing account database: [FAIL]");
	} else {
		OUTPUT("Closing account database: [OK]");
	}

	if(false == g_kInventoryDB.Release()) {
		OUTPUT("Closing inventory database: [FAIL]");
	} else {
		OUTPUT("Closing inventory database: [OK]");
	}
}

bool
CDbMgr::LoadMapInfo() {
	CMapInfoDbm kDbm;
	if(kDbm.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		if(0 >= kDbm.Query()) {
			OUTPUT("["<<g_kTick.GetTime()<<"] db's table empty or data is error: ");
			kDbm.Release();
			return false;
		}
		kDbm.Release();
		return true;
	} else {
		OUTPUT("["<<g_kTick.GetTime()<<"] host: "<<&GetGameHost()<<" : "<<&GetGameDB()<<" : "<<&GetGameUser());
	}
	kDbm.Release();
	return false;
}

bool
CDbMgr::LoadModInfo() {
	CModInfoDbm kDbm;
	if(kDbm.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		if(0 >= kDbm.Query()) {
			OUTPUT("["<<g_kTick.GetTime()<<"] db's table empty or data is error: ");
			kDbm.Release();
			return false;
		}
		kDbm.Release();
		return true;
	} else {
		OUTPUT("["<<g_kTick.GetTime()<<"] host: "<<&GetGameHost()<<" : "<<&GetGameDB()<<" : "<<&GetGameUser());
	}
	kDbm.Release();
	return false;
}

bool
CDbMgr::LoadItemInfo() {
	CItemInfoDbm kDbm;
	if(kDbm.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		if(0 >= kDbm.Query()) {
			OUTPUT("["<<g_kTick.GetTime()<<"] db's table empty or data is error: ");
			kDbm.Release();
			return false;
		}
		kDbm.Release();
		return true;
	} else {
		OUTPUT("["<<g_kTick.GetTime()<<"] host: "<<&GetGameHost()<<" : "<<&GetGameDB()<<" : "<<&GetGameUser());
	}
	kDbm.Release();
	return false;
}

bool
CDbMgr::LoadDropInfo() {
	CDropInfoDbm kDbm;
	if(kDbm.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		if(0 >= kDbm.Query()) {
			OUTPUT("["<<g_kTick.GetTime()<<"] db's table empty or data is error: ");
			kDbm.Release();
			return false;
		}
		kDbm.Release();
		return true;
	} else {
		OUTPUT("["<<g_kTick.GetTime()<<"] host: "<<&GetGameHost()<<" : "<<&GetGameDB()<<" : "<<&GetGameUser());
	}
	kDbm.Release();
	return false;
}

bool
CDbMgr::LoadRewardInfo() {
	CRewardInfoDbm kDbm;
	if(kDbm.Initialize(GetGameHost(), GetGameDB(), GetGameUser(), GetGamePassword(), GetSecureAuth())) {
		if(0 >= kDbm.Query()) {
			OUTPUT("["<<g_kTick.GetTime()<<"] db's table empty or data is error: ");
			kDbm.Release();
			return false;
			//return true;
		}
		kDbm.Release();
		return true;
	} else {
		OUTPUT("["<<g_kTick.GetTime()<<"] host: "<<&GetGameHost()<<" : "<<&GetGameDB()<<" : "<<&GetGameUser());
	}
	kDbm.Release();
	return false;
}
