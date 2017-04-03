/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"

#define g_kRewardInfoDB CRewardInfoDbm::GetInstance()

class CRewardInfoDbm : public CDBM, public CSingleton< CRewardInfoDbm > {
public:
	CRewardInfoDbm() {}
	virtual ~CRewardInfoDbm() {}

	bool	Load();

private:

};
