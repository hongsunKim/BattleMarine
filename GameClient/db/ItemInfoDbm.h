/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"

#define g_kItemInfoDB CItemInfoDbm::GetInstance()

class CItemInfoDbm : public CDBM, public CSingleton< CItemInfoDbm > {
public:
	CItemInfoDbm() {}
	virtual ~CItemInfoDbm() {}

	bool	Load();

private:

};
