#include "TextureMappingNormalMappingPhongShader.h"

TextureMappingNormalMappingPhongShader::~TextureMappingNormalMappingPhongShader()
{
    delete texture;
    delete textureMapping;
    delete normalTexture;
    delete normalMapping;
    delete phongShader;
}
void TextureMappingNormalMappingPhongShader::SetTexture(std::string textureName,std::string normalTextureName)
{
    this->texture = new Texture(textureName);
    this->textureMapping = new TextureMapping(texture);
    this->normalTexture = new Texture(normalTextureName);
    this->normalMapping = new NormalMapping(normalTexture);
}
void TextureMappingNormalMappingPhongShader::BindInput(Output output)
{
    input = output;
    delete phongShader;
    lightDir = PhongShader::DirectionalLight.Normalize().Reverse();
    textureMapping->BindUV(input.textureVertex[0], input.textureVertex[1], input.textureVertex[2],
                           input.zPositionInViewCoordinate[0], input.zPositionInViewCoordinate[1], input.zPositionInViewCoordinate[2]);
}
Vector3 TextureMappingNormalMappingPhongShader::Calculate(std::pair<float, float> uv)
{
    Vector3 color = textureMapping->Calcuate(uv);
    Vector3 tangentNormal = normalMapping->Calcuate(uv);
    tangentNormal = (tangentNormal * 2 - Vector3(1,1,1)).Normalize();

    Matrix3x3 TBN = Matrix3x3(input.tangent.x, input.binormal.x, input.normal.x,
                              input.tangent.y, input.binormal.y, input.normal.y,
                              input.tangent.z, input.binormal.z, input.normal.z);
    Vector3 worldNormal = TBN * tangentNormal;

    float diffuseAmount = Math::Max<float>(worldNormal.Dot(lightDir), 0);
    Vector3 diffuse = PhongShader::GlobalLightColor * diffuseAmount;

    Vector3 reflectDirection = lightDir.Reverse().Reflect(worldNormal);
    reflectDirection = reflectDirection.Normalize();

    Vector3 position = input.worldCoordinateVertex[0] + ((input.worldCoordinateVertex[1] - input.worldCoordinateVertex[0]) * uv.first) + ((input.worldCoordinateVertex[2] - input.worldCoordinateVertex[0]) * uv.second);

    Vector3 viewDirection = (position - PhongShader::CameraPosition).Normalize();
    Vector3 reverseViewVector = viewDirection.Reverse();
    float spec = pow(Math::Max<float>(reflectDirection.Dot(reverseViewVector), 0.0f), 32.0f);

    Vector3 specular = PhongShader::GlobalLightColor *  PhongShader::SpecularStrength * spec;

    Vector3 ambient = PhongShader::GlobalLightColor * PhongShader::Ambient;
    Vector3 result = (ambient + diffuse + specular) * color;
    result.x = Math::Min<float>(result.x, 255);
    result.y = Math::Min<float>(result.y, 255);
    result.z = Math::Min<float>(result.z, 255);
    return result;
}