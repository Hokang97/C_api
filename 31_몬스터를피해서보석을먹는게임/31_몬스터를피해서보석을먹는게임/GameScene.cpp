#include "GameScene.h"
#pragma warning(disable:4996)
void GameScene::Init()
{
	// ����Ʈ �ʱ�ȭ
	if (m_MonsterList.size() > 0)
		m_MonsterList.clear();
	
	// �� ������ �ҷ�����
	LoadMap(const_cast<char*>("Resource/Map/Firstmap.txt"));

	// �� �̹��� �ҷ�����
	m_TileMap.LoadBitmapByPath("Resource/tilemap.bmp");

	m_Char.Init(this);
	m_Char.Init();

	m_Gem.Init(this);
	m_Gem.Init();

}

void GameScene::Update(float dt)
{
	for (auto itor = m_MonsterList.begin(); itor != m_MonsterList.end(); ++itor)
		itor->Update(dt);

	m_Char.Update(dt);
	m_Gem.Update(dt);
	
}

void GameScene::Render(HDC hdc, float dt)
{
	DrawMap(hdc, dt);
	for (auto itor = m_MonsterList.begin(); itor != m_MonsterList.end(); ++itor)
		itor->Render(hdc, dt);
	
	m_Gem.Render(hdc, dt);
	m_Char.Render(hdc, dt);

}

void GameScene::Destroy()
{
	for (auto itor = m_MonsterList.begin(); itor != m_MonsterList.end(); ++itor)
		itor->Destroy();
	
	m_Gem.Destroy();
	m_Char.Destroy();

}

void GameScene::LoadMap(char* fileDir)
{
	std::ifstream inputFile(fileDir);

	// 1.�� �ε��� ��������
	for (int i = 0; i < TILE_NUM_Y; i++)
	{
		for (int j = 0; j < TILE_NUM_X; j++)
		{
			inputFile >> m_Map[i][j];
		}
	}

	// 2. �� �浹 Ÿ�� ��������
	for (int i = 0; i < TILE_NUM_Y; i++)
	{
		for (int j = 0; j < TILE_NUM_X; j++)
		{
			inputFile >> m_CollMap[i][j];
		}
	}

	// 3. ���� Ÿ�� ��������
	for (int i = 0; i < TILE_NUM_Y; i++)
	{
		for (int j = 0; j < TILE_NUM_X; j++)
		{
			inputFile >> m_MonsterMap[i][j];

			if (m_MonsterMap[i][j] != -1)
			{
				// ���� ����
				Monster tempMonster;
				tempMonster.Init();
				tempMonster.Init(this);
				tempMonster.SetMoveType(j, i, (m_MonsterMap[i][j] == 1) ? MoveType::RIGHT : MoveType::LEFT);

				m_MonsterList.push_front(tempMonster);
			}
		}
	}
	inputFile.close();
}

void GameScene::DrawMap(HDC hdc, float dt)
{
	for (int i = 0; i < TILE_NUM_Y; i++)
	{
		for (int j = 0; j < TILE_NUM_X; j++)
		{
			m_TileMap.DrawBitmapByCropping(hdc, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE,
				(m_Map[i][j] % m_MapAcrossCount) * ORI_TILE_SIZE,
				(m_Map[i][j] / m_MapAcrossCount) * ORI_TILE_SIZE,
				ORI_TILE_SIZE, ORI_TILE_SIZE);

			if (m_viewIndex)
			{
				char index[256];
				sprintf(index, "%d %d", j, i);
				TextOutA(hdc, TILE_SIZE * j, TILE_SIZE * i, index, strlen(index));
			}

		}
	}
}

bool GameScene::CheckMoveAble(DWORD x, DWORD y)
{
	if (x < 0 || y < 0 || x >TILE_NUM_X - 1 || y > TILE_NUM_Y - 1) return FALSE;
	return (m_CollMap[y][x] == 0) ? TRUE : FALSE;
}

bool GameScene::CheckLadder(DWORD x, DWORD y)
{
	switch (m_Map[y][x])
	{
	case 24: case 25: case 27: case 30:
		return TRUE;
	}
	return FALSE;
}

RECT GameScene::GetCharRect()
{
	return m_Char.GetRect();
}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}
