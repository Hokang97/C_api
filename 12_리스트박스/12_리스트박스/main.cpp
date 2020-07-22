#include <Windows.h>

#define IDC_LISTBOX 101
#define IDC_EDIT 102
#define IDC_BTNADD 103
#define IDC_BTNDELETE 104

HWND g_hList, g_hEdit, g_hBtnAdd, g_hBtnDelete;

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
	int index;
	TCHAR str[128];

	switch (msg)
	{
	case WM_CREATE:
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_SORT | LBS_NOTIFY,
			10, 10, 100, 200, hWnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);

		g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 10, 120, 25, hWnd, (HMENU)IDC_EDIT, g_hInst, NULL);

		g_hBtnAdd = CreateWindow(TEXT("button"), TEXT("������ �߰�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			120, 50, 120, 25, hWnd, (HMENU)IDC_BTNADD, g_hInst, NULL);

		g_hBtnDelete = CreateWindow(TEXT("button"), TEXT("������ ����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			120, 80, 120, 25, hWnd, (HMENU)IDC_BTNDELETE, g_hInst, NULL);


		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTNADD:
			SendMessage(g_hEdit, WM_GETTEXT, (WPARAM)128, (LPARAM)str);
			if (lstrlen(str))
			{
				SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)str);
			}
			else
			{
				MessageBox(hWnd, TEXT("���ڿ��� �Է����ּ���"), TEXT("����"), MB_OK);
			}
			break;

		case IDC_BTNDELETE:
			index = SendMessage(g_hList, LB_GETCURSEL, 0, 0);
			if (index == LB_ERR)
			{
				MessageBox(hWnd, TEXT("�����׸� ����"), TEXT("����"), MB_OK);
			}
			else
			{
				SendMessage(g_hList, LB_DELETESTRING, (WPARAM)index, 0);
			}
			break;
		}


		return 0;

	case WM_DESTROY:
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






