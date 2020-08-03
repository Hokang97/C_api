#include "Gem.h"
#include "GameScene.h"
void Gem::Init(GameScene* pGameScene)
{
	m_pGameScene = pGameScene;
}

void Gem::Init()
{
	GetBitmap()->LoadBitmapByPath("Resource/gem.bmp");
	GetBitmap()->SetTransparentColor(RGB(0, 0, 0));

	SetX(m_PosX * TILE_SIZE);
	SetY(m_PosY * TILE_SIZE);
}

void Gem::Update(float dt)
{
	
}

void Gem::Render(HDC hdc, float dt)
{
	GetBitmap()->DrawBitmap(hdc, GetX(), GetY(), TILE_SIZE, TILE_SIZE);

	RECT dest;
	RECT gemRect = { GetX(), GetY(), GetX() + TILE_SIZE, GetY() + TILE_SIZE };

	if (IntersectRect(&dest, &m_pGameScene->GetCharRect(), &gemRect))
	{
		MessageBox(NULL, TEXT("게임 클리어!"), TEXT("알림"), MB_OK);
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("MenuScene");
	}
}

void Gem::Destroy()
{
}

Gem::Gem()
{
}

Gem::~Gem()
{
}
