/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "../CommonHeader.h"

CConnector::CConnector()
: m_acRecvBuffer(NULL), m_pkSocket(NULL), m_pkSensor(NULL), m_pkBody(NULL), m_bRegister(false) {
	m_pkSocket = new CTcpSocket();
	m_acRecvBuffer = new char[iDEFAULT_SO_RCVBUF_SIZE];

	if(isptr(m_acRecvBuffer)) {
		m_kStreamBuffer.SetBuffer(m_acRecvBuffer, iDEFAULT_SO_RCVBUF_SIZE);
	}
}

CConnector::~CConnector() {
	SAFE_DELETE_ARRAY(m_acRecvBuffer);
	SAFE_DELETE(m_pkSocket);
}

bool
CConnector::Connect(const char* szAddr_, int iPort_) {
	if (isptr(m_pkSensor)) {
		if (0 < iPort_) {
			if (IsRegister()) {
				m_pkSensor->Unregister(GetSocket());
				SetRegister(false);
			}

			if (m_pkSocket->Connect(szAddr_, iPort_)) {
				SetConnected();

				CPlayer* pkPlayer = (CPlayer*)g_kPlayerFactory.Create();
				pkPlayer->SetIndex((UINT)m_pkSocket->GetSocket());
				pkPlayer->SetName("NONAME");
				pkPlayer->SetConnector(this);
				SetBody(pkPlayer);

				//SetRemoteAddress(m_pkSocket->GetRemoteAddressIn());

				g_kPlayerMgr.Insert(*pkPlayer);
				g_kPlayerMgr.SetMainPlayer(pkPlayer);

				if (m_pkSensor->Register(GetSocket())) {
					SetRegister(true);
					return true;
				}
				Disconnect(GetSocket());
				return false;
			} else {
				OUTPUT("critical error: Connect() is failed: " << szAddr_ << ", port: " << iPort_);
			}
		}
	}
	return false;
}

bool
CConnector::Disconnect(const SOCKET o) {
	OUTPUT("disconnect: socket [" << o << "]");
	if (GetSocket() == o) {
		Clear();
		return (o != INVALID_SOCKET);
	}
	return false;
}

void
CConnector::Clear() {
	if (IsRegister()) {
		if(isptr(m_pkSensor)) {
			m_pkSensor->Unregister(GetSocket());
		}
		SetRegister(false);
	}

	if (isptr(m_pkSocket)) {
		m_pkSocket->Disconnect();
	}
}

INT
CConnector::Send(CCommand& rkCommand_, INT iSize_) {
	iSize_ += iCOMMAND_HEAD_SIZE;
	if (iSize_ <= iPACKET_DATA_SIZE) {
		if (IsConnected()) {
			CTcpPacket kPacket(GetSocket());
			memcpy((char*)&kPacket.GetCommand(), (const char*)&rkCommand_, iSize_);


			iSize_ += iTCP_PACKET_HEAD_SIZE;
			kPacket.SetSize(iSize_);

			return m_pkSocket->Send((const char&)kPacket, iSize_);
		}
		else {
			OUTPUT("critical error: Send() is failed: disconnected: [" << rkCommand_.GetOrder() << "] " << iSize_ << ":" << iPACKET_DATA_SIZE);
		}
	} else {
		OUTPUT("critical error: Send() is failed: data is too big size: [" << rkCommand_.GetOrder() << "] " << iSize_ << ":" << iPACKET_DATA_SIZE);
		return 0;
	}
	return -2;
}

bool
CConnector::Read() {
	if (IsConnected()) {
		CTcpPacket* pkPacket = NULL;
		UINT uiBufferSize = m_kStreamBuffer.GetSize();

		INT iCurrentSize = 0;

		do {
			while ((UINT)(iTCP_PACKET_HEAD_SIZE) <= uiBufferSize) {
				char* pcBuffer = m_kStreamBuffer.GetBuffer(iCurrentSize);
				pkPacket = (CTcpPacket*)pcBuffer;

				if ((iTCP_PACKET_HEAD_SIZE + iCOMMAND_HEAD_SIZE) <= pkPacket->GetSize()) {
					STcpPacketHeader& pkPacketHeader = pkPacket->GetPacketHeader();
					if ((iTCP_PACKET_HEAD_SIZE <= pkPacketHeader.size)) {
						if (pkPacket->GetSize() <= uiBufferSize) {
							Launcher(&pkPacket->GetCommand());

							iCurrentSize += pkPacket->GetSize();
							uiBufferSize -= pkPacket->GetSize();
						} else {
							break;
						}
					} else {
						//OUTPUT("[" << GetSocket() << "] critical error: packet is invalid: " << GetRemoteAddress());
						return false;
					}
				} else {
					if ((UINT)(iTCP_PACKET_HEAD_SIZE) != pkPacket->GetSize()) {
						//OUTPUT("[" << GetSocket() << "] critical error: header is invalid: " << GetRemoteAddress());
						return false;
					} else {
						iCurrentSize += iTCP_PACKET_HEAD_SIZE;
						uiBufferSize -= iTCP_PACKET_HEAD_SIZE;
					}
				}
			}

			if (0 < iCurrentSize) {
				uiBufferSize = m_kStreamBuffer.Move(iCurrentSize);
				iCurrentSize = 0;
				//break;
				return true;
			}

			TRACE("buffer size: " << uiBufferSize);

			// 여기가 첫 실행. -> 이후 계속 대기하면서 실행.
			// GetLast 함수는 Offset 위치가 반영이된 버퍼 포인터 반환.
			INT iRet = m_pkSocket->Read(m_kStreamBuffer.GetLast(), (INT)m_kStreamBuffer.RestSize());
			if (0 < iRet) {
				// AddSize를 하면서 실제 버퍼의 Offset 위치를 이동.
				uiBufferSize = m_kStreamBuffer.AddSize(iRet);
			} else {
				if (SOCKET_ERROR == iRet) {
					return false;
				} else {
					return true;
				}
			}
		} while ((UINT)(iTCP_PACKET_HEAD_SIZE) <= uiBufferSize);

		return true;
	}
	else {
		OUTPUT("[" << GetSocket() << "] is disconnected: ");
	}
	return false;
}

void
CConnector::SetConnected() {
	m_kStreamBuffer.Clear();

	if (INVALID_SOCKET != GetSocket()) {
		ULONG iVal = 1;
		ioctlsocket(GetSocket(), FIONBIO, &iVal);
	} else {
		OUTPUT("critical error: INVALID_SOCKET");
	}

	m_pkSocket->SetConnected();
}
