/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

bool
CRoom::Initialize() {
	Clear();
	return true;
}

bool
CRoom::Release() {
	for (UINT i = 0; i < GetTopCount(); ++i) {
		if (isptr(m_pkMembers[i])) {
			m_pkMembers[i] = NULL;
		} else {
			TRACE("critical error: player[" << i << "] is null: " << GetTopCount());
		}
	}
	return true;
}

void
CRoom::Clear() {
	for (UINT i = 0; i < GetTopCount(); ++i) {
		CPlayer* pkPlayer = m_pkMembers[i];
		if (isptr(pkPlayer)) {
			if (isptr(pkPlayer->GetRoomHandler())) {
				pkPlayer->GetRoomHandler()->Clear();
			}
		}
	}

	memset(m_pkMembers, 0, sizeof(m_pkMembers));
	m_uiTopCount = 0;

	m_bOffset = false;
	m_uiMaxUser = 0;
	m_eModType = MOD_NONE;
	m_eRoomState = ROOM_STATE_READY;
	memset(m_uiTeamPoint, 0, sizeof(m_uiTeamPoint));
}

bool
CRoom::Update() {
	//for (UINT i = 0; i < GetTopCount(); ++i) {
	//	CPlayer* pkPlayer = m_pkMembers[i];
	//	if (isptr(pkPlayer)) {
	//		if (isptr(pkPlayer->GetRoomHandler())) {
	//			if (isptr(pkPlayer->GetRoomHandler()->GetRoom())) {
	//				if (isptr(pkPlayer->GetIsSteamPack())) {
	//					//pkPlayer->SetISSteamPackTime(pkPlayer->GetIsSteamPackTime() - )
	//					
	//				}
	//			}
	//		}
	//	}
	//}

	return true;
}

bool
CRoom::Create(CPlayer& rkPlayer_) {
	CRoomHandler* pkRoomHandler = rkPlayer_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		if (false == isptr(pkRoomHandler->GetRoom())) {
			m_pkMembers[0] = &rkPlayer_;

			pkRoomHandler->SetRoom(this);
			pkRoomHandler->SetOffset(0);

			rkPlayer_.SetIsRoom(true);

			// 플레이어 상태도 변경 필요.
			// STATUS_READY

			IncreasedTopCount();

			return true;
		} else {
			OUTPUT("critical error: in room");
		}
	} else {
		OUTPUT("critical error: handler is null");
	}
	return false;
}

bool
CRoom::Join(CPlayer& rkPlayer_) {
	//if (GetTopCount() < GetMaxUser()) {
		CRoomHandler* pkRoomHandler = rkPlayer_.GetRoomHandler();
		if (isptr(pkRoomHandler)) {
			if (false == isptr(pkRoomHandler->GetRoom())) {
				pkRoomHandler->SetRoom(this);
				pkRoomHandler->SetOffset(GetTopCount());

				if (pkRoomHandler->Join()) {
					m_pkMembers[GetTopCount()] = &rkPlayer_;
					IncreasedTopCount();

					OUTPUT("Join OK: [" << rkPlayer_.GetKey() << "] : " << GetTopCount() << " < " << iMAX_ROOM_MEMBERS);

					return true;
				} else {
					pkRoomHandler->Clear();
				}
			}
		}
	//}
	return false;
}

bool
CRoom::Leave(CPlayer& rkPlayer_) {
	CRoomHandler* pkRoomHandler = rkPlayer_.GetRoomHandler();
	if (isptr(pkRoomHandler)) {
		UINT uiOutIndex = pkRoomHandler->GetOffset();
		if (InRange(uiOutIndex)) {
			if (&rkPlayer_ == m_pkMembers[uiOutIndex]) {
				DecreasedTopCount();

				if (0 >= GetTopCount()) {
					OUTPUT("room clear: ");
					pkRoomHandler->Clear();
				} else {
					if (uiOutIndex == GetTopCount()) {
						m_pkMembers[GetTopCount()] = NULL;
						pkRoomHandler->Leave();
						OUTPUT("out unit index: " << GetTopCount());
					} else {
						CRoomHandler* pkNewRoomHandler = NULL;
						if (&rkPlayer_ == m_pkMembers[0]) {
							// 방장이 나갈 경우.
							UINT uiIndex = 1;

							if (3 > GetTopCount()) {
								if (2 != GetTopCount()) {
									uiIndex = 0;
								}
							}

							if ((0 < uiIndex) && (uiIndex <= GetTopCount())) {
								m_pkMembers[0] = m_pkMembers[uiIndex];
								m_pkMembers[uiIndex] = NULL;
								pkNewRoomHandler = m_pkMembers[0]->GetRoomHandler();
								if (isptr(pkNewRoomHandler)) {
									pkNewRoomHandler->SetOffset(0);
								}

								if (uiIndex < GetTopCount()) {
									m_pkMembers[uiIndex] = m_pkMembers[GetTopCount()];
									m_pkMembers[GetTopCount()] = NULL;
									pkNewRoomHandler = m_pkMembers[uiIndex]->GetRoomHandler();
									if (isptr(pkNewRoomHandler)) {
										pkNewRoomHandler->SetOffset(uiIndex);
									}
								}

								OUTPUT("Leave OK: ");
								OUTPUT("leader: out player: name: " << rkPlayer_.GetName());
								OUTPUT("leader: in player: name: " << m_pkMembers[0]->GetName() << " (" << uiIndex << "-> 0");
								OUTPUT("leader: move player: name: " << m_pkMembers[uiIndex]->GetName() << " (" << GetTopCount() << " -> " << uiIndex << ")");

								// 빠져나간 플레이어와 새로운 방장을 함께 전달할 경우 각 클라이언트들은 동일한 갱신이 가능.
								pkRoomHandler->Leave(m_pkMembers[0]);
							} else {
								// 방안에 아무도 없음.

								m_pkMembers[0] = m_pkMembers[GetTopCount()];
								m_pkMembers[GetTopCount()] = NULL;

								pkNewRoomHandler = m_pkMembers[0]->GetRoomHandler();
								if (isptr(pkNewRoomHandler)) {
									pkNewRoomHandler->SetOffset(0);
								}

								OUTPUT("Leave OK: ");
								pkRoomHandler->Leave(m_pkMembers[0]);
							}
							return true;
						}

						OUTPUT("switch a member position in room: " << uiOutIndex << " <-> " << GetTopCount());
						m_pkMembers[uiOutIndex] = m_pkMembers[GetTopCount()];
						m_pkMembers[GetTopCount()] = NULL;
						pkNewRoomHandler = m_pkMembers[uiOutIndex]->GetRoomHandler();
						if (isptr(pkNewRoomHandler)) {
							pkNewRoomHandler->SetOffset(uiOutIndex);
						}
						pkRoomHandler->Leave();
					}
				}
				return true;
			}
		} else {
			OUTPUT("critical error: offset is error: ");
		}
	}
	return false;
}


void
CRoom::SetMember(UINT o, CPlayer& p)
{
	if (o > (UINT)(iMAX_ROOM_MEMBERS)) return;

	m_pkMembers[o] = &p;
	//IncreasedTopCount();
}

FLOAT
CRoom::TimeUpdate(FLOAT o)
{
	if (0 < m_fTimeOut) {
		m_fTimeOut -= o;
		return m_fTimeOut;
	}
}

UINT			
CRoom::GetTeamPoint(TEAM_TYPE team)
{
	return m_uiTeamPoint[team];
}

void			
CRoom::SetTeamPoint(TEAM_TYPE team, int point)
{
	m_uiTeamPoint[team] = point;
}

void			
CRoom::IncreaseTeamPoint(TEAM_TYPE team, int point)
{
	m_uiTeamPoint[team] += point;
}

UINT
CRoom::GetTeamCount(TEAM_TYPE team)
{
	UINT result = 0;
	for (UINT i = 0; i < m_uiTopCount; ++i) {
		if (team == GetMember(i)->GetTeamType()) {
			++result;
		}
	}
	return result;
}
