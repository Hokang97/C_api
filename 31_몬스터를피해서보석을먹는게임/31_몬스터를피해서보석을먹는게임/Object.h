#pragma once
#include "Bitmap.h"

class Object
{
private:
	Bitmap mBitmap;
	DWORD mPosiX = 0;
	DWORD mPosiY = 0;

public:
	void SetX(int value) { mPosiX = value; }
	void SetY(int value) { mPosiY = value; }

	Bitmap* GetBitmap() { return &mBitmap; }
	DWORD GetX() { return mPosiX; }
	DWORD GetY() { return mPosiY; }

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc, float dt) = 0;
	virtual void Destroy() = 0;


};