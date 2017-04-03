/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "ChannelMgr.h"

#include "../CommonHeader.h"

bool
CChannelMgr::Initialize() {
	//for (UINT j = 0; j < (UINT)(iMAX_ROOMS); ++j) {
	//	m_iEmptyRoomList[j] = -1;
	//}

	for (UINT j = 0; j < (UINT)(iMAX_ROOMS); ++j) {
		m_iEmptyRoomList[j] = -1;
		m_pkRoomList[j] = (CRoom*)g_kRoomFactory.Create();
		if (isptr(m_pkRoomList[j])) {
			if (m_pkRoomList[j]->Initialize()) {
				m_pkRoomList[j]->SetId(j);
			} else {
				OUTPUT("[" << j << "] critical error: room created: failed: system memory is not enough");
				for (UINT l = 0; l<j; ++l) {
					SAFE_DELETE_RELEASE(m_pkRoomList[l]);
				}
				return false;
			}
		} else {
			OUTPUT("[" << j << "] critical error: room created failed: system memory is not enough");
			for (UINT l = 0; l<j; ++l) {
				SAFE_DELETE_RELEASE(m_pkRoomList[l]);
			}
			return false;
		}
	}
	return true;
}

bool
CChannelMgr::Release() {
	for (UINT j = 0; j < (UINT)(iMAX_ROOMS); ++j) {
		m_iEmptyRoomList[j] = -1;
		SAFE_DELETE_RELEASE(m_pkRoomList[j]);
	}
	return true;
}

void
CChannelMgr::Update() {
	for (INT i = 0; i<m_iRoomTopIndex; ++i) {
		if(m_pkRoomList[i]->IsAvailable()) {
			m_pkRoomList[i]->Update();
		}
	}
}

CRoom*
CChannelMgr::NewRoom() {
	if (0 < m_iEmptyRoomCount) {
		--m_iEmptyRoomCount;
		INT iIndex = m_iEmptyRoomList[m_iEmptyRoomCount];
		m_iEmptyRoomList[m_iEmptyRoomCount] = -1;

		if ((0 <= iIndex) && (m_iRoomTopIndex > iIndex)) {
			++m_iUsedRoomCount;
			OUTPUT("new room[" << iIndex << "]: OK: count: " << m_iUsedRoomCount << ", id: " << m_pkRoomList[iIndex]->GetId() << " : " << m_pkRoomList[iIndex]->GetTopCount());
			return m_pkRoomList[iIndex];
		}
	}

	if ((0 <= m_iRoomTopIndex) && (iMAX_ROOMS > m_iRoomTopIndex)) {
		INT iIndex = m_iRoomTopIndex;

		++m_iRoomTopIndex;
		++m_iUsedRoomCount;

		return m_pkRoomList[iIndex];
	} else {
		OUTPUT("critical error: room is full: U: " << m_iUsedRoomCount << " - T: " << m_iRoomTopIndex << " - E: " << m_iEmptyRoomCount);
	}
	return NULL;
}

bool
CChannelMgr::DeleteRoom(UINT uiIndex_) {
	if (uiIndex_ < m_iRoomTopIndex) {
		if (uiIndex_ == UINT(m_iRoomTopIndex - 1)) {
			--m_iRoomTopIndex;
		} else {
			m_iEmptyRoomList[m_iEmptyRoomCount] = uiIndex_;
			++m_iEmptyRoomCount;
		}

		--m_iUsedRoomCount;
		TRACE("room is deleted: OK: ");

		m_pkRoomList[uiIndex_]->Clear();
		return true;
	} else {
		OUTPUT("room delete: failed: room index is wrong: (" << uiIndex_ << ") - U: " << m_iUsedRoomCount << " - T: " << m_iRoomTopIndex << " - E: " << m_iEmptyRoomCount);
	}
	return false;
}

CRoom*
CChannelMgr::FindRoom(UINT uiIndex_) {
	if (uiIndex_ < iMAX_ROOMS) {
		return m_pkRoomList[uiIndex_];
	} else {
		OUTPUT("error: invalid condition: id: " << uiIndex_ << ", index: " << uiIndex_);
	}
	return NULL;
}

CRoom*
CChannelMgr::FindMatchRoom() {
	for (UINT i = 0; i < m_iRoomTopIndex; ++i) {
		if (isptr(m_pkRoomList[i])) {
			if ((0 < m_pkRoomList[i]->GetTopCount()) && (m_pkRoomList[i]->GetTopCount() < m_pkRoomList[i]->GetMaxUser())) {
				// Auth Matching 선택 가능하게 하려면 IsAuthMatch() flag 넣고 검색 하도록 처리
				return m_pkRoomList[i];
			}
		}
	}
	return NULL;
}

bool
CChannelMgr::InUser(CPlayer& rkPlayer_) {
	if (0 <= rkPlayer_.GetChannelIndex()) {
		OutUser(rkPlayer_);
	}

	if (0 < m_iEmptyUserCount) {
		if (0 <= m_iEmptyUserList[m_iEmptyUserCount - 1]) {
			m_pkUserList[m_iEmptyUserList[m_iEmptyUserCount - 1]] = &rkPlayer_;
			rkPlayer_.SetUserIndex(m_iEmptyUserList[m_iEmptyUserCount - 1]);
			m_iEmptyUserList[m_iEmptyUserCount - 1] = -1;
			--m_iEmptyUserCount;
		} else {
			OUTPUT("critical error: index is wrong: ");
			return false;
		}
	} else {
		m_pkUserList[m_iUserTopIndex] = &rkPlayer_;
		rkPlayer_.SetUserIndex(m_iUserTopIndex);
		++m_iUserTopIndex;
	}
	rkPlayer_.SetChannelIndex(0);

	CCommand kCommand;
	kCommand.SetOrder(INFO_USER_LIST);
	kCommand.SetExtra(IN_);

	SInfoUserInGsToCl& rtSData = (SInfoUserInGsToCl&)kCommand.GetData();
	rtSData.target = rkPlayer_.GetKey();
	rtSData.SetName(rkPlayer_.GetName());

	Broadcast(&rkPlayer_, kCommand, sizeof(SInfoUserInGsToCl));

	OUTPUT("CHANNEL: IN: key: " << rkPlayer_.GetKey() << ", channel index: " << rkPlayer_.GetChannelIndex() << ", user index: " << rkPlayer_.GetUserIndex());

	return true;
}

void
CChannelMgr::OutUser(CPlayer& rkPlayer_) {
	INT iIndex = rkPlayer_.GetUserIndex();
	if (0 <= iIndex) {
		m_pkUserList[iIndex] = NULL;

		rkPlayer_.SetChannelIndex(-1);
		rkPlayer_.SetUserIndex(-1);

		if (iIndex == m_iUserTopIndex - 1) {
			--m_iUserTopIndex;
		} else {
			m_iEmptyUserList[m_iEmptyUserCount] = iIndex;
			++m_iEmptyUserCount;
		}

		CCommand kCommand;
		kCommand.SetOrder(INFO_USER_LIST);
		kCommand.SetExtra(OUT_);

		SInfoUserOutGsToCl& rtSData = (SInfoUserOutGsToCl&)kCommand.GetData();
		rtSData.target = rkPlayer_.GetKey();

		Broadcast(&rkPlayer_, kCommand, sizeof(SInfoUserOutGsToCl));

		OUTPUT("CHANNEL: OUT: key: " << rkPlayer_.GetKey() << ", channel user index: " << iIndex);
	} else {
		OUTPUT("critical error: index is wrong: " << rkPlayer_.GetKey() << " : " << rkPlayer_.GetChannelIndex());
	}
}

void
CChannelMgr::GetRoomList(CPlayer& rkPlayer_) {
	if (0 <= rkPlayer_.GetChannelIndex()) {
		CCommand kCommand;
		kCommand.SetOrder(ROOM_LIST);
		kCommand.SetMission(0);
		SRoomListGsToCl& rtSData = (SRoomListGsToCl&)kCommand.GetData();

		kCommand.SetExtra(NEW);
		INT iCount = 0;
		for (INT i = 0; i<m_iRoomTopIndex; ++i) {
			if (m_pkRoomList[i]->IsAvailable()) {
				if (iCount >= iMAX_PACKET_ROOM_LIST) {
					TRACE("iMAX_PACKET_ROOM_LIST: count: " << iMAX_PACKET_ROOM_LIST << ", overflow: " << iCount);
					kCommand.SetOption(iMAX_PACKET_ROOM_LIST);
					rkPlayer_.Send(kCommand, sizeof(SRoomListGsToCl));
					iCount = 0;
					kCommand.SetExtra(CHANGE);
				}

				rtSData.list[iCount].id = m_pkRoomList[i]->GetId();
				rtSData.list[iCount].max = m_pkRoomList[i]->GetMaxUser();
				rtSData.list[iCount].mod = m_pkRoomList[i]->GetModType();

				rtSData.list[iCount].SetName(m_pkRoomList[i]->GetName());

				if (m_pkRoomList[i]->IsDoing()) {
					rtSData.list[iCount].offset = 1;
				} else {
					rtSData.list[iCount].offset = 0;
				}

				rtSData.list[iCount].state = m_pkRoomList[i]->GetRoomState();

				++iCount;
			}
		}

		if (0 < iCount) {
			kCommand.SetOption(iCount);
			rkPlayer_.Send(kCommand, sizeof(SRoomInfo) * iCount);
			TRACE("NEW or CHANGE: ");

			kCommand.SetExtra(DONE);
			kCommand.SetOption(0);
			rkPlayer_.Send(kCommand);
		}
		else {
			if (NEW == kCommand.GetExtra()) {
				kCommand.SetExtra(EMPTY);
				kCommand.SetOption(0);
				rkPlayer_.Send(kCommand);
			}
		}
	}
}

bool
CChannelMgr::GetRoomMemberList(CPlayer& rkPlayer_) {
	if (0 <= rkPlayer_.GetChannelIndex()) {
		CRoomHandler* pkRoomHandler = rkPlayer_.GetRoomHandler();
		if (isptr(pkRoomHandler)) {
			CRoom* pkRoom = pkRoomHandler->GetRoom();
			if (isptr(pkRoom)) {
				INT iCount = 0;
				CPlayer* pkPlayer = NULL;
				CConnector*	pkConnector = NULL;

				CCommand kCommand;
				kCommand.SetOrder(ROOM_LIST);
				kCommand.SetExtra(NEW);
				kCommand.SetMission(1);	// 1번은 맴버 목록.

				SRoomMemberListGsToCl& rtSData = (SRoomMemberListGsToCl&)kCommand.GetData();

				for (UINT i = 0; i < pkRoom->GetTopCount(); ++i) {
					pkPlayer = pkRoom->GetMember(i);
					if (isptr(pkPlayer)) {
						if (pkRoom != pkPlayer->GetRoomHandler()->GetRoom()) {
							OUTPUT("critical error: unit is not in this room: " << pkRoom->GetTopCount());
							return false;
						}

						pkConnector = pkPlayer->GetConnector();
						if (isptr(pkConnector)) {
							if (iCount >= iMAX_PACKET_ROOM_MEMBER_LIST) {
								TRACE("iMAX_PACKET_ROOM_MEMBER_LIST: count: " << iMAX_PACKET_ROOM_MEMBER_LIST << ", overflow: " << iCount);
								kCommand.SetOption(iMAX_PACKET_ROOM_MEMBER_LIST);
								rkPlayer_.Send(kCommand, iCount * sizeof(SRoomMember));
								iCount = 0;
								kCommand.SetExtra(CHANGE);
							}

							rtSData.list[iCount].actor = pkPlayer->GetKey();
							rtSData.list[iCount].SetName(pkPlayer->GetName());
							rtSData.list[iCount].status = pkPlayer->GetStatus();
							rtSData.list[iCount].team = pkPlayer->GetTeamType();

							rtSData.list[iCount].pos.x = pkPlayer->GetPosition().x;
							rtSData.list[iCount].pos.y = pkPlayer->GetPosition().y;

							rtSData.list[iCount].color.A = pkPlayer->GetColor().A;
							rtSData.list[iCount].color.R = pkPlayer->GetColor().R;
							rtSData.list[iCount].color.G = pkPlayer->GetColor().G;
							rtSData.list[iCount].color.B = pkPlayer->GetColor().B;

							OUTPUT("[" << pkPlayer->GetName() << ":" << pkPlayer->GetKey() << ":" << pkPlayer->GetStatus() << "] pos: (" << pkPlayer->GetPosition().x << ":" << pkPlayer->GetPosition().y << ", color: (" << pkPlayer->GetColor().A << ":" << pkPlayer->GetColor().R << ":" << pkPlayer->GetColor().G << ":" << pkPlayer->GetColor().B << ")");

							++iCount;
						}
					} else {
						OUTPUT("[" << i << "] room's member is null: " << pkRoom->GetTopCount());
						break;
					}
				}

				if (0 < iCount) {
					kCommand.SetOption(iCount);
					rkPlayer_.Send(kCommand, iCount * sizeof(SRoomMember));
					TRACE("NEW or CHANGE: ");

					kCommand.SetExtra(DONE);
					kCommand.SetOption(0);
					SRoomMemberLeaderGsToCl& rtLeaderData = (SRoomMemberLeaderGsToCl&)kCommand.GetData();
					if (isptr(pkRoom->GetLeader())) {
						rtLeaderData.leader = pkRoom->GetLeader()->GetKey();
					}

					rkPlayer_.Send(kCommand, sizeof(SRoomMemberLeaderGsToCl));
				} else {
					if (NEW == kCommand.GetExtra()) {
						kCommand.SetExtra(EMPTY);
						kCommand.SetOption(0);
						rkPlayer_.Send(kCommand);
					}
				}
			}
		}
	}
	return true;
}

void
CChannelMgr::GetUserList(CPlayer& rkPlayer_) {
	if (0 <= rkPlayer_.GetChannelIndex()) {
		CCommand kCommand;
		kCommand.SetOrder(INFO_USER_LIST);
		kCommand.SetExtra(NONE);

		SInfoUserListGsToCl& rtSData = (SInfoUserListGsToCl&)kCommand.GetData();
		rtSData.actor = rkPlayer_.GetKey();

		// 들어온 클라이언트에게 플레이어 목록 전송
		for (INT i = 0; i < m_iUserTopIndex; ++i) {
			if (isptr(m_pkUserList[i])) {
				rtSData.target = m_pkUserList[i]->GetKey();
				rtSData.SetName(m_pkUserList[i]->GetName());

				rkPlayer_.Send(kCommand, sizeof(SInfoUserListGsToCl));
			}
		}
	}
}

//장현우 구현
void
CChannelMgr::RoomSync(CPlayer& rkPlayer_, CCommand& rkCommand_)
{
	if (0 <= rkPlayer_.GetChannelIndex())
	{		
		CCommand kCommand;
		kCommand.SetOrder(rkCommand_.GetOrder());
		kCommand.SetExtra(rkCommand_.GetExtra());

		SRoomSyncGsToCl& rtSData = (SRoomSyncGsToCl&)kCommand.GetData();

		if (kCommand.GetExtra() == CONNECT)
		{
			for (UINT i = 0; i < GetRoomTopIndex(); ++i)
			{
				for (UINT j = 0; j < m_pkRoomList[i]->GetTopCount(); ++j)
				{
					rtSData.actor = m_pkRoomList[i]->GetMember(j)->GetKey();
					rkPlayer_.Send(kCommand, sizeof(SRoomSyncGsToCl));
				}
			}
		}
		else if (kCommand.GetExtra() == NONE)
		{
			rtSData.actor = rkPlayer_.GetKey();
			g_kChannelMgr.Broadcast(&rkPlayer_, kCommand, sizeof(SRoomSyncGsToCl));
		}
		else if (kCommand.GetExtra() == OUT_)
		{
			rtSData.actor = rkPlayer_.GetKey();
			g_kChannelMgr.Broadcast(&rkPlayer_, kCommand, sizeof(SRoomSyncGsToCl));
		}

	}
}

void
CChannelMgr::Broadcast(CPlayer* pkPlayer_, CCommand& rkCommand_, INT iSize_) {
	if (isptr(pkPlayer_)) {
		if (isptr(pkPlayer_->GetRoomHandler())) {
			for (INT i = 0; i<m_iUserTopIndex; ++i) {
				if (isptr(m_pkUserList[i])) {
					if (m_pkUserList[i] != pkPlayer_) {
						if (0 < m_pkUserList[i]->GetKey()) {
							OUTPUT("send: key: " << m_pkUserList[i]->GetKey());
							m_pkUserList[i]->Send(rkCommand_, iSize_);
						}
					}
				}
			}
		}
	}
}

void
CChannelMgr::Shutdown() {
	for (INT j = 0; j<m_iUserTopIndex; ++j) {
		if (isptr(m_pkUserList[j])) {
			if (0 < m_pkUserList[j]->GetKey()) {
				if(isptr(m_pkUserList[j]->GetConnector())) {
					m_pkUserList[j]->GetConnector()->Disconnect(m_pkUserList[j]->GetConnector()->GetSocket());
				}
			}
		}
	}
}
