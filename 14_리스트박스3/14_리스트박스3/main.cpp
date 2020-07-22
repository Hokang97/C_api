#include <Windows.h>

#define IDC_LISTBOX 101
HWND g_hList;
COLORREF ColorTable[15] = { RGB(0,0,0), RGB(255,255,255), RGB(255,0,0), RGB(0,255,0), RGB(0,0,255),
							RGB(255,255,0), RGB(255,0,255), RGB(0,255,255), RGB(128,128,128), RGB(0,128,0),
							RGB(0,0,128), RGB(128,128,0), RGB(0,128,128), RGB(128,0,0), RGB(0,0,128) };

COLORREF SelColor = RGB(255, 255, 255);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LPMEASUREITEMSTRUCT lpmis;
	LPDRAWITEMSTRUCT lpdis;
	HBRUSH bkBrush, ColorBrush, OldBrush;
	COLORREF color;
	int i, index;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
		// LBS_OWNERDRAWFIXED
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_NOTIFY | LBS_OWNERDRAWFIXED,
			10, 10, 150, 200, hWnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);

		for (int i = 0; i < 15; i++)
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)ColorTable[i]);

		return 0;

	case WM_MEASUREITEM:
		lpmis = (LPMEASUREITEMSTRUCT)lParam;
		lpmis->itemHeight = 24;

		return 0;

	case WM_DRAWITEM:
		lpdis = (LPDRAWITEMSTRUCT)lParam;

		if (lpdis->itemState && ODS_SELECTED)
		{
			bkBrush = GetSysColorBrush(COLOR_HIGHLIGHT);
		}
		else
		{
			bkBrush = GetSysColorBrush(COLOR_WINDOW);
		}

		// 선택된 아이템 배경을 색칠
		FillRect(lpdis->hDC, &lpdis->rcItem, bkBrush);


		// 색상 바 출력
		color = (COLORREF)lpdis->itemData;
		ColorBrush = CreateSolidBrush(color);
		OldBrush = (HBRUSH)SelectObject(lpdis->hDC, ColorBrush);
		Rectangle(lpdis->hDC, lpdis->rcItem.left + 5, lpdis->rcItem.top + 2, lpdis->rcItem.right + 5, lpdis->rcItem.bottom - 5);
		
		DeleteObject(SelectObject(lpdis->hDC, OldBrush));

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LISTBOX:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				index = SendMessage(g_hList, LB_GETCURSEL, 0, 0);
				SelColor = (COLORREF)SendMessage(g_hList, LB_GETITEMDATA, index, 0);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		ColorBrush = CreateSolidBrush(SelColor);
		OldBrush = (HBRUSH)SelectObject(hdc, ColorBrush);
		Rectangle(hdc, 200, 10, 400, 200);
		DeleteObject(SelectObject(hdc, OldBrush));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		// WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






