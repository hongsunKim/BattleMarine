/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

CPlayer::CPlayer() : m_pkRoomHandler(NULL), m_uiIndex(0), m_uiKey(0), m_pkConnector(NULL)
, m_uiAid(0), m_tmLoginTime(0), m_tmLogoutTime(0)
, m_eStatusType(STATUS_EXIT), m_eDirection(DIRECTION_UP), m_eTeamType(TEAM_NONE)
, m_iChannelIndex(-1), m_iUserIndex(-1)
, m_iCurLife(iPLAYER_MAX_LIFE), m_iMaxLife(iPLAYER_MAX_LIFE), m_iPower(iPLAYER_HIT_POWER)
, m_ulSteamPackTiem(100), m_bSteamPack(false), m_bIsRoom(false), m_uiPoint(1000), m_uiCurAmmo(50), m_uiMaxAmmo(50), m_eGameResult(GAME_RESULT_NONE)
{
	memset(m_szName, 0, iPLAYER_NAME_LEN);
}

CPlayer::~CPlayer()
{
	SAFE_DELETE(m_pkRoomHandler);
}

void
CPlayer::Clear() {
	// 아직 적용 안했음
	memset(&m_tPosition, 0, sizeof(SPosition));
	memset(&m_tColor, 0, sizeof(SColor));
	memset(&m_tMapIdx, 0, sizeof(SPosition));

	m_iMaxLife = iPLAYER_MAX_LIFE;
	m_iCurLife = iPLAYER_MAX_LIFE;
	m_iPower = iPLAYER_HIT_POWER;

	m_uliDeathStartTick = 0;

	m_eStatusType = STATUS_EXIT;
	m_eDirection = DIRECTION_UP;
	m_eTeamType = TEAM_NONE;
	m_eGameResult = GAME_RESULT_NONE;
}

INT
CPlayer::Send(CCommand& rkCommand_, INT iSize_)
{
	CConnector* pkConnector = GetConnector();
	if(isptr(pkConnector)) {
		return pkConnector->Send(rkCommand_, iSize_);
	}

	return -2;
}

void
CPlayer::Disconnect() {
	CConnector* pkConnector = GetConnector();
	if (isptr(pkConnector)) {
		pkConnector->Disconnect(pkConnector->GetSocket());
	}
}

void
CPlayer::SetPosition(SPosition o) {
	m_tPosition.x = o.x;
	m_tPosition.y = o.y;
	m_tMapIdx.x = (-float(m_tPosition.x) / 10.f) - 0.5;
	m_tMapIdx.y = (-float(m_tPosition.y) / 10.f) - 0.5;
}

void
CPlayer::SetPosition(INT o, INT p) {
	m_tPosition.x = o;
	m_tPosition.y = p;
	m_tMapIdx.x = (-float(m_tPosition.x) / 10.f) - 0.5;
	m_tMapIdx.y = (-float(m_tPosition.y) / 10.f) - 0.5;
}
