/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */
#pragma once
#include "../item/ItemEx.h"

class CItemEx;

class CInventory {

public:
	CInventory() {}
	~CInventory() {}

	UINT 
	GetSize() {
		return m_Inventory.size();
	}

	void 
	Clear() {
		m_Inventory.clear();
	}

	bool 
	Empty() {
		return m_Inventory.empty();
	}

	void 
	InsertItem(CItemEx* CItemEx_) {
		m_Inventory.push_back(CItemEx_);
	}

	CItemEx*
	GetInventoryItem(UINT o) {
		if (false == m_Inventory.empty()) {
			IterInventoryList iter = m_Inventory.begin();
			advance(iter, o);
			if (iter != m_Inventory.end()) {
				return (*iter);
			}
		}
		return NULL;
	}

private:
	typedef std::list<CItemEx*>				stl_InventoryList;
	typedef stl_InventoryList::iterator		IterInventoryList;

	stl_InventoryList						m_Inventory;
};