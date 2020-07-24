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

bool bCapture;
int Mx, My;
int xPos, yPos, xlnc, ylnc;
int xMax = 1000, yMax = 1000;

// �ݹ��Լ� �Ű�����
// hwnd - �޼����� ���� ������ �ڵ鷯
// msg	- � ������ �޼������� Ȯ���� �� �ִ� ��
// wParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
// lParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
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

			// y������
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
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






