#pragma once
#include "Object.h"
class BackGround : public Object
{
public:
	void Init(char* imageName, RECT rect);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	void SetTransparentColor(DWORD color);

private:
	DWORD m_Width;
	DWORD m_Height;

public:
	BackGround();
	~BackGround();

};

