#pragma once
#include "Window.h"
#include "math.h"

class Texture
{
private:
    HBITMAP hBit;
    BITMAP bitmap;
    DWORD *pixels;
    HDC textureHDC;
    HGDIOBJ oldBit;
public:
    Texture();
    Texture(std::string name);
    ~Texture();
    DWORD GetPixel(float x,float y);
};