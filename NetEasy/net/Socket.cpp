/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "Socket.h"

#include "../CommonHeader.h"

CTcpSocket::CTcpSocket()
: m_stSize(sizeof(SOCKADDR)), m_skSocket(INVALID_SOCKET), m_bConnected(false)
, m_iRecvFlags(0), m_iSendFlags(0)
{
	memset(&m_saRemoteAddr_in, 0, sizeof(SOCKADDR_IN));
	memset(&m_saLocalAddr_in, 0, sizeof(SOCKADDR_IN));
}

CTcpSocket::~CTcpSocket() {
}

SOCKET
CTcpSocket::CreateSocket() {
	if (INVALID_SOCKET != GetSocket()) {
		return GetSocket();
	}

	SOCKET skSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET != skSocket) {
		SetSocket(skSocket);

		INT iSendValue = iDEFAULT_SO_SNDBUF_SIZE;
		SetSocketOption(SO_SNDBUF, iSendValue);

		INT iRecvValue = iDEFAULT_SO_RCVBUF_SIZE;
		SetSocketOption(SO_RCVBUF, iRecvValue);

		SetTcpOption(TCP_NODELAY, true);

		ULONG iVal = 1;
		ioctlsocket(GetSocket(), FIONBIO, &iVal);

		return GetSocket();
	} else {
		OUTPUT("critical error: socket create failed: ");
	}
	return INVALID_SOCKET;
}

bool
CTcpSocket::Clear() {
	memset(&m_saRemoteAddr_in, 0, sizeof(SOCKADDR_IN));
	memset(&m_saLocalAddr_in, 0, sizeof(SOCKADDR_IN));

	m_bConnected = false;
	m_skSocket = INVALID_SOCKET;

	return true;
}

bool
CTcpSocket::Connect(const char* szAddr_, INT iPort_) {
	if(INVALID_SOCKET != CreateSocket()) {
		SetRemoteAddress(szAddr_, iPort_);

		ULONG iVal = 0;
		ioctlsocket(GetSocket(), FIONBIO, &iVal);

		INT iRet = connect(GetSocket(), (const SOCKADDR*)&m_saRemoteAddr_in, m_stSize);
		if (0 == iRet) {
			iVal = 1;
			ioctlsocket(GetSocket(), FIONBIO, &iVal);

			OUTPUT("[" << GetSocket() << "]");
			OUTPUT("local address: " << GetLocalAddress() << ", port: " << GetLocalPort());
			OUTPUT("remote address: " << GetRemoteAddress() << ", port: " << GetRemotePort());
			return true;
		} else if((EINPROGRESS == ERRNO) || (EWOULDBLOCK == ERRNO)) {
			// 예외 처리 위치
			OUTPUT("error: EINPTOGRESS or EWOULDBLOCK");
		} else {
			OUTPUT("critical error: [" << GetSocket() << "] connect failed: errno[" << ERRNO << "]");
			OUTPUT("local address: " << GetLocalAddress() << ", port: " << GetLocalPort());
			OUTPUT("remote address: " << GetRemoteAddress() << ", port: " << GetRemotePort());
		}
		Disconnect();
	}
	return false;
}

bool
CTcpSocket::Disconnect() {
	
	m_bConnected = false;

	if (INVALID_SOCKET != m_skSocket) {
		shutdown(m_skSocket, SD_BOTH);
		if (0 != closesocket(m_skSocket)) {
			OUTPUT("critical error: close failed: [" << m_skSocket << "]");
		}
		m_skSocket = INVALID_SOCKET;
		return true;
	}
	m_skSocket = INVALID_SOCKET;
	return false;
}

SOCKET
CTcpSocket::Bind(const char* szAddr_, INT iPort_) {
	if (INVALID_SOCKET != CreateSocket()) {
		SetLocalAddress(szAddr_, iPort_);

		SetSocketOption(SO_REUSEADDR, true);

		if (0 == bind(GetSocket(), (SOCKADDR*)&m_saLocalAddr_in, sizeof(SOCKADDR))) {
			getsockname(GetSocket(), (SOCKADDR*)&m_saLocalAddr_in, (INT*)&m_stSize);
			return GetSocket();
		} else {
			OUTPUT("bind failed: " << GetSocket() << ": errno[" << ERRNO << "]");
		}
		Disconnect();
	}
	return INVALID_SOCKET;
}

bool
CTcpSocket::SetSocketOption(INT iOption_, INT iValue_)
{
	if (INVALID_SOCKET != m_skSocket) {
		if (0 == setsockopt(m_skSocket, SOL_SOCKET, iOption_, (const char*)&iValue_, sizeof(iValue_))) {
			return true;
		} else {
			//
		}
	} else {
		OUTPUT("critical error: socket is invalid");
	}
	return false;
}

INT
CTcpSocket::GetSocketOption(INT iOption_) {
	if (INVALID_SOCKET != m_skSocket) {
		INT iValue = -1;
		size_t stOption = sizeof(iValue);
		if (0 == getsockopt(m_skSocket, SOL_SOCKET, iOption_, (char*)&iValue, (INT*)&stOption)) {
			return iValue;
		} else {
			OUTPUT("critical error: getsockopt() failed: errno[" << ERRNO << "]");
		}
	}
	else {
		OUTPUT("critical error: socket is invalid");
	}
	return -1;
}

bool
CTcpSocket::SetTcpOption(INT iOption_, INT iValue_) {
	if (INVALID_SOCKET != GetSocket()) {
		INT iRet = setsockopt(GetSocket(), IPPROTO_TCP, iOption_, (const char*)&iValue_, sizeof(iValue_));
		if (0 == iRet) {
			return true;
		}
		else {
			OUTPUT("critical error: setsockopt() failed: errno[" << ERRNO << "]");
		}
	}
	else {
		OUTPUT("critical error: socket is invalid");
	}
	return false;
}

bool
CTcpSocket::SameRemoteAddressIn(const SOCKADDR_IN& rsaSockAddr_) {
	if ((rsaSockAddr_.sin_port == m_saRemoteAddr_in.sin_port)
	&& (rsaSockAddr_.sin_addr.s_addr == m_saRemoteAddr_in.sin_addr.s_addr)) {
		return true;
	}
	return false;
}

bool
CTcpSocket::SameLocalAddressIn(const SOCKADDR_IN& rsaSockAddr_) {
	if ((rsaSockAddr_.sin_port == m_saLocalAddr_in.sin_port)
		&& (rsaSockAddr_.sin_addr.s_addr == m_saLocalAddr_in.sin_addr.s_addr)) {
		return true;
	}
	return false;
}

void
CTcpSocket::SetRemoteAddress(const char* szAddr_, INT iPort_) {
	memset(&m_saRemoteAddr_in, 0, sizeof(SOCKADDR_IN));

	m_saRemoteAddr_in.sin_family = AF_INET;

	if (isptr(szAddr_)) {
		m_saRemoteAddr_in.sin_addr.s_addr = inet_addr(szAddr_);
		m_saRemoteAddr_in.sin_port = htons(iPort_);
	}
}

void
CTcpSocket::SetLocalAddress(const char* szAddr_, INT iPort_) {
	memset(&m_saLocalAddr_in, 0, sizeof(SOCKADDR_IN));

	m_saLocalAddr_in.sin_family = AF_INET;

	if (isptr(szAddr_)) {
		m_saLocalAddr_in.sin_addr.s_addr = inet_addr(szAddr_);
		m_saLocalAddr_in.sin_port = htons(iPort_);
	}
}

void
CTcpSocket::SetRemoteAddress(const SOCKADDR_IN& rsaSockAddr_) {
	memcpy(&m_saRemoteAddr_in, &rsaSockAddr_, m_stSize);
}

void
CTcpSocket::SetLocalAddress(const SOCKADDR_IN& rsaSockAddr_) {
	memcpy(&m_saLocalAddr_in, &rsaSockAddr_, m_stSize);
}

INT
CTcpSocket::Read(char& szData_, INT iSize_) {
	INT iRet = recv(GetSocket(), &szData_, iSize_, m_iRecvFlags);

	if (0 < iRet) {
		return iRet;
	}
	else {
		if ((EWOULDBLOCK == ERRNO) || (EINTR == ERRNO) || (ENOBUFS == ERRNO)) {
			return 0;
		}
	}
	return SOCKET_ERROR;
}

INT
CTcpSocket::Send(const char& szData_, INT iSize_) {
	INT iRet = send(GetSocket(), &szData_, iSize_, m_iSendFlags);
	
	if (0 < iRet) {
		return iRet;
	} else {
		if ((EWOULDBLOCK == ERRNO) || (EINTR == ERRNO) || (ENOBUFS == ERRNO)) {
			return 0;
		}
	}
	return SOCKET_ERROR;
}

SOCKET
CTcpSocket::Listen(const char* szAddr_, INT iPort_) {
	if (0 < iPort_) {
		if (INVALID_SOCKET != CreateSocket()) {
			SetLocalAddress(szAddr_, iPort_);

			SetSocketOption(SO_REUSEADDR, true);

			if (0 == bind(GetSocket(), (struct sockaddr*)&m_saLocalAddr_in, m_stSize)) {
				INT iRet = listen(GetSocket(), iTCP_MAX_SYN_BACKLOG);
				if (0 == iRet) {
					OUTPUT("[" << GetSocket() << "] Listen() OK: " << GetLocalAddress() << ", " << GetLocalPort());
					return GetSocket();
				} else {
					OUTPUT("critical error: Listen() - listen() failed: " << GetLocalAddress() << ", " << GetLocalPort());
				}
			} else {
				OUTPUT("crtical error: Listen() - bind() failed: " << GetLocalAddress() << ", " << GetLocalPort());
			}
			Disconnect();
		} else {
			// socket error
		}
	}
	else {
		// Address is null
		OUTPUT("critical error: Listen() failed: port is wrong: addr: " << szAddr_ << ", port: " << iPort_);
	}
	return INVALID_SOCKET;
}

SOCKET
CTcpSocket::Accept() {
	SOCKET skNewSocket = accept(GetSocket(), (SOCKADDR*)&m_saRemoteAddr_in, (INT*)&m_stSize);
	if (0 < skNewSocket) {
		TRACE("Accept() OK: [" << skNewSocket << "] retmote address: " << GetRemoteAddress() << ", port: " << GetRemotePort());
		return skNewSocket;
	} else {
		OUTPUT("critical error: Accept() failed: errno[" << ERRNO << "]");
	}
	return INVALID_SOCKET;
}
