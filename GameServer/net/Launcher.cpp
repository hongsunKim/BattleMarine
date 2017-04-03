/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

ProtocolLauncher g_bpfLauncher[PROTOCOL_MAX] = { 0, };

void
ServerLauncher(CPlayer& rkActor_, CCommand& rkCommand_) {
	if ((0 < rkCommand_.GetOrder()) &&
		(rkCommand_.GetOrder() < PROTOCOL_MAX)) {
		ProtocolLauncher pkLauncher = g_bpfLauncher[rkCommand_.GetOrder()];
		if (isptr(pkLauncher)) {
			pkLauncher(rkActor_, rkCommand_);
		} else {
			OUTPUT("error: order is none: " << rkCommand_.GetOrder());
		}
	} else {
		OUTPUT("error: order range over: " << rkCommand_.GetOrder());
	}
}

void
InitializeCommand() {
	InitializeIdCommand();
	InitializeInfoCommand();
	InitializeItemCommand();
	InitializeRoomCommand();
	InitializeUserCommand();
}
