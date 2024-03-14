#include "VertexShader.h"

void VertexShader::BindMatrix(Matrix4x4 modelMatrix, Matrix4x4 viewMatrix, Matrix4x4 projectionMatrix)
{
    this->modelMatrix = modelMatrix;
    this->viewMatrix = viewMatrix;
    this->projectionMatrix = projectionMatrix;
}
Output VertexShader::Calculate(Vector3 v[], Vector2 vt[])
{
    Output output;
    for(int i=0;i<3;i++)
    {
        Vector4 p = Vector4(v[i]);
        Vector4 vWcs = modelMatrix * p;
        output.worldCoordinateVertex[i] = Vector3(vWcs.x, vWcs.y, vWcs.z);

        Vector4 vVcs = viewMatrix * vWcs;
        output.zPositionInViewCoordinate[i] = vVcs.z;

        Vector4 vNdcs = projectionMatrix * vVcs;

        // Clipping coordinate system -> Normalized device coordinate system
        output.deviceCoordinateVectex[i] = Vector3(vNdcs.x / vNdcs.w, vNdcs.y / vNdcs.w, vNdcs.z / vNdcs.w);

        // Normalized device coordinate system -> Device coordinate system
        output.deviceCoordinateVectex[i].x += 1;
        output.deviceCoordinateVectex[i].x *= (float)Window::width / 2.0f;
        output.deviceCoordinateVectex[i].y += 1;
        output.deviceCoordinateVectex[i].y *= (float)Window::height / 2.0f;
     
        output.textureVertex[i] = vt[i];
    }
    Vector3 s1 = output.worldCoordinateVertex[1] - output.worldCoordinateVertex[0];
    Vector3 s2 = output.worldCoordinateVertex[2] - output.worldCoordinateVertex[0];
    Vector3 normal = s1.Cross(s2);
    output.normal = normal.Normalize();

    Vector3 edge1 = output.worldCoordinateVertex[1] - output.worldCoordinateVertex[0];
    Vector3 edge2 = output.worldCoordinateVertex[2] - output.worldCoordinateVertex[0];
    Vector2 deltaUV1 = output.textureVertex[1] - output.textureVertex[0];
    Vector2 deltaUV2 = output.textureVertex[2] - output.textureVertex[0];

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    output.tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    output.tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    output.tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    output.tangent = output.tangent.Normalize();

    output.binormal.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    output.binormal.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    output.binormal.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    output.binormal = output.binormal.Normalize();
    return output;
}