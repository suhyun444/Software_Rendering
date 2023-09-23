#include "TextureMapping.h"

TextureMapping::TextureMapping()
{

}
TextureMapping::TextureMapping(Texture* texture) : texture(texture)
{
    
}

void TextureMapping::BindUV(const Vector2 &vt1, const Vector2 &vt2, const Vector2 &vt3)
{
    this->vt1 = vt1;
    this->vt2 = vt2;
    this->vt3 = vt3;
}
DWORD TextureMapping::Calcuate(std::pair<float, float> UV, float invZ0, float invZ1, float invZ2, float invZ)
{
    float oneMinusST = 1 - UV.first - UV.second;
    Vector2 position = (vt1 * oneMinusST * invZ0 + vt2 * UV.first * invZ1 + vt3 * UV.second * invZ2) * invZ;
    return texture->GetPixel(position.x,position.y);
}
