#include "Object.h"

Object::Object()
{
    scale = Vector3(1, 1, 1);
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
}
Object::~Object()
{
    delete texture;
    delete textureMapping;
}
void Object::SetTexture(std::string name)
{
    this->texture = new Texture(name);
    this->textureMapping = new TextureMapping(texture);
}
void Object::InitVertexVector()
{
    worldCoordinateVertices.resize(vertices.size());
    deviceCoordinateVertices.resize(vertices.size());
    zPositionInViewCoordinate.resize(vertices.size());
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

        Vector3 v1 = output.worldCoordinateVertex[0], v2 = output.worldCoordinateVertex[1], v3 = output.worldCoordinateVertex[2];
        Vector3 s1 = v2 - v1;
        Vector3 s2 = v3 - v1;
        Vector3 normal = s1.Cross(s2);
        normal = normal.Normalize();
        Vector3 viewingVector = position - camera.position;
        // back-face culling
        if (DontNeedToDraw(position - camera.position, normal))
            continue;

        Vector3 p1 = output.deviceCoordinateVectex[0];
        Vector3 p2 = output.deviceCoordinateVectex[1];
        Vector3 p3 = output.deviceCoordinateVectex[2];

        Vector2 vt1 = output.textureVertex[0];
        Vector2 vt2 = output.textureVertex[1];
        Vector2 vt3 = output.textureVertex[2];
        PhongShader phongShader = PhongShader(normal, v1, v2, v3);

        float z1 = output.zPositionInViewCoordinate[0];
        float z2 = output.zPositionInViewCoordinate[1];
        float z3 = output.zPositionInViewCoordinate[2];
        textureMapping->BindUV(vt1, vt2, vt3, z1, z2, z3);
        Draw::DrawTriangle(bitmapBuffer, p1, p2, p3, phongShader, *textureMapping);
    }
}