#pragma once
#include "Scene.h"

class FirstScene : public Scene
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

public:
	FirstScene();
	~FirstScene();

};

