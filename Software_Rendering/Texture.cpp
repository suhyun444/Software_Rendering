#include "Texture.h"

Texture::Texture()
{

}
Texture::Texture(std::string name)
{
    std::string path = "D:\\Winapi\\Software_Rendering\\Software_Rendering\\Texture\\" + name;
    hBit = (HBITMAP)LoadImageA(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    GetObject(hBit, sizeof(BITMAP), &bitmap);

    textureHDC = CreateCompatibleDC(NULL);
    oldBit = SelectObject(textureHDC, hBit);
    DWORD pixelsSize = bitmap.bmWidth * bitmap.bmHeight;
    pixels = new DWORD[pixelsSize];
    //0을 반환한다 error
    int success = GetDIBits(textureHDC, hBit, 0, bitmap.bmHeight, pixels, (BITMAPINFO *)&bitmap, DIB_RGB_COLORS);
    std::cout << GetLastError() << "\n";
    std::cout << success<<"\n";
}
Texture::~Texture()
{
    delete[] pixels;
    SelectObject(textureHDC, oldBit);
    DeleteDC(textureHDC);
    DeleteObject(hBit);
}
DWORD Texture::GetPixel(float x,float y)
{
    int xPosition = x * bitmap.bmWidth;
    int yPosition = y * bitmap.bmHeight;
    xPosition = Math::Min<int>(Math::Max<int>(xPosition, 0), bitmap.bmWidth);
    yPosition = Math::Min<int>(Math::Max<int>(yPosition, 0), bitmap.bmHeight);
    return pixels[xPosition + yPosition * bitmap.bmWidth];
}