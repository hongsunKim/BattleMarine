/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "Protocol.h"
#include "Command.h"

class CTcpPacket {
public:
	CTcpPacket(UINT iKey_)	{}

	UINT	GetKey()		{ return m_tHeader.key; }
	UINT	GetSize()		{ return m_tHeader.size; }

	STcpPacketHeader&	GetPacketHeader()	{ return m_tHeader; }
	char*				GetHeader()			{ return (char*)&m_tHeader; }
	char*				GetData()			{ return (char*)&m_kCommand; }
	CCommand&			GetCommand()		{ return m_kCommand; }

	void				SetKey(UINT o)		{ m_tHeader.key = o; }
	void				SetSize(UINT o)		{ m_tHeader.size = o; }

public:
	STcpPacketHeader	m_tHeader;
	CCommand			m_kCommand;
};
