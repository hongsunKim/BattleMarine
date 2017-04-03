/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "DbData.h"

#define g_kDbMgr CDbMgr::GetInstance()

class CDbMgr : public CSingleton< CDbMgr > {
public:
	CDbMgr();
	~CDbMgr();

	bool			Initialize();
	bool			Release();

	bool			LoadInfo();
	bool			Open();
	void			Close();

	bool			LoadMapInfo();
	bool			LoadModInfo();
	bool			LoadItemInfo();
	bool			LoadDropInfo();
	bool			LoadRewardInfo();

	void			SetSecureAuth(bool o)			{ m_bSecureAuth = o; }
	bool			GetSecureAuth()					{ return m_bSecureAuth; }

	void			SetGameHost(const char* o)		{ m_tGameDB.SetHost(o); }
	void			SetGameDB(const char* o)		{ m_tGameDB.SetDB(o); }
	void			SetGameUser(const char* o)		{ m_tGameDB.SetUser(o); }
	void			SetGamePassword(const char* o)	{ m_tGameDB.SetPassword(o); }

	const char&		GetGameHost()					{ return *m_tGameDB.GetHost(); }
	const char&		GetGameDB()						{ return *m_tGameDB.GetDB(); }
	const char&		GetGameUser()					{ return *m_tGameDB.GetUser(); }
	const char&		GetGamePassword()				{ return *m_tGameDB.GetPassword(); }

	const char*		GetCharacterSet()				{ return m_szCharacterSet; }
	void			SetCharacterSet(const char* o)	{ strncpy(m_szCharacterSet, o, strlen(o)); }

private:
	SDbInfo			m_tGameDB;

	char			m_szCharacterSet[iDATABASE_CHARACTER_SET_LEN];

	bool			m_bInitialized;
	bool			m_bSecureAuth;

};
