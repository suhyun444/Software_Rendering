#include "TextureMapping.h"

TextureMapping::TextureMapping()
{

}
TextureMapping::TextureMapping(Texture* texture) : texture(texture)
{
    
}

void TextureMapping::BindUV(const Vector2 &vt1, const Vector2 &vt2, const Vector2 &vt3, float z1, float z2, float z3)
{
    this->vt1 = vt1;
    this->vt2 = vt2;
    this->vt3 = vt3;
    this->invZ1 = 1.0f / z1;
    this->invZ2 = 1.0f / z2;
    this->invZ3 = 1.0f / z3;
}
DWORD TextureMapping::Calcuate(std::pair<float, float> UV)
{
    float oneMinusST = 1 - UV.first - UV.second;
    float z = invZ1 * oneMinusST + invZ2 * UV.first + invZ3 * UV.second;
    float invZ = 1.0f / z;
    Vector2 position = (vt1 * oneMinusST * invZ1 + vt2 * UV.first * invZ2 + vt3 * UV.second * invZ3) * invZ;
    return texture->GetPixel(position.x,position.y);
}
