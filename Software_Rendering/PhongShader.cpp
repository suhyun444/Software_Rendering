#include "PhongShader.h"

Vector3 PhongShader::DirectionalLight = Vector3(0.0f, -0.45, 1.0f);
Vector3 PhongShader::CameraPosition = Vector3(0.0f, 0.0f, 1.0f);

PhongShader::PhongShader(Vector3 normalVector, const Vector3 &worldPositon1, const Vector3 &worldPositon2, const Vector3 &worldPositon3)
    : normalVector(normalVector), worldPositon1(worldPositon1), worldPositon2(worldPositon2), worldPositon3(worldPositon3)
{
    Vector3 lightDir = DirectionalLight.Normalize().Reverse();
    float diffuseAmount = Math::Max<float>(normalVector.Dot(lightDir), 0);
    ambient = GlobalLightColor * Ambient;
    diffuse = GlobalLightColor * diffuseAmount;
    reflectDirection = lightDir.Reverse().Reflect(normalVector);
    reflectDirection = reflectDirection.Normalize();
}
Vector3 PhongShader::Calculate(Vector3 rgb, std::pair<int, int> UV)
{
    Vector3 position = worldPositon1 + ((worldPositon2 - worldPositon1) * UV.first) + ((worldPositon3 - worldPositon1) * UV.second);

    Vector3 viewDirection = (position - CameraPosition).Normalize();
    Vector3 reverseViewVector = viewDirection.Reverse();
    float spec = pow(Math::Max<float>(reflectDirection.Dot(reverseViewVector), 0.0f), 32.0f);

    Vector3 specular = GlobalLightColor * SpecularStrength * spec;

    Vector3 result = (ambient + diffuse + specular) * rgb;
    result.x = Math::Min<float>(result.x, 1);
    result.y = Math::Min<float>(result.y, 1);
    result.z = Math::Min<float>(result.z, 1);
    result = result * 255;
    return result;
}