/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "DbMgr.h"
#include "../CommonHeader.h"

CDbMgr::CDbMgr() : m_bInitialized(false) {
}

CDbMgr::~CDbMgr() {
	Release();
}

bool
CDbMgr::Initialize() {
	if(LoadInfo()) {
		m_bInitialized = true;
		return true;
	}
	return false;
}

bool
CDbMgr::Release() {
	if(m_bInitialized) {
		g_kModInfoList.Clear();
		g_kMapInfoList.Clear();
		g_kItemInfoList.Clear();
		g_kDropInfoList.Clear();
		g_kRewardInfoList.Clear();

		g_kModInfoList.ReleaseInstance();
		g_kMapInfoList.ReleaseInstance();
		g_kItemInfoList.ReleaseInstance();
		g_kDropInfoList.ReleaseInstance();
		g_kRewardInfoList.ReleaseInstance();

		m_bInitialized = false;

		return true;
	}
	return false;
}

bool
CDbMgr::LoadInfo() {
	bool bCheck = true;

	CONSOLE("load info: modinfo");
	if(false == g_kModInfoDB.Load()) {
		CONSOLE("load info failed: modinfo");
		bCheck = false;
	}

	CONSOLE("load info: mapinfo");
	if(false == g_kMapInfoDB.Load()) {
		CONSOLE("load info failed: mapinfo");
		bCheck = false;
	}

	CONSOLE("load info: iteminfo");
	if(false == g_kItemInfoDB.Load()) {
		CONSOLE("load info failed: iteminfo");
		bCheck = false;
	}

	CONSOLE("load info: dropinfo");
	if(false == g_kDropInfoDB.Load()) {
		CONSOLE("load info failed: dropinfo");
		bCheck = false;
	}

	CONSOLE("load info: rewardinfo");
	if(false == g_kRewardInfoDB.Load()) {
		CONSOLE("load info failed: rewardinfo");
		bCheck = false;
	}

	return bCheck;
}
