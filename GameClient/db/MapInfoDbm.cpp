/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "MapInfoDbm.h"

#include "../CommonHeader.h"

bool
CMapInfoDbm::Load() {
	std::string szPath = "..\\Data\\mapinfo.csv";

	if (false == CDBM::Load(szPath.c_str())) {
		CONSOLE("file not found: " << szPath.c_str());
		return false;
	}

	g_kMapInfoList.Clear();

	INT iIdOffset = GetField("mi_id")->GetOffset();
	INT iNameOffset = GetField("mi_name")->GetOffset();
	INT iMaxUserOffset = GetField("mi_max_user")->GetOffset();
	INT iModFFAOffset = GetField("mi_mod_ffa")->GetOffset();
	INT iModTDMOffset = GetField("mi_mod_tdm")->GetOffset();
	INT iModZOMBIEOffset = GetField("mi_mod_zombie")->GetOffset();
	INT iDescOffset = GetField("mi_desc")->GetOffset();

	INT iIdSize = GetField("mi_id")->GetSize();
	INT iNameSize = GetField("mi_name")->GetSize();
	INT iMaxUserSize = GetField("mi_max_user")->GetSize();
	INT iModFFASize = GetField("mi_mod_ffa")->GetSize();
	INT iModTDMSize = GetField("mi_mod_tdm")->GetSize();
	INT iModZOMBIESize = GetField("mi_mod_zombie")->GetSize();
	INT iDescSize = GetField("mi_desc")->GetSize();

	for(INT i = 0; i < GetDataCount(); ++i) {
		std::string szId(GetData(i, iIdOffset), iIdSize);
		std::string szName(GetData(i, iNameOffset), iNameSize);
		std::string szMaxUser(GetData(i, iMaxUserOffset), iMaxUserSize);
		std::string szModFFA(GetData(i, iModFFAOffset), iModFFASize);
		std::string szModTDM(GetData(i, iModTDMOffset), iModTDMSize);
		std::string szModZOMBIE(GetData(i, iModZOMBIEOffset), iModZOMBIESize);
		std::string szDesc(GetData(i, iDescOffset), iDescSize);

		UINT uiId = atoll(szId.c_str());
		UINT uiMaxUser = atoll(szMaxUser.c_str());

		bool bModFFA = false;
		if(0 == strcmp(szModFFA.c_str(), "TRUE")) {
			bModFFA = true;
		}

		bool bModTDM = false;
		if(0 == strcmp(szModTDM.c_str(), "TRUE")) {
			bModTDM = true;
		}

		bool bModZOMBIE = false;
		if(0 == strcmp(szModZOMBIE.c_str(), "TRUE")) {
			bModZOMBIE = true;
		}

		SMapInfo tInfo;
		tInfo.id = uiId;
		tInfo.SetName(szName.c_str());
		tInfo.max_user = uiMaxUser;
		tInfo.mod_ffa = bModFFA;
		tInfo.mod_tdm = bModTDM;
		tInfo.mod_zombie = bModZOMBIE;
		tInfo.SetDesc(szDesc.c_str());

		//CONSOLE("mapinfo: id: " << tInfo.GetId() << ", name: " << tInfo.GetName() << ", max user: " << tInfo.GetMaxUser() << ", ffa: " << tInfo.IsModFFA() << ", tdm: " << tInfo.IsModTDM() << ", zombie: " << tInfo.IsModZOMBIE());
		//CONSOLE("mapinfo: desc: " << tInfo.GetDesc());

		g_kMapInfoList.Insert(tInfo);
	}

	Clear();
	return true;
}
