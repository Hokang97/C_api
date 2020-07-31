#include "GameDirector.h"

GameDirector::GameDirector()
{
	ApplicationHandle = this;
	m_SceneManager = new SceneManager;
}

GameDirector::~GameDirector()
{
	delete m_SceneManager;
}

GameDirector* GameDirector::GetGameDirector()
{
	static GameDirector dir;
	return &dir;
}

LRESULT GameDirector::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return ApplicationHandle->MessageHandler(hwnd, message, wParam, lParam);
	}
}

LRESULT GameDirector::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		m_SceneManager->SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void GameDirector::ProcessingLoop()
{
	static DWORD prevFrameTime = 0;
	if (GetTickCount() - prevFrameTime > m_FrameInterval)
	{
		prevFrameTime = GetTickCount();
		HDC hdc = GetDC(m_hWnd);

		Update(((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		Render(hdc, ((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		ReleaseDC(m_hWnd, hdc);
	}
}

void GameDirector::Update(float dt)
{
	m_SceneManager->Update(dt);
}

void GameDirector::Render(HDC hdc, float dt)
{
	HDC hMemDC;
	RECT windowRect;
	HBITMAP bitmap;

	GetClientRect(this->GetWndHandle(), &windowRect);
	
	hMemDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &windowRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	m_SceneManager->Render(hMemDC, dt);
}

void GameDirector::SetFrameInterval(DWORD interval)
{
	m_FrameInterval = interval;
}

DWORD GameDirector::GetFrameInterval()
{
	return m_FrameInterval;
}

SceneManager* GameDirector::GetSceneManager()
{
	return m_SceneManager;
}
