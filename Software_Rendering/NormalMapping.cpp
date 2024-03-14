#include "NormalMapping.h"

NormalMapping::NormalMapping()
{
}
NormalMapping::NormalMapping(Texture *texture) : texture(texture)
{
}

void NormalMapping::BindUV(const Vector2 &vt1, const Vector2 &vt2, const Vector2 &vt3, float z1, float z2, float z3)
{
    this->vt1 = vt1;
    this->vt2 = vt2;
    this->vt3 = vt3;
    this->invZ1 = 1.0f / z1;
    this->invZ2 = 1.0f / z2;
    this->invZ3 = 1.0f / z3;
}
Vector3 NormalMapping::Calcuate(std::pair<float, float> UV)
{
    float oneMinusST = 1 - UV.first - UV.second;
    float z = invZ1 * oneMinusST + invZ2 * UV.first + invZ3 * UV.second;
    float invZ = 1.0f / z;
    Vector2 position = (vt1 * oneMinusST * invZ1 + vt2 * UV.first * invZ2 + vt3 * UV.second * invZ3) * invZ;
    DWORD color = texture->GetPixel(position.x, position.y);
    Vector3 rgb = Vector3(GetBValue(color), GetGValue(color), GetRValue(color));
    return rgb;
}
