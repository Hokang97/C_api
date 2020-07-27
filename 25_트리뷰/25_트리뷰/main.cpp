#include <Windows.h>
#include "resource.h"
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

#define IDC_EDIT_NAME 101
#define IDC_BTN_ADD 102
#define IDC_BTN_DEL 103

HWND g_hTree;
HIMAGELIST IL;
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

void AddItem(HWND hwnd)
{
	HTREEITEM hSelect;
	TVINSERTSTRUCT TI;
	TVITEMEX TVEX;
	TCHAR name[30];

	hSelect = TreeView_GetSelection(g_hTree);
	GetDlgItemText(hwnd, IDC_EDIT_NAME, name, 30);

	if (hSelect == NULL)
	{
		TI.hParent = 0;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;

		TI.item.iImage = 0;
		TI.item.iSelectedImage = 4;
		TI.item.pszText = name;
		TreeView_InsertItem(g_hTree, &TI);
	}
	else
	{
		// �̹��� ��ȣ�� �̿��� ������ �׸����� üũ
		TVEX.mask = TVIF_IMAGE;
		TVEX.hItem = hSelect;
		TreeView_GetItem(g_hTree, &TVEX);

		if (TVEX.iImage == 3)
		{
			MessageBox(hwnd, TEXT("������ �����ۿ��� ���ο� �������� �߰��� �� �����ϴ�."), TEXT("�˸�"), MB_OK);
			return;
		}

		TI.hParent = hSelect;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
		TI.item.iImage = TVEX.iImage + 1;
		TI.item.iSelectedImage = TVEX.iImage + 5;
		TI.item.pszText = name;
		TreeView_InsertItem(g_hTree, &TI);

		// TVE_EXPAND : ������ ����� �ڽĵ��� Ȯ��
		TreeView_Expand(g_hTree, hSelect, TVE_EXPAND);
	}
}

void DelItem()
{
	HTREEITEM hSelect = TreeView_GetSelection(g_hTree);

	if (hSelect != NULL)
	{
		TreeView_DeleteItem(g_hTree, hSelect);
	}
}

// �ݹ��Լ� �Ű�����
// hwnd - �޼����� ���� ������ �ڵ鷯
// msg	- � ������ �޼������� Ȯ���� �� �ִ� ��
// wParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
// lParam	- �޼����� �ΰ� ���� (�޼����� ���� �ٸ�)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TVINSERTSTRUCT TI;
	HTREEITEM ItemA, ItemB, ItemC;

	switch (msg)
	{
	case WM_CREATE:
		InitCommonControls();
		g_hTree = CreateWindow(WC_TREEVIEW, TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES,
			10, 10, 200, 300, hwnd, NULL, g_hInst, NULL);

		// Ʈ���信 ����� �̹��� ����Ʈ�� ����� �߰�
		IL = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1), 16, 1, RGB(255, 255, 255));

		SendMessage(g_hTree, TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)IL);

		// TVI_FIRST : ���� ��
		// TVI_LAST  : ���� ������
		// TVI_SORT  : ��������
		TI.hParent = 0;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		
		TI.item.iImage = 0;
		TI.item.iSelectedImage = 4;
		TI.item.pszText = (LPWSTR)TEXT("������ A");
		ItemA = (HTREEITEM)SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.hParent = ItemA;
		TI.item.iImage = 1;
		TI.item.iSelectedImage = 5;
		TI.item.pszText = (LPWSTR)TEXT("������ B");
		ItemB = (HTREEITEM)SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.hParent = ItemB;
		TI.item.iImage = 2;
		TI.item.iSelectedImage = 6;
		TI.item.pszText = (LPWSTR)TEXT("������ C");
		ItemC = (HTREEITEM)SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.hParent = ItemC;
		TI.item.iImage = 3;
		TI.item.iSelectedImage = 7;
		TI.item.pszText = (LPWSTR)TEXT("������ D");
		SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.item.pszText = (LPWSTR)TEXT("������ D-2");
		SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);



		CreateWindow(TEXT("static"), TEXT("�̸�"), WS_CHILD | WS_VISIBLE | SS_CENTER,
			220, 10, 90, 25, hwnd, (HMENU)-1, g_hInst, NULL);

		CreateWindow(TEXT("edit"), NULL, WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,
			320, 10, 90, 25, hwnd, (HMENU)IDC_EDIT_NAME, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("�߰�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 40, 90, 25, hwnd, (HMENU)IDC_BTN_ADD, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 40, 90, 25, hwnd, (HMENU)IDC_BTN_DEL, g_hInst, NULL);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BTN_ADD:
			AddItem(hwnd);
			break;

		case IDC_BTN_DEL:
			DelItem();
			break;
		}
		return 0;

	case WM_DESTROY:
		// WM_QUIT �޼����� �߼�
		ImageList_Destroy(IL);
		PostQuitMessage(0);
		return 0;
	}

	// �� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






