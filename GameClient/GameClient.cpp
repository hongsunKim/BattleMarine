/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

//#include "stdafx.h"

#include "GameClient.h"
#include "CommonHeader.h"

using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "lib_json.lib")
#pragma comment(lib, "msimg32.lib")	//박준석

#define MAX_LOADSTRING 100

tick_t g_kPingTick = 0;

bool g_bRunning = true;
bool g_bWireFrame = false;
bool g_bCollisionMap = false;

bool g_bLobby = false;
bool g_bRoom = false;
bool g_bInventory = false;
bool g_bConsole = false;

bool g_bAttack = false;
bool g_bUp = false;
bool g_bRight = false;
bool g_bDown = false;
bool g_bLeft = false;

int g_iElapsedTime = 0;
int g_iFramePerSecond = 0;
char g_cFPS[16] = { 0, };

CConnector* g_pkConnector = NULL;

Bitmap* g_pkBackgroundMap = NULL;
Bitmap* g_pkCollisionMap = NULL;

//장미경
bool g_bDropItem = false;
Bitmap* g_pkActiveItem = NULL;
Bitmap* g_pkPassiveItem = NULL;
CInventory* g_pkInventory = NULL;


Color *Red_Color = new Color(ARGB(4294901760));  //전병찬

Bitmap* g_pkPlayerSymbol = NULL;		//박준석
bool	g_fogOnOff = 0;					//박준석
bool	g_fogMemory = false;			//박준석

HBITMAP g_hBit = NULL;

HWND g_hWnd = NULL;
//HWND g_hDlg = NULL;

HWND g_hLobbyDlg = NULL;
HWND g_hRoomDlg = NULL;
HWND g_hInventoryDlg = NULL;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ConnectDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    JoinUsDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AccountDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    NewRoomDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    LobbyDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    RoomDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    InventoryDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ConsoleDialog(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void
REFRESH_USER_LIST() {
	if (isptr(g_hLobbyDlg)) {
		SendMessage(GetDlgItem(g_hLobbyDlg, IDC_USER_LIST), LB_RESETCONTENT, 0, 0);

		for (UINT i = 0; i < g_kPlayerMgr.Size(); ++i) {
			CPlayer* pkPlayer = g_kPlayerMgr.Seek(i);
			if (isptr(pkPlayer)) {
				if (pkPlayer->GetIsRoom() == false)
				{
					TCHAR szPlayerName[iPLAYER_NAME_LEN + 30] = { 0, };
					sprintf(szPlayerName, "%s (%d:%d)", pkPlayer->GetName(), pkPlayer->GetIndex(), pkPlayer->GetKey());

					SendMessage(GetDlgItem(g_hLobbyDlg, IDC_USER_LIST), LB_ADDSTRING, 0, (LPARAM)szPlayerName);
				}
			}
		}
	}
}

void
REFRESH_ROOM_LIST() {
	if (isptr(g_hLobbyDlg)) {
		SendMessage(GetDlgItem(g_hLobbyDlg, IDC_ROOM_LIST), LB_RESETCONTENT, 0, 0);

		for (UINT i = 0; i < g_kMainRoom.SizeRoomList(); ++i) {
			SRoomInfo* ptRoomInfo = g_kMainRoom.SeekRoomList(i);
			if (isptr(ptRoomInfo)) {
				TCHAR szRoomName[iROOM_NAME_LEN + 30] = { 0, };
				sprintf(szRoomName, "%d,%s (%d:%d)", ptRoomInfo->id, ptRoomInfo->GetName(), ptRoomInfo->max, ptRoomInfo->mod);
				if (MOD_TDM == ptRoomInfo->mod) {
					switch (ptRoomInfo->state)
					{
					case ROOM_STATE_READY:
						strcat(szRoomName, " Ready");
						break;
					case ROOM_STATE_PLAYING:
						strcat(szRoomName, " Playing");
						break;
					case ROOM_STATE_END:
						strcat(szRoomName, " End");
						break;
					default:
						break;
					}
				}
				SendMessage(GetDlgItem(g_hLobbyDlg, IDC_ROOM_LIST), LB_ADDSTRING, 0, (LPARAM)szRoomName);
			}
		}
	}
}

void
REFRESH_ROOM_MEMBER_LIST() {
	if (isptr(g_hRoomDlg)) {
		SendMessage(GetDlgItem(g_hRoomDlg, IDC_MEMBER_LIST), LB_RESETCONTENT, 0, 0);

		for (UINT i = 0; i < g_kMainRoom.GetTopCount(); ++i) {
			CPlayer* pkPlayer = g_kMainRoom.GetMember(i);
			if (isptr(pkPlayer)) {
				TCHAR szMemberName[iPLAYER_NAME_LEN + 30] = { 0, };
				sprintf(szMemberName, "%s (%d:%d)", pkPlayer->GetName(), pkPlayer->GetKey(), pkPlayer->GetTeamType());

				SendMessage(GetDlgItem(g_hRoomDlg, IDC_MEMBER_LIST), LB_ADDSTRING, 0, (LPARAM)szMemberName);
			}
		}
	}
}

//장미경
void 
REFRESH_INVENTORY_LIST() {
	if (isptr(g_hInventoryDlg))	{
		SendMessage(GetDlgItem(g_hInventoryDlg, IDC_INVENTORY_LIST), LB_RESETCONTENT, 0, 0);
		g_pkInventory = ((CPlayerEx*)g_kMainPlayer)->GetInventory();

		for (UINT i = 0; i < g_pkInventory->GetSize(); i++) {
			CItemEx* item = g_pkInventory->GetInventoryItem(i);
			SItemInfo* itemInfo = (SItemInfo*)item->GetItemInfo();

			TCHAR szItemDesc[iITEM_DESC_LEN] = { 0, };
			sprintf(szItemDesc, "%s : %d", itemInfo->GetName(), itemInfo->GetSellPoint());
			SendMessage(GetDlgItem(g_hInventoryDlg, IDC_INVENTORY_LIST), LB_ADDSTRING, 0, (LPARAM)szItemDesc);
		}
	}
}

size_t
WriteWebData(void* vData_, size_t stSize_, size_t stCount, void* vStream_) {
	((std::string*)vStream_)->append((char*)vData_, 0, stSize_ * stCount);
	return stSize_ * stCount;
}

INT
NetworkUpdate() {
	if (isptr(g_pkConnector)) {
		if (g_pkConnector->IsConnected()) {
			if (g_kTick.GetTick() == 0) {
				g_kPingTick = g_kTick.GetTick();
			} else {
				if ((g_kPingTick + 1500) <= g_kTick.GetTick()) {
					CCommand kCommand;
					kCommand.SetOrder(ID_PING);
					SIdPingClToGs& rtSData = (SIdPingClToGs&)kCommand.GetData();
					rtSData.tick = g_kTick.GetTick();

					//CONSOLE("send tick: " << rtSData.tick << ", count: " << iCount);
					
					g_kMainPlayer->Send(kCommand, sizeof(SIdPingClToGs));

					g_kPingTick = g_kTick.GetTick();
				}
			}
		}
		return g_pkConnector->GetSensor()->WaitEvent(0);
	}
	return -1;
}

void
OnPaint(HDC hdc)
{
	PAINTSTRUCT ps;
	RECT tRect;

	GetClientRect(g_hWnd, &tRect);

	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hMemBit = CreateCompatibleBitmap(hdc, tRect.right, tRect.bottom);

	SelectObject(hMemDC, hMemBit);

	Graphics graphics(hMemDC);
	graphics.DrawImage(g_pkBackgroundMap, 0, 0, iGAME_MAP_WIDTH, iGAME_MAP_HEIGHT);

	if(g_bCollisionMap) {
		ColorMatrix colorMatrix = {
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, fCOLLITION_MAP_TRANSPARENCY, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		ImageAttributes kImageAttr;
		kImageAttr.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		kImageAttr.SetColorKey(Color(0, 0, 0), Color(0, 0, 0));
		graphics.DrawImage(g_pkCollisionMap, Rect(0, 0, iGAME_MAP_WIDTH, iGAME_MAP_HEIGHT), 0, 0, iGAME_MAP_WIDTH, iGAME_MAP_HEIGHT, UnitPixel, &kImageAttr);
	}

	if(g_bWireFrame) {
		Pen kPenLine(Color(32, 255, 255, 255), 1);
		Pen kPenCheck1(Color(64, 255, 255, 255), 1);
		Pen kPenCheck2(Color(64, 255, 255, 0), 1);
		Pen kPenHalf(Color(64, 255, 255, 0), 2);

		INT iVerticalHalf = (iGAME_MAP_WIDTH / iSECTION_DISTANCE) / 2;
		INT iHorizontalHalf = (iGAME_MAP_HEIGHT / iSECTION_DISTANCE) / 2;

		// 수직선
		for(INT i = 0; i <= (iGAME_MAP_WIDTH / iSECTION_DISTANCE); ++i) {
			if(i == iVerticalHalf) {
				graphics.DrawLine(&kPenHalf, (i*iSECTION_DISTANCE), 0, (i*iSECTION_DISTANCE), iGAME_MAP_HEIGHT);
			} else if((i % 10) == 0) {
				graphics.DrawLine(&kPenCheck2, (i*iSECTION_DISTANCE), 0, (i*iSECTION_DISTANCE), iGAME_MAP_HEIGHT);
			} else if((i % 5) == 0) {
				graphics.DrawLine(&kPenCheck1, (i*iSECTION_DISTANCE), 0, (i*iSECTION_DISTANCE), iGAME_MAP_HEIGHT);
			} else {
				graphics.DrawLine(&kPenLine, (i*iSECTION_DISTANCE), 0, (i*iSECTION_DISTANCE), iGAME_MAP_HEIGHT);
			}
		}

		// 수평선
		for(INT i = 0; i <= (iGAME_MAP_HEIGHT / iSECTION_DISTANCE); ++i) {
			if(i == iHorizontalHalf) {
				graphics.DrawLine(&kPenHalf, 0, (i*iSECTION_DISTANCE), iGAME_MAP_WIDTH, (i*iSECTION_DISTANCE));
			} else if((i % 10) == 0) {
				graphics.DrawLine(&kPenCheck2, 0, (i*iSECTION_DISTANCE), iGAME_MAP_WIDTH, (i*iSECTION_DISTANCE));
			} else if((i % 5) == 0) {
				graphics.DrawLine(&kPenCheck1, 0, (i*iSECTION_DISTANCE), iGAME_MAP_WIDTH, (i*iSECTION_DISTANCE));
			} else {
				graphics.DrawLine(&kPenLine, 0, (i*iSECTION_DISTANCE), iGAME_MAP_WIDTH, (i*iSECTION_DISTANCE));
			}
		}
	}

	for(INT i = 0; i < g_kMainRoom.GetTopCount(); ++i) {
		CPlayerEx* pkPlayer = (CPlayerEx*)g_kMainRoom.GetMember(i);
		if(isptr(pkPlayer)) {
			if (STATUS_NORMAL == pkPlayer->GetStatus()) {
				CAnimator* pkAnimator = pkPlayer->GetAnimator();
				if (isptr(pkAnimator)) {
					pkAnimator->Update(hMemDC);
				}
			}
		}
	}

	//장미경
	for (UINT i = 0; i < g_kDropItemMgr.GetSize(); ++i) {
		CItemEx* pkItem = g_kDropItemMgr.SeekDropItem(i);

		if (isptr(pkItem)) {
			SPosition pos = pkItem->GetPos();

			if (((CPlayerEx*)(g_kMainPlayer))->CollideWithItem(pos)) {
				if (((CPlayerEx*)(g_kMainPlayer))->GetKey() == pkItem->GetOwner()) {
					g_pkInventory = ((CPlayerEx*)g_kMainPlayer)->GetInventory();
					g_pkInventory->InsertItem(pkItem);

					UINT64 serial = pkItem->GetSerial();
					g_kDropItemMgr.DeleteDropItem(serial);
					
					CCommand kCommand;
					kCommand.SetOrder(ITEM_PICK);
					kCommand.SetExtra(OK);

					SItemPickClToGs& rtSData = (SItemPickClToGs&)kCommand.GetData();
					rtSData.picker = ((CPlayerEx*)(g_kMainPlayer))->GetKey();
					rtSData.serial = pkItem->GetSerial();
					g_kMainPlayer->Send(kCommand, sizeof(SItemPickClToGs));

				}
			}
				Font kFont(L"돋움", 10, FontStyleRegular, UnitPixel);
				FLOAT fPosX = (pkItem->GetPos().x * -1) - 20;
				FLOAT fPosY = (pkItem->GetPos().y * -1) - 10;
				PointF kPoint(fPosX, fPosY);
				SolidBrush kBrush(Color(255, 255, 255, 255));
								
				char szOwnerName[iPLAYER_NAME_LEN] = { 0, };
				sprintf(szOwnerName, "owner: %d", pkItem->GetOwner());
				INT iLength = MultiByteToWideChar(CP_ACP, 0, szOwnerName, strlen(szOwnerName), NULL, NULL);
				wchar_t szOwnerNameWide[iPLAYER_NAME_LEN] = { 0, };
				MultiByteToWideChar(CP_ACP, 0, szOwnerName, strlen(szOwnerName), szOwnerNameWide, iLength);

				graphics.DrawString(szOwnerNameWide, -1, &kFont, kPoint, &kBrush);
				graphics.DrawImage(g_pkActiveItem, -pkItem->GetPos().x, -pkItem->GetPos().y, iDROP_ITEM_WIDTH, iDROP_ITEM_HEIGHT);

				Pen pen(Color(255, 0, 0), 1.f);
				graphics.DrawRectangle(&pen, -pkItem->GetPos().x, -pkItem->GetPos().y, iDROP_ITEM_WIDTH, iDROP_ITEM_HEIGHT);
		}
	}


	////박준석
	//if (g_kMainRoom.IsDoing())
	//{
	//	HDC hMiniMapMemDC = CreateCompatibleDC(hdc);
	//	HBITMAP hMiniMapMemBit = CreateCompatibleBitmap(hdc, tRect.right, tRect.bottom);
	//	SelectObject(hMiniMapMemDC, hMiniMapMemBit);
	//	Graphics graphicsMiniMap(hMiniMapMemDC);
	//	graphicsMiniMap.DrawImage(g_pkBackgroundMap, 0, 0, iGAME_MAP_WIDTH, iGAME_MAP_HEIGHT);

	//	HDC hFogMemDC = CreateCompatibleDC(hdc);
	//	HBITMAP hFogBit = CreateCompatibleBitmap(hdc, tRect.right, tRect.bottom);
	//	SelectObject(hFogMemDC, hFogBit);
	//	TransparentBlt(hFogMemDC, 0, 0, 600, 600, hMemDC, 0, 0, 600, 600, RGB(255, 0, 255));		//일반 출력
	//	BLENDFUNCTION alpha;
	//	alpha.BlendFlags = 0;
	//	alpha.AlphaFormat = 0;
	//	alpha.BlendOp = AC_SRC_OVER;
	//	alpha.SourceConstantAlpha = 125;

	//	HDC hTempFogMemDC = CreateCompatibleDC(hdc);
	//	HBITMAP hTempFogBit = CreateCompatibleBitmap(hdc, tRect.right, tRect.bottom);
	//	SelectObject(hTempFogMemDC, hTempFogBit);

	//	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	//	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	//	(HPEN)SelectObject(hTempFogMemDC, pen);
	//	(HBRUSH)SelectObject(hTempFogMemDC, brush);
	//	Rectangle(hTempFogMemDC, 0, 0, 600, 600);

	//	static HDC hBlackFogMemDC = CreateCompatibleDC(hdc);									
	//	static HBITMAP hBlackFogBit = CreateCompatibleBitmap(hdc, tRect.right, tRect.bottom);	
	//	SelectObject(hTempFogMemDC, hTempFogBit);
	//	if (!g_fogMemory)	
	//	{
	//		Rectangle(hBlackFogMemDC, 0, 0, 600, 600);
	//		g_fogMemory = true;
	//	}

	//	int EllipseRadius = 50;

	//	for (UINT i = 0; i < g_kMainRoom.GetTopCount(); i++)
	//	{
	//		Graphics playerGraphicsMiniMap(hMiniMapMemDC);
	//		playerGraphicsMiniMap.DrawImage
	//		(g_pkPlayerSymbol, -(g_kMainRoom.GetMember(i)->GetPosX() + 10), -(g_kMainRoom.GetMember(i)->GetPosY() + 17), 20, 34);

	//		brush = CreateSolidBrush(RGB(255, 0, 255));
	//		pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 255));
	//		(HPEN)SelectObject(hTempFogMemDC, pen);
	//		(HBRUSH)SelectObject(hTempFogMemDC, brush);
	//		SelectObject(hTempFogMemDC, hTempFogBit);

	//		Ellipse(hTempFogMemDC,
	//			-(g_kMainRoom.GetMember(i)->GetPosX() + 5 + EllipseRadius),
	//			-(g_kMainRoom.GetMember(i)->GetPosY() + 5 + EllipseRadius),
	//			-(g_kMainRoom.GetMember(i)->GetPosX() + 5 - EllipseRadius),
	//			-(g_kMainRoom.GetMember(i)->GetPosY() + 5 - EllipseRadius));

	//		(HPEN)SelectObject(hBlackFogMemDC, pen);
	//		(HBRUSH)SelectObject(hBlackFogMemDC, brush);
	//		SelectObject(hBlackFogMemDC, hBlackFogBit);

	//		Ellipse(hBlackFogMemDC,
	//			-(g_kMainRoom.GetMember(i)->GetPosX() + 5 + EllipseRadius * 1.5),
	//			-(g_kMainRoom.GetMember(i)->GetPosY() + 5 + EllipseRadius * 1.5),
	//			-(g_kMainRoom.GetMember(i)->GetPosX() + 5 - EllipseRadius * 1.5),
	//			-(g_kMainRoom.GetMember(i)->GetPosY() + 5 - EllipseRadius * 1.5));
	//	}
	//	//브러시 삭제
	//	DeleteObject(brush);

	//	if (g_fogOnOff)
	//	{
	//		SelectObject(hFogMemDC, hFogBit);
	//		TransparentBlt(hFogMemDC, 0, 0, 600, 600, hTempFogMemDC, 0, 0, 600, 600, RGB(255, 0, 255));		//일반 출력
	//		AlphaBlend(hMemDC, 0, 0, 600, 600, hFogMemDC, 0, 0, 600, 600, alpha);
	//		TransparentBlt(hMemDC, 0, 0, 600, 600, hBlackFogMemDC, 0, 0, 600, 600, RGB(255, 0, 255));		//일반 출력
	//	}

	//	StretchBlt(hMemDC, 600 - 100, 0, 100, 100, hMiniMapMemDC, 0, 0, 600, 600, SRCCOPY);

	//	INT iLength;
	//	PointF kPoint;
	//	Font kFont(L"돋움", 10, FontStyleRegular, UnitPixel);
	//	SolidBrush kBrush(Color(255, 255, 255, 255));
	//	char playerNameKillDeathString[128] = { 0, };
	//	sprintf(playerNameKillDeathString, "Name          Kill       Death");
	//	wchar_t szPlayerCurNameKillDeath[128] = { 0, };
	//	kPoint.X = 10;
	//	kPoint.Y = 10;
	//	iLength = MultiByteToWideChar(CP_ACP, 0, playerNameKillDeathString, strlen(playerNameKillDeathString), NULL, NULL);
	//	MultiByteToWideChar(CP_ACP, 0, playerNameKillDeathString, strlen(playerNameKillDeathString), szPlayerCurNameKillDeath, iLength);
	//	graphics.DrawString(szPlayerCurNameKillDeath, -1, &kFont, kPoint, &kBrush);

	//	for (UINT i = 0; i < g_kMainRoom.GetTopCount(); i++)
	//	{
	//		char playerNameKillDeath[128] = { 0, };
	//		wchar_t szPlayerCurNameKillDeath[128] = { 0, };

	//		sprintf(playerNameKillDeath, "%s     %d        %d",
	//			g_kMainRoom.GetMember(i)->GetName(),
	//			g_kMainRoom.GetMember(i)->GetKey(),		//킬로 변경
	//			g_kMainRoom.GetMember(i)->GetKey());	//데스로 변경
	//		kPoint.X = 10;
	//		kPoint.Y = 15 * i + 30;
	//		iLength = MultiByteToWideChar(CP_ACP, 0, playerNameKillDeath, strlen(playerNameKillDeath), NULL, NULL);
	//		MultiByteToWideChar(CP_ACP, 0, playerNameKillDeath, strlen(playerNameKillDeath), szPlayerCurNameKillDeath, iLength);
	//		graphics.DrawString(szPlayerCurNameKillDeath, -1, &kFont, kPoint, &kBrush);
	//	}

	//	DeleteObject(hMiniMapMemBit);
	//	DeleteDC(hMiniMapMemDC);
	//}

	BitBlt(hdc, 0, 0, tRect.right, tRect.bottom, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hMemBit);
	DeleteDC(hMemDC);
	//DeleteDC(hDC);

	//FPS
	{
		//SetBkMode(hdc, TRANSPARENT);

		g_iElapsedTime += g_kTick.GetDeltaMSec();

		if (g_iElapsedTime >= 1000)
		{
			sprintf(g_cFPS, "FPS : %d\0", g_iFramePerSecond);

			g_iElapsedTime = 0;
			g_iFramePerSecond = 0;
		}
		else ++g_iFramePerSecond;

		unsigned int length0 = 0;

		for (unsigned int i = 0; i < sizeof(g_cFPS); ++i)
		{
			if (g_cFPS[i] != '\0') ++length0;
			else break;
		}

		TextOut(hdc, iGAME_MAP_WIDTH - 75, 0, g_cFPS, length0);
	}

	
}

//장현우
void
USER_CHAT_OUT(SUserChatGsToCl o, UINT Extra) {
	if (Extra == LOBBY)
	{
		char szOldMessage[iPLAYER_CHAT_LEN * iPLAYER_CHAT_LEN_LINE] = { 0, };
		GetDlgItemText(g_hLobbyDlg, IDC_LOBBY_CHAT, szOldMessage, iPLAYER_CHAT_LEN * iPLAYER_CHAT_LEN_LINE);

		char szNewMessage[iPLAYER_CHAT_LEN * iPLAYER_CHAT_LEN_LINE] = { 0, };
		if (szOldMessage[0] == '\0')
		{
			SetDlgItemText(g_hLobbyDlg, IDC_LOBBY_CHAT, strcat(strcat(o.name, ": "), o.chat));
		}
		else
		{
			sprintf(szNewMessage, "%s\r\n%s", szOldMessage, strcat(strcat(o.name, ": "), o.chat));
			SetDlgItemText(g_hLobbyDlg, IDC_LOBBY_CHAT, szNewMessage);
		}
		
	}
	else if (Extra == ROOM)
	{
		char szOldMessage[iPLAYER_CHAT_LEN * iPLAYER_CHAT_LEN_LINE] = { 0, };
		GetDlgItemText(g_hRoomDlg, IDC_ROOM_CHAT, szOldMessage, iPLAYER_CHAT_LEN * iPLAYER_CHAT_LEN_LINE);

		char szNewMessage[iPLAYER_CHAT_LEN * iPLAYER_CHAT_LEN_LINE] = { 0, };
		if (szOldMessage[0] == '\0')
		{
			SetDlgItemText(g_hRoomDlg, IDC_ROOM_CHAT, strcat(strcat(o.name, ": "), o.chat));
		}
		else
		{
			sprintf(szNewMessage, "%s\r\n%s", szOldMessage, strcat(strcat(o.name, ": "), o.chat));
			SetDlgItemText(g_hRoomDlg, IDC_ROOM_CHAT, szNewMessage);
		}
	}
}

int
APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
	WSAData wsaData;

	// WinSock2 설정
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return 1;
	}

	// GDI+ 초기화
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok) {
		return FALSE;
	}

    // 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_GAMECLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if(!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMECLIENT));

	g_hLobbyDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LOBBYBOX), g_hWnd, LobbyDialog);
	g_hRoomDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ROOMBOX), g_hWnd, RoomDialog);
	g_hInventoryDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_INVENTORYBOX), g_hWnd, InventoryDialog);

	g_kConsole = new CConsole();
	HWND hConsoleDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CONSOLEBOX), g_hWnd, ConsoleDialog);
	g_kConsole->SetHandler(hConsoleDlg);

	

	g_kConnectorFactory.Register(CConnectorEx::New);
	g_kPlayerFactory.Register(CPlayerEx::New);

	g_kDbMgr.Initialize();
	g_kPlayerMgr.Initialize();
	g_kMainRoom.Initialize();

	InitializeCommand();


	// 리소스 로딩
	Bitmap* pkBackgroundMap = (Bitmap*)Image::FromFile(L"..\\Data\\maps\\Xel_Naga\ Caverns.png");
	if (isptr(pkBackgroundMap)) {
		g_pkBackgroundMap = pkBackgroundMap->Clone(0, 0, pkBackgroundMap->GetWidth(), pkBackgroundMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkBackgroundMap);
	}

	Bitmap* pkCollisionMap = Bitmap::FromFile(L"..\\Data\\maps\\Xel_Naga\ Caverns.bmp");
	if (isptr(pkCollisionMap)) {
		g_pkCollisionMap = pkCollisionMap->Clone(0, 0, pkCollisionMap->GetWidth(), pkCollisionMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkCollisionMap);
	}

	//박준석
	Bitmap* pkPlayerSymbol = Bitmap::FromFile(L"..\\Data\\maps\\playerSymbol.bmp");
	if (isptr(pkPlayerSymbol)) {
		g_pkPlayerSymbol = pkPlayerSymbol->Clone(0, 0, pkPlayerSymbol->GetWidth(), pkPlayerSymbol->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkPlayerSymbol);
	}

	//장미경
	Bitmap* pkActiveItem = Bitmap::FromFile(L"..\\Data\\item\\ITEM_ACTIVE.bmp");
	if (isptr(pkActiveItem))
	{
		g_pkActiveItem = pkActiveItem->Clone(0, 0, pkActiveItem->GetWidth(), pkActiveItem->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkActiveItem);
	}

	Bitmap* pkPassiveItem = Bitmap::FromFile(L"..\\Data\\Item\\ITEM_PASSIVE.bmp");
	if (isptr(pkPassiveItem))
	{
		g_pkPassiveItem = pkPassiveItem->Clone(0, 0, pkPassiveItem->GetWidth(), pkPassiveItem->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkPassiveItem);
	}

    MSG msg;

	CEventSelectSensor* pkSensor = new CEventSelectSensor();
	g_pkConnector = NULL;
	if(isptr(pkSensor)) {
		pkSensor->Initialize(WSA_MAXIMUM_WAIT_EVENTS);

		g_pkConnector = (CConnector*)g_kConnectorFactory.Create();
		if(isptr(g_pkConnector)) {
			g_pkConnector->SetSensor(pkSensor);
		}
	}



    // 기본 메시지 루프입니다.
    while(g_bRunning) {
		GetMessage(&msg, nullptr, 0, 0);

        if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		//LateUpdate();
		//SendMessage(g_hWnd, WM_PAINT, 0, 0);
    }

	if(isptr(pkSensor)) {
		pkSensor->Release();
	}

	g_kMainRoom.Release();
	g_kPlayerMgr.Release();
	g_kDbMgr.Release();

	GdiplusShutdown(gpToken);

	SAFE_DELETE(g_kConsole);

    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMECLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_GAMECLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (iGAME_MAP_WIDTH + 16), (iGAME_MAP_HEIGHT + 59), nullptr, nullptr, hInstance, nullptr);
	//g_hWnd = CreateWindowEx(WS_EX_TOPMOST, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, (iGAME_MAP_WIDTH + 16), (iGAME_MAP_HEIGHT + 59), nullptr, nullptr, hInstance, nullptr);

	if(!g_hWnd) {
		return FALSE;
	}

	DWORD dwStyle = GetWindowLong(g_hWnd, GWL_STYLE);
	dwStyle &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
	SetWindowLong(g_hWnd, GWL_STYLE, dwStyle);

	RedrawWindow(g_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
	case WM_CREATE:
		{
			SetTimer(hWnd, 1, 50, NULL);
			//SetTimer(hWnd, 2, 10, NULL);
		}
		break;

	case WM_TIMER:
		{
			g_kTick.Update();
			g_kPlayerMgr.Update();

			NetworkUpdate();

			if (g_kMainPlayer)
			{
				if (TEAM_GREEN == g_kMainPlayer->GetTeamType())
				{
					if (STATE_INFESTED != ((CPlayerEx*)g_kMainPlayer)->GetState()) ((CPlayerEx*)g_kMainPlayer)->SetState(STATE_INFESTED);
				}
				
				if (STATE_INFESTED == ((CPlayerEx*)g_kMainPlayer)->GetState()) ((CPlayerEx*)g_kMainPlayer)->ZombieInfest();
			}

			InvalidateRect(g_hWnd, NULL, FALSE);

			//if(wParam == 1) {
			//	NetworkUpdate();
			//} else if(wParam == 2) {
			//	InvalidateRect(g_hWnd, NULL, FALSE);
			//}

			switch (g_kMainRoom.GetModType())
			{
			case MOD_FFA:
				break;
			case MOD_TDM:
				if (ROOM_STATE_PLAYING == g_kMainRoom.GetRoomState()) {
					g_kMainRoom.TimeUpdate((FLOAT)g_kTick.GetDeltaMSec() / (FLOAT)1000);
				}
				break;
			case MOD_ZOMBIE:
				break;
			default:
				break;
			}
		}
		break;

	case WM_KEYDOWN:
	{
		if (wParam == VK_RETURN) {
			if (g_kMainPlayer == g_kMainRoom.GetLeader()) {
				if (MOD_TDM == g_kMainRoom.GetModType()) {
					if (ROOM_STATE_READY == g_kMainRoom.GetRoomState()) {
						UINT size;
						size = g_kMainRoom.GetTopCount();
						UINT red, blue;
						red = blue = 0;
						for (UINT i = 0; i < size; ++i) {
							switch (g_kMainRoom.GetMember(i)->GetTeamType()) {
							case TEAM_RED:
								++red;
								break;
							case TEAM_BLUE:
								++blue;
								break;
							default:
								break;
							}
						}
						if (red != blue) {
							break;
						}
						CCommand kCommand;
						kCommand.SetOrder(ROOM_START_PLAYING);
						SRoomStartPlayingClToGs& rtSData = (SRoomStartPlayingClToGs&)kCommand.GetData();
						rtSData.actor = g_kMainPlayer->GetKey();
						g_kMainPlayer->Send(kCommand, sizeof(SRoomStartPlayingClToGs));
					}
				}
			}
		}

		if (MOD_TDM == g_kMainRoom.GetModType()) {
			if (ROOM_STATE_READY == g_kMainRoom.GetRoomState()) {
				break;
			}
		}

		//박준석
		if (wParam == VK_F3) {
			g_fogOnOff = abs(g_fogOnOff - 1);
		}
		if (wParam == 'T') {
			((CPlayerEx*)g_kMainPlayer)->SteamPakc();
		}
		if (wParam == VK_F1) {
			if (g_bWireFrame) {
				g_bWireFrame = false;
			}
			else {
				g_bWireFrame = true;
			}
		}
		else if (wParam == VK_F2) {
			if (g_bCollisionMap) {
				g_bCollisionMap = false;
			}
			else {
				g_bCollisionMap = true;
			}
		}
		else if (wParam == 'W') {
			if (false == ((CPlayerEx*)g_kMainPlayer)->GetAttCheck()) {
				g_bUp = true;
				if (isptr(g_kMainPlayer)) {
					if (g_bUp && g_bLeft) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_LEFT_UP);
					}
					else if (g_bUp && g_bRight) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_RIGHT_UP);
					}
					else {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_UP);
					}
					((CPlayerEx*)g_kMainPlayer)->Move();
				}
			}
		}
		else if (wParam == 'S') {
			if (false == ((CPlayerEx*)g_kMainPlayer)->GetAttCheck()) {
				g_bDown = true;
				if (isptr(g_kMainPlayer)) {
					if (g_bDown && g_bLeft) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_LEFT_DOWN);
					}
					else if (g_bDown && g_bRight) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_RIGHT_DOWN);
					}
					else {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_DOWN);
					}
					((CPlayerEx*)g_kMainPlayer)->Move();
				}
			}
		}
		else if (wParam == 'A') {
			if (false == ((CPlayerEx*)g_kMainPlayer)->GetAttCheck()) {
				g_bLeft = true;
				if (isptr(g_kMainPlayer)) {
					if (g_bLeft && g_bUp) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_LEFT_UP);
					}
					else if (g_bLeft && g_bDown) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_LEFT_DOWN);
					}
					else {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_LEFT);
					}
					((CPlayerEx*)g_kMainPlayer)->Move();
				}
			}
		}
		else if (wParam == 'D') {
			if (false == ((CPlayerEx*)g_kMainPlayer)->GetAttCheck()) {
				g_bRight = true;
				if (isptr(g_kMainPlayer)) {
					if (g_bRight && g_bUp) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_RIGHT_UP);
					}
					else if (g_bRight && g_bDown) {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_RIGHT_DOWN);
					}
					else {
						((CPlayerEx*)g_kMainPlayer)->SetDirection(DIRECTION_RIGHT);
					}
					((CPlayerEx*)g_kMainPlayer)->Move();
				}
			}
		}
		else if (wParam == VK_SPACE) {
			if (isptr(g_kMainPlayer)) {
				switch (((CPlayerEx*)g_kMainPlayer)->GetWeaponType())
				{
				case WEAPON_RIFLE:
					((CPlayerEx*)g_kMainPlayer)->SetAttCheck(true);
					((CPlayerEx*)g_kMainPlayer)->Attack();
					break;
				case WEAPON_LAZOR:
					((CPlayerEx*)g_kMainPlayer)->SetAttCheck(true);
					((CPlayerEx*)g_kMainPlayer)->PlusLazorCount();
				}
			}
		}
		else if (wParam == '1') {
			if (false == ((CPlayerEx*)g_kMainPlayer)->GetAttCheck()) {
				if (isptr(g_kMainPlayer)) {
					((CPlayerEx*)g_kMainPlayer)->SwitchWeapon(WEAPON_RIFLE);
				}
			}
		}
		else if (wParam == '2') {
			if (false == ((CPlayerEx*)g_kMainPlayer)->GetAttCheck()) {
				if (isptr(g_kMainPlayer)) {
					((CPlayerEx*)g_kMainPlayer)->SwitchWeapon(WEAPON_LAZOR);
				}
			}
		}
		//InvalidateRect(hWnd, NULL, FALSE);
	}
	break;

	case WM_KEYUP:
	{
		if (MOD_TDM == g_kMainRoom.GetModType()) {
			if (ROOM_STATE_READY == g_kMainRoom.GetRoomState()) {
				break;
			}
		}
		if (wParam == 'W') {
			g_bUp = false;
			if (isptr(g_kMainPlayer)) {
				((CPlayerEx*)g_kMainPlayer)->Stop();
			}
		}
		else if (wParam == 'S') {
			g_bDown = false;
			if (isptr(g_kMainPlayer)) {
				((CPlayerEx*)g_kMainPlayer)->Stop();
			}
		}
		else if (wParam == 'A') {
			g_bLeft = false;
			if (isptr(g_kMainPlayer)) {
				((CPlayerEx*)g_kMainPlayer)->Stop();
			}
		}
		else if (wParam == 'D') {
			g_bRight = false;
			if (isptr(g_kMainPlayer)) {
				((CPlayerEx*)g_kMainPlayer)->Stop();
			}
		}
		else if (wParam == VK_SPACE) {
			if (isptr(g_kMainPlayer)) {
				switch (((CPlayerEx*)g_kMainPlayer)->GetWeaponType())
				{
				case WEAPON_RIFLE:
					((CPlayerEx*)g_kMainPlayer)->SetAttCheck(false);
					((CPlayerEx*)g_kMainPlayer)->Stop();
					break;
				case WEAPON_LAZOR:
					((CPlayerEx*)g_kMainPlayer)->Attack();
					((CPlayerEx*)g_kMainPlayer)->Stop();
					break;
				}
			}
		}
	}
	break;

	case WM_LBUTTONDOWN:
		if (MOD_TDM == g_kMainRoom.GetModType()) {
			if (ROOM_STATE_READY == g_kMainRoom.GetRoomState()) {
				break;
			}
		}
		{
			if(isptr(g_kMainPlayer)) {
				g_bAttack = true;
				((CPlayerEx*)g_kMainPlayer)->Attack();
			}
		}
		break;

	case WM_LBUTTONUP:
		if (MOD_TDM == g_kMainRoom.GetModType()) {
			if (ROOM_STATE_READY == g_kMainRoom.GetRoomState()) {
				break;
			}
		}
		{
			if(isptr(g_kMainPlayer)) {
				g_bAttack = false;
				((CPlayerEx*)g_kMainPlayer)->Stop();
			}
		}
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId) {
            case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				}
				break;
			case IDM_CONNECT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_CONNECTBOX), hWnd, ConnectDialog);
					if(false == g_pkConnector->IsConnected()) {
						if(g_pkConnector->Connect(REMOTE_ADDRESS, REMOTE_PORT)) {
							CCommand kCommand;
							kCommand.SetOrder(INFO_SERVER);
							if(isptr(g_kMainPlayer)) {
								g_kMainPlayer->Send(kCommand);
								//MessageBox(g_hWnd, "connecting successed.", "Message", NULL);
							}
						} else {
							MessageBox(g_hWnd, "connecting failed.", "Error", 0);
						}
					}
				}
				break;
			case IDM_DISCONNECT:
				{
					if(isptr(g_kMainPlayer)) {
						g_kMainPlayer->Disconnect();
					}
					g_kPlayerMgr.Release();
				}
				break;
			case IDM_JOINUS:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_JOINUSBOX), hWnd, JoinUsDialog);
				}
				break;
			case IDM_ACCOUNT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ACCOUNTBOX), hWnd, AccountDialog);
				}
				break;
			case IDM_NEWROOM:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_NEWROOMBOX), hWnd, NewRoomDialog);
				}
				break;
			case IDM_AUTOMATCH:
				{
					if(g_pkConnector->IsConnected()) {
						if(isptr(g_kMainPlayer)) {
							CCommand kCommand;
							kCommand.SetOrder(ROOM_MATCH);
							kCommand.SetExtra(NONE);

							SRoomMatchClToGs& rtSData = (SRoomMatchClToGs&)kCommand.GetData();

							char szRoomName[iROOM_NAME_LEN] = { 0, };
							sprintf(szRoomName, "AUTH_MATCH (%s)", g_kMainPlayer->GetName());
							rtSData.SetName(szRoomName);
							rtSData.max = 16;
							rtSData.mod = MOD_FFA;

							g_kMainPlayer->Send(kCommand, sizeof(SRoomMatchClToGs));
						}
					}
				}
				break;
			case IDM_LOBBY:
				{
					if(g_pkConnector->IsConnected()) {
						if(isptr(g_kMainPlayer)) {
							CCommand kCommand;
							kCommand.SetOrder(ROOM_LIST);
							kCommand.SetExtra(NONE);
							kCommand.SetMission(0);

							g_kMainPlayer->Send(kCommand);
						}
					}

					if(false == g_bLobby) {
						g_bLobby = true;
						ShowWindow(g_hLobbyDlg, SW_SHOW);
						REFRESH_USER_LIST();
					} else {
						g_bLobby = false;
						ShowWindow(g_hLobbyDlg, SW_HIDE);
					}
				}
				break;
			case IDM_ROOM:
				{
					if(false == g_bRoom) {
						g_bRoom = true;
						ShowWindow(g_hRoomDlg, SW_SHOW);
					} else {
						g_bRoom = false;
						ShowWindow(g_hRoomDlg, SW_HIDE);
					}
				}
				break;
			case IDM_INVENTORY:
				{
					if(false == g_bInventory) {
						g_bInventory = true;
						ShowWindow(g_hInventoryDlg, SW_SHOW);
					} else {
						g_bInventory = false;
						ShowWindow(g_hInventoryDlg, SW_HIDE);
					}
				}
				break;
			case IDM_CONSOLE:
				{
					if(false == g_bConsole) {
						g_bConsole = true;
						ShowWindow(g_kConsole->GetHandler(), SW_SHOW);
					} else {
						g_bConsole = false;
						ShowWindow(g_kConsole->GetHandler(), SW_HIDE);
					}
				}
				break;
            case IDM_EXIT:
				{
	                DestroyWindow(hWnd);
				}
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			OnPaint(hdc);
			EndPaint(hWnd, &ps);
        }
        break;
	case WM_ERASEBKGND:
		{
			return FALSE;
		}
		break;
    case WM_DESTROY:
		{
			g_bRunning = false;
			if(isptr(g_hBit)) {
				DeleteObject(g_hBit);
			}
			PostQuitMessage(0);
			KillTimer(hWnd, 1);
		}
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK ConnectDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			TCHAR szAddress[16] = { 0, };
			TCHAR szPort[11] = { 0, };

			sprintf(szAddress, "%s", REMOTE_ADDRESS);
			sprintf(szPort, "%d", REMOTE_PORT);

			SetDlgItemText(hDlg, IDC_CONNECT_ADDR_INPUT, szAddress);
			SetDlgItemText(hDlg, IDC_CONNECT_PORT_INPUT, szPort);

			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDCONNECT) {
				if(false == g_pkConnector->IsConnected()) {
					TCHAR szAddress[16] = { 0, };
					TCHAR szPort[11] = { 0, };

					GetDlgItemText(hDlg, IDC_CONNECT_ADDR_INPUT, szAddress, 16);
					GetDlgItemText(hDlg, IDC_CONNECT_PORT_INPUT, szPort, 11);

					INT iPort = atoi(szPort);
					if(0 < iPort) {
						if(g_pkConnector->Connect(szAddress, iPort)) {
							CCommand kCommand;
							kCommand.SetOrder(INFO_SERVER);
							if(isptr(g_kMainPlayer)) {
								g_kMainPlayer->Send(kCommand);

								kCommand.SetOrder(ROOM_SYNC);
								kCommand.SetExtra(CONNECT);
								g_kMainPlayer->Send(kCommand);

								//수정중
								kCommand.SetOrder(ROOM_LIST);
								kCommand.SetExtra(NONE);
								kCommand.SetMission(0);
								g_kMainPlayer->Send(kCommand);
								//MessageBox(g_hWnd, "connecting successed.", "Message", NULL);
							}
						} else {
							MessageBox(g_hWnd, "connecting failed.", "Error", 0);
						}
					}
				}

				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCLOSE) {
				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK JoinUsDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDCREATE) {
				TCHAR szLoginId[iLOGIN_ID_LEN + 1] = { 0, };
				TCHAR szLoginPwd[iLOGIN_PWD_LEN + 1] = { 0, };
				TCHAR szLoginConfirmPwd[iLOGIN_PWD_LEN + 1] = { 0, };
				TCHAR szName[iPLAYER_NAME_LEN + 1] = { 0, };

				GetDlgItemText(hDlg, IDC_JOINUS_ID_INPUT, szLoginId, iLOGIN_ID_LEN);
				GetDlgItemText(hDlg, IDC_JOINUS_PASSWD_INPUT, szLoginPwd, iLOGIN_PWD_LEN);
				GetDlgItemText(hDlg, IDC_JOINUS_CONFIRM_INPUT, szLoginConfirmPwd, iLOGIN_PWD_LEN);
				GetDlgItemText(hDlg, IDC_JOINUS_NAME_INPUT, szName, iPLAYER_NAME_LEN);

				TCHAR szMessages[255] = { 0, };
				sprintf_s(szMessages, "%s, %s, %s, %s", szLoginId, szLoginPwd, szLoginConfirmPwd, szName);

				//MessageBox(hDlg, szMessages, "Test", 0);

				wchar_t szTmpName[iPLAYER_NAME_LEN] = { 0, };
				INT iLength = MultiByteToWideChar(CP_ACP, 0, szName, strlen(szName), NULL, NULL);
				MultiByteToWideChar(CP_ACP, 0, szName, strlen(szName), szTmpName, iLength);

				TCHAR szUniName[iPLAYER_NAME_LEN] = { 0, };
				iLength = WideCharToMultiByte(CP_UTF8, 0, szTmpName, lstrlenW(szTmpName), NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_UTF8, 0, szTmpName, lstrlenW(szTmpName), szUniName, iLength, NULL, NULL);

				CCommand kCommand;
				kCommand.SetOrder(ID_CREATE);
				kCommand.SetExtra(NONE);
				SIdCreateClToGs& rtSData = (SIdCreateClToGs&)kCommand.GetData();
				rtSData.SetLoginId(szLoginId);
				rtSData.SetLoginPasswd(szLoginPwd);
				rtSData.SetName(szUniName);

				g_kMainPlayer->Send(kCommand, sizeof(SIdCreateClToGs));

				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCLOSE) {
				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AccountDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			SendMessage(GetDlgItem(hDlg, IDC_NORMAL_RADIO), BM_SETCHECK, BST_CHECKED, 0);
			SendMessage(GetDlgItem(hDlg, IDC_WEB_RADIO), BM_SETCHECK, BST_UNCHECKED, 0);

			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDLOGIN) {
				TCHAR szLoginId[iLOGIN_ID_LEN + 1] = { 0, };
				TCHAR szLoginPwd[iLOGIN_PWD_LEN + 1] = { 0, };

				GetDlgItemText(hDlg, IDC_ID_INPUT, szLoginId, iLOGIN_ID_LEN);
				GetDlgItemText(hDlg, IDC_PWD_INPUT, szLoginPwd, iLOGIN_PWD_LEN);

				if(BST_CHECKED == SendMessage(GetDlgItem(hDlg, IDC_NORMAL_RADIO), BM_GETCHECK, 0, 0)) {
					if(g_pkConnector->IsConnected()) {
						CCommand kCommand;
						kCommand.SetOrder(ID_AUTHORIZE);
						kCommand.SetExtra(NONE);
						SIdAuthorizeClToGs& rtSData = (SIdAuthorizeClToGs&)kCommand.GetData();
						rtSData.SetLoginId(szLoginId);
						rtSData.SetLoginPasswd(szLoginPwd);

						g_kMainPlayer->Send(kCommand, sizeof(SIdAuthorizeClToGs));

					}
				} else {
					//MessageBox(hDlg, szLoginPwd, szLoginId, 0);

					char szAuthUrl[255];
					sprintf(szAuthUrl, "%s/login_auth.php?login_id=%s&login_passwd=%s", WEB_AUTH_URL, szLoginId, szLoginPwd);

					CURL* curl = curl_easy_init();
					if(isptr(curl)) {
						std::string szWebResponse;
						
						curl_easy_setopt(curl, CURLOPT_URL, szAuthUrl);
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteWebData);
						curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szWebResponse);

						CURLcode eError = curl_easy_perform(curl);
						if(CURLE_OK != eError) {
							CONSOLE("request: " << szAuthUrl << ", fail: " << eError);
						} else {
							CONSOLE("request: " << szAuthUrl << ", success: " << eError);
						}

						LONG lHttpCode;
						curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &lHttpCode);
						
						curl_easy_cleanup(curl);

						wchar_t szTmpResponse[iWEB_RESPONSE_BUFFER_LEN] = { 0, };
						INT iLength = MultiByteToWideChar(CP_UTF8, 0, szWebResponse.c_str(), strlen(szWebResponse.c_str()), NULL, NULL);
						MultiByteToWideChar(CP_UTF8, 0, szWebResponse.c_str(), strlen(szWebResponse.c_str()), szTmpResponse, iLength);

						TCHAR szResponse[iWEB_RESPONSE_BUFFER_LEN] = { 0, };
						iLength = WideCharToMultiByte(CP_ACP, 0, szTmpResponse, lstrlenW(szTmpResponse), NULL, 0, NULL, NULL);
						WideCharToMultiByte(CP_ACP, 0, szTmpResponse, lstrlenW(szTmpResponse), szResponse, iLength, NULL, NULL);

						CONSOLE("response: code: " << lHttpCode << ", data: " << szResponse);

						//JSONCPP
						std::string szData(szResponse);

						Json::Reader reader;
						Json::Value root;
						bool bCheck = reader.parse(szData, root);

						if(bCheck) {
							UINT uiAid = atoi(root["ac_aid"].asString().c_str());
							if(0 < uiAid) {
								CONSOLE("json data: ac_aid: " << root["ac_aid"].asString().c_str() << ", ac_name: " << root["ac_name"].asString().c_str());
								CONSOLE("json data: ac_point: " << root["ac_point"].asString().c_str() << ", ac_grade: " << root["ac_grade"].asString().c_str());
								CONSOLE("json data: ac_login_time: " << root["ac_login_time"].asString().c_str() << ", ac_logout_time: " << root["ac_logout_time"].asString().c_str());

								if(g_pkConnector->IsConnected()) {
									g_kMainPlayer->SetAid(atoi(root["ac_aid"].asString().c_str()));
									g_kMainPlayer->SetName(root["ac_name"].asString().c_str());
									g_kMainPlayer->SetLoginTime(_atoi64(root["ac_login_time"].asString().c_str()));
									g_kMainPlayer->SetLogoutTime(_atoi64(root["ac_logout_time"].asString().c_str()));
									g_kMainPlayer->SetPoint(atoi(root["ac_point"].asString().c_str()));

									CCommand kCommand;
									kCommand.SetOrder(ID_AUTHORIZE);
									kCommand.SetExtra(WEB);
									SIdAuthorizeWepClToGs& rtSData = (SIdAuthorizeWepClToGs&)kCommand.GetData();
									rtSData.SetAid(g_kMainPlayer->GetAid());

									g_kMainPlayer->Send(kCommand, sizeof(SIdAuthorizeClToGs));
								}
							} else {
								CONSOLE("json data: ac_aid: " << root["ac_aid"].asString().c_str());
							}
						}
					}
				}

				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCLOSE) {
				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK NewRoomDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDCREATE) {
				TCHAR szRoomName[iROOM_NAME_LEN + 1] = { 0, };
				TCHAR szRoomMax[11] = { 0, };
				TCHAR szRoomMod[11] = { 0, };

				GetDlgItemText(hDlg, IDC_ROOM_NAME_INPUT, szRoomName, iROOM_NAME_LEN);
				GetDlgItemText(hDlg, IDC_ROOM_MAX_INPUT, szRoomMax, 11);
				GetDlgItemText(hDlg, IDC_ROOM_MOD_INPUT, szRoomMod, 11);

				//MessageBox(hDlg, szRoomMax, szRoomName, 0);

				INT iRoomMax = atoi(szRoomMax);
				MOD_TYPE eRoomMod = (MOD_TYPE)atoi(szRoomMod);

				if((0 < iRoomMax) && (16 >= iRoomMax)) {
					if (g_pkConnector->IsConnected()) {
						if(isptr(g_kMainPlayer)) {
							CCommand kCommand;
							kCommand.SetOrder(ROOM_CREATE);
							kCommand.SetExtra(NONE);

							SRoomCreateClToGs& rtSData = (SRoomCreateClToGs&)kCommand.GetData();
							rtSData.SetName(szRoomName);
							rtSData.max = iRoomMax;
							rtSData.mod = eRoomMod;

							g_kMainPlayer->Send(kCommand, sizeof(SRoomCreateClToGs));
							EndDialog(hDlg, LOWORD(wParam));
						}
					} else {
						MessageBox(hDlg, "client is not connected: ", "Error", 0);
					}
				} else {
					MessageBox(hDlg, "max user is not invalid: ", "Error", 0);
				}
			} else if(LOWORD(wParam) == IDCLOSE) {
				EndDialog(hDlg, LOWORD(wParam));
			} else if(LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK LobbyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	 switch (message) {
    case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
    case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDC_USER_LIST) {
				if(HIWORD(wParam) == LBN_DBLCLK) {
					INT iIndex = (INT)SendMessage(GetDlgItem(hDlg, IDC_USER_LIST), LB_GETCURSEL, 0, 0);

					TCHAR szPlayerName[iPLAYER_NAME_LEN + 1] = { 0, };
					SendMessage(GetDlgItem(hDlg, IDC_USER_LIST), LB_GETTEXT, iIndex, (LPARAM)szPlayerName);
					
					MessageBox(g_hWnd, szPlayerName, "Message", NULL);
				}
			} else if(LOWORD(wParam) == IDC_ROOM_LIST) {
				if(HIWORD(wParam) == LBN_DBLCLK) {
					INT iIndex = (INT)SendMessage(GetDlgItem(hDlg, IDC_ROOM_LIST), LB_GETCURSEL, 0, 0);

					TCHAR szRoomName[iROOM_NAME_LEN + 1] = { 0, };
					SendMessage(GetDlgItem(hDlg, IDC_ROOM_LIST), LB_GETTEXT, iIndex, (LPARAM)szRoomName);

					INT iRoomId = -1;
					char* pToken = strtok(szRoomName, ",");
					if(isptr(pToken)) {
						//MessageBox(g_hWnd, pToken, "Message", NULL);
						iRoomId = atoi(pToken);
					}

					if(0 <= iRoomId) {
						if(g_pkConnector->IsConnected()) {
							if(isptr(g_kMainPlayer)) {
								SRoomInfo* roomInfo = g_kMainRoom.FindRoomList(iRoomId);
								if (MOD_TDM == roomInfo->mod && ROOM_STATE_READY != roomInfo->state) {
									break;
								}
								CCommand kCommand;
								kCommand.SetOrder(ROOM_JOIN);
			
								SRoomJoinClToGs& rtSData = (SRoomJoinClToGs&)kCommand.GetData();
								rtSData.id = iRoomId;
								
								g_kMainPlayer->Send(kCommand, sizeof(SRoomJoinClToGs));
							}
						}
					}
				}
			} else if(LOWORD(wParam) == IDREFRESH) {
				if (g_pkConnector->IsConnected()) {
					if(isptr(g_kMainPlayer)) {
						CCommand kCommand;
						kCommand.SetOrder(ROOM_LIST);
						kCommand.SetExtra(NONE);
						kCommand.SetMission(0);

						g_kMainPlayer->Send(kCommand);
					}
				}
				REFRESH_USER_LIST();
			} else if (LOWORD(wParam) == IDJOIN) {
				INT iIndex = (INT)SendMessage(GetDlgItem(hDlg, IDC_ROOM_LIST), LB_GETCURSEL, 0, 0);

				TCHAR szRoomName[iROOM_NAME_LEN + 1] = { 0, };
				SendMessage(GetDlgItem(hDlg, IDC_ROOM_LIST), LB_GETTEXT, iIndex, (LPARAM)szRoomName);

				INT iRoomId = -1;
				char* pToken = strtok(szRoomName, ",");
				if(isptr(pToken)) {
					//MessageBox(g_hWnd, pToken, "Message", NULL);
					iRoomId = atoi(pToken);
				}

				if(0 <= iRoomId) {
					if(g_pkConnector->IsConnected()) {
						if(isptr(g_kMainPlayer)) {
							SRoomInfo* roomInfo = g_kMainRoom.FindRoomList(iRoomId);
							if (MOD_TDM == roomInfo->mod && ROOM_STATE_PLAYING == roomInfo->state) {
								break;
							}
							CCommand kCommand;
							kCommand.SetOrder(ROOM_JOIN);
			
							SRoomJoinClToGs& rtSData = (SRoomJoinClToGs&)kCommand.GetData();
							rtSData.id = iRoomId;

							g_kMainPlayer->Send(kCommand, sizeof(SRoomJoinClToGs));
						}
					}
				}
			} else if(LOWORD(wParam) == IDSEND) {
				//장현우
				TCHAR szChat[iPLAYER_CHAT_LEN] = { 0, };
				GetDlgItemText(hDlg, IDC_LOBBY_CHAT_INPUT, szChat, iPLAYER_CHAT_LEN);
				if (isptr(g_kMainPlayer)) {
					CCommand kCommand;
					kCommand.SetOrder(USER_CHAT);
					kCommand.SetExtra(LOBBY);

					SUserChatClToGs& rtSData = (SUserChatClToGs&)kCommand.GetData();
					rtSData.Setchar(szChat);
					rtSData.Setname(g_kMainPlayer->GetName());

					g_kMainPlayer->Send(kCommand, sizeof(SUserChatClToGs));
					SetDlgItemText(hDlg, IDC_LOBBY_CHAT_INPUT, NULL);
				}
			} else if(LOWORD(wParam) == IDCANCEL) {
				g_bLobby = false;
				ShowWindow(hDlg, SW_HIDE);
			}
			return (INT_PTR)TRUE;
		}
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RoomDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDREFRESH) {
				if(g_pkConnector->IsConnected()) {
					if(isptr(g_kMainPlayer)) {
						CCommand kCommand;
						kCommand.SetOrder(ROOM_LIST);
						kCommand.SetExtra(NONE);
						kCommand.SetMission(1);

						g_kMainPlayer->Send(kCommand);
					}
				}
			} else if(LOWORD(wParam) == IDLEAVE) {
				if(g_pkConnector->IsConnected()) {
					if(isptr(g_kMainPlayer)) {

						g_fogMemory = false;	//박준석

						CCommand kCommand;
						kCommand.SetOrder(ROOM_LEAVE);

						g_kMainPlayer->Send(kCommand);
					}
				}

				g_bRoom = false;
				ShowWindow(hDlg, SW_HIDE);
			} else if(LOWORD(wParam) == IDSEND) {
				//장현우
				TCHAR szChat[iPLAYER_CHAT_LEN] = { 0, };
				GetDlgItemText(hDlg, IDC_ROOM_CHAT_INPUT, szChat, iPLAYER_CHAT_LEN);
				if (isptr(g_kMainPlayer)) {
					CCommand kCommand;
					kCommand.SetOrder(USER_CHAT);
					kCommand.SetExtra(ROOM);

					SUserChatClToGs& rtSData = (SUserChatClToGs&)kCommand.GetData();
					rtSData.Setchar(szChat);
					rtSData.Setname(g_kMainPlayer->GetName());

					g_kMainPlayer->Send(kCommand, sizeof(SUserChatClToGs));
					SetDlgItemText(hDlg, IDC_ROOM_CHAT_INPUT, NULL);
				}
			} else if(LOWORD(wParam) == IDCANCEL) {
				g_bRoom = false;
				ShowWindow(hDlg, SW_HIDE);
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK InventoryDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			TCHAR szMoney[11] = { 0, };
			sprintf(szMoney, "%d", 0);

			SetDlgItemText(hDlg, IDC_INVENTORY_MONEY, szMoney);
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDCSELL) {
				
			} else if(LOWORD(wParam) == IDCDELETE) {

			} else if(LOWORD(wParam) == IDCANCEL) {
				g_bInventory = false;
				ShowWindow(hDlg, SW_HIDE);
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ConsoleDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDCANCEL) {
				g_bConsole = false;
				ShowWindow(hDlg, SW_HIDE);
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		{
			LOGFONT lf_text;
			memset(&lf_text, 0, sizeof(LOGFONT));
			lf_text.lfCharSet = 0x81;
			lf_text.lfHeight = 14;
			strcpy(lf_text.lfFaceName, "돋움체");
			HFONT hTextFont = CreateFontIndirect(&lf_text);

			std::string szMessage;
			szMessage.append("/* PRODUCER\r\n");
			szMessage.append(" * 강귀복 (foxip@vogie.net)\r\n");
			szMessage.append(" */\r\n");
			szMessage.append("\r\n");
			szMessage.append("/* ART DIRECTOR\r\n");
			szMessage.append(" * 장미경 (mjismy@gmail.com)\r\n");
			szMessage.append(" */\r\n");
			szMessage.append("\r\n");
			szMessage.append("/* MODELLER\r\n");
			szMessage.append(" * 박준석 (joonseok_p@naver.com)\r\n");
			szMessage.append(" */\r\n");
			szMessage.append("\r\n");
			szMessage.append("/* PROGRAMERS */\r\n");
			szMessage.append("김홍순 (yourbrodie@naver.com)\r\n");
			szMessage.append("장미경 (mjismy@gmail.com)\r\n");
			szMessage.append("김병묵 (zt00000@naver.com)\r\n");
			szMessage.append("이주봉 (jbdondlek@gmail.com)\r\n");
			szMessage.append("장현우 (zhfldk2002kr@naver.com)\r\n");
			szMessage.append("박준석 (joonseok_p@naver.com)\r\n");
			szMessage.append("이성호 (jrho1234@naver.com)\r\n");
			szMessage.append("전병찬 (jbc04719@naver.com)\r\n");

			SendMessage(GetDlgItem(hDlg, IDC_CREDITS), WM_SETFONT, (WPARAM)hTextFont, 0);
			SetDlgItemText(hDlg, IDC_CREDITS, szMessage.c_str());

			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}