#pragma once
#include "WrappedWnd.h"
#include "SceneManager.h"

class GameDirector : public WrappedWnd
{
public:
	static GameDirector*		GetGameDirector();
	static LRESULT CALLBACK		WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK			MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	virtual void	ProcessingLoop();

	void Update(float dt);
	void Render(HDC hdc, float dt);

	void SetFrameInterval(DWORD interval);
	DWORD GetFrameInterval();

	SceneManager* GetSceneManager();

private:
	SceneManager* m_SceneManager = nullptr;
	DWORD		  m_FrameInterval = 0;

public:
	GameDirector();
	~GameDirector();

};

static GameDirector* ApplicationHandle = 0;
static GameDirector* GetApplicationHandle() { return ApplicationHandle; }

