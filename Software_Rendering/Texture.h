#pragma once
#include "Window.h"

class Texture
{
private:
    HBITMAP hBit;
    BITMAP bitmap;

    DWORD *pixels;
    HDC textureHDC;
    HGDIOBJ oldBit;
public:
    Texture(std::string name);
    ~Texture();
};