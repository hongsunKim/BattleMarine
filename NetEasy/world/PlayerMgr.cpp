/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "PlayerMgr.h"

void
CPlayerMgr::Initialize() {

}

void
CPlayerMgr::Release() {
	for(size_t i = 0; i < Size(); ++i) {
		CPlayer* pkPlayer = Seek(i);
		if (isptr(pkPlayer)) {
			SAFE_DELETE(pkPlayer);
		}
	}
	Clear();
}

void
CPlayerMgr::Update() {
	for(size_t i = 0; i < Size(); ++i) {
		CPlayer* pkPlayer = Seek(i);
		if(isptr(pkPlayer)) {
			pkPlayer->Update();
		}
	}
}

bool
CPlayerMgr::Insert(CPlayer& rkPlayer_) {
	return m_kMap.insert(stl_Map::value_type(rkPlayer_.GetIndex(), &rkPlayer_)).second;
}

bool
CPlayerMgr::Delete(UINT uiIndex_) {
	return (m_kMap.erase(uiIndex_) == 1);
}

bool
CPlayerMgr::DeleteKey(UINT uiKey_) {
	for(size_t i = 0; i < Size(); ++i) {
		CPlayer* pkPlayer = Seek(i);
		if(isptr(pkPlayer)) {
			if(uiKey_ == pkPlayer->GetKey()) {
				return Delete(pkPlayer->GetIndex());
			}
		}
	}
	return false;
}

CPlayer*
CPlayerMgr::GetPlayer(UINT uiKey_) {
	if(0 <= uiKey_) {
		for(size_t i = 0; i < Size(); ++i) {
			CPlayer* pkPlayer = Seek(i);
			if(isptr(pkPlayer)) {
				if(uiKey_ == pkPlayer->GetKey()) {
					return pkPlayer;
				}
			}
		}
	}
	return NULL;
}

CPlayer*
CPlayerMgr::Find(UINT uiIndex_) {
	if (0 <= uiIndex_) {
		Iter iter = m_kMap.find(uiIndex_);
		if (iter != m_kMap.end()) {
			return ((*iter).second);
		}
	}
	return NULL;
}

CPlayer*
CPlayerMgr::Seek(UINT uiIndex_) {
	if (false == m_kMap.empty()) {
		Iter iter = m_kMap.begin();
		advance(iter, uiIndex_);
		if (iter != m_kMap.end()) {
			return ((*iter).second);
		}
	}
	return NULL;
}
