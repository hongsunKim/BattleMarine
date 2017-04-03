/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <winsock2.h>
#include "../ReTypedefined.h"
#include "../GlobalVariable.h"

#include "Listener.h"

class ISensor {
public:
	ISensor() : m_uiCount(0) {}
	virtual ~ISensor() {}

	virtual bool	Initialize(UINT)			{ return true; }
	virtual void	Release()					{}
	virtual void	Clear()						{ m_uiCount = 0; }

	virtual INT		WaitEvent(INT)				{ return -1; }

	virtual bool	Register(const SOCKET)		{ return false; }
	virtual bool	Unregister(const SOCKET)	{ return false; }

			UINT	GetCount()					{ return m_uiCount; }
			void	SetCount(UINT o)			{ m_uiCount = o; }

protected:
			void	IncreasedCount()			{ ++m_uiCount; }
			void	DecreasedCount()			{ --m_uiCount; }

protected:
	UINT	m_uiCount;

};

//class CIOCPSensor : public ISensor {
//public:
//
//private:
//
//};

class CEventSelectSensor : public ISensor {
public:
	CEventSelectSensor();
	virtual ~CEventSelectSensor();

	virtual bool	Initialize(UINT);
	virtual void	Release();
	virtual void	Clear();
	virtual INT		WaitEvent(INT);

	virtual bool	Register(const SOCKET);
	virtual bool	Unregister(const SOCKET);

	CListener*		GetListener()				{ return m_pkListener; }
	void			SetListener(CListener* o)	{ m_pkListener = o; }

private:
	inline void		SetMaxConnection(UINT o)	{ m_uiMaxConnection = o; }
	inline UINT		GetMaxConnection()			{ return m_uiMaxConnection; }

	inline bool		IsACCEPT(LONG o)			{ return ((o & FD_ACCEPT) ? true : false); }
	inline bool		IsREAD(LONG o)				{ return ((o & FD_READ) ? true : false); }
	inline bool		IsCLOSE(LONG o)				{ return ((o & FD_CLOSE) ? true : false); }

	inline bool		InRange(UINT o)				{ return (o < GetMaxConnection()); }

private:
	CListener*	m_pkListener;

	UINT		m_uiMaxConnection;
	SOCKET		m_skSockets[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT	m_kEvents[WSA_MAXIMUM_WAIT_EVENTS];
};
