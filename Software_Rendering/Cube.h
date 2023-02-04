#pragma once
#include "math.h"
#include <Windows.h>
#include "Camera.h"
#include "Window.h"
#include "Time.h"
#include "Draw.h"


class Cube
{
private:
public:
	Vector3 scale;
	Vector3 rotation;
	Vector3 position;
	Vector3 vertices[8];
	Vector3 worldCoordinateVertices[8];
	Vector3 deviceCoordinateVertices[8];
	Index indices[12];
	
	Cube();
	Matrix4x4 GetModelMatrix();
	void UpdateTransform(const Camera& camera);
	bool DontNeedToDraw(Vector3 viewingVector, Vector3 normalVector);
	void Draw(BitmapBuffer& bitmapBuffer, const Camera& camera);
};

