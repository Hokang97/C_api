#pragma once
#include "Object.h"

class GameScene;

class Chracter : public Object
{
public:
	void Init(GameScene* pGameScene);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	RECT GetRect();

private:
	int m_CharImageX = 0;
	int m_CharImageY = 0;
	DWORD m_CharSpeed = 5;

	int m_CharX = 0;
	int m_CharY = 0;

	DWORD m_keyTime = 0;

	MoveType m_MoveType = MoveType::NONE;

	DWORD m_SpriteIndex = 0;
	
	DWORD m_SpriteAnimStart = 0;
	DWORD m_SpriteAnimEnd = 0;

	DWORD m_SpriteAnimTime = 0;

	DWORD m_SpriteAcrossCount = 4;
	DWORD m_SpriteMaxCount = 16;

	GameScene* m_pGameScene;

public:
	Chracter();
	~Chracter();

};

