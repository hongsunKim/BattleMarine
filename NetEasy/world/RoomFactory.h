/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../util/Singleton.h"
#include "../util/Factory.h"

#define g_kRoomFactory CRoomFactory::GetInstance()

class CRoomFactory : public CFactory, public CSingleton< CRoomFactory > {
public:
	CRoomFactory() {}
	virtual ~CRoomFactory() {}

};
