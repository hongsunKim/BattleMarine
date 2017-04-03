/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../Defines.h"
#include "../GlobalVariable.h"

#include "Protocol.h"

class CCommand {
public:
	CCommand()	{
		memset(m_acData, 0, iCOMMAND_DATA_SIZE);
	}

	~CCommand() {}

	UINT			GetOrder()			{ return UINT(m_tHeader.order); }
	UINT			GetExtra()			{ return UINT(m_tHeader.extra); }
	UINT			GetMission()		{ return UINT(m_tHeader.mission); }
	UINT			GetOption()			{ return UINT(m_tHeader.option); }

	SCommandHeader&	GetCommandHeader()	{ return m_tHeader; }
	char&			GetData()			{ return *m_acData; }
	char&			GetHeader()			{ return (char&)m_tHeader; }

	void			SetOrder(UINT o)	{ m_tHeader.order = UINT16(o); }
	void			SetExtra(UINT o)	{ m_tHeader.extra = UINT16(o); }
	void			SetMission(UINT o)	{ m_tHeader.mission = BYTE(o); }
	void			SetOption(UINT o)	{ m_tHeader.option = BYTE(o); }

private:
	SCommandHeader	m_tHeader;
	char			m_acData[iCOMMAND_DATA_SIZE];
};
