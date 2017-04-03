/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "RoomHandler.h"

#include "../CommonHeader.h"

bool
CRoomHandler::Join() {
	m_rkBody.SetStatus(STATUS_DYING);
	m_rkBody.SetCurLife(m_rkBody.GetMaxLife());
	return true;
}

void
CRoomHandler::Leave(CPlayer* pkLeader_) {
	m_rkBody.SetStatus(STATUS_EXIT);
	Clear();
}

void
CRoomHandler::Clear() {
	SetRoom(NULL);
	SetOffset(-1);

	m_rkBody.SetStatus(STATUS_EXIT);
}
