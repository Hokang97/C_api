#pragma once
#include<Windows.h>
#include "GameDefine.h"	
#pragma comment(lib, "msimg32.lib")
class Bitmap
{
public:
	Bitmap();
	Bitmap(const std::string fileDir);
	Bitmap(const Bitmap& bitmap);
	~Bitmap();

public:
	BOOL LoadBitmapByPath(const std::string fileDir);

public:
	BOOL Empty() const;

	HBITMAP			GetBitmapHandle() const;
	const BITMAP	GetBitmapInfo() const;
	std::string		GetFileDirectory() const;

public:
	void	DrawBitmap(HDC hdc, int x, int y, int width, int height) const;
	void	DrawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const;

protected:
	HBITMAP		m_BitmapHandle = nullptr;
	BITMAP		m_BitmapInfo;
	std::string m_FileDir = "";

public:
	void	SetTransparentColor(DWORD color);
	DWORD	GetTransparentColor() const;

private:
	DWORD m_TransparentColor = RGB(255, 0, 255);
};

