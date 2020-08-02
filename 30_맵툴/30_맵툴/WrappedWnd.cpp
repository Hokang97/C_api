#include "WrappedWnd.h"
#include "PrepareWnd.h"

HWND WrappedWnd::GetWndHandle()
{
	return m_hWnd;
}

HINSTANCE WrappedWnd::GetInstanceHandle()
{
	return m_hInstance;
}

WrappedWnd::WrappedWnd()
{
}

WrappedWnd::~WrappedWnd()
{
}

int WrappedWnd::Loop(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;

	PrepareWnd value;
	value.hInstance = hInstance;
	value.nCmdShow = nCmdShow;
	
	this->registrWndClass(value);
	this->createWindow(value);
	this->showWindow(value);

	return this->MessageLoop();
}

void WrappedWnd::registrWndClass(const PrepareWnd& value)
{
	WNDCLASSEX wcex = { 0, };

	wcex.cbSize = sizeof(wcex);
	wcex.style = value.style;
	wcex.hInstance = value.hInstance;
	wcex.hCursor = value.hCursor;
	wcex.hbrBackground = value.hbrBackground;
	wcex.lpszClassName = (LPCWSTR)value.lpszClassName;
	wcex.lpfnWndProc = value.lpfnWndProc;
	RegisterClassEx(&wcex);
}

void WrappedWnd::createWindow(const PrepareWnd& value)
{
	m_hWnd = CreateWindow((LPCWSTR)value.lpszClassName, (LPCWSTR)value.lpWindowName, value.dwStyle, value.X, value.Y, value.nWidth, value.nHeight,
		value.hWndParent, value.hMenu, value.hInstance, value.lpParam);
}

void WrappedWnd::showWindow(const PrepareWnd& value)
{
	ShowWindow(m_hWnd, value.nCmdShow);
	UpdateWindow(m_hWnd);
}

int WrappedWnd::MessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	// ¾À ¼³Á¤ ÇÔ¼ö

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			this->ProcessingLoop();
		}
	}

	return (int)msg.wParam;
}
