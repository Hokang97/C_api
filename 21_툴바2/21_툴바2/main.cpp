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
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT crt;
	HBRUSH hBrush;

	const TCHAR* Message = TEXT("�׽�Ʈ ���ڿ��Դϴ�.");
	const TCHAR* szString = TEXT("��ɹ�ư\0������\0�ʷϻ�\0�Ķ���\0����\0&Drop\0&Drop2\0");

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
			MessageBox(hwnd, TEXT("�޼��� �ڽ� �˸�"), TEXT("�˸�"), MB_OK);
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
			AppendMenu(hPopup, MF_STRING, 0, TEXT("ù��° �˾�"));
			AppendMenu(hPopup, MF_STRING, 1, TEXT("�ι�° �˾�"));
			AppendMenu(hPopup, MF_STRING, 2, TEXT("����° �˾�"));

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
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






