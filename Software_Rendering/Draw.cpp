#include "Draw.h"
#include <iostream>


void Draw::PrintText(const HDC &hdc, const int x, const int y, const LPCTSTR &text)
{
    TextOut(hdc,x,y,text,lstrlen(text));
}
void Draw::DrawTriangle(BitmapBuffer &bitmapBuffer, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, PhongShader &phongShader, TextureMapping &textureMapping)
{
    float minX = Math::Min<float>(Math::Min<float>(v1.x, v2.x), v3.x);
    float maxX = Math::Max<float>(Math::Max<float>(v1.x, v2.x), v3.x);
    float minY = Math::Min<float>(Math::Min<float>(v1.y, v2.y), v3.y);
    float maxY = Math::Max<float>(Math::Max<float>(v1.y, v2.y), v3.y);

    minX = Math::Max<float>(minX, 0);
    maxX = Math::Min<float>(maxX, (float)Window::width);
    minY = Math::Max<float>(minY, 0);
    maxY = Math::Min<float>(maxY, (float)Window::height);

    EdgeEquation e1(v2, v3);
    EdgeEquation e2(v3, v1);
    EdgeEquation e3(v1, v2);

    float area = 0.5f * (e1.c + e2.c + e3.c);

    BaryCenterCalculator baryCenterCalculator(v1,v2,v3);
    for (float x = minX + 0.5f, xm = maxX + 0.5f; x <= xm; x += 1.0f)
        for (float y = minY + 0.5f, ym = maxY + 0.5f; y <= ym; y += 1.0f)
        {
            if (e1.CheckInside(x, y) && e2.CheckInside(x, y) && e3.CheckInside(x, y))
            {
                std::pair<float,float> baryCenter =  baryCenterCalculator.Evaluate(x,y);
                if(baryCenter.first < 0 || baryCenter.second < 0)std::cout << baryCenter.first << " , " << baryCenter.second << "\n";
                float sum = baryCenter.first + baryCenter.second;
                int a = 255;
                float r = ((1 - sum));
                float g = (baryCenter.first);
                float b = (baryCenter.second);
                float z = v1.z * r + v2.z * g + v3.z * b;
                float prevDepth = bitmapBuffer.GetDepth(x,y);
                if(prevDepth > z) continue;
                DWORD color = textureMapping.Calcuate(baryCenter);
                Vector3 rgb = phongShader.Calculate(color, baryCenter);
                color = (a << 24) + ((int)rgb.x << 16) + ((int)rgb.y << 8) + ((int)rgb.z);
                bitmapBuffer.SetDepth(x,y,z);
                bitmapBuffer.SetColor(x,y,color);
            }
        }
}