/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"
#include "DbData.h"

class CRewardInfoDbm : public CDBM {
public:
	CRewardInfoDbm() {}
	virtual ~CRewardInfoDbm() {}

	INT		Query();

private:
	bool	ConvDB2Data(char**, SRewardInfo&);

};
