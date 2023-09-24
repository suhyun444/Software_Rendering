#include "Object.h"

Object::Object()
{
    scale = Vector3(1, 1, 1);
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
}
Object::~Object()
{
    delete fragmentShdaer;
}
void Object::SetTexture(std::string textureName,std::string normalTextureName)
{
    delete fragmentShdaer;
    TextureMappingNormalMappingPhongShader *textureMappingNormalMappingPhongShader = new TextureMappingNormalMappingPhongShader();
    textureMappingNormalMappingPhongShader->SetTexture(textureName, normalTextureName);
    fragmentShdaer = textureMappingNormalMappingPhongShader;
}
Matrix4x4 Object::GetModelMatrix()
{
    return Matrix4x4::GetModelMatrix(scale, rotation, position);
}
void Object::UpdateTransform(const Camera &camera)
{
    Matrix4x4 modelMatrix = Matrix4x4::GetModelMatrix(scale, rotation, position);
    vertexShader.BindMatrix(modelMatrix,camera.GetViewMatrix(),camera.GetProjectionMatrix());
}
// https://velog.io/@jaehyeoksong0/graphics-3
// TODO : BackfaceCulling 최적화하기
bool DontNeedToDraw(Vector3 viewingVector, Vector3 normalVector)
{
    return normalVector.Dot(viewingVector) > 0;
}
void Object::Draw(BitmapBuffer &bitmapBuffer, const Camera &camera)
{
    Vector3 viewingVector = position - camera.position;
    for (int i = 0; i < indices.size(); i++)
    {
        Vector3 v[3] = {vertices[indices[i]._1], vertices[indices[i]._2], vertices[indices[i]._3]};
        Vector2 vt[3] = {textureVertices[textureIndices[i]._1], textureVertices[textureIndices[i]._2], textureVertices[textureIndices[i]._3]};
        Output output = vertexShader.Calculate(v,vt);
        Vector3 viewingVector = position - camera.position;
        // back-face culling
        if (DontNeedToDraw(position - camera.position, output.normal))
            continue;
        fragmentShdaer->BindInput(output);
        Draw::DrawTriangle(bitmapBuffer, output.deviceCoordinateVectex[0], output.deviceCoordinateVectex[1], output.deviceCoordinateVectex[2], *fragmentShdaer);
    }
}