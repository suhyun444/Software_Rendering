#pragma once
#include "Object.h"

class Cube : Object
{
public:
	Cube();
	Matrix4x4 GetModelMatrix();
	void UpdateTransform(const Camera& camera);
	bool DontNeedToDraw(Vector3 viewingVector, Vector3 normalVector);
	void Draw(BitmapBuffer& bitmapBuffer, const Camera& camera);
};

