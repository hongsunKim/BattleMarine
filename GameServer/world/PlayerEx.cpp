/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "PlayerEx.h"
#include "../CommonHeader.h"

CPlayerEx::CPlayerEx() : m_eGradeType(GRADE_PLAYER), m_iRespawnIndex(0), m_fSteamPackTime(-1.0f) {
	if(false == isptr(m_pkRoomHandler)) {
		m_pkRoomHandler = new CRoomHandlerEx(*this);
	}
}

CPlayerEx::~CPlayerEx() {
	if (isptr(m_pkRoomHandler)) {
		SAFE_DELETE(m_pkRoomHandler);
	}
}

void
CPlayerEx::Clear() {
	CPlayer::Clear();

	m_eGradeType = GRADE_PLAYER;
	m_fSteamPackTime = -1.0f;
	m_iRespawnIndex = 0;
}
