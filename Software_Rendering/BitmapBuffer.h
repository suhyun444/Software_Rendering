#pragma once
#include "Window.h"

static const unsigned int BYTES_PER_PIXEL = 3;
static const unsigned int BITS_PER_PIXEL = 8 * BYTES_PER_PIXEL;

class BitmapBuffer
{
private:
    DWORD bgColor;
    DWORD scanlineCount;

    int width;
    int height;
    
    HWND hwnd;
    HDC hdc;
    HDC memDC;
    HBITMAP hBit;
    HBITMAP oldBit;

    BYTE* bits;
public:
    BitmapBuffer(HWND hwnd, int width, int height);
    ~BitmapBuffer();
    void Draw();
    void Clear();

    void SetColor(int x,int y,DWORD color);
};