#include "Texture.h"

Texture::Texture()
{

}
// https://online-converting.com/image/convert2bmp/#google_vignette
//Bitmap converter
Texture::Texture(std::string name)
{
    std::string path = "D:\\Winapi\\Software_Rendering\\Software_Rendering\\Texture\\" + name;
    hBit = (HBITMAP)LoadImageA(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if(GetLastError() == 2)
    {
        std::cout << "FileNotFound\n";
        return;
    }
    else if(hBit == NULL)
    {
        std::cout << "Fail\n";
        return;
    }
    GetObject(hBit, sizeof(BITMAP), &bitmap);
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bitmap.bmWidth;
    bmi.bmiHeader.biHeight = bitmap.bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = bitmap.bmBitsPixel;
    bmi.bmiHeader.biCompression = BI_RGB;

    textureHDC = CreateCompatibleDC(NULL);
    oldBit = SelectObject(textureHDC, hBit);
    
    DWORD pixelsSize = bitmap.bmWidth * bitmap.bmHeight;
    pixels = new DWORD[pixelsSize];
    int success = GetDIBits(textureHDC, hBit, 0, bitmap.bmHeight, pixels, &bmi, DIB_RGB_COLORS);
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