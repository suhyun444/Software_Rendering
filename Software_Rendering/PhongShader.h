#pragma once
#include "math.h"
#include "Window.h"

class PhongShader
{
private:
    const float Ambient = 0.1f;
    const float SpecularStrength = 0.5f;
    Vector3 GlobalLightColor = Vector3(1.0f,1.0f,1.0f);
public:
    static Vector3 DirectionalLight;
    static Vector3 CameraPosition;
    Vector3 worldPositon1, worldPositon2, worldPositon3, normalVector;
    Vector3 diffuse;
    Vector3 ambient;
    Vector3 reflectDirection;
    PhongShader();
    PhongShader(Vector3 normalVector, const Vector3& worldPositon1, const Vector3&worldPositon2, const Vector3 &worldPositon3);
    Vector3 Calculate(Vector3 color,std::pair<float,float> UV);
};