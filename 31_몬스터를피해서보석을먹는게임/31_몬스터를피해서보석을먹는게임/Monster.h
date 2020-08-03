#pragma once
#include "Object.h"

class GameScene;

class Monster : public Object
{
public:
	void Init(GameScene* pGameScene);
	void SetMoveType(int x, int y, MoveType type);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	RECT GetRect();

private:
	GameScene* m_pGameScene = 0;

	int m_TileIndex_X;
	int m_TileIndex_Y;

	MoveType m_MoveType;
	
	DWORD m_SpriteIndex = 0;
	DWORD m_SpriteAnimStart = 0;
	DWORD m_SpriteAnimEnd = 0;
	
	DWORD m_SpriteAnimTime = 0;
	DWORD m_SpriteAcrossCount = 5;

public:
	Monster();
	~Monster();

};

