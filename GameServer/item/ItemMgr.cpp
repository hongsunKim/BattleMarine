/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "ItemMgr.h"

#include "../CommonHeader.h"

bool
CItemMgr::Initialize(INT iId_) {
	TRACE("item manager: ok");

	m_luiSerial = iId_;

	return true;
}

bool
CItemMgr::Release() {
	return true;
}

UINT64
CItemMgr::NewSerial() {
	UINT64 luiTime = UINT64(g_kTick.GetTime()) << 32;
	++m_luiSerial;
	return (luiTime | m_luiSerial);
}
