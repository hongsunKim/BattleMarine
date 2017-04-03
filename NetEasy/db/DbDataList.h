/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <map>

#include "../util/Singleton.h"
#include "../ReTypedefined.h"

#include "DbData.h"

#define g_kItemInfoList			CItemInfoList::GetInstance()
#define g_kDropInfoList			CDropInfoList::GetInstance()
#define g_kRewardInfoList		CRewardInfoList::GetInstance()
#define g_kModInfoList			CModInfoList::GetInstance()
#define g_kMapInfoList			CMapInfoList::GetInstance()

class CItemInfoList : public CSingleton< CItemInfoList > {
public:
	const SItemInfo*
	Find(UINT o) {
		if(0 < o) {
			Iter iter = m_Box.find(o);
			if(iter != m_Box.end()) {
				return &((*iter).second);
			}
		}
		return NULL;
	}

	bool
	Insert(SItemInfo& o) {
		return m_Box.insert(stl_Map::value_type(o.GetId(), o)).second;
	}

	void
	Clear() {
		m_Box.clear();
	}

	bool
	Empty() {
		return m_Box.empty();
	}

private:
	typedef std::map< UINT, SItemInfo, std::less< UINT > >	stl_Map;
	typedef stl_Map::iterator								Iter;

	stl_Map	m_Box;
};

typedef std::multimap< UINT, SDropInfo, std::less< UINT > >	stl_DropInfoMap;
typedef stl_DropInfoMap::iterator							DropInfoIter;

class CDropInfoList : public CSingleton< CDropInfoList > {
public:
	std::pair< DropInfoIter, DropInfoIter >
	EqualRange(MOD_TYPE o, UINT p) {
		if(MOD_FFA == o) {
			return m_FFA_Box.equal_range(p);
		} else if(MOD_TDM == o) {
			return m_TDM_Box.equal_range(p);
		}
		return m_ZOMBIE_Box.equal_range(p);
	}

	const SDropInfo*
	Find(UINT o) {
		if(0 < o) {
			DropInfoIter iter = m_FFA_Box.begin();
			for(; iter != m_FFA_Box.end(); ) {
				SDropInfo* ptInfo = &(*iter).second;
				if(ptInfo->GetId() == o) {
					return ptInfo;
				}
				++iter;
			}

			iter = m_TDM_Box.begin();
			for(; iter != m_TDM_Box.end(); ) {
				SDropInfo* ptInfo = &(*iter).second;
				if(ptInfo->GetId() == o) {
					return ptInfo;
				}
				++iter;
			}

			iter = m_ZOMBIE_Box.begin();
			for(; iter != m_ZOMBIE_Box.end(); ) {
				SDropInfo* ptInfo = &(*iter).second;
				if(ptInfo->GetId() == o) {
					return ptInfo;
				}
				++iter;
			}
		}
		return NULL;
	}

	bool
	Insert(SDropInfo& o) {
		if(MOD_FFA == o.GetModType()) {
			m_FFA_Box.insert(stl_DropInfoMap::value_type(o.GetGroup(), o));
			return true;
		} else if(MOD_TDM == o.GetModType()) {
			m_TDM_Box.insert(stl_DropInfoMap::value_type(o.GetGroup(), o));
			return true;
		} else if (MOD_ZOMBIE == o.GetModType()) {
			m_ZOMBIE_Box.insert(stl_DropInfoMap::value_type(o.GetGroup(), o));
			return true;
		}
		return false;
	}

	void
	Clear() {
		m_FFA_Box.clear();
		m_TDM_Box.clear();
		m_ZOMBIE_Box.clear();
	}

	bool
	Empty(MOD_TYPE o) {
		if(MOD_FFA == o) {
			return m_FFA_Box.empty();
		} else if(MOD_TDM == o) {
			return m_TDM_Box.empty();
		} else if(MOD_ZOMBIE == o) {
			return m_ZOMBIE_Box.empty();
		}
		return true;
	}

	size_t
	Size(MOD_TYPE o) {
		if(MOD_FFA == o) {
			return m_FFA_Box.size();
		} else if(MOD_TDM == o) {
			return m_TDM_Box.size();
		} else if(MOD_ZOMBIE == o) {
			return m_ZOMBIE_Box.size();
		}
		return 0;
	}

	UINT
	GetMaxGroup(MOD_TYPE o) {
		UINT uiGroup = 0;
		if(MOD_FFA == o) {
			DropInfoIter iter = m_FFA_Box.begin();
			for( ; iter != m_FFA_Box.end(); ) {
				SDropInfo* ptInfo = &(*iter).second;
				if(uiGroup < ptInfo->GetGroup()) {
					uiGroup = ptInfo->GetGroup();
				}
				++iter;
			}
		} else if(MOD_TDM == o) {
			DropInfoIter iter = m_TDM_Box.begin();
			for( ; iter != m_TDM_Box.end(); ) {
				SDropInfo* ptInfo = &(*iter).second;
				if(uiGroup < ptInfo->GetGroup()) {
					uiGroup = ptInfo->GetGroup();
				}
				++iter;
			}
		} else if(MOD_ZOMBIE == o) {
			DropInfoIter iter = m_ZOMBIE_Box.begin();
			for( ; iter != m_ZOMBIE_Box.end(); ) {
				SDropInfo* ptInfo = &(*iter).second;
				if(uiGroup < ptInfo->GetGroup()) {
					uiGroup = ptInfo->GetGroup();
				}
				++iter;
			}
		}
		return uiGroup;
	}

private:
	stl_DropInfoMap	m_FFA_Box;
	stl_DropInfoMap	m_TDM_Box;
	stl_DropInfoMap	m_ZOMBIE_Box;
};

typedef std::multimap< UINT, SRewardInfo, std::less< UINT > >	stl_RewardInfoMap;
typedef stl_RewardInfoMap::iterator								RewardInfoIter;

class CRewardInfoList : public CSingleton< CRewardInfoList > {
public:
	std::pair< RewardInfoIter, RewardInfoIter >
	EqualRange(UINT o) {
		return m_Box.equal_range(o);
	}

	bool
	Insert(SRewardInfo& o) {
		m_Box.insert(stl_RewardInfoMap::value_type(o.GetId(), o));
		return true;
	}

	void
	Clear() {
		m_Box.clear();
	}

	bool
	Empty() {
		return m_Box.empty();
	}

	size_t
	Size(MOD_TYPE o) {
		return m_Box.size();
	}

private:
	stl_RewardInfoMap	m_Box;

};

class CModInfoList : public CSingleton< CModInfoList > {
public:
	const SModInfo*
	Find(MOD_TYPE o) {
		if(0 < o) {
			Iter iter = m_Box.find(o);
			if(iter != m_Box.end()) {
				return &((*iter).second);
			}
		}
		return NULL;
	}

	bool
	Insert(SModInfo& o) {
		return m_Box.insert(stl_Map::value_type(o.GetType(), o)).second;
	}

	void
	Clear() {
		m_Box.clear();
	}

	bool
	Empty() {
		return m_Box.empty();
	}

private:
	typedef std::map< MOD_TYPE, SModInfo, std::less< MOD_TYPE > >	stl_Map;
	typedef stl_Map::iterator										Iter;

	stl_Map	m_Box;
};

class CMapInfoList : public CSingleton< CMapInfoList > {
public:
	const SMapInfo*
	Find(UINT o) {
		if(0 < o) {
			Iter iter = m_Box.find(o);
			if(iter != m_Box.end()) {
				return &((*iter).second);
			}
		}
		return NULL;
	}

	bool
	Insert(SMapInfo& o) {
		return m_Box.insert(stl_Map::value_type(o.GetId(), o)).second;
	}

	void
	Clear() {
		m_Box.clear();
	}

	bool
	Empty() {
		return m_Box.empty();
	}

private:
	typedef std::map< UINT, SMapInfo, std::less< UINT > >	stl_Map;
	typedef stl_Map::iterator								Iter;

	stl_Map	m_Box;
};
