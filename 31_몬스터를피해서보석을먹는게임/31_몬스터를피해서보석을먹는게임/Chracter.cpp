#include "Chracter.h"
#include "GameScene.h"
#pragma warning(disable:4996)

void Chracter::Init(GameScene* pGameScene)
{
	m_pGameScene = pGameScene;
}

void Chracter::Init()
{
	// 캐릭터 위치 초기화
	m_CharX = 0;
	m_CharY = 7;

	m_CharImageX = m_CharX * TILE_SIZE;
	m_CharImageY = m_CharY * TILE_SIZE;

	GetBitmap()->LoadBitmapByPath("Resource/spriteimage.bmp");
	GetBitmap()->SetTransparentColor(RGB(160, 151, 168));

	m_SpriteIndex = 8;
}

void Chracter::Update(float dt)
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (m_pGameScene->CheckLadder(m_CharX, m_CharY))
		{
			if (abs((double)(m_CharX * TILE_SIZE) - m_CharImageX) < 10) {
				if (m_CharY > 0) m_CharImageY -= m_CharSpeed;
			}
		}
		else if ((m_CharY * TILE_SIZE) < m_CharImageY)
		{
			m_CharImageY -= m_CharSpeed;
		}

		if (m_MoveType != MoveType::UP)
		{
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::UP;
			m_SpriteIndex = 12;
			
			m_SpriteAnimStart = 12;
			m_SpriteAnimEnd = 15;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_pGameScene->CheckLadder(m_CharX, m_CharY + 1))
		{
			if (abs((double)(m_CharX * TILE_SIZE) - m_CharImageX) < 30) {
				if (m_CharY < TILE_NUM_Y - 1) m_CharImageY += m_CharSpeed;
			}
		}
		else if ((m_CharY * TILE_SIZE) > m_CharImageY)
		{
			m_CharImageY += m_CharSpeed;
		}

		if (m_MoveType != MoveType::UP)
		{
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::UP;
			m_SpriteIndex = 12;

			m_SpriteAnimStart = 12;
			m_SpriteAnimEnd = 15;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_pGameScene->CheckMoveAble(m_CharX - 1, m_CharY))
		{
			if (abs((double)(m_CharY * TILE_SIZE) - m_CharImageY) < 30) {
				if (m_CharX > 0) m_CharImageX -= m_CharSpeed;
			}
		}
		else if ((m_CharX * TILE_SIZE) < m_CharImageX)
		{
			m_CharImageX -= m_CharSpeed;
		}

		if (m_MoveType != MoveType::LEFT)
		{
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::LEFT;
			m_SpriteIndex = 4;

			m_SpriteAnimStart = 4;
			m_SpriteAnimEnd = 7;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_pGameScene->CheckMoveAble(m_CharX + 1, m_CharY))
		{
			if (abs((double)(m_CharY * TILE_SIZE) - m_CharImageY) < 10) {
				if (m_CharX < TILE_NUM_X - 1) m_CharImageX += m_CharSpeed;
			}
		}
		else if ((m_CharX * TILE_SIZE) > m_CharImageX)
		{
			m_CharImageX += m_CharSpeed;
		}

		if (m_MoveType != MoveType::RIGHT)
		{
			m_SpriteAnimTime = GetTickCount();

			m_MoveType = MoveType::RIGHT;
			m_SpriteIndex = 8;

			m_SpriteAnimStart = 8;
			m_SpriteAnimEnd = 11;
		}
		else if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
	}

	m_CharX = (m_CharImageX + 32) / TILE_SIZE;
	m_CharY = (m_CharImageY + 32) / TILE_SIZE;

}

void Chracter::Render(HDC hdc, float dt)
{
//#define VIEW_CHARINFO
#ifdef VIEW_CHARINFO
	// 캐릭터 정보 표시
	Rectangle(hdc, m_CharX * TILE_SIZE, m_CharY * TILE_SIZE,
		m_CharX * TILE_SIZE + TILE_SIZE, m_CharY * TILE_SIZE + TILE_SIZE);

	char text[256];
	sprintf(text, "L : %d, T : %d", m_CharImageX, m_CharImageY);
	TextOutA(hdc, m_CharImageX, m_CharImageY - 30, text, strlen(text));

	sprintf(text, "R : %d, B : %d", m_CharImageX + TILE_SIZE, m_CharImageY + TILE_SIZE);
	TextOutA(hdc, m_CharImageX, m_CharImageY - 10, text, strlen(text));
#endif

	GetBitmap()->DrawBitmapByCropping(hdc, m_CharImageX, m_CharImageY, TILE_SIZE, TILE_SIZE,
		(m_SpriteIndex % m_SpriteAcrossCount) * 51, (m_SpriteIndex / m_SpriteAcrossCount) * 51, 51, 51);
}

void Chracter::Destroy()
{
}

RECT Chracter::GetRect()
{
	RECT rect = { m_CharImageX, m_CharImageY, m_CharImageX + TILE_SIZE, m_CharImageY + TILE_SIZE };

	return rect;
}

Chracter::Chracter()
{
}

Chracter::~Chracter()
{
}
