/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"

#define g_kMapInfoDB CMapInfoDbm::GetInstance()

class CMapInfoDbm : public CDBM, public CSingleton< CMapInfoDbm > {
public:
	CMapInfoDbm() {}
	virtual ~CMapInfoDbm() {}

	bool	Load();

private:

};
