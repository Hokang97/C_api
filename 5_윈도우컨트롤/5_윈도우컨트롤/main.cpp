#include <Windows.h>

#define IDC_BUTTON_1 101
#define IDC_BUTTON_2 102

#define IDC_CHECKBOX_BUTTON_1 103
#define IDC_CHECKBOX_BUTTON_2 104
#define IDC_CHECKBOX_BUTTON_3 105
#define IDC_CHECKBOX_BUTTON_4 106

#define ID_RADIO_GROUP_1 107
#define ID_RADIO_GROUP_2 108

#define IDC_RADIO_BUTTON_1 109
#define IDC_RADIO_BUTTON_2 110
#define IDC_RADIO_BUTTON_3 111
#define IDC_RADIO_BUTTON_4 112
#define IDC_RADIO_BUTTON_5 113
#define IDC_RADIO_BUTTON_6 114


// 함수 호출 방법
// __stdcall : 매개변수의 개수가 고정된 함수    / 크기 작다  / callee (피호출자) stack 정리
// __cdecl   : 매개변수의 개수가 가변적인 함수  / 크기 크다  / caller (호출자)   stack 정리

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND r1, r2, r3, r4, r5, r6;
	static HWND c1, c2, c3, c4;
	static bool bEllipse = false;
	static int graph = 0;
	static COLORREF color = RGB(0, 0, 0);

	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("button1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)IDC_BUTTON_1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("button2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 100, 25, hWnd, (HMENU)IDC_BUTTON_2, g_hInst, NULL);
		
		//체크박스 버튼 만들기

		c1 = CreateWindow(TEXT("button"), TEXT("원그리기"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 80, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_1, g_hInst, NULL);
		c2 = CreateWindow(TEXT("button"), TEXT("종료 메세지 활성화"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 20, 110, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_2, g_hInst, NULL);
		c3 = CreateWindow(TEXT("button"), TEXT("3 State"), WS_CHILD | WS_VISIBLE | BS_3STATE, 20, 140, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_3, g_hInst, NULL);
		c4 = CreateWindow(TEXT("button"), TEXT("Auto 3 State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE, 20, 170, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_4, g_hInst, NULL);


		// 라디오 그룹 만들기
		CreateWindow(TEXT("button"), TEXT("도형"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 200, 120, 110, hWnd, (HMENU)ID_RADIO_GROUP_1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("색상"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 200, 120, 110, hWnd, (HMENU)ID_RADIO_GROUP_2, g_hInst, NULL);

		// 라디오 버튼 만들기
		r1 = CreateWindow(TEXT("button"), TEXT("사각형"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 10, 215, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("원"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 245, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("선"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 275, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_3, g_hInst, NULL);
		r4 = CreateWindow(TEXT("button"), TEXT("검정"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 215, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_4, g_hInst, NULL);
		r5 = CreateWindow(TEXT("button"), TEXT("빨강"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 245, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_5, g_hInst, NULL);
		r6 = CreateWindow(TEXT("button"), TEXT("파랑"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 275, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_6, g_hInst, NULL);
		
		CheckRadioButton(hWnd, IDC_RADIO_BUTTON_1, IDC_RADIO_BUTTON_3, IDC_RADIO_BUTTON_1);
		CheckRadioButton(hWnd, IDC_RADIO_BUTTON_4, IDC_RADIO_BUTTON_6, IDC_RADIO_BUTTON_4);


		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_1 :
			MessageBox(hWnd, TEXT("1버튼 클릭"), TEXT("1번째"), MB_OK);
			break;

		case IDC_BUTTON_2:
			MessageBox(hWnd, TEXT("2번째 클릭"), TEXT("2번째"), MB_OK);
			break;

		case IDC_CHECKBOX_BUTTON_1:
			if (SendMessage(c1, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = true;
			}
			else
			{
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = false;
			}
			break;

		case IDC_CHECKBOX_BUTTON_3:
			if (SendMessage(c3, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
				SendMessage(c3, BM_SETCHECK, BST_CHECKED, 0);
			else if (SendMessageW(c3, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)
				SendMessage(c3, BM_SETCHECK, BST_UNCHECKED, 0);
			else
				SendMessage(c3, BM_SETCHECK, BST_INDETERMINATE, 0);
			break;


		case IDC_RADIO_BUTTON_1: graph = 0; break;
		case IDC_RADIO_BUTTON_2: graph = 1; break;
		case IDC_RADIO_BUTTON_3: graph = 2; break;
		case IDC_RADIO_BUTTON_4: color = RGB(0,0,0); break;
		case IDC_RADIO_BUTTON_5: color = RGB(255, 0, 0); break;
		case IDC_RADIO_BUTTON_6: color = RGB(0, 0, 255); break;

			
		
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (bEllipse)	Ellipse(hdc, 200, 100, 400, 200);
		else			Rectangle(hdc, 200, 100, 400, 200);

		// 라디오 버튼 이벤트 도형 그리기
		HBRUSH myBrush, oldBrush;
		myBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		
		switch (graph)
		{
		case 0: Rectangle(hdc, 300, 210, 500, 310);  break;
		case 1: Ellipse(hdc, 300, 210, 500, 310); break;
		case 2: MoveToEx(hdc, 300, 200, NULL); LineTo(hdc, 500, 310); break;

		}

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED)
			MessageBox(hWnd, TEXT("안녕히"), TEXT("안녕"), MB_OK);
		// WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






