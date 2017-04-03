/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include "Socket.h"
#include "Buffer.h"
#include "Command.h"

class CPlayer;
class ISensor;

class CConnector {
public:
	CConnector();
	virtual ~CConnector();

	virtual bool				Connect(const char* pszAddr_, int iPort_);
	virtual bool				Disconnect(const SOCKET);

			void				Clear();

	virtual void				Launcher(CCommand*)							{}

			SOCKET				Bind(const char* o, INT p)					{ return m_pkSocket->Bind(o, p); }
	virtual INT					Listen(const char* o, INT p)				{ return -1; }

	virtual INT					Send(CCommand&, INT = 0);
	virtual bool				Read();

			void				SetSocket(const SOCKET o)					{ m_pkSocket->SetSocket(o); }

			SOCKET				CreateSocket()								{ return m_pkSocket->CreateSocket(); }

			CTcpSocket*			GetTcpSocket()								{ return m_pkSocket; }
			const SOCKET		GetSocket()									{ if (isptr(m_pkSocket)) { return m_pkSocket->GetSocket(); } return INVALID_SOCKET; }

			ISensor*			GetSensor()									{ return m_pkSensor; }
			void				SetSensor(ISensor* o)						{ m_pkSensor = o; }

			CPlayer*			GetBody()									{ return m_pkBody; }
			void				SetBody(CPlayer* o)							{ m_pkBody = o; }

			void				SetRegister(bool o)							{ m_bRegister = o; }
			bool				IsRegister()								{ return m_bRegister; }

			void				SetConnected();
			bool				IsConnected()								{ return m_pkSocket->IsConnected(); }

			void				SetRemoteAddress(const char* o, INT p)		{ m_pkSocket->SetRemoteAddress(o, p); }
			void				SetLocalAddress(const char* o, INT p)		{ m_pkSocket->SetLocalAddress(o, p); }

			void				SetRemoteAddress(const SOCKADDR_IN& o)		{ m_pkSocket->SetRemoteAddress(o); }
			void				SetLocalAddress(const SOCKADDR_IN& o)		{ m_pkSocket->SetLocalAddress(o); }

			const char*			GetRemoteAddress()							{ return m_pkSocket->GetRemoteAddress(); }
			const SOCKADDR_IN&	GetRemoteAddressIn()						{ return m_pkSocket->GetRemoteAddressIn(); }
			INT					GetRemotePort()								{ return m_pkSocket->GetRemotePort(); }

			const char*			GetLocalAddress()							{ return m_pkSocket->GetLocalAddress(); }
			const SOCKADDR_IN&	GetLocalAddressIn()							{ return m_pkSocket->GetLocalAddressIn(); }
			INT					GetLocalPort()								{ return m_pkSocket->GetLocalPort(); }

			void				ClearRemoteAddress()						{ m_pkSocket->ClearRemoteAddress(); }
			void				ClearLocalAddress()							{ m_pkSocket->ClearLocalAddress(); }

			bool				SameRemoteAddressIn(const SOCKADDR_IN& o)	{ return m_pkSocket->SameRemoteAddressIn(o); }
			bool				SameLocalAddressIn(const SOCKADDR_IN& o)	{ return m_pkSocket->SameLocalAddressIn(o); }

protected:
			CTcpSocket*		m_pkSocket;
			ISensor*		m_pkSensor;
			CPlayer*		m_pkBody;

			bool			m_bRegister;

private:
			CStreamBuffer	m_kStreamBuffer;
			char*			m_acRecvBuffer;
};
