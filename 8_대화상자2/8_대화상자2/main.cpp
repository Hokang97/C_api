#include <Windows.h>
#include "resource.h"
// �Լ� ȣ�� ���
// __stdcall : �Ű������� ������ ������ �Լ�    / ũ�� �۴�  / callee (��ȣ����) stack ����
// __cdecl   : �Ű������� ������ �������� �Լ�  / ũ�� ũ��  / caller (ȣ����)   stack ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
bool bMale = false;
enum tag_Major { MANAGE, KOREAN ,ENGLLISH, LAW} Major;
const TCHAR *arMajor[] = { TEXT("�濵�а�"), TEXT("�����а�"),TEXT("�����а�"),TEXT("���а�") };

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



BOOL CALLBACK MajorDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParma)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		CheckDlgButton(hwnd, IDC_MALE, bMale ? BST_CHECKED : BST_UNCHECKED);
		CheckRadioButton(hwnd, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1 + Major);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_OK:
			bMale = (IsDlgButtonChecked(hwnd, IDC_MALE) == BST_CHECKED);
			if (IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_CHECKED)  Major = MANAGE;
			if (IsDlgButtonChecked(hwnd, IDC_RADIO2) == BST_CHECKED)  Major = KOREAN;
			if (IsDlgButtonChecked(hwnd, IDC_RADIO3) == BST_CHECKED)  Major = ENGLLISH;
			if (IsDlgButtonChecked(hwnd, IDC_RADIO4) == BST_CHECKED)  Major = LAW;
			EndDialog(hwnd, IDOK);

			return true;

		case IDC_BUTTON_CANCLE:
			EndDialog(hwnd, IDCANCEL);
			return true;
		}
	}
	return FALSE;
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
	TCHAR str[128];


	switch (msg)
	{
	case WM_CREATE:
		bMale = false;
		Major = MANAGE;
		return 0;


	case WM_LBUTTONDOWN:
		if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, MajorDlgProc) == IDOK)
		{
			InvalidateRect(hwnd, NULL, true);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		wsprintf(str, TEXT("���� = %s"), bMale ? TEXT("����") : TEXT("����"));
		TextOut(hdc, 10, 10, str, lstrlen(str));
		wsprintf(str, TEXT("���� = %s"), arMajor[Major]);
		TextOut(hdc, 10, 30, str, lstrlen(str));

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






