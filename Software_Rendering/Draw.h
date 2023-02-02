#pragma once
#include "Window.h"
#include "math.h"
#include "ParameterEquation.h"

class Draw
{
public:
    static void PrintText(const HDC& hdc,const int x,const int y, const LPCTSTR& text);
    static void DrawTriangle(const HDC& hdc, const Vector3& v1,const Vector3& v2,const Vector3& v3);
};