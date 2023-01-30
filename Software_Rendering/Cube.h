#pragma once
#include "math.h"
#include <Windows.h>
#include "Camera.h"
#include "Window.h"


class Cube
{
private:
public:
	Vector3 scale;
	Vector3 rotation;
	Vector3 position;
	Vector3 vertices[8];
	Vector3 deviceCoordinateVertices[8];
	Index indices[12];
	
	Cube();
	Matrix4x4 GetModelMatrix();
	void UpdateTransform(Camera camera);
	bool DontNeedToDraw(Vector3 viewingVector, Vector3 p1, Vector3 p2, Vector3 p3);
	void Draw(HDC hdc, Camera camera);
};

