#include <Windows.h>
#include<stdio.h>
#include "resource.h"
#pragma warning(disable : 4996)
#define IDC_EDIT_TEXT 110
HWND g_hEdit;
// �Լ� ȣ�� ���
// __stdcall : �Ű������� ������ ������ �Լ�    / ũ�� �۴�  / callee (��ȣ����) stack ����
// __cdecl   : �Ű������� ������ �������� �Լ�  / ũ�� ũ��  / caller (ȣ����)   stack ����

HCURSOR g_hCur1, g_hCur2, g_hCur3, g_hNow;

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

	HACCEL hAccel = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Msg)) {

			TranslateMessage(&Msg);		// Ű���� �Է� �޼����� ���α׷����� ����� �� �ֵ��� ����
			DispatchMessage(&Msg);		// �޼��� ť���� ���� �޼����� ���ν����� ����
		}
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
	TCHAR title[128];
	
	FILE* fp;
	TCHAR str[128];
	switch (msg)
	{
	case WM_CREATE:
		LoadString(g_hInst, IDS_GAME_TITLE, title, 128);	// ���ڿ� �ҷ�����
		SetWindowText(hwnd, title);		// ���ڿ� Ÿ��Ʋ ����

		g_hCur1 = LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_CURSOR1));
		g_hCur2 = LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_CURSOR2));
		g_hCur3 = LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_CURSOR3));

		g_hNow = g_hCur1;

		g_hEdit = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 220, 25, hwnd, (HMENU)IDC_EDIT_TEXT, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("�ҷ�����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 40, 100, 25, hwnd, (HMENU)0, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("�����ϱ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			120, 40, 100, 25, hwnd, (HMENU)1, g_hInst, NULL);
		return 0;

	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(g_hNow);
		}
		return 0;

	case WM_LBUTTONDOWN:
		if (g_hNow == g_hCur1) g_hNow = g_hCur2;
		else if (g_hNow == g_hCur2) g_hNow = g_hCur3;
		else g_hNow = g_hCur1;
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			fp = fopen("output.txt", "rt");
			fwscanf(fp, TEXT("%s%"), str);
			SetDlgItemText(hwnd, IDC_EDIT_TEXT, str);
			fclose(fp);
			MessageBox(hwnd, TEXT("�ؽ�Ʈ�� �ҷ���"), TEXT("�˸�"), MB_OK);

			break;

		case 1:
			fp = fopen("output.txt", "wt");
			GetDlgItemText(hwnd, IDC_EDIT_TEXT, str, 128);
			fwprintf(fp, TEXT("%s"), str);
			fclose(fp);
			MessageBox(hwnd, TEXT("�ؽ�Ʈ�� �����߽��ϴ�"), TEXT("�˸�"), MB_OK);
			break;


		case IDR_COPY:
			MessageBox(hwnd, TEXT("����"), TEXT("�˸�"), MB_OK);
			break;

		case IDR_CUT:

			MessageBox(hwnd, TEXT("����"), TEXT("�˸�"), MB_OK);
			break;

		case IDR_PASTE:

			MessageBox(hwnd, TEXT("�ٿ��ֱ�"), TEXT("�˸�"), MB_OK);
			break;

		case IDR_UNDO:

			MessageBox(hwnd, TEXT("�ǵ�����"), TEXT("�˸�"), MB_OK);
			break;
		}
		return 0;

	case WM_DESTROY:
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






