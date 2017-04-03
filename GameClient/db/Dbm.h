/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <NetEasy/CommonHeader.h>

#include "../Enums.h"
#include "../GlobalVariable.h"

class CDBHeader {
public:
	CDBHeader() : m_iFieldCount(0), m_iRowCount(0), m_iRowSize(0) {}
	~CDBHeader() {}

public:
	INT	m_iFieldCount;
	INT m_iRowCount;
	INT m_iRowSize;

};

class CDBField {
public:
	CDBField();
	CDBField(FIELD_TYPE, INT, INT);
	CDBField(CDBField& o);

	~CDBField() {}

	void		Clear();

	FIELD_TYPE	GetFieldType()			{ return m_eType; }
	INT			GetOffset()				{ return m_iOffset; }
	INT			GetSize()				{ return m_iSize; }

	void		SetName(const char& o)	{ memcpy(m_szName, &o, iDB_FIELD_NAME_LEN); }
	const char*	GetName()				{ return m_szName; }

public:
	FIELD_TYPE	m_eType;
	INT			m_iSize;
	INT			m_iOffset;
	char		m_szName[iDB_FIELD_NAME_LEN];

};

class CDBM {
public:
	CDBM() : m_szData(NULL) {}
	virtual ~CDBM() {}

	bool		Empty()				{ return m_kBox.empty(); }

	void		Clear();

	INT			GetFieldCount()		{ return m_kHeader.m_iFieldCount; }
	INT			GetDataCount()		{ return m_kHeader.m_iRowCount; }
	INT			GetDataSize()		{ return m_kHeader.m_iRowSize; }

	char*		GetData()			{ return m_szData; }
	char*		GetData(INT, INT);

	CDBField*	GetField(const char*);
	CDBField*	GetField(UINT);

	bool		Load(const char*);

	bool		LoadCSV(std::ifstream&);

protected:
	CDBHeader	m_kHeader;
	char*		m_szData;

	typedef std::list< CDBField* >		stl_BoxList;
	typedef stl_BoxList::iterator		IterBoxList;
	stl_BoxList		m_kBox;

	typedef std::list< std::string >	stl_TmpList;
	typedef stl_TmpList::iterator		IterTmpList;

private:

};
