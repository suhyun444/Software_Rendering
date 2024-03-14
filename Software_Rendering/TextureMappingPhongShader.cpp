#include "TextureMappingPhongShader.h"

TextureMappingPhongShader::~TextureMappingPhongShader()
{
    delete texture;
    delete textureMapping;
    delete phongShader;
}
void TextureMappingPhongShader::SetTexture(std::string name)
{
    this->texture = new Texture(name);
    this->textureMapping = new TextureMapping(texture);
}
void TextureMappingPhongShader::BindInput(Output output)
{
    input = output;
    delete phongShader;
    Vector3 lightDir = PhongShader::DirectionalLight.Normalize().Reverse();
    textureMapping->BindUV(input.textureVertex[0], input.textureVertex[1], input.textureVertex[2],
                           input.zPositionInViewCoordinate[0], input.zPositionInViewCoordinate[1], input.zPositionInViewCoordinate[2]);
}
Vector3 TextureMappingPhongShader::Calculate(std::pair<float,float> uv)
{
    Vector3 color = textureMapping->Calcuate(uv);
    //return phongShader->Calculate(color, uv);
}