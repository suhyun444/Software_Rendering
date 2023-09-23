#pragma once
#include "Camera.h"
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
    Texture* texture;
    TextureMapping* textureMapping;
    Object();
    ~Object();
    void SetTexture(std::string name);
    void InitVertexVector();
    Matrix4x4 GetModelMatrix();
    void UpdateTransform(const Camera &camera);
    void Draw(BitmapBuffer &bitmapBuffer, const Camera &camera);
};