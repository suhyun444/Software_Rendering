#include "Draw.h"
void Draw::PrintText(const HDC &hdc, const int x, const int y, const LPCTSTR &text)
{
    TextOut(hdc,x,y,text,lstrlen(text));
}
void Draw::DrawTriangle(const HDC& hdc,const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
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

    //ParameterEquation r(v1.x, v2.x, v3.x, e1, e2, e3, area);
    //ParameterEquation g(v1.y, v2.y, v3.y, e1, e2, e3, area);
    //ParameterEquation b(v1.z, v2.z, v3.z, e1, e2, e3, area);

    for (float x = minX + 0.5f, xm = maxX + 0.5f; x <= xm; x += 1.0f)
        for (float y = minY + 0.5f, ym = maxY + 0.5f; y <= ym; y += 1.0f)
        {
            if (e1.CheckInside(x, y) && e2.CheckInside(x, y) && e3.CheckInside(x, y))
            {
                SetPixel(hdc, x, y, RGB(0, 1, 1));
            }
        }
}