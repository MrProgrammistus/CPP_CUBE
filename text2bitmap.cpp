#include <iostream>

#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <windows.h>
#include <Gdiplus.h>
#pragma comment( lib,"Gdiplus.lib" )

#include <direct.h>
#include "camera.h"

Gdiplus::Bitmap* img;
Gdiplus::Font* font;

void init() {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	font = new Gdiplus::Font(L"Calibri", 32);
}

void* text2bitmap(int x, int y) {
	delete img;
	img = new Gdiplus::Bitmap(x, y);
	Gdiplus::Graphics graph(img);
	Gdiplus::RectF rect(0, 0, x, y);
	Gdiplus::SolidBrush brush(Gdiplus::Color::White);
	Gdiplus::StringFormat format;
	if(f1) graph.DrawString(L"R - перезапустить симуляцию\nF - приостановить симуляцию\nV - пошаговая прокрутка", 80, font, rect, &format, &brush);
	else graph.DrawString(L"F1 - подсказки", 15, font, rect, &format, &brush);
	Gdiplus::BitmapData bmd{};
	Gdiplus::Rect rect2(0, 0, x, y);
	img->LockBits(&rect2, 0, PixelFormat32bppARGB, &bmd);
	return bmd.Scan0;
}