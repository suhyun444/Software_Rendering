#include "Draw.h"
#include <iostream>

float Draw::Ambient = 0.1f;
float Draw::SpecularStrength = 0.5f;
//Vector3 Draw::DirectionalLight = Vector3(0.0f,-0.5f,1.0f);
Vector3 Draw::DirectionalLight = Vector3(0.0f,-0.4f,1.0f);
Vector3 Draw::CameraPosition = Vector3(0.0f,0.0f,1.0f);
Vector3 Draw::GlobalLightColor = Vector3(1.0f,1.0f,1.0f);

void Draw::PrintText(const HDC &hdc, const int x, const int y, const LPCTSTR &text)
{
    TextOut(hdc,x,y,text,lstrlen(text));
}
void Draw::DrawTriangle(BitmapBuffer &bitmapBuffer, const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Vector3 normalVector, Vector3 &w1, Vector3 &w2, Vector3 &w3)
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
    Vector3 lightDir = DirectionalLight.Normalize().Reverse();
    float diffuseAmount = Math::Max<float>(normalVector.Dot(lightDir), 0);

    for (float x = minX + 0.5f, xm = maxX + 0.5f; x <= xm; x += 1.0f)
        for (float y = minY + 0.5f, ym = maxY + 0.5f; y <= ym; y += 1.0f)
        {
            if (e1.CheckInside(x, y) && e2.CheckInside(x, y) && e3.CheckInside(x, y))
            {
                std::pair<float,float> baryCenter =  baryCenterCalculator.Evaluate(x,y);
                float sum = baryCenter.first + baryCenter.second;
                int a = 255;
                float r = ((1 - sum) * 255.0f);
                float g = (baryCenter.first * 255.0f);
                float b = (baryCenter.second * 255.0f);

                Vector3 albedo = Vector3(123.0f / 255.0f,123.0f / 255.0f,123.0f / 255.0f);
                Vector3 ambient = GlobalLightColor * Ambient;
                Vector3 diffuse = GlobalLightColor * diffuseAmount;
                Vector3 position = w1 + ((w2 - w1) * baryCenter.first) + ((w3 - w1) * baryCenter.second);

                Vector3 viewDirection = (position - CameraPosition).Normalize();
                Vector3 reflectDirection = lightDir.Reverse().Reflect(normalVector);
                reflectDirection = reflectDirection.Normalize();
                Vector3 reverseViewVector = viewDirection.Reverse();
                float spec = pow(Math::Max<float>(reflectDirection.Dot(reverseViewVector), 0.0f), 32.0f);

                Vector3 specular = GlobalLightColor * SpecularStrength * spec;

                Vector3 lightAmount = (ambient + diffuse + specular) * albedo;
                lightAmount.x = Math::Min<float>(lightAmount.x,1);
                lightAmount.y = Math::Min<float>(lightAmount.y,1);
                lightAmount.z = Math::Min<float>(lightAmount.z,1);
                lightAmount = lightAmount * 255;
                DWORD color = (a << 24) + ((int)lightAmount.x << 16) + ((int)lightAmount.y << 8) + ((int)lightAmount.z);
                bitmapBuffer.SetColor(x,y,color);
            }
        }
}