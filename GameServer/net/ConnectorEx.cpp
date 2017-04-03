/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "ConnectorEx.h"
#include "../CommonHeader.h"

// 프로토콜 처리 위치
bool
CConnectorEx::Disconnect(const SOCKET skSocket_) {
	if(isptr(GetBody())) {
		CRoomHandler* pkRoomHandler = GetBody()->GetRoomHandler();
		if (isptr(pkRoomHandler)) {
			CRoom* pkRoom = pkRoomHandler->GetRoom();
			if (isptr(pkRoom)) {
				CCommand kCommand;
				kCommand.SetOrder(ROOM_LEAVE);
				kCommand.SetExtra(NONE);

				ServerLauncher(*GetBody(), kCommand);
			}
		}

		// 접속 중인 클라이언트에게 나가는 플레이어 전송
		g_kChannelMgr.OutUser(*GetBody());
		g_kAccountDB.UpdateLogoutTime(*GetBody());

		return true;
	}
	return false;
}

void
CConnectorEx::Launcher(CCommand* pkCommand_) {
	if(isptr(GetBody())) {
		if(isptr(pkCommand_)) {
			if ((PROTOCOL_NULL < pkCommand_->GetOrder()) && (pkCommand_->GetOrder() < PROTOCOL_MAX)) {
				ProtocolLauncher pkLauncher = g_bpfLauncher[pkCommand_->GetOrder()];
				pkLauncher(*GetBody(), *pkCommand_);
			}
		}
	}
}
