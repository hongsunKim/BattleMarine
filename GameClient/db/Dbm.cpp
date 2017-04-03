/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"
#include "Dbm.h"

const INT iMAX_READLINE_SIZE = 2048;

CDBField::CDBField()
: m_eType(FIELD_BOOL), m_iSize(0), m_iOffset(0) {
	memset(m_szName, 0, iDB_FIELD_NAME_LEN);
}

CDBField::CDBField(FIELD_TYPE eType_, INT iSize_, INT iOffset_)
: m_eType(eType_), m_iSize(iSize_), m_iOffset(iOffset_)
{
	memset(m_szName, 0, iDB_FIELD_NAME_LEN);
}

CDBField::CDBField(CDBField& o)
: m_eType(o.m_eType), m_iSize(o.m_iSize), m_iOffset(o.m_iOffset)
{
	SetName(*o.GetName());
}

void
CDBField::Clear() {
	m_eType = FIELD_BOOL;
	m_iSize = 0;
	m_iOffset = 0;
	memset(m_szName, 0, iDB_FIELD_NAME_LEN);
}

void
CDBM::Clear() {
	m_kHeader.m_iFieldCount = 0;
	m_kHeader.m_iRowSize = 0;
	m_kHeader.m_iRowCount = 0;

	IterBoxList iter = m_kBox.begin();
	for( ; iter != m_kBox.end(); ) {
		CDBField* pkField = (*iter);
		if(isptr(pkField)) {
			pkField->Clear();
			SAFE_DELETE(pkField);
		}
		++iter;
	}
	m_kBox.clear();

	SAFE_DELETE_ARRAY(m_szData);
}

char*
CDBM::GetData(INT iRow_, INT iOffset_) {
	return (m_szData + (iRow_ * m_kHeader.m_iRowSize) + iOffset_);
}

CDBField*
CDBM::GetField(const char* szName_) {
	if(false == Empty()) {
		if(isptr(szName_)) {
			IterBoxList iter = m_kBox.begin();
			for( ; iter != m_kBox.end(); ) {
				CDBField* pkField = (*iter);
				if(isptr(pkField)) {
					if(0 == strcmp(pkField->GetName(), szName_)) {
						return pkField;
					}
				}
				++iter;
			}
		}
	}
	return NULL;
}

CDBField*
CDBM::GetField(UINT uiIndex_) {
	if(false == Empty()) {
		IterBoxList iter = m_kBox.begin();
		advance(iter, uiIndex_);
		if(iter != m_kBox.end()) {
			return (*iter);
		}
	}
	return NULL;
}

bool
CDBM::Load(const char* szPath_) {
	if(isptr(szPath_)) {
		bool bCheck = true;

		std::string szPath(szPath_);

		FILE* fp = fopen(szPath_, "r");
		if(isptr(fp)) {
			fclose(fp);
		} else {
			bCheck = false;
		}

		if(bCheck) {
			size_t stStart = (INT)szPath.rfind(".");
			size_t stEnd = szPath.length();
			if(0 > stStart) {
				bCheck = false;
			} else {
				std::string szExtension = szPath.substr(stStart, stEnd);
				//TRACE("extensions: " << szExtension.c_str());

				if((szExtension.compare(0, 4, ".csv") == 0) || (szExtension.compare(0, 4, ".txt") == 0) || (szExtension.compare(0, 4, ".CSV") == 0) || (szExtension.compare(0, 4, ".TXT") == 0)) {
					std::ifstream kReader(szPath_, std::ios::in);
					return LoadCSV(kReader);
				}
			}
		}
		return bCheck;
	}
	return false;
}

bool
CDBM::LoadCSV(std::ifstream& kReader_) {
	// CSV 포멧의 필드 타입은 모두 string으로 처리합니다.
	char szHeaderLine[iMAX_READLINE_SIZE] = { 0, };
	kReader_.getline(szHeaderLine, iMAX_READLINE_SIZE);
	if(0 >= strlen(szHeaderLine)) {
		kReader_.close();
		return false;
	}

	char* pszHeaderCol = NULL;
	pszHeaderCol = strtok(szHeaderLine, ",");

	for( ; NULL != pszHeaderCol; pszHeaderCol = strtok(NULL, ",")) {
		CDBField* pkField = new CDBField();
		pkField->SetName(*pszHeaderCol);
		m_kBox.push_back(pkField);

		//TRACE("field index: " << m_kHeader.m_iFieldCount << ", name: " << pszHeaderCol);

		// 필드 수 저장.
		++m_kHeader.m_iFieldCount;
	}

	//TRACE("field count: " << m_kHeader.m_iFieldCount);

	stl_TmpList kRow;

	char szDataLine[iMAX_READLINE_SIZE] = { 0, };
	while(kReader_.getline(szDataLine, iMAX_READLINE_SIZE)) {
		if(0 < strlen(szDataLine)) {
			kRow.push_back(szDataLine);
			++m_kHeader.m_iRowCount;
		}
	}

	//TRACE("row count: " << m_kHeader.m_iRowCount);

	// 필드 사이즈 구하기.
	IterTmpList iterTmpList = kRow.begin();
	for( ; iterTmpList != kRow.end(); ) {
		memset(szDataLine, 0, iMAX_READLINE_SIZE);
		memcpy(szDataLine, (*iterTmpList).c_str(), (*iterTmpList).length());

		char* pszDataCol = strtok(szDataLine, ",");
		for(INT i = 0; NULL != pszDataCol; pszDataCol = strtok(NULL, ","), ++i) {
			std::string szData(pszDataCol);

			IterBoxList iterBoxList = m_kBox.begin();
			advance(iterBoxList, i);
			if(iterBoxList != m_kBox.end()) {
				CDBField* pkField = (*iterBoxList);
				if(isptr(pkField)) {
					if(pkField->GetSize() < (INT)szData.length()) {
						pkField->m_iSize = (INT)szData.length();
					}
				}
			}
		}
		++iterTmpList;
	}

	INT iOffset = 0;
	IterBoxList iterBoxList = m_kBox.begin();
	for( ; iterBoxList != m_kBox.end(); ) {
		CDBField* pkField = (*iterBoxList);
		if(isptr(pkField)) {
			INT iSize = pkField->GetSize();

			pkField->m_iOffset = iOffset;

			iOffset += iSize;
			m_kHeader.m_iRowSize += iSize;
		}
		++iterBoxList;
	}

	//TRACE("row size: " << m_kHeader.m_iRowSize);

	INT iDataSize = m_kHeader.m_iRowCount * m_kHeader.m_iRowSize;
	//TRACE("data size: " << iDataSize);

	m_szData = new char[iDataSize];

	// 데이터 행(Row) 저장.
	INT iRowCount = 0;
	iterTmpList = kRow.begin();
	for( ; iterTmpList != kRow.end(); ) {
		memset(szDataLine, 0, iMAX_READLINE_SIZE);
		memcpy(szDataLine, (*iterTmpList).c_str(), (*iterTmpList).length());

		char* pszDataCol = strtok(szDataLine, ",");
		for(INT i = 0; NULL != pszDataCol; pszDataCol = strtok(NULL, ","), ++i) {
			std::string szData(pszDataCol);

			iterBoxList = m_kBox.begin();
			advance(iterBoxList, i);
			if(iterBoxList != m_kBox.end()) {
				CDBField* pkField = (*iterBoxList);
				if(isptr(pkField)) {
					if((INT)szData.length() < pkField->GetSize()) {
						for(INT j = 0; j < (pkField->GetSize() - (INT)szData.length()); ++j) {
							szData += '\0';
						}
					}
					memcpy(m_szData + (iRowCount * m_kHeader.m_iRowSize) + pkField->GetOffset(), szData.c_str(), pkField->GetSize());
				}
			}
		}
		++iRowCount;
		++iterTmpList;
	}

	kRow.clear();

	kReader_.close();

	return true;
}

/* EOF */
