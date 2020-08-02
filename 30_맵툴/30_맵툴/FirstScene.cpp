#include "FirstScene.h"
#include "GameDirector.h"
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int tempMap[MAP_WIDTH][MAP_HEIGHT];
int collMap[MAP_WIDTH][MAP_HEIGHT];
int monsterMap[MAP_WIDTH][MAP_HEIGHT];

void FirstScene::Init()
{
	m_TileMap.LoadBitmapByPath("Resource/tilemap.bmp");
	m_Monster.LoadBitmapByPath("Resource/slimesprite.bmp");

	//m_TileMap.SetTransparentColor(RGB(255, 255, 255));
	m_Monster.SetTransparentColor(RGB(0, 0, 0));
	
	m_MapSize.x = MAP_WIDTH;
	m_MapSize.y = MAP_HEIGHT;

	m_ScreenSize.x = m_MapSize.x * TILE_SIZE;
	m_ScreenSize.y = m_MapSize.y * TILE_SIZE + 20;

	m_ItemListSize.x = m_ScreenSize.x;
	m_ItemListSize.y = m_ScreenSize.y + TILE_SIZE;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			tempMap[i][j] = 0;
			collMap[i][j] = 0;
			monsterMap[i][j] = -1;
		}
	}
	
	LoadMap();
}

void FirstScene::Update(float dt)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_AddNum > 0) m_AddNum--;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_AddNum < m_MapMaxCount - m_MapSize.x) m_AddNum++;
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT mPosi;

		mPosi.x = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
		mPosi.y = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

		// 맵 타일 범위를 클릭했을 때
		if (mPosi.x >= 0 && mPosi.x <= m_ScreenSize.x && mPosi.y >= 0 && mPosi.y <= m_ScreenSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;
			int mY = mPosi.y / TILE_SIZE;

			if (m_IsMakeMonster)
			{
				monsterMap[mY][mX] = m_SelectNumber;
			}
			else
			{
				tempMap[mY][mX] = m_SelectNumber;

				// 충돌체크가 되었을 경우 충돌처리
				if (m_IsColl) collMap[mY][mX] = 1;
				else		  collMap[mY][mX] = 0;
			}
		}

		// 아이템 범위를 클릭했을 때
		else if (mPosi.x <= m_ItemListSize.x && mPosi.y <= m_ItemListSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;
			m_SelectNumber = mX + m_AddNum;
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		POINT mPosi;

		mPosi.x = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionX();
		mPosi.y = GameDirector::GetGameDirector()->GetSceneManager()->GetMousePositionY();

		// 맵 타일 범위를 클릭했을 때
		if (mPosi.x >= 0 && mPosi.x <= m_ScreenSize.x && mPosi.y >= 0 && mPosi.y <= m_ScreenSize.y)
		{
			int mX = mPosi.x / TILE_SIZE;
			int mY = mPosi.y / TILE_SIZE;

			monsterMap[mY][mX] = -1;
		}
	}

	// S키 저장
	if (GetAsyncKeyState(0x53))
	{
		MessageBox(NULL, TEXT("맵을 저장했습니다"), TEXT("알림"), MB_OK);
		SaveMap();
	}
	// C키를 눌렀다면 충돌 활성화/비활성화
	if (GetAsyncKeyState(0x43) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_IsColl = !m_IsColl;
	}

	// M키를 누를때 몬스터 / 맵타일 모드 변경
	if (GetAsyncKeyState(0x4D) && GetTickCount() - m_KeyTime > 100)
	{
		m_KeyTime = GetTickCount();

		m_IsMakeMonster = !m_IsMakeMonster;

		m_SelectNumber = 0;
		m_AddNum = 0;
	}
}

void FirstScene::Render(HDC hdc, float dt)
{
	// 1. 맵타일 그리기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			m_TileMap.DrawBitmapByCropping(hdc, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE,
				(tempMap[i][j] % m_MapAcrossCount) * ORI_TILE_SIZE,
				(tempMap[i][j] / m_MapAcrossCount) * ORI_TILE_SIZE,
				ORI_TILE_SIZE, ORI_TILE_SIZE);
				
			// 몬스터 그리기
			if (monsterMap[i][j] != -1)
			{
				m_Monster.DrawBitmapByCropping(hdc, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE, TILE_SIZE,
					(monsterMap[i][j] / 5) * TILE_SIZE,
					(monsterMap[i][j] % 5) * TILE_SIZE,
					TILE_SIZE, TILE_SIZE);
			}

			// 충돌맵 그리기
			if (collMap[i][j] == 1)
			{
				Ellipse(hdc, TILE_SIZE * j, TILE_SIZE * i, TILE_SIZE * j + 20, TILE_SIZE * i + 20);
			}
		}
	}

	// 2. 아이템 리스트 그리기
	for (int i = 0; i < m_MapSize.x; i++)
	{
		if (m_IsMakeMonster)
		{
			m_Monster.DrawBitmapByCropping(hdc, TILE_SIZE * i, m_ScreenSize.y, TILE_SIZE, TILE_SIZE,
				0, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
		else
		{
			m_TileMap.DrawBitmapByCropping(hdc, TILE_SIZE * i, m_ScreenSize.y, TILE_SIZE, TILE_SIZE,
				((i + m_AddNum) % m_MapAcrossCount) * ORI_TILE_SIZE,
				((i + m_AddNum) / m_MapAcrossCount) * ORI_TILE_SIZE,
				ORI_TILE_SIZE, ORI_TILE_SIZE);
		}
	}

	// 3. 선택한 타일 이미지 그리기
	RECT rect = {
		TILE_SIZE * m_MapSize.x + 20, m_ScreenSize.y - 20,
		TILE_SIZE * m_MapSize.x + 105, m_ScreenSize.y };

	DrawText(hdc, TEXT("선택한 타일"), 12, &rect, NULL);

	if (m_IsMakeMonster)
	{
		m_Monster.DrawBitmapByCropping(hdc, TILE_SIZE * m_MapSize.x + 20,
			m_ScreenSize.y, TILE_SIZE, TILE_SIZE,
			(m_SelectNumber / 5) * TILE_SIZE, 
			(m_SelectNumber % 5) * TILE_SIZE, 
			TILE_SIZE, TILE_SIZE);
	}
	else
	{
		m_TileMap.DrawBitmapByCropping(hdc, TILE_SIZE * m_MapSize.x + 20,
			m_ScreenSize.y, TILE_SIZE, TILE_SIZE,
			(m_SelectNumber % m_MapAcrossCount) * ORI_TILE_SIZE, 
			(m_SelectNumber / m_MapAcrossCount) * ORI_TILE_SIZE,
			ORI_TILE_SIZE, ORI_TILE_SIZE);

		if (m_IsColl)
		{
			Ellipse(hdc, TILE_SIZE * m_MapSize.x + 20, m_ScreenSize.y,
				TILE_SIZE * m_MapSize.x + 40, m_ScreenSize.y + 20);
		}
	}
}

void FirstScene::Destroy()
{
}

void FirstScene::LoadMap()
{
	std::ifstream inputFile("output.txt");

	// 1. 일반 타일 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			inputFile >> tempMap[i][j];
		}
	}

	// 2. 충돌 타일 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			inputFile >> collMap[i][j];
		}
	}

	// 3. 몬스터 오브젝트 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			inputFile >> monsterMap[i][j];
		}
	}
	inputFile.close();
}

void FirstScene::SaveMap()
{
	std::ofstream outputFile("output.txt");

	// 1. 일반 타일 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			outputFile << tempMap[i][j] << " ";
		}
		outputFile << std::endl;

	}

	// 2. 충돌 타일 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			outputFile << collMap[i][j] << " ";
		}
		outputFile << std::endl;
	}

	// 3. 몬스터 오브젝트 불러오기
	for (int i = 0; i < m_MapSize.y; i++)
	{
		for (int j = 0; j < m_MapSize.x; j++)
		{
			outputFile << monsterMap[i][j] << " ";
		}
		outputFile << std::endl;
	}
	outputFile.close();
}

FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{
}
