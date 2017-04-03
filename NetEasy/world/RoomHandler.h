/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../ReTypedefined.h"
#include "../GlobalVariable.h"

class CRoom;
class CPlayer;
class CCommand;

class CRoomHandler {
public:
	CRoomHandler(CPlayer& o) : m_rkBody(o), m_pkRoom(NULL), m_iOffset(0) {}
	virtual ~CRoomHandler() {}

	virtual bool	Join();
	virtual void	Leave(CPlayer* = NULL);

	virtual void	Clear();

			void	SetOffset(INT o)		{ m_iOffset = o; }
			INT		GetOffset()				{ return m_iOffset; }

			void	SetRoom(CRoom* o)		{ m_pkRoom = o; }
			CRoom*	GetRoom()				{ return m_pkRoom; }

			bool	InRoom()				{ return (isptr(GetRoom())); }

protected:
		CPlayer&	GetBody()			{ return m_rkBody; }

protected:
		CPlayer&	m_rkBody;
		CRoom*		m_pkRoom;
		INT			m_iOffset;

};
