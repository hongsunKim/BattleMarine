/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "../GlobalVariable.h"
#include "../Enums.h"

#include "ItemData.h"
#include "../db/DbDataList.h"

class CPlayer;

class CItem {
public:
	CItem() : m_ptItemInfo(NULL), m_uiKey(0), m_pkBody(NULL) {}
	virtual ~CItem() { Clear(); }

	virtual	void				Initialize()					{}
	virtual	void				Release()						{ Clear(); }

	virtual	void
	Clear() {
		m_uiKey = 0;
		m_pkBody = NULL;

		m_tData.Clear();
		m_ptItemInfo = NULL;
	}

			CPlayer*			GetBody()						{ return m_pkBody; }
			void				SetBody(CPlayer* o)				{ m_pkBody = o; }

			const UINT			GetKey() const					{ return m_uiKey; }
			void				SetKey(const UINT o)			{ m_uiKey = o; }

			const SItemInfo*	GetItemInfo() const				{ return m_ptItemInfo; }
			const SItemData&	GetData() const					{ return m_tData; }

			const UINT			GetId() const					{ return m_tData.id; }
			const UINT			GetStocks() const				{ return m_tData.stocks; }
			const UINT64		GetSerial() const				{ return m_tData.serial; }

			void				SetData(const SItemData& o)		{ m_tData = o; }

			void				SetId(const UINT o)				{
									const SItemInfo* ptItemInfo = g_kItemInfoList.Find(o);
									if(isptr(ptItemInfo)) {
										m_tData.id = o;
										m_ptItemInfo = ptItemInfo;
									} else {
										Clear();
									}
								}

			void				SetStocks(const UINT o)			{ m_tData.stocks = o; }
			void				SetSerial(const UINT64 o)		{ m_tData.serial = o; }

			void				Consume()						{ if(0 < m_tData.stocks) --m_tData.stocks; }

			ITEM_TYPE			GetItemType()					{
									if(isptr(m_ptItemInfo)) {
										return m_ptItemInfo->GetItemType();
									} else {
										return ITEM_NONE;
									}
								}

protected:
			const SItemInfo*	m_ptItemInfo;
			SItemData			m_tData;
			SPosition			m_tPos;

private:
			UINT		m_uiKey;
			CPlayer*	m_pkBody;

};
