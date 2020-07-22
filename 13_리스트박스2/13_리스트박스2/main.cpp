#include <Windows.h>

#define IDC_LISTBOX 101
#define IDC_BTNRESET 102
#define IDC_BTNDELETE 103

HWND g_hList, g_hBtnReset, g_hBtnDelete;
const TCHAR* data[] = { TEXT("������1"),TEXT("������2"),TEXT("������3"),TEXT("������4"),TEXT("������5"),TEXT("������6")
,TEXT("������7"),TEXT("������8"),TEXT("������9"),TEXT("������10")};

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
	

	switch (msg)
	{
	case WM_CREATE:
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_MULTIPLESEL | LBS_NOTIFY,
			10, 10, 200, 300, hWnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);

		g_hBtnReset = CreateWindow(TEXT("button"), TEXT("������ �ʱ�ȭ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 50, 120, 25, hWnd, (HMENU)IDC_BTNRESET, g_hInst, NULL);

		g_hBtnDelete = CreateWindow(TEXT("button"), TEXT("������ �����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 80, 120, 25, hWnd, (HMENU)IDC_BTNDELETE, g_hInst, NULL);
		
		for (int i = 0; i < 10; i++)
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)data[i]);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTNRESET:
			SendMessage(g_hList, LB_RESETCONTENT, 0, 0);
			for (int i = 0; i < 10; i++)
				SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)data[i]);
			break;


		case IDC_BTNDELETE:
		{
			int num = SendMessage(g_hList, LB_GETSELCOUNT, 0, 0);
			if (num != 0)
			{
				int buffer[100];
				SendMessage(g_hList, LB_GETSELITEMS, 100, (LPARAM)buffer);

				for (int i = num - 1; i >= 0; i--)
					SendMessage(g_hList, LB_DELETESTRING, buffer[i], 0);
			}
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






