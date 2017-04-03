/*
* Education Frameworks
* Copyright © 2015-2017 Origin Studio Inc.
*
*/
#pragma once
//장미경
#include "../CommonHeader.h"

#define g_kDropItemMgr	CDropItemMgr::GetInstance()


class CItemEx;
class CDropItemMgr : public CSingleton< CDropItemMgr >
{
public:
	CDropItemMgr() {}
	~CDropItemMgr() {}

	bool 
	Empty()	{ 
		return m_kDropItem.empty(); 
	}

	UINT 
	GetSize() { 
		return m_kDropItem.size(); 
	}

	void 
	ClearDropItem()	{ 
		m_kDropItem.clear(); 
	}

	bool 
	EmptyDropItem()	{ 
		return m_kDropItem.empty(); 
	}

	bool 
	InsertDropItem(CItemEx* cItemEx_) {
		return m_kDropItem.insert(stl_DropItemMap::value_type(cItemEx_->GetSerial(), cItemEx_)).second;
	}

	void
	DeleteDropItem(UINT64 uiSerial_) {
		m_kDropItem.erase(uiSerial_);
	}

	const CItemEx* 
	GetDropItem(UINT64 o) {
		if (0 < o) {
			Iter iter = m_kDropItem.find(o);
			if (iter != m_kDropItem.end()) {
				return (*iter).second;
			}
		}
		return NULL;
	}

	CItemEx* 
	SeekDropItem(UINT uiIndex_) {
		if (false == m_kDropItem.empty()) {
			Iter iter = m_kDropItem.begin();
			advance(iter, uiIndex_);
			if (iter != m_kDropItem.end()) {
				return (*iter).second;
			}
		}
	}


private:
	typedef std::map<UINT64, CItemEx*, std::less<UINT>>	stl_DropItemMap;
	typedef stl_DropItemMap::iterator					Iter;

	stl_DropItemMap			m_kDropItem;

};

