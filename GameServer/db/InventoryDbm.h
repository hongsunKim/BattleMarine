/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"
#include "DbData.h"

#define g_kInventoryDB	CInventoryDbm::GetInstance()

class CInventoryDbm : public CDBM, public CSingleton< CInventoryDbm > {
public:
	CInventoryDbm() {}
	virtual ~CInventoryDbm() {}

	bool	Query(UINT, CPlayer&);

private:
	bool	ConvDB2Data(char**, CPlayer&);

};
