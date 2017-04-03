/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "DbData.h"

#define g_kDbMgr CDbMgr::GetInstance()

class CDbMgr : public CSingleton< CDbMgr > {
public:
	CDbMgr();
	~CDbMgr();

	bool			Initialize();
	bool			Release();

	bool			LoadInfo();

private:
	bool			m_bInitialized;

};
