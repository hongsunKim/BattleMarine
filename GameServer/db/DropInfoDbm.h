/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"
#include "DbData.h"

class CDropInfoDbm : public CDBM {
public:
	CDropInfoDbm() {}
	virtual ~CDropInfoDbm() {}

	INT		Query();

private:
	bool	ConvDB2Data(char**, SDropInfo&);

};
