#pragma once
#include "math.h"
#include <Windows.h>
#include "Camera.h"
#include "Window.h"
#include "Time.h"
#include "Draw.h"
#include <vector>

class Object
{
public:
    Vector3 scale;
    Vector3 rotation;
    Vector3 position;
    std::vector<Vector3> vertices;
    std::vector<Vector3> worldCoordinateVertices;
    std::vector<Vector3> deviceCoordinateVertices;
    std::vector<Vector2> textureVertices;
    std::vector<Index> indices;
    std::vector<Index> textureIndices;
    Object();
    void InitVertexVector();
    Matrix4x4 GetModelMatrix();
    void UpdateTransform(const Camera &camera);
    void Draw(BitmapBuffer &bitmapBuffer, const Camera &camera);
};