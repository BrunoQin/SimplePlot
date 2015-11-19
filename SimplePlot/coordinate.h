#pragma once
#include <windows.h>
#include <string>

#include "cal.h"

void RVS_drawLine_width(HDC hDC, int x1, int y1, int x2, int y2, COLORREF color);

void createCoordinate(HDC hdc, int sx, int sy, int tick) {

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(190, 190, 190));
	HPEN old = (HPEN)SelectObject(hdc, pen);
	int tem = 10000 / tick * tick;

	for (int i = -tem; i < tem; i = i + tick) {
		if (i == 0) {
			pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			old = (HPEN)SelectObject(hdc, pen);
			MoveToEx(hdc, -tem, sy - i * 2, NULL);
			LineTo(hdc, tem, sy - i * 2);
			pen = CreatePen(PS_SOLID, 1, RGB(190, 190, 190));
			old = (HPEN)SelectObject(hdc, pen);
			continue;
		}
		MoveToEx(hdc, -tem, sy - i * 2, NULL);
		LineTo(hdc, tem, sy - i * 2);
	}

	for (int i = -tem; i < tem; i = i + tick) {
		if (i == 0) {
			pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			old = (HPEN)SelectObject(hdc, pen);
			MoveToEx(hdc, sx - i * 2, -tem, NULL);
			LineTo(hdc, sx - i * 2, tem);
			pen = CreatePen(PS_SOLID, 1, RGB(190, 190, 190));
			old = (HPEN)SelectObject(hdc, pen);
			continue;
		}
		MoveToEx(hdc, sx - i * 2, -tem, NULL);
		LineTo(hdc, sx - i * 2, tem);
	}


}

void drawfunc(HDC hdc, int sx, int sy, int tick, string funcStr, BOOL exist, int R, int G, int B, int start, int end) {

	if (exist) {
		int myStart = start * tick;
		int myEnd = end * tick;
		double result;
		int n = myStart - myEnd;
		POINT  apt[20000];
		char strtem[300];
		double ex;
		int points = 0;
		strcpy_s(strtem, funcStr.c_str());

		for (int i = -10000; i < 10000; i++) {
			if (i >= myStart && i <= myEnd) {
				ex = i / tick;
				apt[points].x = tick * ex + sx;
				apt[points].y = -10 * tick * calculate(ex / 10, strtem, strlen(strtem) + 1) + sy;
				points++;
			}
		}
		//Polyline(hdc, apt, 200);
		for (int j = 0; j < points - 1; j++) {
			RVS_drawLine_width(hdc, apt[j].x, apt[j].y, apt[j + 1].x, apt[j + 1].y, RGB(R, G, B));
		}
	}

}

void RVS_drawLine_width(HDC hDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	// Calculate line params
	int dx = (x2 - x1);
	int dy = (y2 - y1);
	COLORREF bgColor;
	int temp;
	float k;

	// X-dominant line
	if (abs(dx) > abs(dy))
	{
		// Ex-change line end points
		if (dx < 0)
		{
			temp = x1;
			x1 = x2;
			x2 = temp;

			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		k = (float)dy / (float)dx;

		int xs;
		float yt = (float)y1;
		float distance;
		UCHAR red, green, blue;


		for (xs = x1; xs <= x2; xs++)
		{
			distance = (float)(yt - (int)(yt));

			bgColor = ::GetPixel(hDC, xs, (int)yt - 1);
			red = (UCHAR)(distance*GetRValue(bgColor)) + (UCHAR)((1.0f - distance)*GetRValue(color));
			green = (UCHAR)(distance*GetGValue(bgColor)) + (UCHAR)((1.0f - distance)*GetGValue(color));
			blue = (UCHAR)(distance*GetBValue(bgColor)) + (UCHAR)((1.0f - distance)*GetBValue(color));
			::SetPixel(hDC, xs, (int)yt - 1, RGB(red, green, blue));

			//::SetPixel(hDC, xs, (int)yt-1, color);
			::SetPixel(hDC, xs, (int)yt, color);


			bgColor = ::GetPixel(hDC, xs, (int)yt + 1);
			red = (UCHAR)((1.0f - distance)*GetRValue(bgColor)) + (UCHAR)(distance*GetRValue(color));
			green = (UCHAR)((1.0f - distance)*GetGValue(bgColor)) + (UCHAR)(distance*GetGValue(color));
			blue = (UCHAR)((1.0f - distance)*GetBValue(bgColor)) + (UCHAR)(distance*GetBValue(color));
			::SetPixel(hDC, xs, (int)yt + 1, RGB(red, green, blue));

			yt += k;
		}

	}
	// Y-dominant line
	else
	{
		// Ex-change line end points
		if (dy < 0)
		{
			temp = x1;
			x1 = x2;
			x2 = temp;

			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		k = (float)dx / (float)dy;

		int ys;
		float xt = (float)x1;
		float distance;
		UCHAR red, green, blue;
		for (ys = y1; ys <= y2; ys++)
		{
			distance = (float)(xt - (int)(xt));

			bgColor = ::GetPixel(hDC, (int)xt - 1, ys);
			red = (UCHAR)(distance*GetRValue(bgColor)) + (UCHAR)((1.0f - distance)*GetRValue(color));
			green = (UCHAR)(distance*GetGValue(bgColor)) + (UCHAR)((1.0f - distance)*GetGValue(color));
			blue = (UCHAR)(distance*GetBValue(bgColor)) + (UCHAR)((1.0f - distance)*GetBValue(color));
			::SetPixel(hDC, (int)xt - 1, ys, RGB(red, green, blue));

			//::SetPixel(hDC, (int)xt-1, ys, color);
			::SetPixel(hDC, (int)xt, ys, color);


			bgColor = ::GetPixel(hDC, (int)xt + 1, ys);
			red = (UCHAR)((1.0f - distance)*GetRValue(bgColor)) + (UCHAR)(distance*GetRValue(color));
			green = (UCHAR)((1.0f - distance)*GetGValue(bgColor)) + (UCHAR)(distance*GetGValue(color));
			blue = (UCHAR)((1.0f - distance)*GetBValue(bgColor)) + (UCHAR)(distance*GetBValue(color));
			::SetPixel(hDC, (int)xt + 1, ys, RGB(red, green, blue));

			xt += k;
		}
	}

}