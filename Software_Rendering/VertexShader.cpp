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
    return output;
}