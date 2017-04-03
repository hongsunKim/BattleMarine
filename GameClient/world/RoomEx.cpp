/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "RoomEx.h"
#include "../CommonHeader.h"

bool
CRoomEx::Initialize() {
	if (CRoom::Initialize()) {
		return true;
	}
	return false;
}

bool
CRoomEx::Release() {
	if (CRoom::Release()) {
		return true;
	}
	return false;
}

void
CRoomEx::Clear() {
	CRoom::Clear();
}

bool
CRoomEx::InsertRoomList(SRoomInfo& stRoomInfo_) {
	return m_kMap.insert(stl_Map::value_type(stRoomInfo_.id, stRoomInfo_)).second;
}

bool
CRoomEx::DeleteRoomList(UINT uiId_) {
	return (m_kMap.erase(uiId_) == 1);
}

SRoomInfo*
CRoomEx::PeekFrontRoomList() {
	return SeekRoomList(0);
}

SRoomInfo*
CRoomEx::FindRoomList(UINT uiId_) {
	Iter iter = m_kMap.find(uiId_);
	if(iter != m_kMap.end()) {
		return &((*iter).second);
	}
	return NULL;
}

SRoomInfo*
CRoomEx::SeekRoomList(UINT uiIndex_) {
	if (false == m_kMap.empty()) {
		Iter iter = m_kMap.begin();
		advance(iter, uiIndex_);
		if (iter != m_kMap.end()) {
			return &((*iter).second);
		}
	}
	return NULL;
}