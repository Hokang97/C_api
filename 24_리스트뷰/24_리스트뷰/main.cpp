#include <Windows.h>
#include <CommCtrl.h>
#pragma comment (lib, "ComCtl32.lib")
#include "resource.h"

HWND g_hList;
HIMAGELIST g_hImgSm, g_hImgLa;

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

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

void SetListViewStyle(HWND hList, DWORD dwView)
{
	DWORD dwStyle;
	dwStyle = GetWindowLong(hList, GWL_STYLE);
	if ((dwStyle & LVS_TYPEMASK) != dwView)
	{
		SetWindowLong(hList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
	}
}


// �ݹ��Լ� �Ű�����
// hwnd - �޼����� ���� ������ �ڵ鷯
// msg	- � ������ �޼������� Ȯ���� �� �ִ� ��
// wParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
// lParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LVCOLUMN COL;
	LVITEM LI;

	switch (msg)
	{
	case WM_CREATE:
		InitCommonControls();
		g_hList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
			10, 10, 500, 200, hwnd, NULL, g_hInst, NULL);
		
		// �̹��� ����Ʈ �߰�
		g_hImgSm = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1), 16, 1, RGB(255, 255, 255));
		g_hImgLa = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 32, 1, RGB(255, 255, 255));

		SendMessage(g_hList, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)g_hImgSm);
		SendMessage(g_hList, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)g_hImgLa);

		//����� �߰��մϴ�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("�̸�");
		COL.iSubItem = 0;
		SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

		COL.pszText = (LPWSTR)TEXT("��ȭ��ȣ");
		COL.iSubItem = 1;
		SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

		COL.pszText = (LPWSTR)TEXT("�ּ�");
		COL.iSubItem = 2;
		COL.cx = 300;
		SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

		// ù��° ������
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iImage = 0;
		LI.iSubItem = 0;
		LI.iItem = 0;
		LI.pszText = (LPWSTR)TEXT("������");
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iImage = -1;
		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)TEXT("123-2424");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = (LPWSTR)TEXT("����� ������");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		// �ι�° ������
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iImage = 1;
		LI.iSubItem = 0;
		LI.iItem = 1;
		LI.pszText = (LPWSTR)TEXT("�����");
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iImage = -1;
		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)TEXT("456-2424");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = (LPWSTR)TEXT("����� âõ��");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		// ����° ������
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iImage = 1;
		LI.iSubItem = 0;
		LI.iItem = 2;
		LI.pszText = (LPWSTR)TEXT("ȣ����");
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iImage = -1;
		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)TEXT("789-2424");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = (LPWSTR)TEXT("����� �漮��");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ICON:
			SetListViewStyle(g_hList, LVS_ICON);
			break;

		case ID_SMALLICON:
			SetListViewStyle(g_hList, LVS_SMALLICON);
			break;
			
		case ID_LIST:
			SetListViewStyle(g_hList, LVS_LIST);
			break;

		case ID_REPORT:
			SetListViewStyle(g_hList, LVS_REPORT);
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






