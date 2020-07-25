#include <Windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#include "resource.h"

#define ID_TOOLBAR 101

COLORREF Back;
DWORD iMode;
HWND g_hToolBar;

TBBUTTON ToolBtn[] =
{
	{0, 10, TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0},
	{5, 0, 0, TBSTYLE_SEP,0,0,0,0},

	{1, 11, TBSTATE_ENABLED | TBSTATE_CHECKED, TBSTYLE_CHECKGROUP,0,0,0, 1},
	{2, 12, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP,0,0,0, 2},
	{3, 13, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP,0,0,0, 3},
	{5, 0, 0, TBSTYLE_SEP,0,0,0,0},

	{4,14,TBSTATE_ENABLED, TBSTYLE_CHECK | TBSTYLE_AUTOSIZE,0,0,0,4},
	{5,15,TBSTATE_ENABLED, TBSTYLE_DROPDOWN | TBSTYLE_NOPREFIX,0,0,0,5},
	{6,16,TBSTATE_ENABLED, TBSTYLE_DROPDOWN | BTNS_WHOLEDROPDOWN,0,0,0,6}


};

// 함수 호출 방법
// __stdcall : 매개변수의 개수가 고정된 함수    / 크기 작다  / callee (피호출자) stack 정리
// __cdecl   : 매개변수의 개수가 가변적인 함수  / 크기 크다  / caller (호출자)   stack 정리

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	// 1. 윈도우 클래스 설정/초기화
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbClsExtra = 0;	// 특수한 목적으로 사용될 예약 영역
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;		// 윈도우 클래스를 등록하는 프로그램의 번호
	WndClass.lpfnWndProc = WndProc;		// 프로시저 설정
	WndClass.lpszClassName = TEXT("WndClass");
	WndClass.lpszMenuName = NULL;

	// 2. 윈도우 클래스 등록
	RegisterClass(&WndClass);

	// 3. 윈도우 창 생성
	hWnd = CreateWindow(WndClass.lpszClassName, TEXT("윈도우타이틀"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 640, NULL, NULL, hInstance, NULL);


	// 4. 윈도우 창 활성화/표시
	ShowWindow(hWnd, SW_SHOW);

	// 5. 메세지 루프/처리
	// GetMessage()
	// PeekMessage()


	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);		// 키보드 입력 메세지를 프로그램에서 사용할 수 있도록 가공
		DispatchMessage(&Msg);		// 메세지 큐에서 꺼낸 메세지를 프로시저에 전달
	}

	return (int)Msg.wParam;





}

// 콜백함수 매개변수
// hwnd - 메세지를 받을 윈도우 핸들러
// msg	- 어떤 종류의 메세지인지 확일할 수 있는 값
// wParam	- 메세지의 부가 정보 (메세지에 따라 다름)
// lParam	- 메세지의 부가 정보 (메세지에 따라 다름)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT crt;
	HBRUSH hBrush;

	const TCHAR* Message = TEXT("테스트 문자열입니다.");
	const TCHAR* szString = TEXT("명령버튼\0빨간색\0초록색\0파란색\0투명\0&Drop\0&Drop2\0");

	switch (msg)
	{
	case WM_CREATE:
		InitCommonControls();
		g_hToolBar = CreateToolbarEx(hwnd, WS_CHILD | WS_VISIBLE | WS_BORDER | TBSTYLE_FLAT,
			ID_TOOLBAR, 10, g_hInst, IDB_BITMAP1, ToolBtn, 9, 16, 16, 16, 16, sizeof(TBBUTTON));
		SendMessage(g_hToolBar, TB_ADDSTRING, NULL, (LPARAM)szString);
		Back = RGB(255, 0, 0);
		iMode = OPAQUE;


		return 0;

	case WM_SIZE:
		SendMessage(g_hToolBar, TB_AUTOSIZE, 0, 0);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 10:
			MessageBox(hwnd, TEXT("메세지 박스 알림"), TEXT("알림"), MB_OK);
			break;

		case 11:
			Back = RGB(255, 0, 0);
			InvalidateRect(hwnd, NULL, true);
			break;

		case 12:
			Back = RGB(0, 255, 0);
			InvalidateRect(hwnd, NULL, true);
			break;

		case 13:
			Back = RGB(0, 0, 255);
			InvalidateRect(hwnd, NULL, true);
			break;

		case 14:
			if (SendMessage(g_hToolBar, TB_ISBUTTONCHECKED, 14, 0)) iMode = TRANSPARENT;
			else													iMode = OPAQUE;
			break;
		}
		return 0;


	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code)
		{
		case TBN_DROPDOWN:
			HMENU hPopup;
			POINT pt;
			hPopup = CreatePopupMenu();
			AppendMenu(hPopup, MF_STRING, 0, TEXT("첫번째 팝업"));
			AppendMenu(hPopup, MF_STRING, 1, TEXT("두번째 팝업"));
			AppendMenu(hPopup, MF_STRING, 2, TEXT("세번째 팝업"));

			GetCursorPos(&pt);
			TrackPopupMenu(hPopup, TPM_LEFTALIGN, pt.x, pt.y, 0, hwnd, NULL);
			DestroyMenu(hPopup);

			return TBDDRET_DEFAULT;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &crt);
		hBrush = CreateSolidBrush(Back);
		FillRect(hdc, &crt, hBrush);
		DeleteObject(hBrush);
		SetBkMode(hdc, iMode);
		TextOut(hdc, 10, 50, Message, lstrlen(Message));
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		// WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






