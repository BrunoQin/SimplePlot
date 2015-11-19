#pragma once

#include <windows.h> 
#include <tchar.h>
#include <string>
#include "coordinate.h"

TCHAR szClassName[] = _T("Customt_control_12345");
int state = 0;
POINT source = { 100, 100 };
POINTS curMousePos = { 0, 0 };
POINTS oldMousePos = { 0, 0 };
HDC hDCMem = 0;
HBITMAP hBmpMem = 0;
HBITMAP hBmpMemOld = 0;
HBRUSH hBrush;
BOOL myExist[6];
string myFuncStr[6];
int tick = 20;
string myFuncString[6];


LRESULT CALLBACK Custom_Control_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void setFunc(HWND hwnd, string funcString[6], BOOL exist[6]);

void InitCustomControl()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = szClassName;
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = Custom_Control_WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)GetSysColorBrush(RGB(255, 255, 255));
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIconSm = 0;
	RegisterClassEx(&wc);
}

void destroyBuffer()
{
	SelectObject(hDCMem, hBmpMemOld);
	DeleteObject(hBmpMem);
	hBmpMem = 0;
	hBmpMemOld = 0;
	DeleteDC(hDCMem);
}

void createBuffer(HWND hwnd)
{
	if (hDCMem) {
		destroyBuffer();
	}

	RECT rect;
	GetWindowRect(hwnd, &rect);
	hDCMem = CreateCompatibleDC(GetDC(hwnd));
	hBmpMem = CreateCompatibleBitmap(GetDC(hwnd), rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hDCMem, hBmpMem);
}

LRESULT CALLBACK Custom_Control_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	PAINTSTRUCT ps;

	int x = 0, y = 0;

	static RECT rect;
	short zDelta;


	switch (msg)
	{

	case WM_CREATE:

		return 0;
	case WM_SIZE:

		createBuffer(hwnd);

	return 0;

	case WM_COMMAND:

		return 0;

	case WM_MOUSEMOVE:

		static POINT NewPos;
		static RECT subrect;

		if (state == 1) {

			curMousePos = MAKEPOINTS(lParam);
			x = curMousePos.x - oldMousePos.x;
			y = curMousePos.y - oldMousePos.y;


			source.x = source.x + x;
			source.y = source.y + y;

			oldMousePos.x = curMousePos.x;
			oldMousePos.y = curMousePos.y;

			InvalidateRect(hwnd, NULL, false);

		}
		
		return 0;

	case WM_LBUTTONDOWN:

		oldMousePos = MAKEPOINTS(lParam);
		state = 1;

		return 0;

	case WM_LBUTTONUP:

		state = 0;

		return 0;	

	case WM_MOUSEWHEEL:
		zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (zDelta > 0 && tick > 10) {
			tick = tick - 10;
			InvalidateRect(hwnd, NULL, false);
		}
		else if (zDelta < 0){
			//MessageBox(NULL, "r", TEXT("HWND"), MB_OK);
			tick = tick + 10;
			InvalidateRect(hwnd, NULL, false);
		}
		else {
			return 0;
		}

	case WM_PAINT:	

		hdc = BeginPaint(hwnd, &ps);

		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		GetClientRect(hwnd, &rect);
		FillRect(hDCMem, &rect, hBrush);  //用画刷把位图清除干净

		createCoordinate(hDCMem, source.x, source.y, tick);
		drawfunc(hDCMem, source.x, source.y, tick, myFuncStr[0], myExist[0], 255, 0, 0);
		drawfunc(hDCMem, source.x, source.y, tick, myFuncStr[1], myExist[1], 0, 255, 0);
		drawfunc(hDCMem, source.x, source.y, tick, myFuncStr[2], myExist[2], 0, 0, 255);
		drawfunc(hDCMem, source.x, source.y, tick, myFuncStr[3], myExist[3], 255, 255, 0);
		drawfunc(hDCMem, source.x, source.y, tick, myFuncStr[4], myExist[4], 0, 255, 255);
		drawfunc(hDCMem, source.x, source.y, tick, myFuncStr[5], myExist[5], 255, 0, 255);

		BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hDCMem, 0, 0, SRCCOPY);		/* 将双缓冲区图像复制到显示缓冲区 */
		DeleteObject(hBrush);

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY: //当窗口关闭时产生的原因

		PostQuitMessage(0);//产生WM_QUIT消息
		break;


	default: //执行默认的消息处理
		return(DefWindowProc(hwnd, msg, wParam, lParam));
	}
	return (0);
}

HWND CreateCustomControlFunc(HWND hwndParent, int x, int y, int width, int height)
{
	HWND hwndCtrl;
	InitCustomControl();
	hwndCtrl = CreateWindowEx(
		WS_EX_CLIENTEDGE, // give it a standard border
		szClassName,
		_T("A custom control"),
		WS_VISIBLE | WS_CHILD,
		x, y, width, height,
		hwndParent,
		NULL, GetModuleHandle(0), NULL
		);

	return hwndCtrl;
}

void setFunc(HWND hwnd, string funcString[6], BOOL exist[6]) {
	myFuncStr[0] = funcString[0]; myExist[0] = exist[0];
	myFuncStr[1] = funcString[1]; myExist[1] = exist[1];
	myFuncStr[2] = funcString[2]; myExist[2] = exist[2];
	myFuncStr[3] = funcString[3]; myExist[3] = exist[3];
	myFuncStr[4] = funcString[4]; myExist[4] = exist[4];
	myFuncStr[5] = funcString[5]; myExist[5] = exist[5];
	InvalidateRect(hwnd, NULL, false);
}


