#include<windows.h>
#include<stdio.h>
#include<cmath>

#include "resource.h"
#include "view.h"

const double pi = 3.1415926535;

HINSTANCE hInst; //当前实例的句柄
HWND hWndMain; //主窗口的句柄
BOOL CALLBACK DiaProc(HWND, UINT, WPARAM, LPARAM);

int x, y;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PSTR lpszCmdLine, int nCmdShow)
{
	MSG msg; //消息

	hWndMain = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DiaProc, NULL);

	ShowWindow(hWndMain, nCmdShow);//显示窗口
	UpdateWindow(hWndMain); //更新窗口，包括窗口的客户区
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); //转换某些键盘信息
		DispatchMessage(&msg); //将消息发送给窗口过程，这里是WndProc
	}
	return msg.wParam;
}
BOOL CALLBACK DiaProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{

	static HWND button, view;

	switch (message)
	{

	case WM_SIZE:

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		return 0;
	case WM_CREATE: //窗口创建产生的消息
		
		//button = createButton(button, hwnd);
		return 0;

	case WM_COMMAND: //命令消息，控件产生的通知代码在wParam的高字中

		return 0;

	case WM_PAINT:
		//button = CreateWindow(L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 60, 20, 100, 40, hwnd, (HMENU)1234, NULL, NULL);

		RECT rect;
		GetClientRect(hwnd, &rect);


		view = CreateCustomControlFunc(hwnd, rect.right/2, 0, rect.right / 2, rect.bottom);

		return 0;

	case WM_DESTROY: //当窗口关闭时产生的原因

		PostQuitMessage(0);//产生WM_QUIT消息
		break;

	default: //执行默认的消息处理
		return(DefWindowProc(hwnd, message, wParam, lParam));
	}
	return (0);
}