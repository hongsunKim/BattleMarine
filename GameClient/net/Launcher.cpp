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
InitializeCommand() {
	InitializeIdCommand();
	InitializeInfoCommand();
	InitializeItemCommand();
	InitializeRoomCommand();
	InitializeUserCommand();
	InitializeOtherCommand();
	InitializeCheatCommand();
}
