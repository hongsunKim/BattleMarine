/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#define g_kChannelMgr CChannelMgr::GetInstance()

#include <NetEasy/CommonHeader.h>

#include "../GlobalVariable.h"

class CChannelMgr : public CSingleton< CChannelMgr > {
public:
	CChannelMgr() {
		for (UINT j = 0; j < (UINT)(iMAX_CHANNEL_USERS); ++j) {
			m_pkUserList[j] = NULL;
			m_iEmptyUserList[j] = -1;
		}

		m_iUserMaxCount = 0;

		m_iUserTopIndex = 0;
		m_iEmptyUserCount = 0;

		m_iUsedRoomCount = 0;

		m_iRoomTopIndex = 0;
		m_iEmptyRoomCount = 0;
	}

	virtual ~CChannelMgr() {
		for (UINT j = 0; j < (UINT)(iMAX_ROOMS); ++j) {
			SAFE_DELETE_RELEASE(m_pkRoomList[j]);
		}
	}

	bool			Initialize();
	bool			Release();

	void			Update();

	CRoom*			NewRoom();
	bool			DeleteRoom(UINT);

	CRoom*			FindRoom(UINT);
	CRoom*			FindMatchRoom();

	bool			InUser(CPlayer&);
	void			OutUser(CPlayer&);

	void			GetRoomList(CPlayer&);
	bool			GetRoomMemberList(CPlayer&);
	void			GetUserList(CPlayer&);

	INT				GetUsedRoomCount() { return m_iUsedRoomCount; }
	INT				GetRoomTopIndex() { return m_iRoomTopIndex; }
	INT				GetEmptyRoomCount() { return m_iEmptyRoomCount; }

	void			Broadcast(CPlayer*, CCommand&, INT = 0);

	void			Shutdown();
	
	void			RoomSync(CPlayer&, CCommand&);
private:
	CRoom*		m_pkRoomList[iMAX_ROOMS];
	INT			m_iEmptyRoomList[iMAX_ROOMS];

	INT			m_iUsedRoomCount;
	INT			m_iRoomTopIndex;
	INT			m_iEmptyRoomCount;

	CPlayer*	m_pkUserList[iMAX_CHANNEL_USERS];
	INT			m_iEmptyUserList[iMAX_CHANNEL_USERS];

	INT			m_iUserMaxCount;
	INT			m_iUserTopIndex;
	INT			m_iEmptyUserCount;

};
