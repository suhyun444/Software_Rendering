#pragma once
#include "Window.h"
#include "math.h"
#include "BaryCenterCalculator.h"
#include "BitmapBuffer.h"

class Draw
{
public:
    static float Ambient;
    static float SpecularStrength;
    static Vector3 CameraPosition;
    static Vector3 DirectionalLight;
    static Vector3 GlobalLightColor;
    static void Update(const Vector3 &cameraPosition) { CameraPosition = cameraPosition; }
    static void PrintText(const HDC& hdc,const int x,const int y, const LPCTSTR& text);
    static void DrawTriangle(BitmapBuffer &bitmapBuffer, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Vector3 normalVector, Vector3 &w1, Vector3 &w2, Vector3 &w3);
};