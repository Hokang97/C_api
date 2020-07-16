#include <Windows.h>
#include "resource.h"
// �Լ� ȣ�� ���
// __stdcall : �Ű������� ������ ������ �Լ�    / ũ�� �۴�  / callee (��ȣ����) stack ����
// __cdecl   : �Ű������� ������ �������� �Լ�  / ũ�� ũ��  / caller (ȣ����)   stack ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ���̾�α� ���
HINSTANCE g_hInst;
int x, y;
TCHAR str[128];


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASS WndClass;

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

BOOL CALLBACK InfoDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hwnd, IDC_EDIT_STR, str);
		SetDlgItemInt(hwnd, IDC_EDIT_X, x, false);
		SetDlgItemInt(hwnd, IDC_EDIT_Y, y, false);

		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_OK:
			GetDlgItemText(hwnd, IDC_EDIT_STR, str, 128);
			x = GetDlgItemInt(hwnd, IDC_EDIT_X, NULL, true);
			y = GetDlgItemInt(hwnd, IDC_EDIT_Y, NULL, true);
			EndDialog(hwnd, IDOK);
			break;

		case IDC_BUTTON_CANCLE:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		return true;
	}

	return false;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;



	switch (msg)
	{
	case WM_CREATE:
		x = 100;
		y = 100;
		lstrcpy(str, TEXT("���ڿ��� �Է����ּ���"));
		break;

	case WM_LBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, InfoDlgProc) == IDOK)
		{
			InvalidateRect(hwnd, NULL, true);
		}

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, x, y, str, lstrlen(str));
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






