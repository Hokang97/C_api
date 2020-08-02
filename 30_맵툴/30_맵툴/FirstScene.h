#pragma once
#include "Scene.h"
#include "Bitmap.h"
#include <fstream>

class FirstScene : public Scene
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	void LoadMap();
	void SaveMap();

private:
	POINT m_ScreenSize;
	POINT m_MapSize;
	POINT m_ItemListSize;

	Bitmap m_TileMap;
	Bitmap m_Monster;
	
	DWORD m_MapAcrossCount = 8;	// 타일 가로 크기
	DWORD m_MapMaxCount = 32;	// 맵 타일 최대 개수
	
	DWORD m_SelectNumber = 0;	// 선택된 타일 인덱스
	DWORD m_AddNum = 0;			// 아이템 리스트 이동 값
	
	BOOL m_IsColl = FALSE;			// 충돌 체크
	BOOL m_IsMakeMonster = FALSE;	// 몬스터 생성 모드

	DWORD m_KeyTime = 0; // 키 입력 시간

public:
	FirstScene();
	~FirstScene();

};

