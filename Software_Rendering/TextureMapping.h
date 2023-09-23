#pragma once
#include "math.h"
#include "Texture.h"

class TextureMapping
{
private:
    Vector2 vt1,vt2,vt3;
    Texture* texture;
public:
    TextureMapping();
    TextureMapping(Texture* texture);
    void BindUV(const Vector2 &vt1, const Vector2 &vt2, const Vector2& vt3);
    DWORD Calcuate(std::pair<float,float> UV);
};