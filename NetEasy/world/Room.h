/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../ReTypedefined.h"
#include "../GlobalVariable.h"

class CCommand;
class CPlayer;

class CRoom {
public:
	CRoom() : m_uiTopCount(0), m_uiId(0), m_bOffset(false), m_uiMaxUser(0), m_eModType(MOD_NONE),
		m_fTimeOut(0), m_eRoomState(ROOM_STATE_READY) {
		memset(m_pkMembers, 0, sizeof(m_pkMembers));
		memset(m_szName, 0, sizeof(m_szName));
	}

	virtual ~CRoom() {}

	virtual bool	Initialize();
	virtual bool	Release();
	virtual void	Clear();

	virtual bool	Update();

	virtual bool	Create(CPlayer&);
	virtual bool	Join(CPlayer&);
	virtual bool	Leave(CPlayer&);

	virtual bool	Broadcast(CCommand&, INT = 0, CPlayer* = NULL, CPlayer* = NULL)	{ return false; }

	CPlayer*		GetMember(UINT o)		{ if (o < (UINT)(iMAX_ROOM_MEMBERS)) return m_pkMembers[o]; else return NULL; }
	void			SetMember(UINT o, CPlayer&);
	CPlayer*		GetLeader()				{ return m_pkMembers[0]; }

	const char*		GetName()				{ return m_szName; }
	void
	SetName(const char* o) {
		memset(m_szName, 0, iROOM_NAME_LEN);
		memcpy(m_szName, o, iROOM_NAME_LEN);
		m_szName[iROOM_NAME_LEN] = '\0';
	}

	void			SetId(UINT o)			{ m_uiId = o; }
	UINT			GetId()					{ return m_uiId; }

	void			SetDoing(bool o)		{ m_bOffset = o; }
	bool			IsDoing()				{ return m_bOffset; }

	bool			IsAvailable()			{ return (0 < m_uiTopCount); }

	void			SetMaxUser(UINT o)		{ if ((UINT)(iMAX_ROOM_MEMBERS) > o) { m_uiMaxUser = o; } else { m_uiMaxUser = iMAX_ROOM_MEMBERS; } }
	UINT			GetMaxUser()			{ return m_uiMaxUser; }

	MOD_TYPE		GetModType()			{ return m_eModType; }
	void			SetModType(MOD_TYPE o)	{ m_eModType = o; }

	UINT			GetTopCount()			{ return m_uiTopCount; }

	FLOAT			GetTimeOut() { return m_fTimeOut; }
	void			SetTimeOut(FLOAT o) { m_fTimeOut = o; }
	FLOAT			TimeUpdate(FLOAT o);
	
	ROOM_STATE		GetRoomState() { return m_eRoomState; }
	void			SetRoomState(ROOM_STATE state) { m_eRoomState = state; }

	UINT			GetTeamPoint(TEAM_TYPE);
	void			SetTeamPoint(TEAM_TYPE, int);
	void			IncreaseTeamPoint(TEAM_TYPE, int point = 1	);
	void			ResetTeamPoint() { memset(m_uiTeamPoint, 0, sizeof(m_uiTeamPoint)); }

	UINT			GetTeamCount(TEAM_TYPE);

	//void			SetRoomMember();
protected:
	void			IncreasedTopCount()		{ ++m_uiTopCount; }
	void			DecreasedTopCount()		{ --m_uiTopCount; }

	void			SetTopCount(UINT o)		{ m_uiTopCount = o; }

	bool			InRange(UINT o)			{ return (o < m_uiTopCount); }

protected:
	CPlayer*		m_pkMembers[iMAX_ROOM_MEMBERS];

	UINT			m_uiTopCount;

private:
	UINT			m_uiId;	//< Room Key
	bool			m_bOffset;
	UINT			m_uiMaxUser;
	FLOAT			m_fTimeOut;
	ROOM_STATE		m_eRoomState;

	MOD_TYPE		m_eModType;

	char			m_szName[iROOM_NAME_LEN + 1];

	UINT			m_uiTeamPoint[TEAM_MAX];
};
