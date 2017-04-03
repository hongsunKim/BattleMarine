/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "RoomHandlerEx.h"
#include "../CommonHeader.h"

bool
CRoomHandlerEx::Join() {
	CRoom* pkRoom = GetRoom();
	if (isptr(pkRoom)) {
		if(CRoomHandler::Join()) {
			OUTPUT("in: [" << m_rkBody.GetKey() << "]");
			g_kChannelMgr.GetRoomMemberList(m_rkBody);

			CConnector* pkConnector = m_rkBody.GetConnector();
			if (isptr(pkConnector)) {
				CCommand kCommand;
				kCommand.SetOrder(ROOM_JOIN_OTHER);
				kCommand.SetExtra(OK);

				SRoomJoinOtherGsToCl& rtSData = (SRoomJoinOtherGsToCl&)kCommand.GetData();
				rtSData.actor = m_rkBody.GetKey();
				rtSData.SetName(m_rkBody.GetName());

				OUTPUT("[" << m_rkBody.GetName() << ":" << m_rkBody.GetKey() << "]");

				Broadcast(kCommand, sizeof(SRoomJoinOtherGsToCl), &m_rkBody);
			}

			return true;
		}
	} else {
		OUTPUT("critical error: room is null: ");
	}
	return false;
}

void
CRoomHandlerEx::Leave(CPlayer* pkLeader_) {
	CCommand kCommand;
	kCommand.SetOrder(ROOM_LEAVE_OTHER);

	SRoomLeaveOtherGsToCl& rtSData = (SRoomLeaveOtherGsToCl&)kCommand.GetData();
	rtSData.actor = m_rkBody.GetKey();

	if (isptr(pkLeader_)) {
		kCommand.SetExtra(CHECK);
		//pkLeader_->SetStatus(STATUS_NORMAL);

		rtSData.leader = pkLeader_->GetKey();

		OUTPUT("ROOM_LEAVE_OTHER: CHECK: body: " << m_rkBody.GetKey() << ", leader: " << pkLeader_->GetKey());

		Broadcast(kCommand, sizeof(SRoomLeaveOtherGsToCl), &m_rkBody);
	} else {
		kCommand.SetExtra(OK);

		OUTPUT("ROOM_LEAVE_OTHER: OK: body: " << m_rkBody.GetKey());

		Broadcast(kCommand, sizeof(SRoomLeaveOtherGsToCl) - sizeof(UINT32), &m_rkBody);
	}

	CRoomHandler::Leave(pkLeader_);
}

bool
CRoomHandlerEx::Broadcast(CCommand& rkCommand_, INT iSize_, CPlayer* pkActor_, CPlayer* pkTarget_) {
	if (isptr(GetRoom())) {
		return GetRoom()->Broadcast(rkCommand_, iSize_, pkActor_, pkTarget_);
	}
	return false;
}

