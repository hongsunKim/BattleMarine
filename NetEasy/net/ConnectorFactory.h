/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../util/Singleton.h"
#include "../util/Factory.h"

#define g_kConnectorFactory CConnectorFactory::GetInstance()

class CConnectorFactory : public CFactory, public CSingleton< CConnectorFactory > {
public:
	CConnectorFactory() {}
	virtual ~CConnectorFactory() {}

};
