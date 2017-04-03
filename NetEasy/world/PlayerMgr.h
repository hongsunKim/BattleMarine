/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <map>

#include "../util/Singleton.h"
#include "Player.h"

#define g_kMainPlayer CPlayerMgr::GetInstance().GetMainPlayer()
#define g_kPlayerMgr CPlayerMgr::GetInstance()

class CPlayerMgr : public CSingleton< CPlayerMgr > {
public:
	CPlayerMgr() : m_pkMainPlayer(NULL) {}
	~CPlayerMgr() {}

	void		Initialize();
	void		Release();

	void		Update();

	bool		Insert(CPlayer&);

	bool		Delete(UINT);
	bool		DeleteKey(UINT);

	CPlayer*	GetPlayer(UINT);

	CPlayer*	Find(UINT);
	CPlayer*	Seek(UINT);

	size_t		Size()						{ return m_kMap.size(); }
	void		Clear()						{ m_kMap.clear(); }
	bool		Empty()						{ return m_kMap.empty(); }

	CPlayer*	GetMainPlayer()				{ return m_pkMainPlayer; }
	void		SetMainPlayer(CPlayer* o)	{ m_pkMainPlayer = o; }

private:
	CPlayer*	m_pkMainPlayer;

private:
	typedef std::map< UINT, CPlayer*, std::less<UINT> >	stl_Map;
	typedef stl_Map::iterator	Iter;

	stl_Map		m_kMap;

};
