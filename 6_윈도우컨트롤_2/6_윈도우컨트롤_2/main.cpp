#include <Windows.h>

// 함수 호출 방법
// __stdcall : 매개변수의 개수가 고정된 함수    / 크기 작다  / callee (피호출자) stack 정리
// __cdecl   : 매개변수의 개수가 가변적인 함수  / 크기 크다  / caller (호출자)   stack 정리

// 에디드
#define IDC_EDIT 101
HWND g_hEdit;

// 리스트
#define IDC_LISTBOX 102
const TCHAR* Items[] = { TEXT("apple"), TEXT("orange"), TEXT("melon"), TEXT("graph"),TEXT("strawberry") };
HWND g_hList;

// 콤보박스
#define IDC_COMBOBOX 103
HWND g_hCombo;

// 스크롤바
#define IDC_SCRRED 104
#define IDC_SCRGREEN 105
#define IDC_SCRBLUE 106
HWND g_hRed;
HWND g_hGreen;
HWND g_hBlue;
int iREd, iGreen, iBlue;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	g_hInst = hInstance;
	HWND hWnd;
	MSG Msg;
	WNDCLASS WndClass;

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
	TCHAR str[128];
	
	int i;
	TCHAR strList[128];

	// 스크롤바 변수
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH myBrush, oldBrush;
	int tempPos;

	switch (msg)
	{
	case WM_CREATE:
		//에디트 생성
		g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25, hWnd, (HMENU)IDC_EDIT, g_hInst, NULL);
		
		//리스트 박스 생성
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			10, 40, 100, 200, hWnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);

		
		// 콤보박스 생성
		g_hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN,
			120, 40, 100, 200, hWnd, (HMENU)IDC_COMBOBOX, g_hInst, NULL);
		
		
		// 리스트, 콤보박스 아이템 추가
		for (int i = 0; i < 5; i++)
		{
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
			SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}

		g_hRed = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			70, 250, 400, 20, hWnd, (HMENU)IDC_SCRRED, g_hInst, NULL);
		g_hGreen = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			70, 280, 400, 20, hWnd, (HMENU)IDC_SCRGREEN, g_hInst, NULL);
		g_hBlue = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			70, 310, 400, 20, hWnd, (HMENU)IDC_SCRBLUE, g_hInst, NULL);

		// 스크롤바 범위 설정 및 최초 위치 설정
		// SB_HORZ / SB_VERT / SB_CTL / SB_BOTH - 스크롤바 형태
		SetScrollRange(g_hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hRed, SB_CTL, 0, true);

		SetScrollRange(g_hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hGreen, SB_CTL, 0, true);

		SetScrollRange(g_hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hBlue, SB_CTL, 0, true);

		// 스태틱 컨트롤 생성
		CreateWindow(TEXT("static"), TEXT("Red"), WS_CHILD | WS_VISIBLE, 10, 250, 50, 25, hWnd, (HMENU)-1, g_hInst, NULL);
		CreateWindow(TEXT("static"), TEXT("Green"), WS_CHILD | WS_VISIBLE, 10, 280, 50, 25, hWnd, (HMENU)-1, g_hInst, NULL);
		CreateWindow(TEXT("static"), TEXT("Blue"), WS_CHILD | WS_VISIBLE, 10, 310, 50, 25, hWnd, (HMENU)-1, g_hInst, NULL);


		return 0;


	case WM_COMMAND :
		switch (LOWORD(wParam))
		{
		case IDC_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(g_hEdit, str, 128);
				SetWindowText(hWnd, str);
				break;
			}
			break;

			//리스트 이벤트처리
		case IDC_LISTBOX:
			switch (HIWORD(wParam))
			{
				//사용자에 의해 선택된 항목이 변경되었을 때
			case LBN_SELCHANGE:
				i = SendMessage(g_hList, LB_GETCURSEL, 0, 0);
				SendMessageW(g_hList, LB_GETTEXT, i, (LPARAM)strList); // 텍스트를 가져와 strList안에 입력
				SetWindowText(hWnd, strList);
				break;
			}

		case IDC_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				i = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
				SendMessageW(g_hCombo, CB_GETLBTEXT, i, (LPARAM)strList); // 텍스트를 가져와 strList안에 입력
				SetWindowText(hWnd, strList);
				break;

			case CBN_EDITCHANGE:
				GetWindowText(g_hCombo, strList, 128);
				SetWindowText(hWnd, strList);
				break;
			}
			break;
		}

		return 0;

	case WM_HSCROLL:
		if ((HWND)lParam == g_hRed)		tempPos = iREd;
		if ((HWND)lParam == g_hGreen)	tempPos = iGreen;
		if ((HWND)lParam == g_hBlue)	tempPos = iBlue;

		// 이벤트 처리
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			tempPos = max(0, tempPos - 1);
			break;

		case SB_LINERIGHT:
			tempPos = min(255, tempPos + 1);
			break;

		case SB_PAGELEFT:
			tempPos = max(0, tempPos - 10);
			break;

		case SB_PAGERIGHT:
			tempPos = min(255, tempPos + 10);
			break;

		case SB_THUMBTRACK:
			tempPos = HIWORD(wParam);
			break;
		}


		if ((HWND)lParam == g_hRed)		iREd	= tempPos;
		if ((HWND)lParam == g_hGreen)	iGreen	= tempPos;
		if ((HWND)lParam == g_hBlue)	iBlue	= tempPos;
		SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);
		InvalidateRect(hWnd, NULL, FALSE);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		myBrush = CreateSolidBrush(RGB(iREd, iGreen, iBlue));
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, 70, 340, 470, 540);
		DeleteObject(SelectObject(hdc, oldBrush));

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






