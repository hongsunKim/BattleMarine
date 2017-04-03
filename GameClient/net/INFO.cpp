/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Launcher.h"
#include "../CommonHeader.h"

bool
CMD_INFO_USER_LIST(CCommand& rkCommand_) {
	//CONSOLE("CMD_INFO_USER_LIST: actor: " << g_kMainPlayer->GetKey());

	if (NONE == rkCommand_.GetExtra()) {
		// 서버에 접속 중인 전체 플레이어 정보 (본인 포함)
		SInfoUserListGsToCl& rtRData = (SInfoUserListGsToCl&)rkCommand_.GetData();
		CONSOLE("CMD_INFO_USER_LIST: NONE: index: " << g_kMainPlayer->GetIndex() << ", actor: " << rtRData.actor << ", target: " << rtRData.target << ", name: " << rtRData.GetName());

		if(rtRData.actor == rtRData.target) {
			// 클라이언트 본인
			g_kMainPlayer->SetKey(rtRData.actor);
			g_kMainPlayer->SetName(rtRData.GetName());
		} else {
			// 다른 클라이언트
			CPlayerEx* pkMember = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.target);
			if(false == isptr(pkMember)) {
				pkMember = (CPlayerEx*)g_kPlayerFactory.Create();
				pkMember->SetIndex(rtRData.target);
				pkMember->SetKey(rtRData.target);
				pkMember->SetName(rtRData.GetName());

				g_kPlayerMgr.Insert(*pkMember);
			}
		}

		REFRESH_USER_LIST();
	} else if (IN_ == rkCommand_.GetExtra()) {
		// 서버에 접속한 플레이어 (본인은 안옴)
		SInfoUserInGsToCl& rtRData = (SInfoUserInGsToCl&)rkCommand_.GetData();
		CONSOLE("CMD_INFO_USER_LIST: IN_: target: " << rtRData.target << ", name: " << rtRData.GetName());
		CPlayerEx* pkMember = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.target);
		if(false == isptr(pkMember)) {
			pkMember = (CPlayerEx*)g_kPlayerFactory.Create();
			pkMember->SetIndex(rtRData.target);
			pkMember->SetKey(rtRData.target);
			pkMember->SetName(rtRData.GetName());

			g_kPlayerMgr.Insert(*pkMember);
		}

		REFRESH_USER_LIST();
	} else if (OUT_ == rkCommand_.GetExtra()) {
		// 서버에서 나간 플레이어 (본인은 안옴)
		SInfoUserOutGsToCl& rtRData = (SInfoUserOutGsToCl&)rkCommand_.GetData();
		CONSOLE("CMD_INFO_USER_LIST: OUT_: target: " << rtRData.target);
		CPlayerEx* pkMember = (CPlayerEx*)g_kPlayerMgr.GetPlayer(rtRData.target);
		if(isptr(pkMember)) {
			g_kPlayerMgr.DeleteKey(rtRData.target);
			SAFE_DELETE(pkMember);
		}

		REFRESH_USER_LIST();
	}
	return true;
}

bool
CMD_INFO_SERVER(CCommand& rkCommand_) {
	SInfoServerGsToCl& rtRData = (SInfoServerGsToCl&)rkCommand_.GetData();
	CONSOLE("CMD_INFO_SERVER: before tick: " << g_kTick.GetTick() << ", server tick: " << rtRData.tick);

	g_kTick.Reset(rtRData.tick * 10);
	
	CONSOLE("CMD_INFO_SERVER: after tick: " << g_kTick.GetTick() << ", server tick: " << rtRData.tick);
	return true;
}

void
InitializeInfoCommand() {
	SET_COMMAND(INFO_USER_LIST);
	SET_COMMAND(INFO_SERVER);
}
