/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "Dbm.h"
#include "DbData.h"

#define g_kAccountDB	CAccountDbm::GetInstance()

class CAccountDbm : public CDBM, public CSingleton< CAccountDbm > {
public:
	CAccountDbm() {}
	virtual ~CAccountDbm() {}

	bool	QueryCheck(const char*);
	//장현우
	bool	QueryCheck(const UINT);
	bool	QueryLogin(const char*, const char*, CPlayer&);
	//장현우
	bool	QueryLogin(const UINT, CPlayer&);

	bool	Insert(const char*, const char*, const char*);

	//장현우
	bool	UpdateLoginTime(CPlayer&);
	bool	UpdateLogoutTime(CPlayer&);

private:
	bool	ConvDB2Data(char**, CPlayer&);

};
