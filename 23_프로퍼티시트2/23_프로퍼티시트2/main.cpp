#include <Windows.h>
#include <CommCtrl.h>
#pragma comment (lib, "Comctl32.lib")
#include "resource.h"

HWND g_hTab;
HWND g_hStatic;
HIMAGELIST g_IL;
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
	TCITEM tie;
	const TCHAR* arNum[3] = { TEXT("ù��° ������"), TEXT("�ι�° ������"), TEXT("����° ������") };

	switch (msg)
	{
	case WM_CREATE:
		InitCommonControls();


		g_hTab = CreateWindow(WC_TABCONTROL, TEXT(""), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | TCS_FIXEDWIDTH | TCS_FORCEICONLEFT,
			0, 0, 0, 0, hwnd, (HMENU)0, g_hInst, NULL);
		g_hStatic = CreateWindow(TEXT("static"), arNum[0], WS_CHILD | WS_VISIBLE,
			0, 0, 0, 0, hwnd, (HMENU)1, g_hInst, NULL);

		TabCtrl_SetItemSize(g_hTab, 220, 22);

		g_IL = ImageList_LoadImage(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1), 16, 1, RGB(255, 255, 255), IMAGE_BITMAP, 0);

		TabCtrl_SetImageList(g_hTab, g_IL);

		tie.mask = TCIF_TEXT | TCIF_IMAGE;

		tie.pszText = (LPWSTR)TEXT("ù��° ��");
		tie.iImage = 0;
		TabCtrl_InsertItem(g_hTab, 0, &tie);

		tie.pszText = (LPWSTR)TEXT("�ι�° ��");
		tie.iImage = 1;
		TabCtrl_InsertItem(g_hTab, 1, &tie);

		tie.pszText = (LPWSTR)TEXT("����° ��");
		tie.iImage = 2;
		TabCtrl_InsertItem(g_hTab, 2, &tie);
		return 0;

	case WM_NOTIFY:
		switch ((((LPNMHDR)lParam)->code))
		{
		case TCN_SELCHANGE:
			SetWindowText(g_hStatic, arNum[TabCtrl_GetCurSel(g_hTab)]);
			break;
		}
		return 0;

	case WM_SIZE:
		MoveWindow(g_hTab, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		MoveWindow(g_hStatic, LOWORD(lParam) / 2 - 250, HIWORD(lParam) / 2, 500, 25, TRUE);
		return 0;

	case WM_DESTROY:
		// WM_QUIT �޼����� �߼�
		ImageList_Destroy(g_IL);
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






