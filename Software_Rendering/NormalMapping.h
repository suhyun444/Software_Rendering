#pragma once
#include "math.h"
#include "Texture.h"

class NormalMapping
{
private:
    Vector2 vt1, vt2, vt3;
    Texture *texture;
    float invZ1, invZ2, invZ3;

public:
    NormalMapping();
    NormalMapping(Texture *texture);
    void BindUV(const Vector2 &vt1, const Vector2 &vt2, const Vector2 &vt3, float z1, float z2, float z3);
    Vector3 Calcuate(std::pair<float, float> UV);
};