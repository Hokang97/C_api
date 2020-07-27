#include <Windows.h>
#include "resource.h"
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

#define IDC_EDIT_NAME 101
#define IDC_BTN_ADD 102
#define IDC_BTN_DEL 103

HWND g_hTree;
HIMAGELIST IL;
// 함수 호출 방법
// __stdcall : 매개변수의 개수가 고정된 함수    / 크기 작다  / callee (피호출자) stack 정리
// __cdecl   : 매개변수의 개수가 가변적인 함수  / 크기 크다  / caller (호출자)   stack 정리

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	// 1. 윈도우 클래스 설정/초기화
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbClsExtra = 0;	// 특수한 목적으로 사용될 예약 영역
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;		// 윈도우 클래스를 등록하는 프로그램의 번호
	WndClass.lpfnWndProc = WndProc;		// 프로시저 설정
	WndClass.lpszClassName = TEXT("WndClass");
	WndClass.lpszMenuName = NULL;

	// 2. 윈도우 클래스 등록
	RegisterClass(&WndClass);

	// 3. 윈도우 창 생성
	hWnd = CreateWindow(WndClass.lpszClassName, TEXT("윈도우타이틀"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 640, NULL, NULL, hInstance, NULL);


	// 4. 윈도우 창 활성화/표시
	ShowWindow(hWnd, SW_SHOW);

	// 5. 메세지 루프/처리
	// GetMessage()
	// PeekMessage()


	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);		// 키보드 입력 메세지를 프로그램에서 사용할 수 있도록 가공
		DispatchMessage(&Msg);		// 메세지 큐에서 꺼낸 메세지를 프로시저에 전달
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
		// 이미지 번호를 이용해 마지막 항목인지 체크
		TVEX.mask = TVIF_IMAGE;
		TVEX.hItem = hSelect;
		TreeView_GetItem(g_hTree, &TVEX);

		if (TVEX.iImage == 3)
		{
			MessageBox(hwnd, TEXT("최하위 아이템에는 새로운 아이템을 추가할 수 없습니다."), TEXT("알림"), MB_OK);
			return;
		}

		TI.hParent = hSelect;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
		TI.item.iImage = TVEX.iImage + 1;
		TI.item.iSelectedImage = TVEX.iImage + 5;
		TI.item.pszText = name;
		TreeView_InsertItem(g_hTree, &TI);

		// TVE_EXPAND : 지정한 노드의 자식들을 확장
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

// 콜백함수 매개변수
// hwnd - 메세지를 받을 윈도우 핸들러
// msg	- 어떤 종류의 메세지인지 확일할 수 있는 값
// wParam	- 메세지의 부가 정보 (메세지에 따라 다름)
// lParam	- 메세지의 부가 정보 (메세지에 따라 다름)
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

		// 트리뷰에 사용할 이미지 리스트를 만들어 추가
		IL = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1), 16, 1, RGB(255, 255, 255));

		SendMessage(g_hTree, TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)IL);

		// TVI_FIRST : 가장 위
		// TVI_LAST  : 가장 마지막
		// TVI_SORT  : 오름차순
		TI.hParent = 0;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		
		TI.item.iImage = 0;
		TI.item.iSelectedImage = 4;
		TI.item.pszText = (LPWSTR)TEXT("아이템 A");
		ItemA = (HTREEITEM)SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.hParent = ItemA;
		TI.item.iImage = 1;
		TI.item.iSelectedImage = 5;
		TI.item.pszText = (LPWSTR)TEXT("아이템 B");
		ItemB = (HTREEITEM)SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.hParent = ItemB;
		TI.item.iImage = 2;
		TI.item.iSelectedImage = 6;
		TI.item.pszText = (LPWSTR)TEXT("아이템 C");
		ItemC = (HTREEITEM)SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.hParent = ItemC;
		TI.item.iImage = 3;
		TI.item.iSelectedImage = 7;
		TI.item.pszText = (LPWSTR)TEXT("아이템 D");
		SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		TI.item.pszText = (LPWSTR)TEXT("아이템 D-2");
		SendMessage(g_hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);



		CreateWindow(TEXT("static"), TEXT("이름"), WS_CHILD | WS_VISIBLE | SS_CENTER,
			220, 10, 90, 25, hwnd, (HMENU)-1, g_hInst, NULL);

		CreateWindow(TEXT("edit"), NULL, WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL,
			320, 10, 90, 25, hwnd, (HMENU)IDC_EDIT_NAME, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("추가"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			220, 40, 90, 25, hwnd, (HMENU)IDC_BTN_ADD, g_hInst, NULL);

		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
		// WM_QUIT 메세지를 발송
		ImageList_Destroy(IL);
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






