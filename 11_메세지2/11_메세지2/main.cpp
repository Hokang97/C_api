#include <Windows.h>

#define ID_EDIT1 101
#define ID_EDIT2 102
HWND g_hEidt1, g_hEdit2;
WNDPROC OldEditSubProc, OldEditSuperProc;

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

LRESULT CALLBACK EditSuperProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		MessageBeep(0);
		return 0;
	}

	return CallWindowProc(OldEditSuperProc, hwnd, msg, wParam, lParam);
}


LRESULT CALLBACK EditSubProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			MessageBox(hwnd, TEXT("����Ű�� ����"), TEXT("�˸�"), MB_OK);
			SetFocus(hwnd);
			
		}
		return 0;
	}

	return CallWindowProc(OldEditSubProc, hwnd, msg, wParam, lParam);
}

// �ݹ��Լ� �Ű�����
// hwnd - �޼����� ���� ������ �ڵ鷯
// msg	- � ������ �޼������� Ȯ���� �� �ִ� ��
// wParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
// lParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WNDCLASS SuperWndClass;

	switch (msg)
	{
	case WM_CREATE:
		g_hEidt1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25, hWnd, (HMENU)ID_EDIT1, g_hInst, NULL);

		//����Ŭ����
		GetClassInfo(NULL, TEXT("edit"), &SuperWndClass);
		SuperWndClass.hInstance = g_hInst;
		SuperWndClass.lpszClassName = TEXT("SuperEdit");
		SuperWndClass.hCursor = LoadCursor(NULL, IDC_WAIT);
		
		// ���ν��� ����
		OldEditSuperProc = SuperWndClass.lpfnWndProc;
		SuperWndClass.lpfnWndProc = EditSuperProc;

		// Ŭ���� ���
		RegisterClass(&SuperWndClass);

		g_hEdit2 = CreateWindow(TEXT("SuperEdit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 50, 200, 25, hWnd, (HMENU)ID_EDIT2, g_hInst, NULL);
		

		// ���� Ŭ����
		SetFocus(g_hEidt1);
		OldEditSubProc = (WNDPROC)SetWindowLongPtr(g_hEidt1, GWLP_WNDPROC, (LONG_PTR)EditSubProc);
		

		return 0;


	case WM_DESTROY:
		// WM_QUIT �޼����� �߼�
		SetWindowLongPtr(g_hEidt1, GWLP_WNDPROC, (LONG_PTR)OldEditSubProc);
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hWnd, msg, wParam, lParam);

}






