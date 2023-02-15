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
}
Matrix4x4 Object::GetModelMatrix()
{
    return Matrix4x4::GetModelMatrix(scale, rotation, position);
}
void Object::UpdateTransform(const Camera &camera)
{
    Matrix4x4 modelMatrix = Matrix4x4::GetModelMatrix(scale, rotation, position);
    Matrix4x4 t = camera.GetProjectionMatrix() * camera.GetViewMatrix() * modelMatrix;
    for (int i = 0; i < vertices.size(); i++)
    {
        Vector4 p = Vector4(vertices[i]);

        Vector4 vWcs = Matrix4x4::GetModelMatrix(scale, rotation, position) * p;
        worldCoordinateVertices[i] = Vector3(vWcs.x, vWcs.y, vWcs.z);

        Vector4 vNdcs = t * p;
        // Clipping coordinate system -> Normalized device coordinate system
        deviceCoordinateVertices[i] = Vector3(vNdcs.x / vNdcs.w, vNdcs.y / vNdcs.w, vNdcs.z / vNdcs.w);
        // Normalized device coordinate system -> Device coordinate system
        deviceCoordinateVertices[i].x += 1;
        deviceCoordinateVertices[i].x *= (float)Window::width / 2.0f;
        deviceCoordinateVertices[i].y += 1;
        deviceCoordinateVertices[i].y *= (float)Window::height / 2.0f;
    }
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
        Vector3 v1 = worldCoordinateVertices[indices[i]._1], v2 = worldCoordinateVertices[indices[i]._2], v3 = worldCoordinateVertices[indices[i]._3];
        Vector3 s1 = v2 - v1;
        Vector3 s2 = v3 - v1;
        Vector3 normal = s1.Cross(s2);
        normal = normal.Normalize();
        Vector3 viewingVector = position - camera.position;
        // back-face culling
        if (DontNeedToDraw(position - camera.position, normal))
            continue;
        Vector3 p1 = deviceCoordinateVertices[indices[i]._1];
        Vector3 p2 = deviceCoordinateVertices[indices[i]._2];
        Vector3 p3 = deviceCoordinateVertices[indices[i]._3];

        Vector2 vt1 = textureVertices[textureIndices[i]._1];
        Vector2 vt2 = textureVertices[textureIndices[i]._2];
        Vector2 vt3 = textureVertices[textureIndices[i]._3];
        PhongShader phongShader = PhongShader(normal, v1, v2, v3);
        textureMapping->BindUV(vt1,vt2,vt3);
        Draw::DrawTriangle(bitmapBuffer, p1, p2, p3, phongShader, *textureMapping);
    }
}