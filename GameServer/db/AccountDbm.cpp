/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "AccountDbm.h"

#include "../CommonHeader.h"

#define DB_ACCOUNT_TABLE		"`account`"

//장현우(ac_point 추가)
#define SQL_ACCOUNT_STRUCTURE	"ac_aid,ac_name,ac_grade-1,ac_login_time,ac_logout_time,ac_point"

#define SQL_ACCOUNT_SELECT_AID	"SELECT ac_aid FROM "DB_ACCOUNT_TABLE" WHERE ac_loginid='%s'"
#define SQL_ACCOUNT_SELECT_ID	"SELECT "SQL_ACCOUNT_STRUCTURE" FROM "DB_ACCOUNT_TABLE" WHERE ac_loginid='%s' and ac_passwd=password('%s')"
//장현우(ac_create_time 추가)
#define SQL_ACCOUNT_INSERT		"INSERT INTO "DB_ACCOUNT_TABLE" (ac_loginid,ac_passwd,ac_name,ac_create_time) VALUES('%s',password('%s'),'%s',unix_timestamp())"

//#define SQL_ACCOUNT_UPDATE	"UPDATE "SQL_ACCOUNT_STRUCTURE" SET "

//장현우
#define SQL_ACCOUNT_LOGIN_TIME_UPDATE "UPDATE account SET ac_login_time = unix_timestamp() WHERE ac_aid = %d"
#define SQL_ACCOUNT_LOGOUT_TIME_UPDATE "UPDATE account SET ac_logout_time = unix_timestamp() WHERE ac_aid = %d"
#define SQL_ACCOUNT_SELECT_INFO	"SELECT "SQL_ACCOUNT_STRUCTURE" FROM "DB_ACCOUNT_TABLE" WHERE ac_aid = %d"

enum DB_ACCOUNT_INFO {
	DB_ACCOUNT_AID = 0,
	DB_ACCOUNT_NAME,
	DB_ACCOUNT_GRADE,
	DB_ACCOUNT_LOGIN_TIME,
	DB_ACCOUNT_LOGOUT_TIME,
	DB_ACCOUNT_POINT,
	DB_ACCOUNT_MAX
};

bool
CAccountDbm::QueryCheck(const char* szLoginId_) {
	if (isptr(szLoginId_)) {
		char** ppRow;
		sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_SELECT_AID, szLoginId_);

		if (RealQuery()) {
			void* pvResult = StoreResult();
			if (isptr(pvResult)) {
				if (NULL != (ppRow = FetchRow(pvResult))) {
					FreeResult(pvResult);
					return true;
				}
				FreeResult(pvResult);
			} else {
				OUTPUT("query result is failed: " << m_szSQL);
			}
		} else {
			ErrMsg();
		}
	} else {
		OUTPUT("error: login id is null: ");
	}
	return false;
}

//장현우
bool
CAccountDbm::QueryCheck(UINT uiAid_)
{
	if (0 < uiAid_)
	{
		char** ppRow;
		sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_SELECT_INFO, uiAid_);

		if (RealQuery())
		{
			void* pvResult = StoreResult();
			if (isptr(pvResult))
			{
				if (NULL != (ppRow = FetchRow(pvResult)))
				{
					FreeResult(pvResult);
					return true;
				}
				FreeResult(pvResult);
			}
			else
			{
				OUTPUT("query result is failed: " << m_szSQL);
			}
		}
		else
		{
			ErrMsg();
		}
	}
	else
	{
		OUTPUT("error: login id is null: ");
	}

	return false;
}

bool
CAccountDbm::QueryLogin(const char* szLoginId_, const char* szLoginPasswd_, CPlayer& rkPlayer_) {
	if (isptr(szLoginId_)) {
		if (isptr(szLoginPasswd_)) {
			char** ppRow;
			sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_SELECT_ID, szLoginId_, szLoginPasswd_);

			if (RealQuery()) {
				void* pvResult = StoreResult();
				if (isptr(pvResult)) {
					if (NULL != (ppRow = FetchRow(pvResult))) {
						ConvDB2Data(ppRow, rkPlayer_);
						FreeResult(pvResult);

						return true;
					}
					FreeResult(pvResult);
				} else {
					OUTPUT("query result is failed: " << m_szSQL);
				}
			} else {
				ErrMsg();
			}
		} else {
			OUTPUT("error: login passwd is null: ");
		}
	} else {
		OUTPUT("error: login id is null: ");
	}
	return false;
}

//장현우
bool
CAccountDbm::QueryLogin(const UINT uiAid_, CPlayer& rkPlayer_) {
	if (0 < uiAid_) {
		char** ppRow;
		sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_SELECT_INFO, uiAid_);

		if (RealQuery())
		{
			void* pvResult = StoreResult();
			if (isptr(pvResult))
			{
				if (NULL != (ppRow = FetchRow(pvResult)))
				{
					ConvDB2Data(ppRow, rkPlayer_);
					FreeResult(pvResult);

					return true;
				}
				FreeResult(pvResult);
			}
			else
			{
				OUTPUT("query result is failed: " << m_szSQL);
			}
		}
		else
		{
			ErrMsg();
		}
	}
	else
	{
		OUTPUT("error: PlayerKey is null: ");
	}
	return false;
}

bool
CAccountDbm::Insert(const char* szLoginId_, const char* szLoginPasswd_, const char* szName_) {
	if(isptr(szLoginId_)) {
		if(isptr(szLoginPasswd_)) {
			if(isptr(szName_)) {
				sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_INSERT, szLoginId_, szLoginPasswd_, szName_);
				return RealQuery();
			} else {
				OUTPUT("error: name is null: ");
			}
		} else {
			OUTPUT("error: login passwd is null: ");
		}
	} else {
		OUTPUT("error: login id is null: ");
	}
	return false;
}

//장현우
bool
CAccountDbm::UpdateLoginTime(CPlayer& rkPlayer_)
{
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_LOGIN_TIME_UPDATE, rkPlayer_.GetAid());
	return RealQuery();
}
//장현우
bool
CAccountDbm::UpdateLogoutTime(CPlayer& rkPlayer_)
{
	sprintf_s(m_szSQL, iDATABASE_SQL_BUFFER_LEN, SQL_ACCOUNT_LOGOUT_TIME_UPDATE, rkPlayer_.GetAid());
	return RealQuery();
}

bool
CAccountDbm::ConvDB2Data(char** row, CPlayer& rkPlayer_) {
	rkPlayer_.SetAid(RTOQ(DB_ACCOUNT_AID));
	if(0 < rkPlayer_.GetAid()) {
		rkPlayer_.SetName(RTOS(DB_ACCOUNT_NAME));

		((CPlayerEx&)rkPlayer_).SetGradeType(GRADE_TYPE(RTOI(DB_ACCOUNT_GRADE)));
		rkPlayer_.SetLoginTime(RTOQ(DB_ACCOUNT_LOGIN_TIME));
		rkPlayer_.SetLogoutTime(RTOQ(DB_ACCOUNT_LOGOUT_TIME));
		rkPlayer_.SetPoint(RTOQ(DB_ACCOUNT_POINT));
		return true;
	} else {
		OUTPUT("error: aid is 0");
	}
	return false;
}
