#include <Windows.h>

#define IDC_BUTTON_1 101
#define IDC_BUTTON_2 102

#define IDC_CHECKBOX_BUTTON_1 103
#define IDC_CHECKBOX_BUTTON_2 104
#define IDC_CHECKBOX_BUTTON_3 105
#define IDC_CHECKBOX_BUTTON_4 106

#define ID_RADIO_GROUP_1 107
#define ID_RADIO_GROUP_2 108

#define IDC_RADIO_BUTTON_1 109
#define IDC_RADIO_BUTTON_2 110
#define IDC_RADIO_BUTTON_3 111
#define IDC_RADIO_BUTTON_4 112
#define IDC_RADIO_BUTTON_5 113
#define IDC_RADIO_BUTTON_6 114


// �Լ� ȣ�� ���
// __stdcall : �Ű������� ������ ������ �Լ�    / ũ�� �۴�  / callee (��ȣ����) stack ����
// __cdecl   : �Ű������� ������ �������� �Լ�  / ũ�� ũ��  / caller (ȣ����)   stack ����

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	g_hInst = hInstance;
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND r1, r2, r3, r4, r5, r6;
	static HWND c1, c2, c3, c4;
	static bool bEllipse = false;
	static int graph = 0;
	static COLORREF color = RGB(0, 0, 0);

	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("button1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)IDC_BUTTON_1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("button2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 100, 25, hWnd, (HMENU)IDC_BUTTON_2, g_hInst, NULL);
		
		//üũ�ڽ� ��ư �����

		c1 = CreateWindow(TEXT("button"), TEXT("���׸���"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 80, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_1, g_hInst, NULL);
		c2 = CreateWindow(TEXT("button"), TEXT("���� �޼��� Ȱ��ȭ"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 20, 110, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_2, g_hInst, NULL);
		c3 = CreateWindow(TEXT("button"), TEXT("3 State"), WS_CHILD | WS_VISIBLE | BS_3STATE, 20, 140, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_3, g_hInst, NULL);
		c4 = CreateWindow(TEXT("button"), TEXT("Auto 3 State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE, 20, 170, 160, 25, hWnd, (HMENU)IDC_CHECKBOX_BUTTON_4, g_hInst, NULL);


		// ���� �׷� �����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 200, 120, 110, hWnd, (HMENU)ID_RADIO_GROUP_1, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 200, 120, 110, hWnd, (HMENU)ID_RADIO_GROUP_2, g_hInst, NULL);

		// ���� ��ư �����
		r1 = CreateWindow(TEXT("button"), TEXT("�簢��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 10, 215, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 245, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 275, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_3, g_hInst, NULL);
		r4 = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 215, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_4, g_hInst, NULL);
		r5 = CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 245, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_5, g_hInst, NULL);
		r6 = CreateWindow(TEXT("button"), TEXT("�Ķ�"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 275, 100, 30, hWnd, (HMENU)IDC_RADIO_BUTTON_6, g_hInst, NULL);
		
		CheckRadioButton(hWnd, IDC_RADIO_BUTTON_1, IDC_RADIO_BUTTON_3, IDC_RADIO_BUTTON_1);
		CheckRadioButton(hWnd, IDC_RADIO_BUTTON_4, IDC_RADIO_BUTTON_6, IDC_RADIO_BUTTON_4);


		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_1 :
			MessageBox(hWnd, TEXT("1��ư Ŭ��"), TEXT("1��°"), MB_OK);
			break;

		case IDC_BUTTON_2:
			MessageBox(hWnd, TEXT("2��° Ŭ��"), TEXT("2��°"), MB_OK);
			break;

		case IDC_CHECKBOX_BUTTON_1:
			if (SendMessage(c1, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = true;
			}
			else
			{
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = false;
			}
			break;

		case IDC_CHECKBOX_BUTTON_3:
			if (SendMessage(c3, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
				SendMessage(c3, BM_SETCHECK, BST_CHECKED, 0);
			else if (SendMessageW(c3, BM_GETCHECK, 0, 0) == BST_INDETERMINATE)
				SendMessage(c3, BM_SETCHECK, BST_UNCHECKED, 0);
			else
				SendMessage(c3, BM_SETCHECK, BST_INDETERMINATE, 0);
			break;


		case IDC_RADIO_BUTTON_1: graph = 0; break;
		case IDC_RADIO_BUTTON_2: graph = 1; break;
		case IDC_RADIO_BUTTON_3: graph = 2; break;
		case IDC_RADIO_BUTTON_4: color = RGB(0,0,0); break;
		case IDC_RADIO_BUTTON_5: color = RGB(255, 0, 0); break;
		case IDC_RADIO_BUTTON_6: color = RGB(0, 0, 255); break;

			
		
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (bEllipse)	Ellipse(hdc, 200, 100, 400, 200);
		else			Rectangle(hdc, 200, 100, 400, 200);

		// ���� ��ư �̺�Ʈ ���� �׸���
		HBRUSH myBrush, oldBrush;
		myBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		
		switch (graph)
		{
		case 0: Rectangle(hdc, 300, 210, 500, 310);  break;
		case 1: Ellipse(hdc, 300, 210, 500, 310); break;
		case 2: MoveToEx(hdc, 300, 200, NULL); LineTo(hdc, 500, 310); break;

		}

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED)
			MessageBox(hWnd, TEXT("�ȳ���"), TEXT("�ȳ�"), MB_OK);
		// WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






