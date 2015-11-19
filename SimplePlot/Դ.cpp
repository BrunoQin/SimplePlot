#include<windows.h>
#include<stdio.h>
#include<cmath>

#include "resource.h"
#include "view.h"

const double pi = 3.1415926535;

HINSTANCE hInst; //��ǰʵ���ľ��
HWND hWndMain; //�����ڵľ��
BOOL CALLBACK DiaProc(HWND, UINT, WPARAM, LPARAM);

int x, y;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PSTR lpszCmdLine, int nCmdShow)
{
	MSG msg; //��Ϣ

	hWndMain = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DiaProc, NULL);

	ShowWindow(hWndMain, nCmdShow);//��ʾ����
	UpdateWindow(hWndMain); //���´��ڣ��������ڵĿͻ���
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); //ת��ĳЩ������Ϣ
		DispatchMessage(&msg); //����Ϣ���͸����ڹ��̣�������WndProc
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
	case WM_CREATE: //���ڴ�����������Ϣ
		
		//button = createButton(button, hwnd);
		return 0;

	case WM_COMMAND: //������Ϣ���ؼ�������֪ͨ������wParam�ĸ�����

		return 0;

	case WM_PAINT:
		//button = CreateWindow(L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 60, 20, 100, 40, hwnd, (HMENU)1234, NULL, NULL);

		RECT rect;
		GetClientRect(hwnd, &rect);


		view = CreateCustomControlFunc(hwnd, rect.right/2, 0, rect.right / 2, rect.bottom);

		return 0;

	case WM_DESTROY: //�����ڹر�ʱ������ԭ��

		PostQuitMessage(0);//����WM_QUIT��Ϣ
		break;

	default: //ִ��Ĭ�ϵ���Ϣ����
		return(DefWindowProc(hwnd, message, wParam, lParam));
	}
	return (0);
}