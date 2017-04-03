/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <winsock2.h>
#include <mysql.h>
#include <errmsg.h>

#include "../GlobalVariable.h"

#define RTOI(o) atoi(row[o])
#define RTOF(o) atof(row[o])
#define RTOL(o) atol(row[o])
#define RTOQ(o) atoll(row[o])
#define RTOS(o) row[o]

class CDbConnector {
public:
	CDbConnector() : m_szHost(NULL), m_szDatabase(NULL), m_szUser(NULL), m_szPassword(NULL), m_szCharacterset(NULL), m_bSecureAuth(false), m_bConnected(false), m_iReferenceCount(0) {}
	virtual ~CDbConnector() {}

			bool		IsConnected()					{ return GetConnected(); }

			const char*	GetHost()						{ return m_szHost; }
			const char*	GetDatabase()					{ return m_szDatabase; }
			const char*	GetUser()						{ return m_szUser; }
			const char*	GetPassword()					{ return m_szPassword; }
			const char*	GetCharacterSet()				{ return m_szCharacterset; }

			bool		GetConnected()					{ return m_bConnected; }
			bool		GetReferenceCount()				{ return m_iReferenceCount; }

			void		SetHost(const char* o)			{ m_szHost = o; }
			void		SetDatabase(const char* o)		{ m_szDatabase = o; }
			void		SetUser(const char* o)			{ m_szUser = o; }
			void		SetPassword(const char* o)		{ m_szPassword = o; }
			void		SetCharacterSet(const char* o)	{ m_szCharacterset = o; }

			bool		GetSecureAuth()					{ return m_bSecureAuth; }
			void		SetSecureAuth(bool o)			{ m_bSecureAuth = o; }

			void		SetConnected(bool o)			{ m_bConnected = o; }
			void		SetReferenceCount(int o)		{ m_iReferenceCount = o; }

			INT			IncrementReference()			{ return ++m_iReferenceCount; }
			INT			DecrementReference()			{ return --m_iReferenceCount; }

			bool		Initialize();
			bool		Release();
			void		Clear();

			bool		Connect();
			bool		Close();

			INT			GetErrno();
			const char*	GetError();

			bool		Query(char&);
			void*		StoreResult();
			UINT64		AffectedRows();
			UINT		FieldCount();
			char**		FetchRow(void*);
			bool		NextResult();
			void		FreeResult(void*);

protected:
			MYSQL		m_Mysql;

			const char*	m_szHost;
			const char*	m_szDatabase;
			const char*	m_szUser;
			const char*	m_szPassword;
			const char*	m_szCharacterset;

			bool		m_bSecureAuth;
			bool		m_bConnected;
			INT			m_iReferenceCount;
};

class CDBM {
public:
	CDBM();
	virtual ~CDBM();

			INT				GetErrno() const				{ if(isptr(GetDbConnector())) return GetDbConnector()->GetErrno(); else return -1; }
			const char*		GetError() const				{ if(isptr(GetDbConnector())) return GetDbConnector()->GetError(); else return "No Error"; }
			void			ErrMsg();

			bool			IsConnected()					{ if(isptr(GetDbConnector())) return GetDbConnector()->IsConnected(); else return false; }

			const char*		GetSQL() const					{ return m_szSQL; }

			CDbConnector*	GetDbConnector() const			{ return m_pkDbConnector; }
			void			SetDbConnector(CDbConnector* o)	{ m_pkDbConnector = o; }

	virtual bool			Initialize(const char&, const char&, const char&, const char&, bool, const char* =NULL);
	virtual bool			Release();

	virtual void			Clear();
	virtual bool			RealQuery();
	virtual UINT64			AffectedRows();
	virtual UINT			FieldCount();
	virtual void*			StoreResult();
	virtual char**			FetchRow(void*);
	virtual bool			NextResult();
	virtual void			FreeResult(void*);

protected:
    		char			m_szSQL[iDATABASE_SQL_BUFFER_LEN];

    		CDbConnector*	m_pkDbConnector;

};
