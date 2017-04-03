/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>
#include "../util/Utility.h"

class CRoomEx : public CRoom {
public:
	CRoomEx() {}
	virtual ~CRoomEx() {}

	virtual bool		Initialize();
	virtual bool		Release();
	virtual void		Clear();

	virtual bool		Update();

	virtual bool		Create(CPlayer&);
	virtual bool		Join(CPlayer&);
	virtual bool		Leave(CPlayer&);

	virtual bool		Broadcast(CCommand&, INT = 0, CPlayer* = NULL, CPlayer* = NULL);

	SRespawnPosition*	GetRespawnPosition(CPlayer&);
	SRespawnColor*		GetRespawnColor(CPlayer&);

	static void*		New()		{ return new CRoomEx; }

	bool				CheckWin(CPlayer* player = nullptr);

private:
	SRespawnPosition	m_tRespawnPosition[iMAX_ROOM_MEMBERS];
	SRespawnColor		m_tRespawnColor[iMAX_ROOM_MEMBERS];

};
