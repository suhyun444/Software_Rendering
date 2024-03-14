#pragma once
#include "FragmentShader.h"
#include "PhongShader.h"
#include "TextureMapping.h"
#include "NormalMapping.h"

class TextureMappingNormalMappingPhongShader : public FragmentShdaer
{
public:
    ~TextureMappingNormalMappingPhongShader();
    PhongShader *phongShader;
    Texture *texture;
    TextureMapping *textureMapping;
    Texture *normalTexture;
    NormalMapping *normalMapping;
    Vector3 lightDir; 
    void SetTexture(std::string textureName, std::string normalTextureName);
    void BindInput(Output output) override;
    Vector3 Calculate(std::pair<float, float> uv) override;
};