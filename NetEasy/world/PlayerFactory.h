/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../util/Singleton.h"
#include "../util/Factory.h"

#define g_kPlayerFactory CPlayerFactory::GetInstance()

class CPlayerFactory : public CFactory, public CSingleton< CPlayerFactory > {
public:
	CPlayerFactory() {}
	virtual ~CPlayerFactory() {}

};
