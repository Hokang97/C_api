#include <Windows.h>

// �Լ� ȣ�� ���
// __stdcall : �Ű������� ������ ������ �Լ�    / ũ�� �۴�  / callee (��ȣ����) stack ����
// __cdecl   : �Ű������� ������ �������� �Լ�  / ũ�� ũ��  / caller (ȣ����)   stack ����

// �����
#define IDC_EDIT 101
HWND g_hEdit;

// ����Ʈ
#define IDC_LISTBOX 102
const TCHAR* Items[] = { TEXT("apple"), TEXT("orange"), TEXT("melon"), TEXT("graph"),TEXT("strawberry") };
HWND g_hList;

// �޺��ڽ�
#define IDC_COMBOBOX 103
HWND g_hCombo;

// ��ũ�ѹ�
#define IDC_SCRRED 104
#define IDC_SCRGREEN 105
#define IDC_SCRBLUE 106
HWND g_hRed;
HWND g_hGreen;
HWND g_hBlue;
int iREd, iGreen, iBlue;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;

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
	TCHAR str[128];
	
	int i;
	TCHAR strList[128];

	// ��ũ�ѹ� ����
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH myBrush, oldBrush;
	int tempPos;

	switch (msg)
	{
	case WM_CREATE:
		//����Ʈ ����
		g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25, hWnd, (HMENU)IDC_EDIT, g_hInst, NULL);
		
		//����Ʈ �ڽ� ����
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			10, 40, 100, 200, hWnd, (HMENU)IDC_LISTBOX, g_hInst, NULL);

		
		// �޺��ڽ� ����
		g_hCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN,
			120, 40, 100, 200, hWnd, (HMENU)IDC_COMBOBOX, g_hInst, NULL);
		
		
		// ����Ʈ, �޺��ڽ� ������ �߰�
		for (int i = 0; i < 5; i++)
		{
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
			SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}

		g_hRed = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			70, 250, 400, 20, hWnd, (HMENU)IDC_SCRRED, g_hInst, NULL);
		g_hGreen = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			70, 280, 400, 20, hWnd, (HMENU)IDC_SCRGREEN, g_hInst, NULL);
		g_hBlue = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			70, 310, 400, 20, hWnd, (HMENU)IDC_SCRBLUE, g_hInst, NULL);

		// ��ũ�ѹ� ���� ���� �� ���� ��ġ ����
		// SB_HORZ / SB_VERT / SB_CTL / SB_BOTH - ��ũ�ѹ� ����
		SetScrollRange(g_hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hRed, SB_CTL, 0, true);

		SetScrollRange(g_hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hGreen, SB_CTL, 0, true);

		SetScrollRange(g_hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hBlue, SB_CTL, 0, true);

		// ����ƽ ��Ʈ�� ����
		CreateWindow(TEXT("static"), TEXT("Red"), WS_CHILD | WS_VISIBLE, 10, 250, 50, 25, hWnd, (HMENU)-1, g_hInst, NULL);
		CreateWindow(TEXT("static"), TEXT("Green"), WS_CHILD | WS_VISIBLE, 10, 280, 50, 25, hWnd, (HMENU)-1, g_hInst, NULL);
		CreateWindow(TEXT("static"), TEXT("Blue"), WS_CHILD | WS_VISIBLE, 10, 310, 50, 25, hWnd, (HMENU)-1, g_hInst, NULL);


		return 0;


	case WM_COMMAND :
		switch (LOWORD(wParam))
		{
		case IDC_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(g_hEdit, str, 128);
				SetWindowText(hWnd, str);
				break;
			}
			break;

			//����Ʈ �̺�Ʈó��
		case IDC_LISTBOX:
			switch (HIWORD(wParam))
			{
				//����ڿ� ���� ���õ� �׸��� ����Ǿ��� ��
			case LBN_SELCHANGE:
				i = SendMessage(g_hList, LB_GETCURSEL, 0, 0);
				SendMessageW(g_hList, LB_GETTEXT, i, (LPARAM)strList); // �ؽ�Ʈ�� ������ strList�ȿ� �Է�
				SetWindowText(hWnd, strList);
				break;
			}

		case IDC_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				i = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
				SendMessageW(g_hCombo, CB_GETLBTEXT, i, (LPARAM)strList); // �ؽ�Ʈ�� ������ strList�ȿ� �Է�
				SetWindowText(hWnd, strList);
				break;

			case CBN_EDITCHANGE:
				GetWindowText(g_hCombo, strList, 128);
				SetWindowText(hWnd, strList);
				break;
			}
			break;
		}

		return 0;

	case WM_HSCROLL:
		if ((HWND)lParam == g_hRed)		tempPos = iREd;
		if ((HWND)lParam == g_hGreen)	tempPos = iGreen;
		if ((HWND)lParam == g_hBlue)	tempPos = iBlue;

		// �̺�Ʈ ó��
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			tempPos = max(0, tempPos - 1);
			break;

		case SB_LINERIGHT:
			tempPos = min(255, tempPos + 1);
			break;

		case SB_PAGELEFT:
			tempPos = max(0, tempPos - 10);
			break;

		case SB_PAGERIGHT:
			tempPos = min(255, tempPos + 10);
			break;

		case SB_THUMBTRACK:
			tempPos = HIWORD(wParam);
			break;
		}


		if ((HWND)lParam == g_hRed)		iREd	= tempPos;
		if ((HWND)lParam == g_hGreen)	iGreen	= tempPos;
		if ((HWND)lParam == g_hBlue)	iBlue	= tempPos;
		SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);
		InvalidateRect(hWnd, NULL, FALSE);

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		myBrush = CreateSolidBrush(RGB(iREd, iGreen, iBlue));
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, 70, 340, 470, 540);
		DeleteObject(SelectObject(hdc, oldBrush));

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






