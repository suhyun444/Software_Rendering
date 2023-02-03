#include "BitmapBuffer.h"

BitmapBuffer::BitmapBuffer(HWND hwnd, int width, int height) : hwnd(hwnd), width(width), height(height), scanlineCount(width * 3 + ((width * 3) & 3))
{
    bgColor = 0xffffffff;
    hdc = GetDC(hwnd);
    memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = BITS_PER_PIXEL;
    bmi.bmiHeader.biCompression = BI_RGB;

    hBit = CreateDIBSection(memDC, &bmi, DIB_RGB_COLORS, (LPVOID *)&bits, NULL, 0);
    oldBit = (HBITMAP)SelectObject(memDC, hBit);
}

BitmapBuffer::BitmapBuffer::~BitmapBuffer()
{
    DeleteObject(SelectObject(memDC, oldBit));
    DeleteObject(hBit);
    ReleaseDC(hwnd, memDC);
}
void BitmapBuffer::Draw()
{
	BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
}

void BitmapBuffer::Clear()
{
	for (int i = 0; i < scanlineCount; i += BYTES_PER_PIXEL)
		*(DWORD*)(bits + i) = bgColor;

	for (int i = 1; i < height; i++)
		memcpy(bits + (i * scanlineCount), bits, scanlineCount);
}

void BitmapBuffer::SetColor(int x, int y, DWORD color)
{
    y = Window::height - y;
	if (x < 0 || x >= width || y < 0 || y >= height) return;
	*(DWORD*)(bits + x * BYTES_PER_PIXEL + y * scanlineCount) = color;
}