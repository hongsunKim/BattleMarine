/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <map>

#include <NetEasy/CommonHeader.h>

#define g_kMainRoom	CRoomEx::GetInstance()

class CRoomEx : public CRoom, public CSingleton< CRoomEx > {
public:
	CRoomEx() {}
	virtual ~CRoomEx() {}

	virtual bool		Initialize();
	virtual bool		Release();
	virtual void		Clear();

	static void*		New()				{ return new CRoomEx; }

			bool		InsertRoomList(SRoomInfo&);

			bool		DeleteRoomList(UINT);

			SRoomInfo*	PeekFrontRoomList();

			SRoomInfo*	FindRoomList(UINT);
			SRoomInfo*	SeekRoomList(UINT);

			size_t		SizeRoomList()		{ return m_kMap.size(); }
			void		ClearRoomList()		{ m_kMap.clear(); }
			bool		EmptyRoomList()		{ return m_kMap.empty(); }

private:
	typedef std::map< UINT, SRoomInfo, std::less<UINT> >	stl_Map;
	typedef stl_Map::iterator	Iter;

	stl_Map		m_kMap;
};
