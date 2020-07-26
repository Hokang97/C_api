#include <Windows.h>
#include <CommCtrl.h>
#pragma comment (lib, "ComCtl32.lib")
#include "resource.h"

HWND g_hList;
HIMAGELIST g_hImgSm, g_hImgLa;

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

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

void SetListViewStyle(HWND hList, DWORD dwView)
{
	DWORD dwStyle;
	dwStyle = GetWindowLong(hList, GWL_STYLE);
	if ((dwStyle & LVS_TYPEMASK) != dwView)
	{
		SetWindowLong(hList, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
	}
}


// 콜백함수 매개변수
// hwnd - 메세지를 받을 윈도우 핸들러
// msg	- 어떤 종류의 메세지인지 확일할 수 있는 값
// wParam	- 메세지의 부가 정보 (메세지에 따라 다름)
// lParam	- 메세지의 부가 정보 (메세지에 따라 다름)
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
		
		// 이미지 리스트 추가
		g_hImgSm = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1), 16, 1, RGB(255, 255, 255));
		g_hImgLa = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2), 32, 1, RGB(255, 255, 255));

		SendMessage(g_hList, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)g_hImgSm);
		SendMessage(g_hList, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)g_hImgLa);

		//헤더를 추가합니다
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("이름");
		COL.iSubItem = 0;
		SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

		COL.pszText = (LPWSTR)TEXT("전화번호");
		COL.iSubItem = 1;
		SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

		COL.pszText = (LPWSTR)TEXT("주소");
		COL.iSubItem = 2;
		COL.cx = 300;
		SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

		// 첫번째 아이탬
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iImage = 0;
		LI.iSubItem = 0;
		LI.iItem = 0;
		LI.pszText = (LPWSTR)TEXT("강아지");
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iImage = -1;
		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)TEXT("123-2424");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = (LPWSTR)TEXT("서울시 논현동");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		// 두번째 아이탬
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iImage = 1;
		LI.iSubItem = 0;
		LI.iItem = 1;
		LI.pszText = (LPWSTR)TEXT("고양이");
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iImage = -1;
		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)TEXT("456-2424");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = (LPWSTR)TEXT("서울시 창천동");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		// 세번째 아이탬
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iImage = 1;
		LI.iSubItem = 0;
		LI.iItem = 2;
		LI.pszText = (LPWSTR)TEXT("호랑이");
		SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

		LI.iImage = -1;
		LI.iSubItem = 1;
		LI.pszText = (LPWSTR)TEXT("789-2424");
		SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

		LI.iSubItem = 2;
		LI.pszText = (LPWSTR)TEXT("서울시 흑석동");
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
		// WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	// 그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);

}






