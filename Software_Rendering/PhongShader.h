#pragma once
#include "math.h"
#include "Window.h"

class PhongShader
{
public:
    static Vector3 DirectionalLight;
    static Vector3 CameraPosition;
    static constexpr float Ambient = 0.1f;
    static constexpr float SpecularStrength = 0.5f;
    static Vector3 GlobalLightColor;
};