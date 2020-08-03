#pragma once
#include "Object.h"

class GameScene;
class Gem : public Object
{
public:
	void Init(GameScene* pGameScene);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

private:
	GameScene* m_pGameScene;
	int m_PosX = 9;
	int m_PosY = 0;
public:
	Gem();
	~Gem();

};

