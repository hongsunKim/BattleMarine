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
	CItemEx() {}
	virtual			~CItemEx() {}

	void			SetPos(SPosition o) { m_tPos = o; }
	SPosition		GetPos() { return m_tPos; }

	void			SetOwner(UINT32 o) { m_uiOwner = o; }
	UINT32			GetOwner() { return m_uiOwner; }

private:
	SPosition	m_tPos;
	UINT32		m_uiOwner;

};