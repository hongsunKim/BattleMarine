/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#pragma once

#include <winsock2.h>
#include "../ReTypedefined.h"

class CTcpSocket {
public:
	CTcpSocket();
	virtual ~CTcpSocket();

	virtual	SOCKET				CreateSocket();

	virtual	bool				Clear();
	
	virtual	bool				Connect(const char*, INT);
	virtual	bool				Disconnect();

			INT					Read(char&, INT);
			INT					Send(const char&, INT);

			SOCKET				Bind(const char*, INT);

			SOCKET				Listen(const char*, INT);
			SOCKET				Accept();

			bool				SetSocketOption(INT, INT);
			INT					GetSocketOption(INT);

			bool				SetTcpOption(INT, INT);

			bool				IsConnected()				{ return m_bConnected; }
			void				SetConnect(bool o)			{ m_bConnected = o; }

			const SOCKET		GetSocket() const			{ return m_skSocket; }
			void				SetSocket(const SOCKET o)	{ m_skSocket = o; }
			void				SetConnected()				{ m_bConnected = true; }

			const char*			GetRemoteAddress() const	{ return inet_ntoa(m_saRemoteAddr_in.sin_addr); }
			const ULONG			GetRemoteSinAddress() const	{ return m_saRemoteAddr_in.sin_addr.s_addr; }
			const SOCKADDR_IN&	GetRemoteAddressIn()		{ return m_saRemoteAddr_in; }
			INT					GetRemotePort()				{ return ntohs(m_saRemoteAddr_in.sin_port); }

			const char*			GetLocalAddress() const		{ return inet_ntoa(m_saLocalAddr_in.sin_addr); }
			const ULONG			GetLocalSinAddress() const	{ return m_saLocalAddr_in.sin_addr.s_addr; }
			const SOCKADDR_IN&	GetLocalAddressIn()			{ return m_saLocalAddr_in; }
			INT					GetLocalPort()				{ return ntohs(m_saLocalAddr_in.sin_port); }

			bool				SameRemoteAddressIn(const SOCKADDR_IN&);
			bool				SameLocalAddressIn(const SOCKADDR_IN&);

			void				SetRemoteAddress(const char*, INT);
			void				SetLocalAddress(const char*, INT);

			void				SetRemoteAddress(const SOCKADDR_IN&);
			void				SetLocalAddress(const SOCKADDR_IN&);

			void				ClearRemoteAddress()		{ memset(&m_saRemoteAddr_in, 0, sizeof(SOCKADDR_IN)); }
			void				ClearLocalAddress()			{ memset(&m_saLocalAddr_in, 0, sizeof(SOCKADDR_IN)); }

private:
			SOCKADDR_IN		m_saRemoteAddr_in;
			SOCKADDR_IN		m_saLocalAddr_in;
			size_t			m_stSize;
			SOCKET			m_skSocket;

			bool			m_bConnected;

			INT				m_iRecvFlags;
			INT				m_iSendFlags;
};
