/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "Connector.h"

class CListener : public CConnector {
public:
	CListener() {}
	virtual ~CListener() {}

	virtual INT			Listen(const char*, INT);
	virtual bool		Read();
	virtual bool		Disconnect(const SOCKET) { return true; }

private:
};
