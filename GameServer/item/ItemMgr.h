/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#define g_kItemMgr CItemMgr::GetInstance()

class CItem;

class CItemMgr : public CSingleton<CItemMgr> {
public:
	CItemMgr() : m_luiSerial(0) {}
	~CItemMgr() {}

	bool	Initialize(INT = 0);
	bool	Release();

	UINT64	NewSerial();

private:
	UINT64	m_luiSerial;

};
