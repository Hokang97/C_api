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
	
	DWORD m_MapAcrossCount = 8;	// Ÿ�� ���� ũ��
	DWORD m_MapMaxCount = 32;	// �� Ÿ�� �ִ� ����
	
	DWORD m_SelectNumber = 0;	// ���õ� Ÿ�� �ε���
	DWORD m_AddNum = 0;			// ������ ����Ʈ �̵� ��
	
	BOOL m_IsColl = FALSE;			// �浹 üũ
	BOOL m_IsMakeMonster = FALSE;	// ���� ���� ���

	DWORD m_KeyTime = 0; // Ű �Է� �ð�

public:
	FirstScene();
	~FirstScene();

};

