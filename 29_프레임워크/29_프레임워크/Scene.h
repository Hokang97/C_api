#pragma once
#include "GameDefine.h"


class Scene
{

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc, float dt) = 0;
	virtual void Destroy() = 0;


};
