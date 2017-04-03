/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../../CommonHeader.h"

#pragma pack(4)
struct SIdPingClToGs {
	tick_t	tick;
};

struct SIdPingGsToCl {
	tick_t	tick;
	FLOAT	timeOut;
};

struct SIdAuthorizeClToGs
{
	SIdAuthorizeClToGs()	{ memset(this, 0, sizeof(SIdAuthorizeClToGs)); }

	const char*	GetLoginId()					{ return login_id; }
	void		SetLoginId(const char* o)		{ memcpy(login_id, o, iLOGIN_ID_LEN); login_id[iLOGIN_ID_LEN] = '\0'; }

	const char*	GetLoginPasswd()				{ return login_passwd; }
	void		SetLoginPasswd(const char* o)	{ memcpy(login_passwd, o, iLOGIN_PWD_LEN); login_passwd[iLOGIN_PWD_LEN] = '\0'; }

	char	login_id[iLOGIN_ID_LEN + 1];
	char	login_passwd[iLOGIN_PWD_LEN + 1];
};

struct SIdAuthorizeGsToCl
{
	SIdAuthorizeGsToCl()	{ memset(this, 0, sizeof(SIdAuthorizeGsToCl)); }

	const char* GetName()						{ return name; }
	void		SetName(const char* o)			{ memcpy(name, o, iPLAYER_NAME_LEN); name[iPLAYER_NAME_LEN] = '\0'; }

	const UINT	GetPoint()						{ return point; }
	void		SetPoint(const UINT o)			{ point = o; }

	const UINT	GetLoginTime()					{ return login_time; }
	void		SetLoginTime(const UINT o)		{ login_time = o; }

	const UINT	GetLogoutTime()					{ return logout_time; }
	void		SetLogoutTime(const UINT o)		{ logout_time = o; }

	const UINT	GetAid()						{ return aid; }
	void		SetAid(const UINT o)			{ aid = o; }

	UINT32	aid;
	UINT32	point;
	UINT32	login_time;
	UINT32	logout_time;

	char	name[iPLAYER_NAME_LEN + 1];
};

struct SIdCreateClToGs {
	SIdCreateClToGs()	{ memset(this, 0, sizeof(SIdCreateClToGs)); }

	const char*	GetLoginId()					{ return login_id; }
	void		SetLoginId(const char* o)		{ memcpy(login_id, o, iLOGIN_ID_LEN); login_id[iLOGIN_ID_LEN] = '\0'; }

	const char*	GetLoginPasswd()				{ return login_passwd; }
	void		SetLoginPasswd(const char* o)	{ memcpy(login_passwd, o, iLOGIN_PWD_LEN); login_passwd[iLOGIN_PWD_LEN] = '\0'; }

	const char*	GetName()						{ return name; }
	void		SetName(const char* o)			{ memcpy(name, o, iPLAYER_NAME_LEN); name[iPLAYER_NAME_LEN] = '\0'; }

	char	login_id[iLOGIN_ID_LEN + 1];
	char	login_passwd[iLOGIN_PWD_LEN + 1];
	char	name[iPLAYER_NAME_LEN + 1];
};

struct SIdCreateGsToCl {
	SIdCreateGsToCl()	{ memset(this, 0, sizeof(SIdCreateGsToCl)); }

};

struct SIdAuthorizeWepClToGs
{
	SIdAuthorizeWepClToGs() { memset(this, 0, sizeof(SIdAuthorizeWepClToGs)); }

	const void SetAid(UINT o) { actor = o; }
	const UINT GetAid() { return actor; }

private:
	UINT actor;
};

#pragma pack()
