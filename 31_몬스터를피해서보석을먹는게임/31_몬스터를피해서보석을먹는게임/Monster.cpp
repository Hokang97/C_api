#include "Monster.h"
#include "GameScene.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Init(GameScene* pGameScene)
{
	m_pGameScene = pGameScene;
	m_MoveType = MoveType::RIGHT;
}

void Monster::SetMoveType(int x, int y, MoveType type)
{
	SetX(x * TILE_SIZE);
	SetY(y * TILE_SIZE);

	m_MoveType = type;

	m_TileIndex_X = x;
	m_TileIndex_Y = y;

	switch (m_MoveType)
	{
	case MoveType::LEFT:
		m_SpriteIndex = 0;
		m_SpriteAnimStart = 0;
		m_SpriteAnimEnd = 4;
		break;

	case MoveType::RIGHT:
		m_SpriteIndex = 5;
		m_SpriteAnimStart = 5;
		m_SpriteAnimEnd = 9;
		break;
	}
}

void Monster::Init()
{
	GetBitmap()->LoadBitmapByPath("Resource/slimesprite.bmp");
}

void Monster::Update(float dt)
{
	switch (m_MoveType)
	{
	case MoveType::LEFT:
		if (m_pGameScene->CheckMoveAble(m_TileIndex_X - 1, m_TileIndex_Y))
		{
			if (m_TileIndex_X > 0) SetX(GetX() - 3);
		}
		else if ((m_TileIndex_X * TILE_SIZE) < GetX())
		{
			SetX(GetX() - 3);
		}
		else
		{
			SetX(m_TileIndex_X * TILE_SIZE);
			m_MoveType = MoveType::RIGHT;
			m_SpriteIndex = 5;
			m_SpriteAnimStart = 5;
			m_SpriteAnimEnd = 9;
		}

		if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}

		break;

	case MoveType::RIGHT:
		if (m_pGameScene->CheckMoveAble(m_TileIndex_X + 1, m_TileIndex_Y))
		{
			if (m_TileIndex_X < TILE_NUM_X - 1) SetX(GetX() + 3);
		}
		else if ((m_TileIndex_X * TILE_SIZE) > GetX())
		{
			SetX(GetX() + 3);
		}
		else
		{
			SetX(m_TileIndex_X * TILE_SIZE);
			m_MoveType = MoveType::LEFT;
			m_SpriteIndex = 0;
			m_SpriteAnimStart = 0;
			m_SpriteAnimEnd = 4;
		}

		if (GetTickCount() - m_SpriteAnimTime > 100)
		{
			m_SpriteAnimTime = GetTickCount();
			m_SpriteIndex = (++m_SpriteIndex > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteIndex;
		}
		break;
	}

	m_TileIndex_X = (GetX() + 32) / TILE_SIZE;
	m_TileIndex_Y = (GetY() + 32) / TILE_SIZE;

	// 캐릭터와 몬스터 충돌처리
	RECT dest;
	if (IntersectRect(&dest, &m_pGameScene->GetCharRect(), &GetRect()))
	{
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("MenuScene");
	}

}

void Monster::Render(HDC hdc, float dt)
{
	GetBitmap()->SetTransparentColor(RGB(0, 0, 0));
	GetBitmap()->DrawBitmapByCropping(hdc, GetX(), GetY(), TILE_SIZE, TILE_SIZE,
		(m_SpriteIndex % m_SpriteAcrossCount) * TILE_SIZE,
		(m_SpriteIndex / m_SpriteAcrossCount) * TILE_SIZE,
		TILE_SIZE, TILE_SIZE);
}

void Monster::Destroy()
{
}

RECT Monster::GetRect()
{
	RECT rect = { GetX() + 20, GetY() + 20, GetX() + TILE_SIZE - 20, GetY() + TILE_SIZE - 20 };
	return rect;
}
