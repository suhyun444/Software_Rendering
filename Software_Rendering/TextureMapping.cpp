#include "TextureMapping.h"

TextureMapping::TextureMapping()
{

}
TextureMapping::TextureMapping(Texture texture) : texture(texture)
{
    
}

void TextureMapping::BindUV(const Vector2 &vt1, const Vector2 &vt2, const Vector2 &vt3)
{
    this->vt1 = vt1;
    this->vt2 = vt2;
    this->vt3 = vt3;
}
DWORD TextureMapping::Calcuate(std::pair<float,float> UV)
{
    Vector2 position = vt1 + ((vt2 - vt1) * UV.first) + ((vt3 - vt1) * UV.second);
    return texture.GetPixel(position.x,position.y);
}
