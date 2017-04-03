/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../GlobalVariable.h"
#include "../Enums.h"

struct SDbInfo {
	SDbInfo() { memset(this, 0, sizeof(SDbInfo)); }

	void		Clear()						{ memset(this, 0, sizeof(SDbInfo)); }

	void		SetHost(const char* o)		{ memcpy(host, o, iDB_HOST_NAME_LEN); }
	void		SetDB(const char* o)		{ memcpy(db, o, iDB_DATABASE_NAME_LEN); }
	void		SetUser(const char* o)		{ memcpy(user, o, iDB_USER_NAME_LEN); }
	void		SetPassword(const char* o)	{ memcpy(password, o, iDB_PASSWD_NAME_LEN); }

	const char*	GetHost()					{ return host; }
	const char*	GetDB()						{ return db; }
	const char*	GetUser()					{ return user; }
	const char*	GetPassword()				{ return password; }

	char		host[iDB_HOST_NAME_LEN+1];
	char		db[iDB_DATABASE_NAME_LEN+1];
	char		user[iDB_USER_NAME_LEN+1];
	char		password[iDB_PASSWD_NAME_LEN+1];

};
