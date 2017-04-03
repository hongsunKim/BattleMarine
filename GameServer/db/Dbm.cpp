/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "Dbm.h"
#include "../CommonHeader.h"

bool
CDbConnector::Initialize() {
	if(false == IsConnected()) {
		mysql_init(&m_Mysql);
		return true;
	}
	return true;
}

bool
CDbConnector::Release() {
	mysql_close(&m_Mysql);
	Clear();
	return true;
}

void
CDbConnector::Clear() {
	m_szHost = NULL;
	m_szDatabase = NULL;
	m_szUser = NULL;
	m_szPassword = NULL;
	m_szCharacterset = NULL;

	m_bConnected = false;
	m_iReferenceCount = 0;
}

bool
CDbConnector::Connect() {
	if(false == IsConnected()) {
		if(isptr(m_szHost) && isptr(m_szDatabase) && isptr(m_szUser) && isptr(m_szPassword)) {
			if(isptr(m_szCharacterset)) {
				mysql_options(&m_Mysql, MYSQL_SET_CHARSET_NAME, m_szCharacterset);
			} else {
				mysql_options(&m_Mysql, MYSQL_SET_CHARSET_NAME, "utf8");
			}

			if(false == m_bSecureAuth) {
				my_bool* pbSecureAuth = 0;
				mysql_options(&m_Mysql, MYSQL_SECURE_AUTH, &pbSecureAuth);
			}

			if(isptr(mysql_real_connect(&m_Mysql, m_szHost, m_szUser, m_szPassword, m_szDatabase, 0, NULL, CLIENT_MULTI_STATEMENTS|CLIENT_MULTI_RESULTS|CLIENT_REMEMBER_OPTIONS))) {
				SetConnected(true);

				return true;
			}

			OUTPUT("other err: " << mysql_error(&m_Mysql)<<" ("<<mysql_errno(&m_Mysql)<<")");
		}
	} else {
		return true;
	}

	mysql_close(&m_Mysql);
	SetConnected(false);
	return false;
}

bool
CDbConnector::Close() {
	if(GetReferenceCount() <= 0) {
		if (IsConnected()) {
			mysql_close(&m_Mysql);
			SetConnected(false);

			return true;
		}
		return true;
	}
	return true;
}


INT
CDbConnector::GetErrno() {
	return mysql_errno(&m_Mysql);
}

const char*
CDbConnector::GetError() {
	const char* error = mysql_error(&m_Mysql);
	if(isptr(error)) {
		if(error[0] != '\0') {
			return error;
		}
	}
	return "no error";
}

bool
CDbConnector::Query(char& szQuery_) {
	if(IsConnected()) {
		INT iRet = mysql_query(&m_Mysql, &szQuery_);
		if(0 == iRet) {
			return true;
		} else {
			iRet = mysql_errno(&m_Mysql);
			if((CR_CONN_HOST_ERROR == iRet) || (CR_SERVER_LOST == iRet) || (CR_SERVER_GONE_ERROR == iRet)) {
				OUTPUT("["<<iRet<<"] server gone error: ["<<&szQuery_<<"] : " << mysql_error(&m_Mysql));
				mysql_close(&m_Mysql);
				SetConnected(false);
			} else {
				TRACE("other err: ["<<&szQuery_<<"] : " << mysql_error(&m_Mysql)<<" ("<<iRet<<":"<<mysql_errno(&m_Mysql)<<")");
			}
		}
	} else {
		OUTPUT("server was disconnected: ["<<&szQuery_<<"] : " << mysql_error(&m_Mysql));
		mysql_close(&m_Mysql);
	}

	return false;
}

void*
CDbConnector::StoreResult() {
	return mysql_store_result(&m_Mysql);
}

UINT64
CDbConnector::AffectedRows() {
	return UINT64(mysql_affected_rows(&m_Mysql));
}

UINT
CDbConnector::FieldCount() {
	return mysql_field_count(&m_Mysql);
}

char**
CDbConnector::FetchRow(void* pvResults_) {
	if(isptr(pvResults_)) {
		return mysql_fetch_row((MYSQL_RES*)pvResults_);
	} else {
		OUTPUT("pvResults_ is null: ");
	}
	return NULL;
}

bool
CDbConnector::NextResult() {
	INT iStatus = mysql_next_result(&m_Mysql);
	if(0 == iStatus) {
		return true;
	} else if(0 < iStatus) {
		OUTPUT("mysql_next_result: error: "<<iStatus);
		return true;
	}
	return false;
}

void
CDbConnector::FreeResult(void* pvResults_) {
	if(isptr(pvResults_)) {
		mysql_free_result((MYSQL_RES*)pvResults_);
	}
}


CDBM::CDBM() : m_pkDbConnector(NULL) {
	memset(m_szSQL, 0, sizeof(m_szSQL));
}

CDBM::~CDBM() {
}

void
CDBM::Clear() {
	if(isptr(GetDbConnector())) {
		if(GetDbConnector()->IsConnected()) {
			if(0 <= GetDbConnector()->DecrementReference()) {
				GetDbConnector()->Close();
			}
		}
	}
	SAFE_DELETE(m_pkDbConnector);
	memset(m_szSQL, 0, sizeof(m_szSQL));
}

bool
CDBM::Initialize(const char& szHost_, const char& szDatabase_, const char& szUser_, const char& szPassword_, bool bSecureAuth_, const char* szCharset_) {
	m_pkDbConnector = new CDbConnector;

	if(isptr(GetDbConnector())) {
		GetDbConnector()->SetHost(&szHost_);
		GetDbConnector()->SetDatabase(&szDatabase_);
		GetDbConnector()->SetUser(&szUser_);
		GetDbConnector()->SetPassword(&szPassword_);
		GetDbConnector()->SetSecureAuth(bSecureAuth_);
		GetDbConnector()->SetCharacterSet(szCharset_);
		GetDbConnector()->SetReferenceCount(0);

		if(GetDbConnector()->Initialize()) {
			if(GetDbConnector()->Connect()) {
				if(0 < GetDbConnector()->IncrementReference()) {
					return true;
				}
			}
		}
	}

    return false;
}

bool
CDBM::Release() {
	Clear();

    return true;
}

bool
CDBM::RealQuery() {
	if(isptr(GetDbConnector())) {
		if(GetDbConnector()->Query(*m_szSQL)) {
			return true;
		} else {
			if(false == GetDbConnector()->IsConnected()) {
				GetDbConnector()->DecrementReference();
				if(GetDbConnector()->Initialize()) {
					if(GetDbConnector()->Connect()) {
						if(0 < GetDbConnector()->IncrementReference()) {
							if(GetDbConnector()->Query(*m_szSQL)) {
								OUTPUT("server is reconnected: OK: ");
								return true;
							} else {
								if(false == GetDbConnector()->IsConnected()) {
									GetDbConnector()->DecrementReference();
								}
							}
						}
					} else {
						OUTPUT("server is connected: FAILED: "<<GetDbConnector()->GetHost()<<" : "<<GetDbConnector()->GetDatabase());
					}
				}
			}
		}
	}
	return false;
}

void
CDBM::ErrMsg() {
	OUTPUT("["<<GetDbConnector()->GetErrno()<<"] "<<GetDbConnector()->GetError()<<" ("<<m_szSQL<<")");
}

void*
CDBM::StoreResult() {
	return GetDbConnector()->StoreResult();
}

UINT64
CDBM::AffectedRows() {
	return GetDbConnector()->AffectedRows();
}

UINT
CDBM::FieldCount() {
	return GetDbConnector()->FieldCount();
}

char**
CDBM::FetchRow(void* pResult_) {
	return GetDbConnector()->FetchRow(pResult_);
}

bool
CDBM::NextResult() {
	return GetDbConnector()->NextResult();
}

void
CDBM::FreeResult(void* pResult_) {
	GetDbConnector()->FreeResult(pResult_);
}
