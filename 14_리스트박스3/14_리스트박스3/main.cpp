#include <Windows.h>

#define IDC_LISTBOX 101
HWND g_hList;
COLORREF ColorTable[15] = { RGB(0,0,0), RGB(255,255,255), RGB(255,0,0), RGB(0,255,0), RGB(0,0,255),
							RGB(255,255,0), RGB(255,0,255), RGB(0,255,255), RGB(128,128,128), RGB(0,128,0),
							RGB(0,0,128), RGB(128,128,0), RGB(0,128,128), RGB(128,0,0), RGB(0,0,128) };

COLORREF SelColor = RGB(255, 255, 255);

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

// �ݹ��Լ� �Ű�����
// hwnd - �޼����� ���� ������ �ڵ鷯
// msg	- � ������ �޼������� Ȯ���� �� �ִ� ��
// wParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
// lParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
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

		// ���õ� ������ ����� ��ĥ
		FillRect(lpdis->hDC, &lpdis->rcItem, bkBrush);


		// ���� �� ���
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
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






