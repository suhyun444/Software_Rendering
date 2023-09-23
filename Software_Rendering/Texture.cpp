#include "Texture.h"

Texture::Texture(std::string name)
{
    std::string path = "D:\\Winapi\\Software_Rendering\\Software_Rendering\\Texture\\" + name;
    hBit = (HBITMAP)LoadImageA(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    bitmap;

    int success = GetObject(hBit, sizeof(BITMAP), &bitmap);

    textureHDC = CreateCompatibleDC(NULL);
    oldBit = SelectObject(textureHDC, hBit);
    DWORD pixelsSize = bitmap.bmWidth * bitmap.bmHeight;
    pixels = new DWORD[pixelsSize];
    GetDIBits(textureHDC, hBit, 0, bitmap.bmHeight, pixels, (BITMAPINFO *)&bitmap, DIB_RGB_COLORS);
}
Texture::~Texture()
{
    delete[] pixels;
    SelectObject(textureHDC, oldBit);
    DeleteDC(textureHDC);
    DeleteObject(hBit);
}