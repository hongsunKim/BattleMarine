/*
 * Education Frameworks
 * Copyright © 2015-2017 Origin Studio Inc.
 *
 */

#include "Animator.h"
#include "../CommonHeader.h"

extern HWND g_hWnd;

bool
CAnimator::Initialize() {
	Load();
	
	if ("Check Room Mode if Zombie or not") LoadZombieMotions();
	
	return true;
}

bool
CAnimator::Release() {
	return true;
}

void
CAnimator::Load() {
	Bitmap* pkMap = NULL;
	WCHAR szPath[MAX_PATH] = { 0, };

	// IDLE
	for (INT i = 0; i < iANIMATOR_IDLE_LEN; ++i) {
		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_RIGHT_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleRightUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_RIGHT", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleRight[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_RIGHT_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleRightDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_LEFT_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleLeftDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_LEFT", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleLeft[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"IDLE", L"IDLE_LEFT_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkIdleLeftUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);
	}

	// ATTACK
	for (INT i = 0; i < iANIMATOR_ATTACK_LEN; ++i) {
		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_RIGHT_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackRightUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_RIGHT", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackRight[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_RIGHT_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackRightDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_LEFT_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackLeftDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_LEFT", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackLeft[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"ATTACK", L"ATTACK_LEFT_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkAttackLeftUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);
	}

	// MOVE
	for (INT i = 0; i < iANIMATOR_MOVE_LEN; ++i) {
		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_RIGHT_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveRightUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_RIGHT", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveRight[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_RIGHT_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveRightDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_LEFT_DOWN", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveLeftDown[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_LEFT", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveLeft[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);

		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"MOVE", L"MOVE_LEFT_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkMoveLeftUp[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);
	}

	// DIED
	for (INT i = 0; i < iANIMATOR_DIED_LEN; ++i) {
		memset(szPath, 0, MAX_PATH);
		swprintf(szPath, L"..\\Data\\marine\\%s\\%s_%d.bmp", L"DIED", L"DIED_UP", (i + 1));
		pkMap = Bitmap::FromFile(szPath);
		m_pkDied[i] = pkMap->Clone(0, 0, pkMap->GetWidth(), pkMap->GetHeight(), PixelFormat32bppARGB);
		SAFE_DELETE(pkMap);
	}
}

void CAnimator::LoadZombieMotions()
{
	Bitmap* map0 = nullptr;
	WCHAR path0[MAX_PATH] = { 0, };

	//m_pkZombie[ZOMBIE_STATE_IDLE] = (new Bitmap**[DIRECTION_COUNT]);
	//
	//for (INT i = 0; i < DIRECTION_COUNT; ++i) {
	//	m_pkZombie[ZOMBIE_STATE_IDLE][i] = (new Bitmap*[iANIMATOR_ZOMBIE_IDLE_LENGTH]);
	//}
	//
	//Bitmap* pkTest = m_pkZombie[ZOMBIE_STATE_IDLE][0][0];

	//m_pkZombie[ZOMBIE_STATE_IDLE] = m_pkZombieIdle;
	//m_pkZombie[ZOMBIE_STATE_INFEST] = &m_pkZombieInfest[0][0];
	//m_pkZombie[ZOMBIE_STATE_MOVE] = &m_pkZombieInfest[0][0];
	//m_pkZombie[ZOMBIE_STATE_DIE] = &m_pkZombieDie[0];

	m_ppppkZombie = new Bitmap***[ZOMBIE_STATE_COUNT];
	
	m_ppppkZombie[ZOMBIE_STATE_IDLE] = new Bitmap**[DIRECTION_COUNT];
	m_ppppkZombie[ZOMBIE_STATE_INFEST] = new Bitmap**[DIRECTION_COUNT];
	m_ppppkZombie[ZOMBIE_STATE_MOVE] = new Bitmap**[DIRECTION_COUNT];
	m_ppppkZombie[ZOMBIE_STATE_DIE] = new Bitmap**[1];

	for (unsigned int i = 0; i < ZOMBIE_STATE_COUNT; ++i)
	{
		if (i == ZOMBIE_STATE_DIE)
		{
			m_ppppkZombie[i][0] = new Bitmap*[iANIMATOR_ZOMBIE_MOTION_LENGTH[i]];

			continue;
		}

		for (unsigned int j = 0; j < DIRECTION_COUNT; ++j)
		{
			m_ppppkZombie[i][j] = new Bitmap*[iANIMATOR_ZOMBIE_MOTION_LENGTH[i]];
		}
	}

	//Bitmap* m_xxx[iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//Bitmap*(* m_yyy)[iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//Bitmap(** m_zzz)[iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//
	//m_ppppkZombie[ZOMBIE_STATE_IDLE] = new Bitmap*[DIRECTION_COUNT][iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//m_xxx = new Bitmap*[DIRECTION_COUNT][iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//m_yyy = new Bitmap*[DIRECTION_COUNT][iANIMATOR_ZOMBIE_IDLE_LENGTH];
	//m_zzz = new Bitmap*[DIRECTION_COUNT][iANIMATOR_ZOMBIE_IDLE_LENGTH];

	wchar_t* states0[ZOMBIE_STATE_COUNT];
	wchar_t* directions0[DIRECTION_COUNT];

	states0[ZOMBIE_STATE_IDLE] = L"IDLE";
	states0[ZOMBIE_STATE_INFEST] = L"INFEST";
	states0[ZOMBIE_STATE_MOVE] = L"MOVE";
	states0[ZOMBIE_STATE_DIE] = L"DIE";

	directions0[DIRECTION_UP] = L"UP";
	directions0[DIRECTION_RIGHT_UP] = L"RIGHT_UP";
	directions0[DIRECTION_RIGHT] = L"RIGHT";
	directions0[DIRECTION_RIGHT_DOWN] = L"RIGHT_DOWN";
	directions0[DIRECTION_DOWN] = L"DOWN";
	directions0[DIRECTION_LEFT_DOWN] = L"LEFT_DOWN";
	directions0[DIRECTION_LEFT] = L"LEFT";
	directions0[DIRECTION_LEFT_UP] = L"LEFT_UP";

	for (unsigned int i = 0; i < ZOMBIE_STATE_COUNT; ++i)
	{
		for (unsigned int k = 0; k < iANIMATOR_ZOMBIE_MOTION_LENGTH[i]; ++k)
		{
			if (i == ZOMBIE_STATE_DIE)
			{
				memset(path0, 0, MAX_PATH);
				swprintf(path0, L"..\\Data\\infestedTerran\\%s\\%s_%d.bmp", states0[i], states0[i], (k + 1));
				map0 = Bitmap::FromFile(path0);
				m_ppppkZombie[i][0][k] = map0->Clone(0, 0, map0->GetWidth(), map0->GetHeight(), PixelFormat32bppARGB);
				SAFE_DELETE(map0);

				continue;
			}

			for (unsigned int j = 0; j < DIRECTION_COUNT; ++j)
			{
				memset(path0, 0, MAX_PATH);
				swprintf(path0, L"..\\Data\\infestedTerran\\%s\\%s_%s_%d.bmp", states0[i], states0[i], directions0[j], (k + 1));
				map0 = Bitmap::FromFile(path0);
				m_ppppkZombie[i][j][k] = map0->Clone(0, 0, map0->GetWidth(), map0->GetHeight(), PixelFormat32bppARGB);
				SAFE_DELETE(map0);
			}
		}
	}
}

bool
CAnimator::ChangeColor(Bitmap* pkBitmap_) {
	if(isptr(pkBitmap_)) {
		Color kOrigColor1(255, 247, 15, 15);
		Color kOrigColor2(255, 191, 23, 23);
		Color kOrigColor3(255, 162, 15, 15);
		Color kOrigColor4(255, 130, 0, 0);
		Color kOrigColor5(255, 107, 0, 0);
		Color kOrigColor6(255, 85, 0, 0);

		Color kNewColor(GetBody().GetColor().A, GetBody().GetColor().R, GetBody().GetColor().G, GetBody().GetColor().B);
		Color kCurColor;

		for(INT i = 0; i < pkBitmap_->GetWidth(); ++i) {
			for(INT j = 0; j < pkBitmap_->GetHeight(); ++j) {
				pkBitmap_->GetPixel(i, j, &kCurColor);
				if(((kOrigColor1.GetAlpha() == kCurColor.GetAlpha()) && (kOrigColor1.GetRed() == kCurColor.GetRed()) && (kOrigColor1.GetGreen() == kCurColor.GetGreen()) && (kOrigColor1.GetBlue() == kCurColor.GetBlue()))
				|| ((kOrigColor2.GetAlpha() == kCurColor.GetAlpha()) && (kOrigColor2.GetRed() == kCurColor.GetRed()) && (kOrigColor2.GetGreen() == kCurColor.GetGreen()) && (kOrigColor2.GetBlue() == kCurColor.GetBlue()))
				|| ((kOrigColor3.GetAlpha() == kCurColor.GetAlpha()) && (kOrigColor3.GetRed() == kCurColor.GetRed()) && (kOrigColor3.GetGreen() == kCurColor.GetGreen()) && (kOrigColor3.GetBlue() == kCurColor.GetBlue()))
				|| ((kOrigColor4.GetAlpha() == kCurColor.GetAlpha()) && (kOrigColor4.GetRed() == kCurColor.GetRed()) && (kOrigColor4.GetGreen() == kCurColor.GetGreen()) && (kOrigColor4.GetBlue() == kCurColor.GetBlue()))
				|| ((kOrigColor5.GetAlpha() == kCurColor.GetAlpha()) && (kOrigColor5.GetRed() == kCurColor.GetRed()) && (kOrigColor5.GetGreen() == kCurColor.GetGreen()) && (kOrigColor5.GetBlue() == kCurColor.GetBlue()))
				|| ((kOrigColor6.GetAlpha() == kCurColor.GetAlpha()) && (kOrigColor6.GetRed() == kCurColor.GetRed()) && (kOrigColor6.GetGreen() == kCurColor.GetGreen()) && (kOrigColor6.GetBlue() == kCurColor.GetBlue()))
				) {
					pkBitmap_->SetPixel(i, j, kNewColor);
				}
			}
		}

		// 김병묵 학생의 엣지 구현 코드
		// (시작)
		Color kEdgeColor(255, 0, 255, 0);

		if (STATE_INFESTED == GetBody().GetState()) kEdgeColor = 0xffff0000;

		bool bEdge = false;

		for(INT j = 0; j < pkBitmap_->GetHeight(); ++j) {
			for(INT i = 0; i < pkBitmap_->GetWidth(); ++i) {
				pkBitmap_->GetPixel(i, j, &kCurColor);

				// 마젠타가 아닐경우 안쪽과 바깥쪽으로 엣지 주는 코드 (수평)
				if((kCurColor.GetValue() != 0xffff00ff) && (kCurColor.GetValue() != kEdgeColor.GetValue()) && (false == bEdge)) {
					bEdge = true;
					pkBitmap_->SetPixel(i - 2, j, kEdgeColor);
					pkBitmap_->SetPixel(i - 3, j, kEdgeColor);
				} else if((kCurColor.GetValue() == 0xffff00ff) && bEdge) {
					bEdge = false;
					pkBitmap_->SetPixel(i + 1, j, kEdgeColor);
					pkBitmap_->SetPixel(i + 2, j, kEdgeColor);
				}
			}
		}

		for(INT i = 0; i < pkBitmap_->GetWidth(); ++i) {
			for(INT j = 0; j < pkBitmap_->GetHeight(); ++j) {
				pkBitmap_->GetPixel(i, j, &kCurColor);

				// 마젠타가 아닐경우 안쪽과 바깥쪽으로 엣지 주는 코드 (수직)
				if((kCurColor.GetValue() != 0xffff00ff) && (kCurColor.GetValue() != kEdgeColor.GetValue()) && (false == bEdge)) {
					bEdge = true;
					pkBitmap_->SetPixel(i, j - 2, kEdgeColor);
					pkBitmap_->SetPixel(i, j - 3, kEdgeColor);
				} else if((kCurColor.GetValue() == 0xffff00ff) && bEdge) {
					bEdge = false;
					pkBitmap_->SetPixel(i, j + 1, kEdgeColor);
					pkBitmap_->SetPixel(i, j + 2, kEdgeColor);
				}
			}
		}
		// (끝)
		// 김병묵 학생의 엣지 구현 코드
		return true;
	}
	return false;
}

void
CAnimator::Update(HDC hDC_) {
	bool bCheck = false;

	if (0 == m_tkDelayTick) {
		m_tkDelayTick = g_kTick.GetTick();
	} else {
		if (STATE_MOVE == GetBody().GetState()) {
			if(g_kTick.GetTick() >= (m_tkDelayTick + iANIMATOR_MOVE_LATENCY)) {
				m_tkDelayTick = g_kTick.GetTick();
			} else {
				bCheck = true;
			}
		} else if (STATE_ATTACK == GetBody().GetState()) {
			if(g_kTick.GetTick() >= (m_tkDelayTick + iANIMATOR_ATTACK_LATENCY)) {
				m_tkDelayTick = g_kTick.GetTick();
			} else {
				bCheck = true;
			}
		} else if (STATE_IDLE == GetBody().GetState()) {
			if(g_kTick.GetTick() >= (m_tkDelayTick + iANIMATOR_IDLE_LATENCY)) {
				m_tkDelayTick = g_kTick.GetTick();
			} else {
				bCheck = true;
			}
		}
		else if (STATE_INFESTED == GetBody().GetState()) {

			if (g_kTick.GetTick() >= (m_tkDelayTick + iANIMATOR_ZOMBIE_MOTION_LATENCY[GetBody().GetZombieState()])) m_tkDelayTick = g_kTick.GetTick();
			else bCheck = 1;

		} else {
			if(g_kTick.GetTick() >= (m_tkDelayTick + iANIMATOR_DIED_LATENCY)) {
				m_tkDelayTick = g_kTick.GetTick();
			} else {
				bCheck = true;
			}
		}
	}

	Graphics graphics(hDC_);
	graphics.ScaleTransform(0.5f, 0.5f);

	//MoveToEx(hDC_, iPosX, iPosY, NULL);

	INT iPosX = (GetBody().GetPosX() + 20) * 2;
	INT iPosY = (GetBody().GetPosY() + 20) * 2;

	ImageAttributes kImageAttr;
	//kImageAttr.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	kImageAttr.SetColorKey(Color(255, 0, 255), Color(255, 0, 255));

	Bitmap* pkClone = NULL;

	if(STATE_IDLE == GetBody().GetState()) {
		if(m_iOffset >= iANIMATOR_IDLE_LEN) {
			m_iOffset = 0;
		}

		if(DIRECTION_UP == GetBody().GetDirection()) {
			pkClone = m_pkIdleUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT_UP == GetBody().GetDirection()) {
			pkClone = m_pkIdleRightUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT == GetBody().GetDirection()) {
			pkClone = m_pkIdleRight[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkIdleRightDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkIdleDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkIdleLeftDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT == GetBody().GetDirection()) {
			pkClone = m_pkIdleLeft[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT_UP == GetBody().GetDirection()) {
			pkClone = m_pkIdleLeftUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		}
	} else if (STATE_ATTACK == GetBody().GetState()) {
		if(m_iOffset >= iANIMATOR_ATTACK_LEN) {
			m_iOffset = 0;
		}

		if(DIRECTION_UP == GetBody().GetDirection()) {
			pkClone = m_pkAttackUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT_UP == GetBody().GetDirection()) {
			pkClone = m_pkAttackRightUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT == GetBody().GetDirection()) {
			pkClone = m_pkAttackRight[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkAttackRightDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkAttackDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkAttackLeftDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT == GetBody().GetDirection()) {
			pkClone = m_pkAttackLeft[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT_UP == GetBody().GetDirection()) {
			pkClone = m_pkAttackLeftUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		}
	} else if (STATE_MOVE == GetBody().GetState()) {
		if(m_iOffset >= iANIMATOR_MOVE_LEN) {
			m_iOffset = 0;
		}

		if(DIRECTION_UP == GetBody().GetDirection()) {
			pkClone = m_pkMoveUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT_UP == GetBody().GetDirection()) {
			pkClone = m_pkMoveRightUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT == GetBody().GetDirection()) {
			pkClone = m_pkMoveRight[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_RIGHT_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkMoveRightDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkMoveDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT_DOWN == GetBody().GetDirection()) {
			pkClone = m_pkMoveLeftDown[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT == GetBody().GetDirection()) {
			pkClone = m_pkMoveLeft[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		} else if(DIRECTION_LEFT_UP == GetBody().GetDirection()) {
			pkClone = m_pkMoveLeftUp[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
			ChangeColor(pkClone);
			graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
		}
	} else if (STATE_INFESTED == GetBody().GetState()) 	{

		if (m_iOffset >= iANIMATOR_ZOMBIE_MOTION_LENGTH[GetBody().GetZombieState()]) m_iOffset = 0;

		pkClone = m_ppppkZombie[GetBody().GetZombieState()][GetBody().GetDirection()][m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
		ChangeColor(pkClone);
		graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);

	} else {
		if(m_iOffset >= iANIMATOR_DIED_LEN) {
			m_iOffset = 0;
		}

		pkClone = m_pkDied[m_iOffset]->Clone(0, 0, m_pkIdleUp[m_iOffset]->GetWidth(), m_pkIdleUp[m_iOffset]->GetHeight(), PixelFormat32bppARGB);
		ChangeColor(pkClone);
		graphics.DrawImage(pkClone, Rect(0, 0, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2)), iPosX, iPosY, (iGAME_MAP_WIDTH * 2), (iGAME_MAP_HEIGHT * 2), UnitPixel, &kImageAttr);
	}



	Font kFont(L"돋움", 20, FontStyleRegular, UnitPixel);
	FLOAT fPosX = (iPosX * -1) - 20;
	FLOAT fPosY = (iPosY * -1) - 10;
	PointF kPoint(fPosX, fPosY);
	SolidBrush kBrush(Color(255, 255, 255, 255));

	wchar_t szPlayerName[iPLAYER_NAME_LEN] = { 0, };
	INT iLength = MultiByteToWideChar(CP_ACP, 0, GetBody().GetName(), strlen(GetBody().GetName()), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, GetBody().GetName(), strlen(GetBody().GetName()), szPlayerName, iLength);

	graphics.DrawString(szPlayerName, -1, &kFont, kPoint, &kBrush);
	fPosX = (iPosX * -1) - 30;
	fPosY = (iPosY * -1) - 30;
	kPoint.X = fPosX; kPoint.Y = fPosY;
	char szPlayerPos[32] = { 0, };
	sprintf(szPlayerPos, "%d, %d", int(GetBody().GetPosition().x), int(GetBody().GetPosition().y));
	iLength = MultiByteToWideChar(CP_ACP, 0, szPlayerPos, strlen(szPlayerPos), NULL, NULL);
	wchar_t szPlayerPosWide[32] = { 0, };
	MultiByteToWideChar(CP_ACP, 0, szPlayerPos, strlen(szPlayerPos), szPlayerPosWide, iLength);
	graphics.DrawString(szPlayerPosWide, -1, &kFont, kPoint, &kBrush);

	Pen pen(Color(255, 0, 0), 3.f);
	switch (GetBody().GetTeamType())
	{
	case TEAM_RED:
		pen.SetColor(Color(255, 0, 0));
		break;
	case TEAM_BLUE:
		pen.SetColor(Color(0, 0, 255));
		break;
	default:
		break;
	}
	graphics.DrawRectangle(&pen, 20*GetBody().GetMapIdxX(), 20* GetBody().GetMapIdxY(), 20, 20);

	fPosX = (iPosX * -1) - 20;
	fPosY = (iPosY * -1) - 50;
	kPoint.X = fPosX; kPoint.Y = fPosY;
	char szPlayerCurHp[32] = { 0, };
	sprintf(szPlayerCurHp, "Hp: %d", GetBody().GetCurLife());
	iLength = MultiByteToWideChar(CP_ACP, 0, szPlayerCurHp, strlen(szPlayerCurHp), NULL, NULL);
	wchar_t szPlayerCurHpWide[32] = { 0, };
	MultiByteToWideChar(CP_ACP, 0, szPlayerCurHp, strlen(szPlayerCurHp), szPlayerCurHpWide, iLength);
	graphics.DrawString(szPlayerCurHpWide, -1, &kFont, kPoint, &kBrush);

	pen.SetColor(Color(255, 255, 255));
	pen.SetWidth(3.f);

	size_t size = g_kMainRoom.GetTopCount();
	for (size_t i = 0; i < size; ++i) {
		CPlayerEx* kPlayer = (CPlayerEx*)g_kMainRoom.GetMember(i);
		if (isptr(kPlayer))
		{
			if (kPlayer->IsFire()) {
				int randX = rand() % 10;
				int randY = rand() % 10;
				graphics.DrawLine(&pen, 20 * kPlayer->GetMapIdxX() + 10, 20 * kPlayer->GetMapIdxY() + 10
					, 20 * kPlayer->GetTargetMapIdx().x + randX, 20 * kPlayer->GetTargetMapIdx().y + randY);
				kPlayer->SetFire(false);
			}
		}
	}
	
	Font timeOutFont(L"돋움", 40, FontStyleBold, UnitPixel);
	kPoint.X = iGAME_MAP_WIDTH;
	kPoint.Y = 0;
	char szPlayerRoomTimeLeft[32] = { 0, };
	itoa(g_kMainRoom.GetTimeOut(), szPlayerRoomTimeLeft, 10);
	wchar_t szPlayerRoomTimeLeftWide[32] = { 0, };
	wsprintfW(szPlayerRoomTimeLeftWide, L"%03d", (INT)g_kMainRoom.GetTimeOut());
	//MultiByteToWideChar(CP_ACP, 0, szPlayerRoomTimeLeft, strlen(szPlayerRoomTimeLeft), szPlayerRoomTimeLeftWide, 32);
	wchar_t szTimeLeft[8] = { 0, };
	wchar_t szReadyWide[] = L"READY";
	wchar_t szInfoWide[] = L"방장이 엔터키를 누르면 시작합니다.";
	wchar_t szInfo2Wide[] = L"양팀의 인원수가 같을 때 시작 가능합니다.";
	wchar_t szRedTeamCount[2] = { 0, };
	wchar_t szBlueTeamCount[2] = { 0, };
	wsprintfW(szRedTeamCount, L"%d", g_kMainRoom.GetTeamPoint(TEAM_RED));
	wsprintfW(szBlueTeamCount, L"%d", g_kMainRoom.GetTeamPoint(TEAM_BLUE));
	StringFormat sf;
	sf.SetAlignment(StringAlignment::StringAlignmentCenter);
	Font resultFont(L"돋움", 80, FontStyleBold, UnitPixel);
	switch (g_kMainRoom.GetModType())
	{
	case MOD_FFA:
		break;
	case MOD_TDM:
		graphics.DrawString(szPlayerRoomTimeLeftWide, 3, &timeOutFont, kPoint, &sf, &kBrush);
		kPoint.X = iGAME_MAP_WIDTH;
		kPoint.Y = iGAME_MAP_HEIGHT - 40;
		if (ROOM_STATE_READY == g_kMainRoom.GetRoomState()) {
			graphics.DrawString(szReadyWide, 5, &timeOutFont, kPoint, &sf, &kBrush);
			kPoint.Y = iGAME_MAP_HEIGHT;
			graphics.DrawString(szInfoWide, 19, &kFont, kPoint, &sf, &kBrush);
			kPoint.Y = iGAME_MAP_HEIGHT + 20;
			graphics.DrawString(szInfo2Wide, 23, &kFont, kPoint, &sf, &kBrush);
		}
		kPoint.X = iGAME_MAP_WIDTH - 100;
		kPoint.Y = 0;
		kBrush.SetColor(Color(250, 100, 100));
		sf.SetAlignment(StringAlignment::StringAlignmentNear);
		graphics.DrawString(szRedTeamCount, 2, &timeOutFont, kPoint, &sf, &kBrush);
		kPoint.X = iGAME_MAP_WIDTH + 120;
		kBrush.SetColor(Color(100, 100, 250));
		sf.SetAlignment(StringAlignment::StringAlignmentFar);
		graphics.DrawString(szBlueTeamCount, 2, &timeOutFont, kPoint, &sf, &kBrush);
		if (ROOM_STATE_END == g_kMainRoom.GetRoomState()) {
			kPoint.X = iGAME_MAP_WIDTH;
			kPoint.Y = iGAME_MAP_HEIGHT - 40;
			sf.SetAlignment(StringAlignment::StringAlignmentCenter);
			kBrush.SetColor(Color(255, 255, 255));
			wchar_t szResultDraw[] = L"DRAW";
			wchar_t szResultLose[] = L"LOSE";
			wchar_t szResultWin[] = L"WIN";
			switch (g_kMainPlayer->GetResult()) {
			case GAME_RESULT_DRAW:
				graphics.DrawString(szResultDraw, 4, &resultFont, kPoint, &sf, &kBrush);
				break;
			case GAME_RESULT_LOSE:
				graphics.DrawString(szResultLose, 4, &resultFont, kPoint, &sf, &kBrush);
				break;
			case GAME_RESULT_WIN:
				graphics.DrawString(szResultWin, 3, &resultFont, kPoint, &sf, &kBrush);
				break;
			}
		}

		break;
	case MOD_ZOMBIE:
		break;
	default:
		break;
	}
	
	if(false == bCheck) {
		++m_iOffset;
	}

	if(isptr(pkClone)) {
		SAFE_DELETE(pkClone);
	}
}
