#pragma once
#include "FragmentShader.h"
#include "PhongShader.h"
#include "TextureMapping.h"

class TextureMappingPhongShader : public FragmentShdaer
{
public:
    ~TextureMappingPhongShader();
    PhongShader* phongShader;
    Texture *texture;
    TextureMapping *textureMapping;
    void SetTexture(std::string name);
    void BindInput(Output output) override;
    Vector3 Calculate(std::pair<float, float> uv) override;
};