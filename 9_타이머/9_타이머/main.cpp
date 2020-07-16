#include <Windows.h>
#include "resource.h"
enum Status {WAIT, RUN, PAUSE} _Status;
int SetSec, NowSec;

BOOL CALLBACK TimerProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TCHAR Mes[256];

	switch (msg)
	{
	case WM_INITDIALOG:
		_Status = WAIT;
		return true;

	case WM_TIMER:
		NowSec--;
		if (NowSec <= 0)
		{
			if (IsDlgButtonChecked(hwnd, IDC_CHECK1) == BST_CHECKED)
				MessageBeep(0);


			KillTimer(hwnd, 0);
			_Status = WAIT;

			MessageBox(hwnd, TEXT("설정한 시간이 끝"), TEXT("알림"), MB_OK);

		}
		wsprintf(Mes, TEXT("남은시간 : %d초"), NowSec);
		SetDlgItemText(hwnd, IDC_STATIC_REMAIN, Mes);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_START:
			SetSec = GetDlgItemInt(hwnd, IDC_EDIT_SEC, NULL, false);
			if (SetSec <= 0)
			{
				MessageBox(hwnd, TEXT("시간을 다시 입력해주세요"), TEXT("알림"), MB_OK);
			}
			NowSec = SetSec;
			SetTimer(hwnd, 0, 1000, NULL);
			SendMessage(hwnd, WM_TIMER, 0, 0);
			_Status = RUN;

			return true;

		case IDC_PAUSE:
			switch (_Status)
			{
			case PAUSE:
				SetTimer(hwnd, 0, 1000, NULL);
				_Status = RUN;
				break;

			case RUN:
				KillTimer(hwnd, 0);
				_Status = PAUSE;
				break;
			}
			return true;

		case IDC_CANCLE:
			if (_Status == RUN) KillTimer(hwnd, 0);
			EndDialog(hwnd, IDCANCEL);
			return true;
		}
		return true;
	}

	return false;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmbParam, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, TimerProc);

	return 0;
}