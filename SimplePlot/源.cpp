#include<windows.h>
#include<stdio.h>
#include <string>
#include<cmath>

#include "resource.h"
#include "view.h"
#include "TCHAR2STRING.h"

const double pi = 3.1415926535;

HINSTANCE hInst;
HWND hWndMain;
HWND button;
HWND view;
WNDPROC OldProc[3];
int idFocus;
BOOL exist[] = { false, false, false, false, false, false };
string funcStr[] = { "", "" ,"", "", "", "" };
string s;
string e;
BOOL CALLBACK DiaProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int x, y;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;

	hWndMain = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DiaProc, NULL);

	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOL CALLBACK DiaProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{

	HWND hWndComboBox = NULL, hWndEdit = NULL;
	static HWND hWndPlot_1, hWndEdit_1;
	static HWND hWndPlot_2, hWndEdit_2;
	static HWND hWndPlot_3, hWndEdit_3;
	static HWND hWndPlot_4, hWndEdit_4;
	static HWND hWndPlot_5, hWndEdit_5;
	static HWND hWndPlot_6, hWndEdit_6;
	static HWND hWndClear_1;
	static HWND hWndClear_2;
	static HWND hWndClear_3;
	static HWND hWndClear_4;
	static HWND hWndClear_5;
	static HWND hWndClear_6;
	static HWND hWndClearAll;
	static HWND hWndStart;
	static HWND hWndEnd;

	PAINTSTRUCT ps;

	COLORREF			rcPrim[3] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255) };					
	int					i;
	TCHAR				szBuffer[10];
	static HINSTANCE	hInstance;
	static RECT			mrect;	
	static RECT         rect;
	static HWND			hScroll[3], hLabel[3], hValue[3], hStatic;								
	static HBRUSH		hBrushScroll[3], hBrushStatic;										
	static int			cyChar, iColor[3];
	TCHAR				*szColorName[3] = { L"Red",L"Green",L"Blue" };
	TCHAR func[255];
	TCHAR myStart[100];
	TCHAR myEnd[100];


	HWND hButton;

	TCHAR szText[256] = L"";
	switch (message)
	{
	case WM_CREATE:

		hWndComboBox = GetDlgItem(hwnd, IDC_COMBO1);
		hWndEdit = GetDlgItem(hwnd, IDC_EDIT1);
		
		return 0;

	case WM_SIZE:

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		break;

	case WM_SETFOCUS:
		SetFocus(hScroll[idFocus]);
		return 0;

	case WM_VSCROLL:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		SetFocus(hScroll[i]);

		switch (LOWORD(wParam))
		{
		case SB_PAGEDOWN:
			iColor[i] = min(255, iColor[i] + 15);
			break;
		case SB_LINEDOWN:
			iColor[i] = min(255, iColor[i] + 1);
			break;
		case SB_PAGEUP:
			iColor[i] = max(0, iColor[i] - 15);
			break;
		case SB_LINEUP:
			iColor[i] = max(0, iColor[i] - 1);
			break;
		case SB_TOP:
			iColor[i] = 0;
			break;
		case SB_BOTTOM:
			iColor[i] = 255;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			iColor[i] = HIWORD(wParam);														
			break;
		}

		SetScrollPos(hScroll[i], SB_CTL, iColor[i], TRUE);
		wsprintf(szBuffer, L"%d", iColor[i]);
		SetWindowText(hValue[i], szBuffer);

		DeleteObject((HBRUSH)SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(iColor[0], iColor[1], iColor[2]))));
		setFunc(view, funcStr, exist, s, e, iColor);
		InvalidateRect(hwnd, &mrect, TRUE);
		return 0;

	case WM_CTLCOLORSCROLLBAR:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		return (LRESULT)hBrushScroll[i];

	case WM_CTLCOLORSTATIC:
		i = GetWindowLong((HWND)lParam, GWL_ID);

		if (i >= 3 && i <= 8)
		{
			SetTextColor((HDC)wParam, rcPrim[i % 3]);
			SetBkColor((HDC)wParam, GetSysColor(COLOR_BTNHIGHLIGHT));
			return (LRESULT)hBrushStatic;
		}

		break;

	case WM_SYSCOLORCHANGE:
		DeleteObject(hBrushStatic);
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		return 0;

	case WM_INITDIALOG:
		hWndPlot_1 = GetDlgItem(hwnd, IDC_BUTTON1);
		hWndEdit_1 = GetDlgItem(hwnd, IDC_EDIT1);
		hWndPlot_2 = GetDlgItem(hwnd, IDC_BUTTON2);
		hWndEdit_2 = GetDlgItem(hwnd, IDC_EDIT5);
		hWndPlot_3 = GetDlgItem(hwnd, IDC_BUTTON3);
		hWndEdit_3 = GetDlgItem(hwnd, IDC_EDIT6);
		hWndPlot_4 = GetDlgItem(hwnd, IDC_BUTTON4);
		hWndEdit_4 = GetDlgItem(hwnd, IDC_EDIT7);
		hWndPlot_5 = GetDlgItem(hwnd, IDC_BUTTON5);
		hWndEdit_5 = GetDlgItem(hwnd, IDC_EDIT8);
		hWndPlot_6 = GetDlgItem(hwnd, IDC_BUTTON6);
		hWndEdit_6 = GetDlgItem(hwnd, IDC_EDIT9);
		hWndClear_1 = GetDlgItem(hwnd, IDC_BUTTON2);
		hWndClear_2 = GetDlgItem(hwnd, IDC_BUTTON4);
		hWndClear_3 = GetDlgItem(hwnd, IDC_BUTTON6);
		hWndClear_4 = GetDlgItem(hwnd, IDC_BUTTON8);
		hWndClear_5 = GetDlgItem(hwnd, IDC_BUTTON10);
		hWndClear_6 = GetDlgItem(hwnd, IDC_BUTTON12);
		hWndClearAll = GetDlgItem(hwnd, IDC_BUTTON13);
		hWndStart = GetDlgItem(hwnd, IDC_EDIT2);
		hWndEnd = GetDlgItem(hwnd, IDC_EDIT3);


		SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)"RED");
		SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 1, (LPARAM)"GREEN");
		SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 2, (LPARAM)"BLUE");

		hBrushStatic = CreateSolidBrush(GetSysColor(RGB(0,0,0)));

		GetClientRect(hwnd, &rect);

		view = CreateCustomControlFunc(hwnd, rect.right / 3, 0, 2 * rect.right / 3, rect.bottom);
		SetFocus(view);

		SetRect(&mrect, 160, 380, 260, 480);

		for (i = 0; i<3; i++)
		{
			hScroll[i] = CreateWindow(L"scrollbar",
				NULL,
				WS_CHILD | WS_VISIBLE | SBS_VERT,
				30 + i * 50, 380, 20, 100,
				hwnd,
				(HMENU)i,
				hInst,
				NULL);

			SetScrollRange(hScroll[i], SB_CTL, 0,255, FALSE);
			SetScrollPos(hScroll[i], SB_CTL, 255, FALSE);

			hLabel[i] = CreateWindow(L"static",
				szColorName[i],
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				20 + i * 50, 350, 40, 18,
				hwnd,
				(HMENU)(i + 3),
				hInst,
				NULL);

			hValue[i] = CreateWindow(L"static",
				L"0",
				WS_CHILD | WS_VISIBLE | SS_CENTER,
				20 + i * 50, 490, 40, 18,
				hwnd,
				(HMENU)(i + 6),
				hInst,
				NULL);

			hBrushScroll[i] = CreateSolidBrush(rcPrim[i]);

			OldProc[i] = (WNDPROC)SetWindowLong(hScroll[i], GWL_WNDPROC, (LONG)ScrollProc);
		}

		cyChar = HIWORD(GetDialogBaseUnits());
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));

		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			SendMessage(hWndEdit_1, WM_GETTEXT, 255, (LPARAM)func);
			SendMessage(hWndStart, WM_GETTEXT, 255, (LPARAM)myStart);
			SendMessage(hWndEnd, WM_GETTEXT, 255, (LPARAM)myEnd);
			funcStr[0] = TCHAR2STRING(func);
			s = TCHAR2STRING(myStart);
			e = TCHAR2STRING(myEnd);

			exist[0] = true;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON3:
			SendMessage(hWndEdit_2, WM_GETTEXT, 255, (LPARAM)func);
			SendMessage(hWndStart, WM_GETTEXT, 255, (LPARAM)myStart);
			SendMessage(hWndEnd, WM_GETTEXT, 255, (LPARAM)myEnd);
			funcStr[1] = TCHAR2STRING(func);
			s = TCHAR2STRING(myStart);
			e = TCHAR2STRING(myEnd);

			exist[1] = true;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON5:
			SendMessage(hWndEdit_3, WM_GETTEXT, 255, (LPARAM)func);
			SendMessage(hWndStart, WM_GETTEXT, 255, (LPARAM)myStart);
			SendMessage(hWndEnd, WM_GETTEXT, 255, (LPARAM)myEnd);
			funcStr[2] = TCHAR2STRING(func);
			s = TCHAR2STRING(myStart);
			e = TCHAR2STRING(myEnd);

			exist[2] = true;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON7:
			SendMessage(hWndEdit_4, WM_GETTEXT, 255, (LPARAM)func);
			SendMessage(hWndStart, WM_GETTEXT, 255, (LPARAM)myStart);
			SendMessage(hWndEnd, WM_GETTEXT, 255, (LPARAM)myEnd);
			funcStr[3] = TCHAR2STRING(func);
			s = TCHAR2STRING(myStart);
			e = TCHAR2STRING(myEnd);

			exist[3] = true;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON9:
			SendMessage(hWndEdit_5, WM_GETTEXT, 255, (LPARAM)func);
			SendMessage(hWndStart, WM_GETTEXT, 255, (LPARAM)myStart);
			SendMessage(hWndEnd, WM_GETTEXT, 255, (LPARAM)myEnd);
			funcStr[4] = TCHAR2STRING(func);
			s = TCHAR2STRING(myStart);
			e = TCHAR2STRING(myEnd);

			exist[4] = true;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON11:
			SendMessage(hWndEdit_6, WM_GETTEXT, 255, (LPARAM)func);
			SendMessage(hWndStart, WM_GETTEXT, 255, (LPARAM)myStart);
			SendMessage(hWndEnd, WM_GETTEXT, 255, (LPARAM)myEnd);
			funcStr[5] = TCHAR2STRING(func);
			s = TCHAR2STRING(myStart);
			e = TCHAR2STRING(myEnd);

			exist[5] = true;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON2:
			funcStr[0] = "";
			exist[0] = false;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON4:
			funcStr[1] = "";
			exist[1] = false;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON6:
			funcStr[2] = "";
			exist[2] = false;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON8:
			funcStr[3] = "";
			exist[3] = false;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON10:
			funcStr[4] = "";
			exist[4] = false;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON12:
			funcStr[5] = "";
			exist[5] = false;
			setFunc(view, funcStr, exist, s, e, iColor);
			SetFocus(view);
			break;
		case IDC_BUTTON13:
			funcStr[0] = "";
			funcStr[1] = "";
			funcStr[2] = "";
			funcStr[3] = "";
			funcStr[4] = "";
			funcStr[5] = "";
			exist[5] = false;
			exist[5] = false;
			exist[5] = false;
			exist[5] = false;
			exist[5] = false;
			exist[5] = false;
			setFunc(view, funcStr, exist, s, e,iColor);
			SetFocus(view);
			break;
		}

		break;

		return 0;

	case WM_PAINT:
		BeginPaint(hwnd, &ps);
		SelectObject(ps.hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(ps.hdc, RGB(255, 0, 0));
		Rectangle(ps.hdc, 15, 152, 30, 167);
		SetDCBrushColor(ps.hdc, RGB(0, 255, 0));
		Rectangle(ps.hdc, 15, 187, 30, 202);
		SetDCBrushColor(ps.hdc, RGB(0, 0, 255));
		Rectangle(ps.hdc, 15, 222, 30, 237);
		SetDCBrushColor(ps.hdc, RGB(255, 255, 0));
		Rectangle(ps.hdc, 15, 257, 30, 272);
		SetDCBrushColor(ps.hdc, RGB(0, 255, 255));
		Rectangle(ps.hdc, 15, 290, 30, 305);
		SetDCBrushColor(ps.hdc, RGB(255, 0, 255));
		Rectangle(ps.hdc, 15, 322, 30, 337);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default:
		return(DefWindowProc(hwnd, message, wParam, lParam));
	}
	return (0);
}

LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int id = GetWindowLong(hwnd, GWL_ID);

	switch (message)
	{
	case WM_KEYDOWN:
		if (LOWORD(wParam) == VK_TAB)
			SetFocus(GetDlgItem(GetParent(hwnd), (3 + id + (GetKeyState(VK_SHIFT) < 0 ? -1 : 1)) % 3));					
		break;
	case WM_SETFOCUS:
		idFocus = id;
		break;
	}

	return CallWindowProc(OldProc[id], hwnd, message, wParam, lParam);
}