/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "ConnectorEx.h"
#include "../CommonHeader.h"

// 프로토콜 처리 위치

void
CConnectorEx::Launcher(CCommand* pkCommand_) {
	if (isptr(g_kMainPlayer)) {
		if (isptr(pkCommand_)) {
			if ((PROTOCOL_NULL < pkCommand_->GetOrder()) && (pkCommand_->GetOrder() < PROTOCOL_MAX)) {
				ProtocolLauncher pkLauncher = g_bpfLauncher[pkCommand_->GetOrder()];
				pkLauncher(*pkCommand_);
			}
		}
	}
}
