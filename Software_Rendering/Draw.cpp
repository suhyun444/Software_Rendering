#include "Draw.h"

void Draw::DrawTriangle(const HDC& hdc,const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
{
    MoveToEx(hdc,v1.x,v1.y,NULL);
    LineTo(hdc,v2.x,v2.y);
    MoveToEx(hdc, v2.x, v2.y, NULL);
    LineTo(hdc, v3.x, v3.y);
    MoveToEx(hdc, v3.x, v3.y, NULL);
    LineTo(hdc, v1.x, v1.y);
    return;
    // Compute triangle bounding box.
    float minX = Math::Min<float>(Math::Min<float>(v1.x, v2.x), v3.x);
    float maxX = Math::Max<float>(Math::Max<float>(v1.x, v2.x), v3.x);
    float minY = Math::Min<float>(Math::Min<float>(v1.y, v2.y), v3.y);
    float maxY = Math::Max<float>(Math::Max<float>(v1.y, v2.y), v3.y);

    // Clip to scissor rect.
    minX = Math::Max<float>(minX, 0);
    maxX = Math::Min<float>(maxX, (float)Window::width);
    minY = Math::Max<float>(minY, 0);
    maxY = Math::Min<float>(maxY, (float)Window::height);

    // Compute edge equations.
    EdgeEquation e0(v2, v3);
    EdgeEquation e1(v3, v1);
    EdgeEquation e2(v1, v2);

    float area = 0.5 * (e0.c + e1.c + e2.c);

    // Check if triangle is backfacing.
    if (area < 0)
        return;

    ParameterEquation r(v1.x, v2.x, v3.x, e0, e1, e2, area);
    ParameterEquation g(v1.y, v2.y, v3.y, e0, e1, e2, area);
    ParameterEquation b(v1.z, v2.z, v3.z, e0, e1, e2, area);

    // Add 0.5 to sample at pixel centers.
    for (float x = minX + 0.5f, xm = maxX + 0.5f; x <= xm; x += 1.0f)
        for (float y = minY + 0.5f, ym = maxY + 0.5f; y <= ym; y += 1.0f)
        {
            if (e0.CheckInside(x, y) && e1.CheckInside(x, y) && e2.CheckInside(x, y))
            {
                int rint = r.Evaluate(x, y) * 255;
                int gint = g.Evaluate(x, y) * 255;
                int bint = b.Evaluate(x, y) * 255;
                SetPixel(hdc, x, y, RGB(rint, gint, bint));
            }
        }
}