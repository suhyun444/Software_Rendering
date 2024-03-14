#pragma once
#include "Window.h"
#include "math.h"

struct Output
{
    Vector3 worldCoordinateVertex[3];
    float zPositionInViewCoordinate[3];
    Vector3 deviceCoordinateVectex[3];
    Vector2 textureVertex[3];
    Vector3 normal;
    Vector3 tangent;
    Vector3 binormal;
};
class VertexShader
{
private:
    Matrix4x4 modelMatrix,viewMatrix,projectionMatrix;
public:
    void BindMatrix(Matrix4x4 modelMatrix,Matrix4x4 viewMatrix, Matrix4x4 projectionMatrix);
    Output Calculate(Vector3 v[],Vector2 vt[]);
};