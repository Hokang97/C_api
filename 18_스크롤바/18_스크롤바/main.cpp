#include <Windows.h>

// �Լ� ȣ�� ���
// __stdcall : �Ű������� ������ ������ �Լ�    / ũ�� �۴�  / callee (��ȣ����) stack ����
// __cdecl   : �Ű������� ������ �������� �Լ�  / ũ�� ũ��  / caller (ȣ����)   stack ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	// 1. ������ Ŭ���� ����/�ʱ�ȭ
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbClsExtra = 0;	// Ư���� �������� ���� ���� ����
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;		// ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ
	WndClass.lpfnWndProc = WndProc;		// ���ν��� ����
	WndClass.lpszClassName = TEXT("WndClass");
	WndClass.lpszMenuName = NULL;

	// 2. ������ Ŭ���� ���
	RegisterClass(&WndClass);

	// 3. ������ â ����
	hWnd = CreateWindow(WndClass.lpszClassName, TEXT("������Ÿ��Ʋ"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 640, NULL, NULL, hInstance, NULL);


	// 4. ������ â Ȱ��ȭ/ǥ��
	ShowWindow(hWnd, SW_SHOW);

	// 5. �޼��� ����/ó��
	// GetMessage()
	// PeekMessage()


	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);		// Ű���� �Է� �޼����� ���α׷����� ����� �� �ֵ��� ����
		DispatchMessage(&Msg);		// �޼��� ť���� ���� �޼����� ���ν����� ����
	}

	return (int)Msg.wParam;





}

int yPos;

// �ݹ��Լ� �Ű�����
// hwnd - �޼����� ���� ������ �ڵ鷯
// msg	- � ������ �޼������� Ȯ���� �� �ִ� ��
// wParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
// lParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[128];
	int ylnc, i;

	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("��ư1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hwnd, (HMENU)0, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("��ư2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 50, 100, 25, hwnd, (HMENU)1, g_hInst, NULL);

		SetScrollRange(hwnd, SB_VERT, 0, 2000, TRUE);
		SetScrollPos(hwnd, SB_VERT, 0, TRUE);
		return 0;

	case WM_VSCROLL:
		ylnc = 0;
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			ylnc = -20;
			break;

		case SB_LINEDOWN:
			ylnc += 20;

			break;

		case SB_PAGEUP:
			ylnc = -200;

			break;

		case SB_PAGEDOWN:
			ylnc += 200;

			break;

		case SB_THUMBTRACK:
			ylnc = HIWORD(wParam) - yPos;

			break;
		}

		if (yPos + ylnc < 0)
			ylnc = -yPos;

		if (yPos + ylnc > 2000)
			ylnc = 2000 - yPos;

		yPos = yPos + ylnc;
		ScrollWindow(hwnd, 0, -ylnc, NULL, NULL);
		SetScrollPos(hwnd, SB_VERT, yPos, true);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Ellipse(hdc, 250, 50 - yPos, 450, 250 - yPos);
		for (int i = 0; i < 100; i++)
		{
			wsprintf(str, TEXT("DATA : %d"), i);
			TextOut(hdc, 150, i * 20 - yPos, str, lstrlen(str));
		}

		EndPaint(hwnd, &ps);
		return 0;


	case WM_DESTROY:
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






