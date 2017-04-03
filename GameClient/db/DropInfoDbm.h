/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

//장미경
#include <NetEasy/CommonHeader.h>

#include "Dbm.h"

#define g_kDropInfoDB CDropInfoDbm::GetInstance()

class CDropInfoDbm : public CDBM, public CSingleton< CDropInfoDbm > {
public:
	CDropInfoDbm() {}
	virtual ~CDropInfoDbm() {}

	bool	Load();

private:

};
