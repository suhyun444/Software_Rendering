#pragma once
#include "Window.h"
#include "BaryCenterCalculator.h"
#include "PhongShader.h"
#include "TextureMapping.h"
#include "BitmapBuffer.h"

class Draw
{
public:
    static void Update(const Vector3& cameraPosition) {PhongShader::CameraPosition = cameraPosition;}
    static void PrintText(const HDC& hdc,const int x,const int y, const LPCTSTR& text);
    static void DrawTriangle(BitmapBuffer &bitmapBuffer, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, PhongShader &phongShader, TextureMapping &textureMapping);
};