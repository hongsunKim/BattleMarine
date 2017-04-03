/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../ReTypedefined.h"
#include "../GlobalVariable.h"
#include "../Enums.h"
#include "../net/Connector.h"
#include "../util/Utility.h"

class CRoomHandler;

class CPlayer {
public:
	CPlayer();
	virtual ~CPlayer();

	virtual void	Clear();
	virtual void	Update()						{}

	UINT			GetIndex()						{ return m_uiIndex; }
	void			SetIndex(UINT o)				{ m_uiIndex = o; }

	UINT			GetKey()						{ return m_uiKey; }
	void			SetKey(UINT o)					{ m_uiKey = o; }

	CConnector*		GetConnector()					{ return m_pkConnector; }
	void			SetConnector(CConnector* o)		{ m_pkConnector = o; }

	UINT			GetAid()						{ return m_uiAid; }
	void			SetAid(UINT o)					{ m_uiAid = o; }

	time_t			GetLoginTime()					{ return m_tmLoginTime; }
	void			SetLoginTime(time_t o)			{ m_tmLoginTime = o; }

	time_t			GetLogoutTime()					{ return m_tmLogoutTime; }
	void			SetLogoutTime(time_t o)			{ m_tmLogoutTime = o; }

	CRoomHandler*	GetRoomHandler()				{ return m_pkRoomHandler; }

	const char*		GetName()						{ return m_szName; }
	void			SetName(const char* o)			{ memcpy(m_szName, o, iPLAYER_NAME_LEN); m_szName[iPLAYER_NAME_LEN] = '\0'; }

	INT				Send(CCommand&, INT = 0);
	void			Disconnect();

	STATUS_TYPE		GetStatus()						{ return m_eStatusType; }
	void			SetStatus(STATUS_TYPE o)		{ m_eStatusType = o; }

	DIRECTION_TYPE	GetDirection()					{ return m_eDirection; }
	void			SetDirection(DIRECTION_TYPE o)	{ m_eDirection = o; }

	SPosition&		GetPosition()					{ return m_tPosition; }
	void			SetPosition(SPosition o);
	void			SetPosition(INT o, INT p);

	INT				GetPosX()						{ return m_tPosition.x; }
	INT				GetPosY()						{ return m_tPosition.y; }

	SPosition&		GetMapIdx()						{ return m_tMapIdx; }

	INT				GetMapIdxX()					{ return m_tMapIdx.x; }
	INT				GetMapIdxY()					{ return m_tMapIdx.y; }

	SColor&			GetColor()						{ return m_tColor; }
	void			SetColor(SColor o)				{ m_tColor.A = o.A; m_tColor.R = o.R; m_tColor.G = o.G; m_tColor.B = o.B; }

	INT				GetUserIndex()					{ return m_iUserIndex;}
	void			SetUserIndex(INT o)				{ m_iUserIndex = o; }

	INT				GetChannelIndex()				{ return m_iChannelIndex; }
	void			SetChannelIndex(INT o)			{ m_iChannelIndex = o; }

	TEAM_TYPE		GetTeamType()					{ return m_eTeamType; }
	void			SetTeamType(TEAM_TYPE o)		{ m_eTeamType = o; }

	INT				GetMaxLife()					{ return m_iMaxLife; }
	void			SetMaxLife(INT o)				{ m_iMaxLife = o; }

	INT				GetCurLife()					{ return m_iCurLife; }
	void			SetCurLife(INT o)				{ m_iCurLife = o; }
	
	INT				GetPower()						{ return m_iPower; }
	void			SetPower(INT o)					{ m_iPower = o; }

	INT				Damaged(INT o)					{ m_iCurLife -= o; if (m_iCurLife < 0) { m_iCurLife = 0; }; return o; }

	tick_t			GetDeathStartTick()				{ return m_uliDeathStartTick; }
	void			SetDeathStartTick(tick_t o)		{ m_uliDeathStartTick = o; }

	tick_t			GetIsSteamPackTime()			{ return m_ulSteamPackTiem; }
	void			SetISSteamPackTime(tick_t o)	{ m_ulSteamPackTiem = o; }

	bool			GetIsSteamPack()				{ return m_bSteamPack; }
	void			SetISSteamPack(bool o)			{ m_bSteamPack = o; }

	bool			GetIsRoom()						{ return m_bIsRoom; }
	void			SetIsRoom(bool o)				{ m_bIsRoom = o; }

	UINT			GetPoint()						{ return m_uiPoint; }
	void			SetPoint(UINT o)				{ m_uiPoint = o; }

	UINT			GetCurAmmo()						{ return m_uiCurAmmo; }
	void			SetCurAmmo(UINT o)					{ m_uiCurAmmo += o; if (m_uiCurAmmo >= m_uiMaxAmmo) m_uiCurAmmo = m_uiMaxAmmo; }

	UINT			GetMaxAmmo()					{ return m_uiMaxAmmo; }
	void			SetMaxAmmo(UINT o)					{ m_uiMaxAmmo = o; }

	GAME_RESULT		GetResult() { return m_eGameResult; }
	void			SetResult(GAME_RESULT o) { m_eGameResult = o; }

protected:
	CRoomHandler*	m_pkRoomHandler;
	SPosition		m_tPosition;
	SColor			m_tColor;
	SPosition		m_tMapIdx;

	INT				m_iMaxLife;
	INT				m_iCurLife;

	INT				m_iPower;

	tick_t			m_uliDeathStartTick;
	//tick_t		m_uliDeathEndTick;

	tick_t			m_ulSteamPackTiem;
	bool			m_bSteamPack;
	bool			m_bIsRoom;

	UINT			m_uiCurAmmo;
	UINT			m_uiMaxAmmo;

private:
	UINT			m_uiIndex;

	UINT			m_uiKey;
	CConnector*		m_pkConnector;

	UINT			m_uiAid;

	time_t			m_tmLoginTime;
	time_t			m_tmLogoutTime;

	STATUS_TYPE		m_eStatusType;

	DIRECTION_TYPE	m_eDirection;
	TEAM_TYPE		m_eTeamType;

	INT				m_iChannelIndex;
	INT				m_iUserIndex;

	char			m_szName[iPLAYER_NAME_LEN + 1];

	UINT			m_uiPoint;

	GAME_RESULT		m_eGameResult;
};
