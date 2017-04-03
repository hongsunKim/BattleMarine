/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

class CRoomHandlerEx : public CRoomHandler {
public:
	CRoomHandlerEx(CPlayer& o) : CRoomHandler(o) {}
	virtual ~CRoomHandlerEx() {}

	virtual bool	Join();
	virtual void	Leave(CPlayer* = NULL);

			bool	Broadcast(CCommand&, INT = 0, CPlayer* = NULL, CPlayer* = NULL);

private:

};
