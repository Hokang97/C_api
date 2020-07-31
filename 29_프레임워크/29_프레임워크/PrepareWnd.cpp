#include "PrepareWnd.h"
#include "GameDirector.h"
PrepareWnd::PrepareWnd()
{
	cbSize = sizeof(WNDCLASSEX);
	style = CS_HREDRAW | CS_VREDRAW;
	lpfnWndProc = GameDirector::WndProc;
	cbClsExtra = 0;
	cbWndExtra = 0;
	hIcon = nullptr;
	hCursor = LoadCursor(nullptr, IDC_ARROW);
	hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	lpszClassName = (LPCSTR)TEXT("winclass");
	lpWindowName = (LPCSTR)TEXT("API Framework");
	dwStyle = WS_OVERLAPPEDWINDOW;
	X = CW_USEDEFAULT;
	Y = CW_USEDEFAULT;
	nWidth = 800;
	nHeight = 600;
	hWndParent = nullptr;
	hMenu = nullptr;
	lpParam = nullptr;
	nCmdShow = SW_SHOW;
}

PrepareWnd::~PrepareWnd()
{
}
