/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

class CConnectorEx : public CConnector {
public:
	CConnectorEx()				{}
	virtual ~CConnectorEx()		{}

	virtual bool			Disconnect(const SOCKET);

	virtual void			Launcher(CCommand*);

			static void*	New()					{ return new CConnectorEx; }

private:

};
