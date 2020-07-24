#include <Windows.h>

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

bool bCapture;
int Mx, My;
int xPos, yPos, xlnc, ylnc;
int xMax = 1000, yMax = 1000;

// 콜백함수 매개변수
// hwnd - 메세지를 받을 윈도우 핸들러
// msg	- 어떤 종류의 메세지인지 확일할 수 있는 값
// wParam	- 메세지의 부가 정보 (메세지에 따라 다름)
// lParam	- 메세지의 부가 정보 (메세지에 따라 다름)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	

	switch (msg)
	{
	case WM_CREATE:
		SetScrollRange(hwnd, SB_HORZ, 0, 1000, true);
		SetScrollPos(hwnd, SB_HORZ, 1000, true);

		SetScrollRange(hwnd, SB_VERT, 0, 1000, true);
		SetScrollPos(hwnd, SB_VERT, 1000, true);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Ellipse(hdc, 0 + xPos, 0 + yPos, 100 + xPos, 100 + yPos);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		Mx = LOWORD(lParam);
		My = HIWORD(lParam);
		bCapture = true;
		SetCapture(hwnd);
		return 0;

	case WM_MOUSEMOVE:
		if (bCapture)
		{
			int Nx, Ny;
			Nx = (int)LOWORD(lParam);
			Ny = (int)HIWORD(lParam);

			// y증가값
			ylnc = My - Ny;
			if (yPos + ylnc < 0) ylnc = -yPos;
			if (yPos + ylnc > yMax) ylnc = yMax - yPos;
			yPos = yPos + ylnc;

			xlnc = Mx - Nx;
			if (xPos + xlnc < 0) xlnc = -xPos;
			if (xPos + xlnc > xMax) xlnc = xMax - xPos;
			xPos = xPos + xlnc;

			My = Ny;
			Mx = Nx;
			SetScrollPos(hwnd, SB_HORZ, 1000 - xPos, true);
			SetScrollPos(hwnd, SB_VERT, 1000 -yPos, true);
			InvalidateRect(hwnd, NULL, true);
		}
		return 0;

	case WM_LBUTTONUP:
		bCapture = false;
		ReleaseCapture();
		return 0;

	case WM_DESTROY:
		// WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






