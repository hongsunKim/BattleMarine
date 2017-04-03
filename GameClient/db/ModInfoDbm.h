/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"

#define g_kModInfoDB CModInfoDbm::GetInstance()

class CModInfoDbm : public CDBM, public CSingleton< CModInfoDbm > {
public:
	CModInfoDbm() {}
	virtual ~CModInfoDbm() {}

	bool	Load();

private:

};
