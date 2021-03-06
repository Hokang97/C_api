#include <Windows.h>

#define IDC_LISTBOX 101
#define IDC_BTNRESET 102
#define IDC_BTNDELETE 103

HWND g_hList, g_hBtnReset, g_hBtnDelete;
const TCHAR* data[] = { TEXT("데이터1"),TEXT("데이터2"),TEXT("데이터3"),TEXT("데이터4"),TEXT("데이터5"),TEXT("데이터6")
,TEXT("데이터7"),TEXT("데이터8"),TEXT("데이터9"),TEXT("데이터10")};

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
	

	switch (msg)
	{
	case WM_CREATE:
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_MULTIPLESEL | LBS_NOTIFY,
			10, 10, 200, 300, hWnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);

		g_hBtnReset = CreateWindow(TEXT("button"), TEXT("아이템 초기화"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 50, 120, 25, hWnd, (HMENU)IDC_BTNRESET, g_hInst, NULL);

		g_hBtnDelete = CreateWindow(TEXT("button"), TEXT("아이템 지우기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 80, 120, 25, hWnd, (HMENU)IDC_BTNDELETE, g_hInst, NULL);
		
		for (int i = 0; i < 10; i++)
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)data[i]);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTNRESET:
			SendMessage(g_hList, LB_RESETCONTENT, 0, 0);
			for (int i = 0; i < 10; i++)
				SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)data[i]);
			break;


		case IDC_BTNDELETE:
		{
			int num = SendMessage(g_hList, LB_GETSELCOUNT, 0, 0);
			if (num != 0)
			{
				int buffer[100];
				SendMessage(g_hList, LB_GETSELITEMS, 100, (LPARAM)buffer);

				for (int i = num - 1; i >= 0; i--)
					SendMessage(g_hList, LB_DELETESTRING, buffer[i], 0);
			}
		}
			break;
		}
		return 0;

	case WM_DESTROY:
		// WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






