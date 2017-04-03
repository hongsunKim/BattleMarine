/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "../Enums.h"

class CItemEx : public CItem {
	
public:
	CItemEx()								{}
	virtual			~CItemEx()				{}

	void			SetPos(SPosition o)		{ m_tPos = o; }
	SPosition		GetPos()				{ return m_tPos; }

private:
	SPosition	m_tPos;

};